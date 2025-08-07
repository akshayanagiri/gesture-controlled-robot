#include <esp_now.h>
#include <WiFi.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;
bool dmpReady = false;
uint8_t devStatus;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
bool espConnected = false;

struct PacketData {
  byte xAxisValue;
  byte yAxisValue;  
};
PacketData data;

esp_now_peer_info_t slave;
#define CHANNEL 1

void InitESPNow() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW Init Success");
  } else {
    Serial.println("ESP-NOW Init Failed");
    ESP.restart();
  }
}

void ScanForSlave() {
  int16_t scanResults = WiFi.scanNetworks(false, false, false, 300, CHANNEL);
  bool slaveFound = false;
  memset(&slave, 0, sizeof(slave));

  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
  } else {
    for (int i = 0; i < scanResults; ++i) {
      String SSID = WiFi.SSID(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (SSID.indexOf("slave") == 0) {
        Serial.println("Found a Slave.");
        Serial.print("Slave SSID: "); Serial.println(SSID);
        int mac[6];
        if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5])) {
          for (int j = 0; j < 6; ++j) {
            slave.peer_addr[j] = (uint8_t)mac[j];
          }
        }
        slave.channel = CHANNEL;
        slave.encrypt = false;

        if (esp_now_add_peer(&slave) == ESP_OK) {
          Serial.println("Peer added successfully");
          espConnected = true;
          break;
        } else {
          Serial.println("Failed to add peer");
        }
      }
    }
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setupMPU() {
  Wire.begin();
  Wire.setClock(400000);
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  if (devStatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.setDMPEnabled(true);
    dmpReady = true;
  } 
}

void setup() {
  Serial.begin(115200);
  InitESPNow();
  ScanForSlave();
  esp_now_register_send_cb(OnDataSent);
  setupMPU();
}

void loop() {
  if (!dmpReady) return;

  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    int xAxisValue = constrain(ypr[2] * 180 / M_PI, -90, 90);
    int yAxisValue = constrain(ypr[1] * 180 / M_PI, -90, 90);
    data.xAxisValue = map(xAxisValue, -90, 90, 0, 254); 
    data.yAxisValue = map(yAxisValue, -90, 90, 0, 254);

    esp_err_t result = esp_now_send(slave.peer_addr, (uint8_t *) &data, sizeof(data));
    Serial.printf("values x: %d  y: %d\n", xAxisValue, yAxisValue);
    delay(100);
  }
}
