/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 2.1.                                            *
*      FECHA:       18 de mayo de 2022.                                      *
*      VERSIÓN:     2.1.                                                     *
*                                                                            *
*      AUTOR:       Esli Castellanos Berján.                                 *
*      E-MAIL:      esli_castellanos@ucol.mx.                                *
*      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          *
*                                                                            *
*      uC:          ESP32-D0WD Dual Core.                                    *
*      Nombre:      ESP32-S.                                                 *
*                                                                            *
******************************************************************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Creación de prototipo de riego automatizado *
*      con registro en una MicroSD, medición de tiempo con RTC y sensores    *  
*      de humedad de tierra, temperatura ambiental y caudal de flujo         *
*                                                                            *
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~LLAMADO A ENCABEZADO DE INSTANCIAS~~~~~~~~~~~~~~*/
#include "practicaTodo.h" //Llama la libreria de las instancias

void setup() {
  Serial.begin(115200); //Configuración de Bauhdios
  
  /*~~~~~~~CONFIGURACIÓN DE PINES A MODO OUTPUT~~~~~~~~~~~~~~*/
  pinMode(rele, OUTPUT);
  pinMode(PinSensor, INPUT);
  
  /*~~~~~~~~~~~~~~~INTERRUPCIÓN PARA FLUJOMETRO~~~~~~~~~~~~~~*/
  attachInterrupt(PinSensor,pulso,RISING);
  
  /*~~~~~~~~~~~~~~~INICIALIZACIÓN DE DHT11~~~~~~~~~~~~~~~~~~~*/
  dht.begin();
  
  /*~~~~~~~~~~~~~~~INICIALIZACIÓN DE PANTALLA LCD~~~~~~~~~~~~*/
  actuators.LCD_init();

  /*~~~~~~~~~~~~~~~CONFIGURACIÓN DE RED PARA MQTT SERVER~~~~~~~~~~~~~~*/
  mqtt.setup_WiFi ( );
  mqtt.set_MQTT_server ( ); // inicialización de MQTT server

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~INICIALIZACIÓN DE RTC~~~~~~~~~~~~~~~~~~~~~~~~~*/
  RTC.rtc_init();

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~INICIALIZACIÓN DE MICROSD~~~~~~~~~~~~~~*/
  MSD.MicroSD_init();
  
}

void loop() { 
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~INICIALIZAR millis() EN MÉTODOS DE tareas.h~~~~~~~~~~~~~~*/
  tasks.currentMillis = millis(); 
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~LLAMADA A FUNCIONES DE tareas.h -> Tareas::nameTask() ~~~~~~~~~~~~~~*/
  tasks._2s(); //imprime datos en lcd
  tasks._4s(); //llama a flujometro (mide caudal de flujo)
  tasks._5s(); //(des)activa bomba mediante relevador
  tasks._6s(); //llama a DHT11
  tasks._10s(); //reconexión y publicación a MQTT
}
