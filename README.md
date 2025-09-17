# 🌡️🔊📡 ESP32 Environmental Logger & Simple API: SHT31 + INMP441

This project provides code for monitoring temperature, humidity, and environmental noise using an ESP32 with a SHT31 sensor and INMP441 MEMS microphone. Data is logged in JSON format and can be accessed via a simple PHP API. Visual feedback is provided using LEDs.

## 🚀 Overview

- ESP32 reads temperature and humidity from SHT31 and noise level from INMP441.
- Data is logged in JSON format on the ESP32.
- A simple PHP API (`simple-api.php`) allows remote access to the log data.
- Visual indication of environmental status with LEDs.

## ✨ Features

- Measure temperature and humidity with SHT31
- Measure noise level with INMP441
- Log data in JSON format
- Access data remotely via PHP API
- Visual indication with LEDs
1. Connect the sensors to the ESP32 as described in the wiring diagrams (coming soon!).
2. Flash the code to your ESP32.

- Adafruit SHT31 Library
- WiFi
- SPIFFS
- WebServer
- Wire

## ⚡ Wiring

| SHT31 | ESP32      |
|-------|------------|
| VCC   | 3.3V       |
| GND   | GND        |
| SDA   | GPIO 21    |
| SCL   | GPIO 22    |

| INMP441     | ESP32      |
|-------------|------------|
| VCC         | 3.3V       |
| GND         | GND        |
| WS (LRCL)   | GPIO 15    |
| SCK (BCLK)  | GPIO 14    |
| SD          | GPIO 32    |

| LED Color | ESP32 GPIO |
|-----------|------------|
| Red       | GPIO 5     |
| Yellow    | GPIO 4     |
| Green     | GPIO 2     |

> **Note:** Confirm the pinout according to your ESP32 board, sensor, and LED versions.
## 📚 Documentation
## 🚦 How to Use
1. Install the required libraries in the Arduino IDE.
2. Connect the SHT31, INMP441, and LEDs as shown above.
3. Edit WiFi credentials in `sht31-inmp441-api.ino`.
4. Upload `sht31-inmp441-api.ino` to your ESP32.
5. Deploy `simple-api.php` to your web server (with permissions to read/write the log file).
6. The ESP32 will log data in JSON format. Use the PHP API to access the data remotely.
7. Open the Serial Monitor to see live readings and debug messages.

## 🖥️ Example Output (log.json)

```json
[
  {
    "temperature": 23.45,
    "humidity": 45.67,
    "noise": 56.23,
    "timestamp": "17-09-25 09:20:15"
  },
  {
    "temperature": 23.50,
    "humidity": 45.60,
    "noise": 55.90,
    "timestamp": "17-09-25 09:20:20"
  }
]
```

## 📝 Notes

- Data is logged in JSON format as an array of objects.
- The PHP API provides remote access to the log data.
- Ensure your web server has permissions to read/write the log file.

## 🤝 Contributing

Feel free to open issues and pull requests to improve this project!

## ⚖️ License

This project is licensed under the MIT License.

---

Made with ❤️ by [ggkooo](https://github.com/ggkooo)
Developed by Giordano Berwig


