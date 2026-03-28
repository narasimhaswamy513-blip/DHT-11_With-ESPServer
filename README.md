
# DHT-11_With-ESPServer# 🔥 Smart Health Monitoring System (ESP / Arduino Based)

## 📌 Overview
This project is a real-time health monitoring system that measures vital parameters such as **Heart Rate (BPM)** and **SpO2 (Oxygen Level)** using sensors and displays/transmits the data using a microcontroller (ESP8266/ESP32/Arduino).

It can be integrated with IoT platforms like Firebase for remote monitoring.

---

## 🚀 Features
- ❤️ Real-time Heart Rate (BPM) monitoring  
- 🫁 SpO2 (Oxygen Level) detection  
- 📡 Wireless data transmission (WiFi-based)  
- ☁️ Cloud integration (Firebase / Web dashboard)  
- 📊 Live data visualization  
- 🔔 Can be extended for alerts (abnormal values)

---

## 🛠️ Hardware Requirements
- ESP8266 / ESP32 / Arduino  
- MAX30100 / MAX30102 Sensor  
- Jumper wires  
- Breadboard  
- Power supply  

---

## 💻 Software Requirements
- Arduino IDE  
- Required Libraries:
  - Wire.h  
  - WiFi.h / ESP8266WiFi.h  
  - MAX30100_PulseOximeter / MAX30102 library  
  - Firebase library (if used)

---

## 🔌 Circuit Connections
| Sensor Pin | Microcontroller Pin |
|------------|--------------------|
| VCC        | 3.3V               |
| GND        | GND                |
| SDA        | D2 / GPIO4         |
| SCL        | D1 / GPIO5         |

> ⚠️ Note: Pin numbers may vary depending on board.

---

## ⚙️ Working Principle
1. The sensor detects blood oxygen level and heart rate.
2. Microcontroller processes the sensor data.
3. Data is displayed on Serial Monitor / Web Dashboard.
4. Optional: Data is sent to Firebase for remote access.

---

## 📸 Output
- BPM and SpO2 values shown in Serial Monitor  
- Data updates in real-time on dashboard  

---

## ▶️ How to Run
1. Install Arduino IDE  
2. Install required libraries  
3. Connect hardware as per circuit  
4. Open `.ino` file  
5. Select correct board & COM port  
6. Upload the code  
7. Open Serial Monitor  

---

## 🌐 Future Improvements
- Mobile app integration  
- Alert system (SMS/Notification)  
- Data logging & analysis  
- AI-based health prediction  

---

## 👨‍💻 Author
**Narasimha Swamy S**  
ECE Student  

---

## 📄 License
This project is open-source and free to use for educational purposes.
