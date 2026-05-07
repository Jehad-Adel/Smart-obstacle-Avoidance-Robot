# Smart-obstacle-Avoidance-Robot
A smart autonomous robot featuring dual-mode operation (Manual/Autonomous). It uses three ultrasonic sensors for real-time obstacle avoidance and decision-making logic, built with Arduino and C++.

# Smart Autonomous & Manual Robot 

An Arduino-based robot that can navigate autonomously using ultrasonic sensors or be controlled manually via Serial commands.

## ✨ Key Features
* Dual Mode: Switch between Smart Auto and Manual Control on the fly.
* Triple Sensor Logic: Uses Front, Left, and Right ultrasonic sensors to decide the best path.
* Intelligent Obstacle Avoidance: If blocked, the robot compares side distances and chooses the widest path.
* Dynamic Speed Control: Slower speed for precision in Auto mode, and full speed for Manual racing.

## 🛠 Hardware Requirements
* Arduino Uno / Nano.
* L298N Motor Driver.
* 3x HC-SR04 Ultrasonic Sensors.
* 2x DC Motors + Chassis.
* Power source (e.g., 2x 18650 batteries).

## 🚀 How to Use
1. Upload `src/main_robot_code.ino` to your Arduino.
2. Open Serial Monitor (9600 baud).
3. Send `A` to start Autonomous mode.
4. Send `W` to take manual control.
  
