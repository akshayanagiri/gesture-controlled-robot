🤖 Gesture Controlled Robot
This project is a Gesture Controlled Robot developed using ESP32 microcontrollers and an MPU6050 sensor, communicating wirelessly via the ESP-NOW protocol. The robot responds to hand gestures to move in different directions, providing an intuitive and contactless control method.

🚀 Project Overview
The Gesture Controlled Robot is designed to aid differently-abled individuals by allowing them to control the movement of a robot or wheelchair using just hand gestures. The transmitter interprets the user's hand motion (yaw, pitch, and roll) and sends corresponding commands to the receiver module wirelessly.

🔧 Hardware Components
ESP32 (x2): One for the transmitter, one for the receiver.

MPU6050: To detect gestures using motion (yaw, pitch, roll).

Motor Driver Module: L298N or similar.

DC Motors & Robot Chassis

Battery Pack: Li-ion / Rechargeable.

Jumper wires & Breadboard

Optional: LEDs, Buzzer (for alerts).

📡 Communication Protocol
ESP-NOW: A low-power wireless communication protocol developed by Espressif. It allows the ESP32 boards to exchange data directly without the need for Wi-Fi.

🧠 Working Principle
The MPU6050 attached to the transmitter ESP32 captures orientation data (yaw, pitch, roll).

Based on these readings, the ESP32 determines the gesture (e.g., forward tilt = move forward).

The gesture command is sent via ESP-NOW to the receiver ESP32.

The receiver decodes the command and controls the motors accordingly to move the robot.

🤖 Gesture Mapping
Gesture	Motion	Robot Action
Tilt forward	Pitch ↓	Move Forward
Tilt backward	Pitch ↑	Move Backward
Tilt left	Roll ←	Turn Left
Tilt right	Roll →	Turn Right
Flat/neutral	Stable	Stop

Export to Sheets
🔍 Features
Wireless control using ESP-NOW (no Wi-Fi needed)

Real-time gesture response

Compact and portable design

Useful for robotics learning and assistive tech prototypes

📁 Repository Structure
gesture-controlled-robot/
├── Transmitter/
│   └── transmitter.ino
├── Receiver/
│   └── receiver.ino
├── images/
│   └── circuit_diagram.png
│   └── robot_demo.gif
├── README.md
🛠️ Future Enhancements
Add Obstacle Detection using ultrasonic sensors and buzzer alerts

Display speed and direction on an LCD

Improve gesture accuracy using complementary filters

Integration with wheelchair chassis for real-life applications

📷 Demo
(Include a short video or GIF showing the robot responding to gestures)

⚙️ How to Run Locally
To set up and run this project, you will need the Arduino IDE and the ESP32 board manager installed.

Clone the repository:

Bash

git clone https://github.com/your-username/gesture-controlled-robot.git
(Replace your-username with your actual GitHub username)

Navigate to the project directory:

Bash

cd gesture-controlled-robot
Open in Arduino IDE: Open the Transmitter.ino and Receiver.ino files in the Arduino IDE.

Compile and Upload: Connect your ESP32 boards, configure the correct port and board, and upload the corresponding code to each module.

🤝 Contributing
Contributions are welcome! If you have ideas for improvements or bug fixes, feel free to fork this repository, create a new branch, and submit a pull request.

📜 License
This project is open source and available under the <u>MIT License</u>.

<footer class="app-footer">
<p>
<span class="heart-emoji">❤️</span>
Project by Akshaya Nagiri
</p>
</footer>
