#include "DHT.h"
#include "Adafruit_CCS811.h"  //Biblioteca para el sensor CCS811

#define DHTTYPE DHT22

const int DHTPin = 18;
const int UVPin = 6;  // what digital pin we're connected to
const int LCDPin = 15;

DHT dht(DHTPin, DHTTYPE);
Adafruit_CCS811 ccs;  //Declaración de un objeto del sensor

void loadDHT()
{
  dht.begin();
}
int leerLuz(){
  //Reading luxometer
  float lux = analogRead(LCDPin);
  Serial.print("Lux: ");
  Serial.println(lux);
  return lux;
}

int leerTemperatura() {
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  return t;
}

int leerHumedad() {
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  return h;
}

void configurarDioxido() {
  if (!ccs.begin()) {
    Serial.println("No se pudo inicializar el sensor, revisa tus conexiones");
    while (1)
      ;  //se detiene el programa
  }
  //Esperando la transmisión de datos del sensor
  while (!ccs.available())
    ;
}

void leerDioxido() {
  if (ccs.available()) {    //si el sensor esta disponible
    if (!ccs.readData()) {  //lee los datos
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      //total de componentes volátiles orgánicos (TVOC)
      Serial.println(ccs.getTVOC());
    } else {
      Serial.println("ERROR al leer el sensor");
      ccs.readData();
    }
  }
}

int leerUV() {
  String UVIndex = "0";
  int sensorValue = 0;

  sensorValue = analogRead(0);                          //connect UV sensor to Analog 0
  int voltage = (sensorValue * (5.0 / 1023.0)) * 1000;  //Voltage in miliVolts

  if (voltage < 50) {
    UVIndex = "0";
  } else if (voltage > 50 && voltage <= 227) {
    UVIndex = "0";
  } else if (voltage > 227 && voltage <= 318) {
    UVIndex = "1";
  } else if (voltage > 318 && voltage <= 408) {
    UVIndex = "2";
  } else if (voltage > 408 && voltage <= 503) {
    UVIndex = "3";
  } else if (voltage > 503 && voltage <= 606) {
    UVIndex = "4";
  } else if (voltage > 606 && voltage <= 696) {
    UVIndex = "5";
  } else if (voltage > 696 && voltage <= 795) {
    UVIndex = "6";
  } else if (voltage > 795 && voltage <= 881) {
    UVIndex = "7";
  } else if (voltage > 881 && voltage <= 976) {
    UVIndex = "8";
  } else if (voltage > 976 && voltage <= 1079) {
    UVIndex = "9";
  } else if (voltage > 1079 && voltage <= 1170) {
    UVIndex = "10";
  } else if (voltage > 1170) {
    UVIndex = "11";
  }
  Serial.print(" UV:");
  Serial.println(UVIndex);
  return sensorValue;
}



double leerTemperaturaBMP(SFE_BMP180 bmp180)
{
  char status;
  double T;

  status = bmp180.startTemperature();//Inicio de lectura de temperatura
  if (status != 0)
  {   
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    if (status != 0)
    {                   
          Serial.print("Temperatura: ");
          Serial.print(T,2);
          Serial.print(" *C , ");
    }   
  }
  return T;
}

double leerPresionBMP(SFE_BMP180 bmp180)
{
  char status;
  double P,T;

  status = bmp180.startPressure(3); //Inicio lectura de presión
  if (status != 0)
  {        
    delay(status);//Pausa para que finalice la lectura        
    status = bmp180.getPressure(P,T); //Obtenemos la presión
    if (status != 0)
    {                  
      Serial.print("Presion: ");
      Serial.print(P,2);
      Serial.println(" mb");          
    }      
  }  
  return P;
}

double leerAltitudBMP(SFE_BMP180 bmp180)
{
  char status;
  double T,P,A;
  double PresionNivelMar = 1013.25; //presion sobre el nivel del mar en mbar
  
  status = bmp180.startTemperature(); //Inicio de lectura de temperatura
  if (status != 0)
  {   
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {        
        delay(status); //Pausa para que finalice la lectura        
        status = bmp180.getPressure(P,T); //Obtener la presión
        if (status != 0)
        {                  
          Serial.print("Temperatura: ");
          Serial.print(T);
          Serial.print(" *C , ");
          Serial.print("Presion: ");
          Serial.print(P);
          Serial.print(" mb , ");     
          
          A= bmp180.altitude(P,PresionNivelMar); //Calcular altura
          Serial.print("Altitud: ");
          Serial.print(A);
          Serial.println(" m");    
        }      
      }      
    }   
  } 
  return A;
}
