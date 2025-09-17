# 🌱 ESP32 Environmental Variable Capture

This repository contains example code for reading temperature and humidity using the SHT31 sensor and displaying the data on an SSD1306 OLED display, both connected to an ESP32.

## 🛠️ Components Used
- ESP32
- SHT31 temperature and humidity sensor
- SSD1306 OLED display (128x64)
- Jumper wires

## ✨ Features
- Measure temperature and humidity
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

| OLED SSD1306 | ESP32      |
|--------------|------------|
| VCC          | 3.3V       |
| GND          | GND        |
| SDA          | GPIO 21    |
| SCL          | GPIO 22    |

> **Note:** Confirm the SDA/SCL pins according to your board.

## 🚀 How to Use
1. Install the libraries listed above.
2. Connect the components as shown in the tables.
3. Upload the `sht31.ino` file to your ESP32.
4. Open the Serial Monitor to see live readings.
5. The OLED display will show temperature (°C) and humidity (%).

## 🖥️ Example Output on Display
```
Temp: 
23.4°C
Umid: 
45.7 %
```

## 📝 Notes
- The code reads data every 500 ms.
- If any device is not found, an error message will be shown in the serial monitor.

## 🤝 Contributing
Feel free to open issues and pull requests to improve this project!

## ⚖️ License
This project is licensed under the MIT License.

---
Developed by Giordano Berwig
