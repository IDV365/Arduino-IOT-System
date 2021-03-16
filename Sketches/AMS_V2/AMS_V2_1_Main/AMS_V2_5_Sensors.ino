


//DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 49
DHT_Unified dht(DHTPIN, DHT11);
float DHT_return(char selector) {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if ( selector == 'T') {
    if (isnan(event.temperature)) {
    }
    else {
      return event.temperature;
    }
  }
  else if ( selector == 'H') {
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
    }
    else {
      return event.relative_humidity;
    }
  }
}


//BH1750
#include <BH1750.h>
BH1750 lightMeter;
float BH1750_return() {
  float lux = lightMeter.readLightLevel();
  return lux;
}




//BMP
#include <Wire.h>
#include "SparkFunBME280.h"
BME280 BMP;
float BMP_return(char selector) {
  if (selector == 'T') {
    return BMP.readTempC();
  } else if (selector == 'F') {
    return BMP.readTempF();
  } else if (selector == 'H') {
    return BMP.readFloatHumidity();
  } else if (selector == 'P') {
    return BMP.readFloatPressure();
  }
}
