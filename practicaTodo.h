/*~~~~~~~~~~~~~~~~~~~~~~~~~~~LIBRERÍAS Y CONFIGURACIÓN DE LCD~~~~~~~~~~~~~~*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define COLUMNAS 16
#define FILAS 2
#define DISPLAY 0x27
LiquidCrystal_I2C lcd(DISPLAY, COLUMNAS, FILAS);
/*---------------------------------------------*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~INSTANCIA A LIBRERÍAS DE SENSORES~~~~~~~~~~~~~~*/
Sensores sensors;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~INSTANCIA A LIBRERÍAS DE ACTUADORES~~~~~~~~~~~~~~*/
#include "actuadores.h" 
 Actuadores actuators; // Instancias de clase 

#include <WiFi.h>
  WiFiClient ESP32_WIFI;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~CONFIGURACIÓN DE CLIENTE PARA HACER PUBLICACIONES MQTT~~~~~~~~~~~~~~*/
#include <PubSubClient.h>
  PubSubClient client ( ESP32_WIFI );
const char* HOTSPOT_WIFI = "EX_6D_HOTSPOT";
const char* HOTSPOT_PWD = "12345678";  
const char* MQTT_SERVER = "test.mosquitto.org";
#define MQTT_PORT 1883
#define TOPIC "E2/6D" 
long lastMsg = 0; //parámetro en evaluación de tiempo en reconexión y publicación MQTT

#include <ArduinoJson.h> //librería para usar JSON
#include <SD.h> //librería para trabajar MicroSD
#include <SPI.h> //librería que permite envío de datos a periféricos relacionados con MSD
#include <Wire.h> //comunicación con sensores que usan protocolo I2C

#define MICROSD_PIN 5
#define EXTENSION ".json"

#include "RTClib.h"
  RTC_DS1307 rtc;
File MicroSD_File;

#include "RTC.h"
  DS1307_RTC RTC;
  
#include "MicroSD.h"
  MicroSD MSD;
  
#include "MQTT.h"
 MQTT mqtt;

#include "tareas.h" // Llama a las librerias de tareas
 Tareas tasks;
