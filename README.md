# Arduino Buggy System

## Overview

Arduino Buggy System is an embedded systems project developed as part of an Electronic Systems Design course. The project demonstrates hardware-software co-design by integrating sensors, motor control, obstacle detection, and track navigation using an Arduino microcontroller.

The buggy follows a predefined track, detects obstacles using an ultrasonic sensor, communicates gantry states through serial communication, and performs autonomous navigation based on sensor inputs.

---

## Features

* Autonomous track navigation
* Obstacle detection using ultrasonic sensor
* Gantry detection and state communication
* DC motor control using Arduino
* IR sensor-based line following
* Serial communication for monitoring system status

---

## Hardware Components

* Arduino Board
* IR Sensors
* Ultrasonic Sensor
* DC Motors
* Motor Driver Circuit
* Breadboard / PCB
* Connecting Wires and Power Supply

---

## Software Tools

* Arduino IDE
* Eagle PCB Design Software

---

## Project Structure

```text
arduino-buggy-system
│
├── README.md
│
├── code/
│   └── arduino_buggy_system.ino
│
├── circuit-design/
│   ├── eagle-schematic.png
│   └── eagle-pcb-layout.png
│
├── images/
│   ├── buggy.jpg
│   └── buggy-circuit.jpg
│
└── demo/
    └── buggy-demo.mp4
```

---

## Working Principle

1. The buggy follows the track using IR sensors.
2. Gantry positions are detected through IR communication.
3. An ultrasonic sensor continuously checks for obstacles.
4. If an obstacle is detected within a predefined distance, the buggy stops.
5. Motor control logic guides navigation and turning decisions.
6. Status updates are transmitted through serial communication.

---

## Future Improvements

* Multi-buggy coordination
* Dynamic path planning
* Wireless communication modules
* Enhanced obstacle avoidance algorithms
* Generalized multi-loop navigation

---

## Author

Moksh

Embedded Systems Design Course Project

