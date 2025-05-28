#define BLYNK_TEMPLATE_ID "TMPL6FsRuqX6e"
#define BLYNK_TEMPLATE_NAME "Health Monitoring System"
#define BLYNK_AUTH_TOKEN "g1SkJvp9YQQKrreaUJZtyD5DyE-_1eeT"

#include <Wire.h>
#include <Ticker.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ====== BLYNK CONFIG ======

char auth[] = "g1SkJvp9YQQKrreaUJZtyD5DyE-_1eeT";
char ssid[] = "Nhom6";
char pass[] = "12345678";

// ====== MAX30100 Setup ======
PulseOximeter pox;
#define REPORTING_PERIOD_MS 1000
Ticker poxTicker;
volatile bool poxReady = false;

// ====== DS18B20 Setup ======
#define DS18B20_PIN 5
OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);
unsigned long lastDSRequest = 0;
bool dsRequested = false;
float bodyTemp = -127.0;

// ====== DHT11 Setup ======
#define DHTPIN 18
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float roomTemp = 0;
float roomHumidity = 0;

// ====== Reporting Time Tracker ======
// Used to keep track of the last time sensor data was sent to Blynk/cloud.
// Helps ensure periodic (e.g., every 1 second) reporting without blocking the main loop.
uint32_t tsLastReport = 0;

// ====== Callback heart beat ======
void onBeatDetected() {

}

// ====== Task for MAX30100 ======
void IRAM_ATTR updatePoxISR() {
  pox.update();
  poxReady = true;
}

void setup() {
  Serial.begin(115200);

  // I2C bus cho MAX30100
  Wire.begin(21, 22);
  Wire.setClock(400000); 

  // Initialize MAX30100 pulse oximeter sensor
if (!pox.begin()) {
  Serial.println("‼ MAX30100 init failed! Halting system.");
  while (1); // Stop execution if sensor fails to initialize
}

// Set callback for heartbeat detection (for logging only)
pox.setOnBeatDetectedCallback(onBeatDetected);

// Set IR LED current for MAX30100 sensor
pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

// Start periodic update for MAX30100 every 20ms using Ticker
poxTicker.attach_ms(20, updatePoxISR);

// Initialize DS18B20 temperature sensor in non-blocking mode
ds18b20.begin();
ds18b20.setWaitForConversion(false);

// Initialize DHT11 temperature and humidity sensor
dht.begin();

// Connect to WiFi and Blynk cloud service
WiFi.begin(ssid, pass);
Blynk.begin(auth, ssid, pass);
}

void loop() {

  Blynk.run();

  unsigned long now = millis();

  // flax poxReady to false to avoid multiple reports in the same loop
  if (poxReady && (now - tsLastReport >= REPORTING_PERIOD_MS)) {
    tsLastReport = now;
    poxReady = false;

    float bpm  = pox.getHeartRate();
    float spo2 = pox.getSpO2();
    Serial.printf("[MAX30100] BPM: %.1f | SpO2: %.1f\n", bpm, spo2);

    // Send data to Blynk virtual pins
    Blynk.virtualWrite(V5, bpm);
    Blynk.virtualWrite(V6, spo2);

    // read DHT11 temperature and humidity
    roomTemp     = dht.readTemperature();
    roomHumidity = dht.readHumidity();
    if (!isnan(roomTemp) && !isnan(roomHumidity)) {
      Serial.printf("[DHT11] Temp: %.1f°C | Humidity: %.1f%%\n", roomTemp, roomHumidity);
      Blynk.virtualWrite(V3, roomTemp);
      Blynk.virtualWrite(V4, roomHumidity);
    } else {
      Serial.println("‼ Lỗi đọc DHT11");
    }
  }

  // initialize DS18B20 temperature reading every 750ms
  if (!dsRequested) {
    ds18b20.requestTemperatures();
    lastDSRequest = now;
    dsRequested = true;
  }
  if (dsRequested && now - lastDSRequest >= 750) {
    dsRequested = false;
    bodyTemp = ds18b20.getTempCByIndex(0);
    if (bodyTemp != DEVICE_DISCONNECTED_C) {
      Serial.printf("[DS18B20] Body Temp: %.2f°C\n", bodyTemp);
      Blynk.virtualWrite(V7, bodyTemp);
    } else {
      Serial.println("‼ Lỗi đọc DS18B20");
    }
  }
}