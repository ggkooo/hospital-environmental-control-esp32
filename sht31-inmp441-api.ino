#include "driver/i2s_std.h"
#include "driver/i2s.h"
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <math.h>

#include <WiFi.h>
#include <WiFiManager.h>
#include "time.h"

#include "FS.h"
#include "SPIFFS.h"
#include <WebServer.h>
#include <HTTPClient.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -10800;
const int daylightOffset_sec = 0;

const char* apiEndpoint = "http://192.168.15.9:8080";

Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define I2S_WS 15
#define I2S_SCK 14
#define I2S_SD 32

#define LED_VERDE 2
#define LED_AMARELO 4
#define LED_VERMELHO 5

int16_t sample_buffer[512];
int bytes_read;
long peak_amplitude = 0;
float noise_level_dB = 0.0;

const char* logFileName = "/log.json";

WebServer server(80);

int lastSecond = -1;
int lastMinute = -1;
String dataBuffer = "";

void sendDataToAPI();
void handleRoot();
void handleFile();

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  Serial.println("Configurando o WiFiManager...");

  WiFiManager wm;

  unsigned long previousMillis = 0;
  const long blinkInterval = 500;

  while (WiFi.status() != WL_CONNECTED) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      digitalWrite(LED_VERDE, !digitalRead(LED_VERDE));
    }
    wm.autoConnect("Giordano's ESP32", "12345678");
  }

  digitalWrite(LED_VERDE, HIGH);
  Serial.println("\nConectado à rede Wi-Fi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin(true)) {
    Serial.println("Ocorreu um erro ao montar o SPIFFS");
    return;
  }
  Serial.println("SPIFFS montado com sucesso.");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  server.on("/", handleRoot);
  server.on("/log.json", handleFile);
  server.begin();
  Serial.println("Servidor HTTP iniciado.");

  Wire.begin();
  delay(100);

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
    .use_apll = false
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  Serial.println("Pronto para coletar dados...");
}

void loop() {
  server.handleClient();

  struct tm timeinfo;
  bool timeSynced = getLocalTime(&timeinfo);

  if (!timeSynced) {
    Serial.println("Falha ao obter o tempo do NTP. Os dados não serão enviados.");
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
  }

  if (timeSynced && timeinfo.tm_min != lastMinute) {
    sendDataToAPI();
    lastMinute = timeinfo.tm_min;
  }

  if (timeinfo.tm_sec % 5 == 0 && timeinfo.tm_sec != lastSecond) {
    digitalWrite(LED_AMARELO, HIGH);

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

    char timestamp_buffer[20];
    strftime(timestamp_buffer, sizeof(timestamp_buffer), "%d-%m-%y %H:%M:%S", &timeinfo);
    String formattedTimestamp = String(timestamp_buffer);

    String jsonString = "{";
    jsonString += "\"temperature\": " + String(t, 2) + ",";
    jsonString += "\"humidity\": " + String(h, 2) + ",";
    jsonString += "\"noise\": " + String(noise_level_dB, 2) + ",";
    jsonString += "\"timestamp\": \"" + formattedTimestamp + "\"";
    jsonString += "}";

    dataBuffer += jsonString + ",";

    lastSecond = timeinfo.tm_sec;

    digitalWrite(LED_AMARELO, LOW);
  }

  delay(100);
}

void sendDataToAPI() {
  if (dataBuffer.length() > 0) {
    digitalWrite(LED_VERMELHO, HIGH);

    HTTPClient http;
    String payload = "[" + dataBuffer.substring(0, dataBuffer.length() - 1) + "]";

    Serial.println("Enviando dados para a API...");
    Serial.println(payload);

    http.begin(apiEndpoint);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.printf("Código de resposta HTTP: %d\n", httpResponseCode);
      String response = http.getString();
      dataBuffer = "";
    } else {
      Serial.printf("Erro no envio HTTP. Código de resposta: %d\n", httpResponseCode);
    }
    http.end();

    digitalWrite(LED_VERMELHO, LOW);
  }
}

void handleRoot() {
  String html = "<h1>Arquivos no ESP32</h1>";
  html += "<ul>";

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    html += "<li><a href='";
    html += file.name();
    html += "'>";
    html += file.name();
    html += "</a></li>";
    file = root.openNextFile();
  }
  html += "</ul>";

  server.send(200, "text/html", html);
}

void handleFile() {
  if (server.hasArg("download")) {
  } else {
    File file = SPIFFS.open(server.uri(), "r");
    if (file) {
      server.streamFile(file, "text/plain");
      file.close();
    } else {
      server.send(404, "text/plain", "Arquivo não encontrado");
    }
  }
}