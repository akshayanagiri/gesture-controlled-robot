**Gesture Controlled Robot**
This project is a Gesture Controlled Robot developed using ESP32 microcontrollers and an MPU6050 sensor, communicating wirelessly via the ESP-NOW protocol. The robot responds to hand gestures to move in different directions, providing an intuitive and contactless control method.


**Project Overview**
The Gesture Controlled Robot is designed to aid differently-abled individuals by allowing them to control the movement of a robot or wheelchair using just hand gestures. The transmitter interprets the user's hand motion (yaw, pitch, and roll) and sends corresponding commands to the receiver module wirelessly.


**Hardware Components**
ESP32 (x2): One for the transmitter, one for the receiver.
MPU6050: To detect gestures using motion (yaw, pitch, roll).
Motor Driver Module: L298N or similar.
DC Motors & Robot Chassis
Battery Pack: Li-ion / Rechargeable.
Jumper Wires & Breadboard
Optional: LEDs, Buzzer (for alerts).


**Communication Protocol**
ESP-NOW: A low-power wireless communication protocol developed by Espressif. It allows the ESP32 boards to exchange data directly without the need for Wi-Fi.


**Working Principle**
The MPU6050 attached to the transmitter ESP32 captures orientation data (yaw, pitch, roll).
Based on these readings, the ESP32 determines the gesture (e.g., forward tilt = move forward).
The gesture command is sent via ESP-NOW to the receiver ESP32.
The receiver decodes the command and controls the motors accordingly to move the robot.


**Gesture Mapping**
Gesture	Motion	Robot Action
Tilt forward	Pitch ↓	Move Forward
Tilt backward	Pitch ↑	Move Backward
Tilt left	Roll ←	Turn Left
Tilt right	Roll →	Turn Right
Flat/neutral	Stable	Stop


**Features**
Wireless control using ESP-NOW (no Wi-Fi needed)
Real-time gesture response
Compact and portable design
Useful for robotics learning and assistive tech prototypes


**License**
This project is open-source under the <u>MIT License</u>.
