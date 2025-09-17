# 🌡️🔊 ESP32 Environmental Monitor: SHT31 + INMP441

This repository contains example code for monitoring temperature, humidity, and environmental noise using the SHT31 sensor and INMP441 MEMS microphone, displaying all data on an SSD1306 OLED display with an ESP32.

## 🛠️ Components Used
- ESP32
- SHT31 temperature and humidity sensor
- INMP441 I2S MEMS microphone
- SSD1306 OLED display (128x64)
- Jumper wires

## ✨ Features
- Real-time temperature and humidity measurement
- Real-time environmental noise level measurement (in dB)
- Alternating display of sensor data on OLED
- Modular and easy-to-understand code

## 📦 Required Libraries
Install the following libraries in the Arduino IDE:
- Adafruit SHT31 Library
- Adafruit SSD1306
- Adafruit GFX Library
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

| OLED SSD1306 | ESP32      |
|--------------|------------|
| VCC          | 3.3V       |
| GND          | GND        |
| SDA          | GPIO 21    |
| SCL          | GPIO 22    |

> **Note:** Confirm the pinout according to your ESP32 board and sensor versions.

## 🚀 How to Use
1. Install the libraries listed above.
2. Connect the components as shown in the tables.
3. Upload the `sht31-inmp441.ino` file to your ESP32.
4. Open the Serial Monitor to see initialization and error messages.
5. The OLED display will alternate between showing temperature/humidity and noise level in dB every 2 seconds.

## 🖥️ Example Output on Display
```
Temp: 23.4°C
Umid: 45.7 %

---

Ruido:
  56.2 dB
```

## 📝 Notes
- The code alternates the OLED display every 2 seconds between temperature/humidity and noise level.
- If any sensor or the display is not detected, an error message will be shown in the Serial Monitor and the program will halt.
- Noise level is calculated in dB based on the peak amplitude from the INMP441 microphone.

## 🤝 Contributing
Feel free to open issues and pull requests to improve this project!

## ⚖️ License
This project is licensed under the MIT License.

---
Developed by Giordano Berwig
