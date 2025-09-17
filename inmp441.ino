#include "driver/i2s_std.h"
#include "driver/i2s.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define I2S_WS 15
#define I2S_SCK 14
#define I2S_SD 32

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int16_t sample_buffer[512];
int bytes_read;
long peak_amplitude = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

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
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Falha ao alocar SSD1306"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Medidor de Ruido");
  display.display();
  delay(2000);
}

void loop() {
  i2s_read(I2S_NUM_0, (char*)sample_buffer, sizeof(sample_buffer), (size_t*)&bytes_read, portMAX_DELAY);

  peak_amplitude = 0;
  for (int i = 0; i < bytes_read / 2; i++) {
    long current_amplitude = abs(sample_buffer[i]);
    if (current_amplitude > peak_amplitude) {
      peak_amplitude = current_amplitude;
    }
  }

  long noise_level = map(peak_amplitude, 0, 30000, 0, 100); 
  
  Serial.print("Pico de amplitude: ");
  Serial.print(peak_amplitude);
  Serial.print(" | Nivel de Ruido: ");
  Serial.println(noise_level);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Ruido:");
  display.setTextSize(4);
  display.setCursor(0, 20);
  display.print(noise_level);
  display.print("%");
  display.display();
  
  delay(100);
}
