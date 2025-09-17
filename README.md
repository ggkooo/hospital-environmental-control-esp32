# 🌡️🔊📡 ESP32 Environmental Logger & Web Server: SHT31 + INMP441

This repository contains example code for monitoring temperature, humidity, and environmental noise using the SHT31 sensor and INMP441 MEMS microphone, logging all data in JSON format on the ESP32 SPIFFS filesystem, and serving the data via a built-in web server.

## 🛠️ Components Used
- ESP32
- SHT31 temperature and humidity sensor
- INMP441 I2S MEMS microphone
- Jumper wires

## ✨ Features
- Real-time temperature, humidity, and noise level measurement
- Data logging in JSON format to SPIFFS
- Timestamping with NTP-synchronized time
- Embedded HTTP web server for data access
- Modular and easy-to-understand code

## 📦 Required Libraries
Install the following libraries in the Arduino IDE:
- Adafruit SHT31 Library
- WiFi
- SPIFFS
- WebServer
- Wire

## ⚡ Wiring

| SHT31      | ESP32      |
|------------|------------|
| VCC        | 3.3V       |
| GND        | GND        |
| SDA        | GPIO 21    |
| SCL        | GPIO 22    |

| INMP441     | ESP32      |
|-------------|------------|
| VCC         | 3.3V       |
| GND         | GND        |
| WS (LRCL)   | GPIO 15    |
| SCK (BCLK)  | GPIO 14    |
| SD          | GPIO 32    |

> **Note:** Confirm the pinout according to your ESP32 board and sensor versions.

## 🚀 How to Use
1. Install the libraries listed above.
2. Connect the components as shown in the tables.
3. Edit the WiFi credentials (`ssid` and `password`) in the code.
4. Upload the `sht31-inmp441-ws.ino` file to your ESP32.
5. Open the Serial Monitor to check for initialization and connection messages.
6. After connecting to WiFi, access the ESP32 IP address in your browser to view and download the log file (`log.json`).

## 🖥️ Example Output (log.json)
```
{
  "temperature": 23.45,
  "humidity": 45.67,
  "noise": 56.23,
  "timestamp": "17-09-25 09:20:15"
}
{
  "temperature": 23.50,
  "humidity": 45.60,
  "noise": 55.90,
  "timestamp": "17-09-25 09:20:20"
}
...
```

## 📝 Notes
- Data is logged every 5 seconds with a timestamp.
- The web server provides a simple HTML interface to browse and download files.
- If SPIFFS or any sensor fails to initialize, an error is shown in the Serial Monitor and logging stops.
- Noise level is calculated in dB based on the peak amplitude from the INMP441 microphone.

## 🤝 Contributing
Feel free to open issues and pull requests to improve this project!

## ⚖️ License
This project is licensed under the MIT License.

---
Developed by Giordano Berwig
