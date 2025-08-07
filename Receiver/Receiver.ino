#include <esp_now.h>
#include <WiFi.h>

#define IN1 5
#define IN2 18
#define IN3 19
#define IN4 21
#define CHANNEL 1

bool front = false;
bool back = false;
bool left = false;
bool right = false;
bool carIsStopped = true;

// Offset values for calibration
const int xOffset = 127;
const int yOffset = 127;

// Timeout settings
unsigned long lastReceivedTime = 0;
const unsigned long timeout = 200;  // Timeout period in milliseconds

typedef struct {
  byte xAxisValue;
  byte yAxisValue;
} PacketData;

PacketData data;

void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}

void configDeviceAP() {
  String ssid = "slave_" + String((uint32_t)ESP.getEfuseMac(), HEX);
  WiFi.softAP(ssid.c_str(), "Slave_Password", CHANNEL, 0);
  Serial.print("AP Config Success. Broadcasting with SSID: ");
  Serial.println(ssid);
}

void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));

  // Update the last received time
  lastReceivedTime = millis();

  // Apply offsets to center the values around 127 (idle position)
  int xAdjusted = data.xAxisValue - xOffset;
  int yAdjusted = data.yAxisValue - yOffset;

  Serial.printf("Received Data - x: %d, y: %d\n", xAdjusted, yAdjusted);

  // Adjust thresholds to define movement directions based on calibrated values
  front = yAdjusted > 23;   // Adjust threshold as needed
  back = yAdjusted < -23;
  left =  xAdjusted > 23;
  right =  xAdjusted < -23;
  carIsStopped = false;
}

void setup() {
  Serial.begin(115200);
  Serial.println("ESP-NOW Receiver Initialized");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  carStop();

  WiFi.mode(WIFI_AP);
  configDeviceAP();
  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("Receive Callback Registered");
}

void loop() {
  // Check for timeout
  if (millis() - lastReceivedTime > timeout) {
    if (!carIsStopped) {
      carStop();
      carIsStopped = true;
    }
  } else {
    if (front) {
      carforward();
    } else if (back) {
      carbackward();
    } else if (left) {
      carturnleft();
    } else if (right) {
      carturnright();
    } else if (!carIsStopped) {
      carStop();
      carIsStopped = true;
    }
  }
  delay(100);
}

void carforward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carbackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carturnleft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Car Turning Left");
}

void carturnright() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
