#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SHT31.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(115200);

  Wire.begin();
  delay(100);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao inicializar o display OLED!"));
    for (;;) ;
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();

  if (!sht31.begin(0x44)) {
    Serial.println("Falha ao encontrar o sensor SHT31!");
    while (1) delay(1);
  }
}

void loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(t, 1);
  display.print((char)247);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Umid: ");
  display.setTextSize(2);
  display.setCursor(0, 40);
  display.print(h, 1);
  display.print(" %");
  
  display.display();
  delay(500);
}