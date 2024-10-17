#include <WiFi.h>
#include <SPIFFS.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SFE_BMP180.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "MQTT.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT.hpp"
#include "Sensores.hpp"

int temp = 0;
int hum = 0;
int lux = 0;

void setup(void)
{
	Serial.begin(115200);
	SPIFFS.begin();
	ConnectWiFi_STA(true);
  loadDHT();

	InitMqtt();
}

void loop()
{
	HandleMqtt();
  temp = leerTemperatura();
  if(temp>=0)
  {
    PublisMqtt(temp, MQTT_TOPIC_TEMP);
  }
  hum = leerHumedad();
  if(hum>=0)
  {
    PublisMqtt(hum, MQTT_TOPIC_HUMI);
  }
  lux = leerLuz();
  if(lux>=0)
  {
    PublisMqtt(lux, MQTT_TOPIC_LUX);
  }

	delay(5000);
}
