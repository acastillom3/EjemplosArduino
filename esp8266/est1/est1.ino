#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SFE_BMP180.h>

#include "config.h" 
#include "MQTT.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_MQTT.hpp"
#include "Sensores.hpp"

// Sensor BMP180
SFE_BMP180 bmp180;

int temp = 0;
int hum = 0;

void setup()
{
	Serial.begin(115200);
    
  if (!bmp180.begin()) {
	  Serial.println("Error al iniciar BMP180");
  }else
  {
	  Serial.println("BMP180 iniciado");
  }

	SPIFFS.begin();
	ConnectWiFi_STA(true);
	InitMqtt();
  PublisMqtt(1, MQTT_TOPIC_LOAD);
}

void loop()
{
	HandleMqtt();
  temp = leerTemperaturaBMP(bmp180);
  if(temp>=0)
  {
    PublisMqtt(temp, MQTT_TOPIC_TEMP);
  }
  hum = leerPresionBMP(bmp180);
  if(hum>=0)
  {
    PublisMqtt(hum, MQTT_TOPIC_HUMI);
  }

	delay(5000);
}


