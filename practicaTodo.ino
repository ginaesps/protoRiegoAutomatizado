/*****************************************************************************
*                                                                            *
*      NOMBRE:      Práctica 2.1.                                            *
*      FECHA:       18 de mayo de 2022.                                      *
*      VERSIÓN:     2.2                                                      *
*                                                                            *
*      AUTORES:     Regina Espinosa González                                 *
*                   María Alejandra Velazco Baltazar                         *
*                   Adelina Mancilla Rojas                                   *
*                   Andrew Joshua Craig Montiel                              *
*      REPOSITORIO: https://github.com/ginaesps/protoRiegoAutomatizado       *
*      COMPAÑÍA:    Universidad de Colima - Facultad de Telemática.          *
*                                                                            *
*      SENSORES UTILIZADOS:          ESP32-D0WD Dual Core.                   *
*                                    DHT11                                   *
*                                    YFS201                                  *
*                                    FC-28                                   *
*                                                                            *
*      ACTUADORES UTILIZADOS:        Bomba de agua                           *
*                                    Relevador G3MB-202P                     *
*                                    Buzzer                                  *
*                                                                            *
*      ADICIONALES UTILIZADOS:       Mini MicroSD                            *
*                                    RTC DS1307                              *
*                                    LCD1602 + I2C                           *
*                                                                            *
******************************************************************************
*                                                                            *
*      DESCRIPCIÓN DEL PROGRAMA: Creación de prototipo de riego automatizado *
*      con registro en una MicroSD, medición de tiempo con RTC y sensores    *  
*      de humedad de tierra, temperatura ambiental y caudal de flujo.        *
*                                                                            *
******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~LLAMADO A ENCABEZADO DE INSTANCIAS~~~~~~~~~~~~~~*/
#include "practicaTodo.h" //Llama la libreria de las instancias

void setup() { //configuraciones iniciales
  Serial.begin(115200); //Configuración de Bauhdios
  
  /*~~~~~~~CONFIGURACIÓN DE PINES A MODO OUTPUT~~~~~~~~~~~~~~*/
  pinMode(rele, OUTPUT);
  pinMode(PinCDF, INPUT);
  
  /*~~~~~~~~~~~~~~~INTERRUPCIÓN PARA FLUJOMETRO~~~~~~~~~~~~~~*/
  attachInterrupt(PinCDF,pulso,RISING);
  
  /*~~~~~~~~~~~~~~~INICIALIZACIÓN DE DHT11~~~~~~~~~~~~~~~~~~~*/
  dht.begin();

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~INICIALIZACIÓN DE RTC~~~~~~~~~~~~~~~~~~~~~~~~~*/
  RTC.rtc_init();

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~INICIALIZACIÓN DE MICROSD~~~~~~~~~~~~~~*/
  MSD.MicroSD_init();
  
  /*~~~~~~~~~~~~~~~INICIALIZACIÓN DE PANTALLA LCD~~~~~~~~~~~~*/
  actuators.LCD_init();

  /*~~~~~~~~~~~~~~~CONFIGURACIÓN DE RED PARA MQTT SERVER~~~~~~~~~~~~~~*/ 
  mqtt.setup_WiFi ( );
  mqtt.set_MQTT_server ( ); // inicialización de MQTT server

  /*~~~~~FUNCIÓN DE CALLBACK PARA SUSCRIPCIÓN MQTT POR PARTE DEL CLIENTE~~~~~~~~~~~*/
  client.setCallback(callback); 
}

void loop() { //código que se va a ejecutar en repetición
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~INICIALIZAR millis() EN MÉTODOS DE tareas.h~~~~~~~~~~~~~~*/
  tasks.currentMillis = millis(); 
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~LLAMADA A FUNCIONES DE tareas.h -> Tareas::nameTask() ~~~~~~~~~~~~~~*/
  mqtt.reconnect_MQTT ( ); //verificación de conexión a MQTT
  tasks._higometroBomba(); //(des)activación de bomba mediante relevador
  tasks._dht11(); //medición de temperatura ambiental
  tasks._printLCD(); //impresión de datos en lcd
  tasks._connectionMQTT(); //reconexión y publicación a MQTT
  
}
