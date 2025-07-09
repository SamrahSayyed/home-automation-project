# Home Automation System using RF, ESP8266, and Blynk

This project allows remote control and monitoring of a home environment using:
- Wireless RF communication
- ESP8266 and Blynk for IoT integration
- OLED display for local data
- Sensors: DHT11 (Temp+Humidity), MQ2 (Gas), PIR (Motion)

## 🛠️ Components Used
- ESP8266 (NodeMCU)
- RF Transmitter + Receiver Modules (433 MHz)
- DHT11 Sensor
- MQ2 Gas Sensor
- PIR Motion Sensor
- OLED Display (SSD1306)
- Blynk IoT Platform

## 📡 System Overview
The system consists of:
1. **Transmitter**: Senses environment and sends commands via RF to the receiver.
2. **Receiver**: Receives commands and toggles appliances like a fan.

## ⚙️ Features
- Fan ON/OFF control via Blynk
- Real-time data (Temp, Humidity, Gas, Motion) to Blynk dashboard
- OLED display for local feedback
- Light level detection
- Wireless RF-based communication

## 🔌 Circuit Diagrams
> (Add wiring diagrams in the `images/` folder)

## 🚀 How to Run
- Upload `transmitter.ino` to ESP8266
- Upload `receiver.ino` to Arduino
- Connect components as per the diagram
- Replace `ssid`, `pass`, and `auth` with your credentials

## 📲 Blynk Dashboard
- V0: Fan Toggle (Button)
- V4–V7: Sensor readings (Temp, Humidity, Gas, Motion)

---

