// ─────────────────────────────────────────────────
//  SINGLE FRIDGE TEMPERATURE MONITOR
//  ESP32 + DS18B20 sensor → Adafruit IO dashboard
// ─────────────────────────────────────────────────

#include "AdafruitIO_WiFi.h"
#include <OneWire.h>
#include <DallasTemperature.h>


#define WIFI_SSID    "thewifinetwork"       
#define WIFI_PASS    "thenetworkspassword"   
#define AIO_USERNAME "myusernamefromadafruitIOwebsite"  
#define AIO_KEY      "mykeyfromAdafruitIOwebsite"       


// GPIO pin the sensor data wire is connected to
#define SENSOR_PIN 4

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensor(&oneWire);

AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *fridgeTemp = io.feed("fridge-temp");

// Send a reading every 60 seconds
const unsigned long INTERVAL = 60000;
unsigned long lastSent = 0;

// ─── SETUP (runs once on power-on) ───────────────
void setup() {
  Serial.begin(115200);
  sensor.begin();

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected! Ready to send data.");
}

// ─── LOOP (repeats) ───────────────────────
void loop() {
  io.run(); // keeps connection alive

  if (millis() - lastSent >= INTERVAL) {
    lastSent = millis();

    sensor.requestTemperatures();
    float tempF = sensor.getTempFByIndex(0);

    Serial.print("Temperature: ");
    Serial.print(tempF);
    Serial.println(" °F — sending to dashboard...");

    fridgeTemp->save(tempF);
  }
}
