#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 49
DHT_Unified dht(DHTPIN, DHT11);

#include <BH1750.h>

#include <Wire.h>
#include "SparkFunBME280.h"
BME280 BMP;


float DHT_return(char selector);
float BH1750_return();
float BMP_return(char selector)
