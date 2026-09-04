# Fridge Temperature Monitor
 
ESP32-based IoT sensor that monitors the temperature of a commercial refrigerator and reports it to a dashboard, with email alerts when the temperature moves outside a safe range.
 
The commercial fridges at my shop don't come with a built-in thermometer, so a failure overnight or over a weekend meant discovering spoiled stock.
 
<!-- Drop a photo of the finished build here. Drag the image into GitHub's README editor and it uploads automatically. -->
<!-- ![The finished build](docs/build.jpg) -->
 
## How it works
 
A waterproof DS18B20 probe sits inside the fridge, with its cable routed through the door gasket to an ESP32 mounted outside. The ESP32 reads the sensor over the 1-Wire protocol every 60 seconds and publishes the reading to Adafruit IO over Wi-Fi via MQTT. A dashboard renders the live value and history, and a reactive trigger sends an email if the temperature crosses either threshold.
 

DS18B20 probe  ──1-Wire──>  ESP32  ──Wi-Fi──>  Adafruit IO  ──>  Dashboard

 
Wiring is three connections: `3.3V`, `GND`, and `GPIO4` for data, with the pull-up resistor bridging `3.3V` and `GPIO4`. Prototyped on a breadboard, then soldered directly to the ESP32 pins for permanent installation.
After that, all that was left was to 3d print a housing for the ESP32.
 
