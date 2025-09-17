#include "driver/i2s_std.h"
#include "driver/i2s.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SHT31.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define I2S_WS 15
#define I2S_SCK 14
#define I2S_SD 32

int16_t sample_buffer[512];
int bytes_read;
long peak_amplitude = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  Wire.begin();
  delay(100);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao inicializar o display OLED!"));
    for (;;) ;
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();

  // Inicializa o sensor SHT31
  if (!sht31.begin(0x44)) {
    Serial.println("Falha ao encontrar o sensor SHT31!");
    while (1) delay(1);
  }

  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = 16000,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false};

  i2s_pin_config_t pin_config = {
      .bck_io_num = I2S_SCK,
      .ws_io_num = I2S_WS,
      .data_out_num = I2S_PIN_NO_CHANGE,
      .data_in_num = I2S_SD};

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Iniciando sensores...");
  display.display();
  delay(2000);
}

void loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  i2s_read(I2S_NUM_0, (char*)sample_buffer, sizeof(sample_buffer), (size_t*)&bytes_read, portMAX_DELAY);
  peak_amplitude = 0;
  for (int i = 0; i < bytes_read / 2; i++) {
    long current_amplitude = abs(sample_buffer[i]);
    if (current_amplitude > peak_amplitude) {
      peak_amplitude = current_amplitude;
    }
  }

  float noise_level_dB = 20 * log10(peak_amplitude / 32768.0) + 94;

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
  delay(2000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Ruido:");
  display.setTextSize(3);
  display.setCursor(0, 20);
  display.print(noise_level_dB, 1);
  display.print(" dB");
  display.display();
  delay(2000);
}
