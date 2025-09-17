# 🌱 ESP32 Environmental Monitoring Projects

Welcome! This repository contains a collection of ESP32-based projects for capturing, displaying, logging, and serving environmental data such as temperature, humidity, and noise levels. All projects are modular, well-documented, and use widely available sensors and displays, making them ideal for learning, prototyping, or real-world IoT applications.

---

## ✨ Features
- Real-time measurement of temperature, humidity, and noise
- OLED display visualization
- Data logging in JSON format
- Web server and API for remote data access
- Visual feedback with LEDs (in some projects)
- Modular and easy-to-understand code

---

## 🧩 Project Variants

### 🔊 Noise Level Meter
- **Sensors:** INMP441 (noise)
- **Display:** SSD1306 OLED
- **Features:** Real-time noise level measurement and display
- **Example Output:**
  ```
  Ruido:
    42%
  ```

### 🌡️🔊📡 Environmental Logger & Simple API
- **Sensors:** SHT31 (temperature/humidity), INMP441 (noise)
- **Features:** Logs data in JSON, provides a PHP API, LED status
- **Example Output (log.json):**
  ```json
  [
    {
      "temperature": 23.45,
      "humidity": 45.67,
      "noise": 56.23,
      "timestamp": "17-09-25 09:20:15"
    }
  ]
  ```

### 🌡️🔊📡 Environmental Logger & Web Server
- **Sensors:** SHT31, INMP441
- **Features:** Logs data in JSON to SPIFFS, serves via web server, HTML interface
- **Example Output (log.json):**
  ```json
  {
    "temperature": 23.45,
    "humidity": 45.67,
    "noise": 56.23,
    "timestamp": "17-09-25 09:20:15"
  }
  ```

### 🌡️🔊 Environmental Monitor with OLED
- **Sensors:** SHT31, INMP441
- **Display:** SSD1306 OLED
- **Features:** Alternates display of temperature/humidity and noise (dB)
- **Example Output:**
  ```
  Temp: 23.4°C
  Umid: 45.7 %
  ---
  Ruido:
    56.2 dB
  ```

### 🌱 Environmental Variable Capture
- **Sensors:** SHT31
- **Display:** SSD1306 OLED
- **Features:** Displays temperature and humidity
- **Example Output:**
  ```
  Temp: 
  23.4°C
  Umid: 
  45.7 %
  ```

---

## ⚡ Common Wiring

| Sensor/Display | ESP32 Pinout Example |
|---------------|---------------------|
| SHT31 SDA     | GPIO 21             |
| SHT31 SCL     | GPIO 22             |
| INMP441 WS    | GPIO 15             |
| INMP441 SCK   | GPIO 14             |
| INMP441 SD    | GPIO 32             |
| OLED SDA      | GPIO 21             |
| OLED SCL      | GPIO 22             |

> **Note:** Always confirm the pinout for your ESP32 board and sensor/display versions.

---

## 🚀 How to Use
1. Install the required libraries in the Arduino IDE:
   - Adafruit SHT31
   - Adafruit SSD1306
   - Adafruit GFX
   - Wire
   - WiFi, SPIFFS, WebServer (for logging/web projects)
2. Connect the sensors and display as shown above.
3. Open the desired `.ino` file in Arduino IDE, edit WiFi credentials if needed.
4. Upload to your ESP32.
5. Use the Serial Monitor and/or OLED display to view live data. For web/API projects, access the ESP32 IP or PHP endpoint.

---

## 🤝 Contributing
Feel free to open issues and pull requests to improve this project!

## ⚖️ License
This project is licensed under the MIT License.

---
Developed by Giordano Berwig
