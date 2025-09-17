# 🔊 ESP32 Noise Level Meter with INMP441

This repository contains example code for measuring environmental noise levels using the INMP441 MEMS microphone and displaying the results on an SSD1306 OLED display, both connected to an ESP32.

## 🛠️ Components Used
- ESP32
- INMP441 I2S MEMS microphone
- SSD1306 OLED display (128x64)
- Jumper wires

## ✨ Features
- Real-time noise level measurement
- OLED display visualization
- Simple and modular code

## 📦 Required Libraries
Install the following libraries in the Arduino IDE:
- Adafruit SSD1306
- Adafruit GFX Library
- Wire

## ⚡ Wiring

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

> **Note:** Confirm the pinout according to your ESP32 board and sensor version.

## 🚀 How to Use
1. Install the libraries listed above.
2. Connect the components as shown in the tables.
3. Upload the `inmp441.ino` file to your ESP32.
4. Open the Serial Monitor to see amplitude and noise level readings.
5. The OLED display will show the current noise level as a percentage.

## 🖥️ Example Output on Display
```
Ruido:
  42%
```

## 📝 Notes
- The code reads audio samples every 100 ms and updates the display in real time.
- The noise level is mapped to a percentage based on the peak amplitude detected.
- If the OLED display is not detected, an error message will be shown in the Serial Monitor and the program will halt.

## 🤝 Contributing
Feel free to open issues and pull requests to improve this project!

## ⚖️ License
This project is licensed under the MIT License.

---
Developed by Giordano Berwig
