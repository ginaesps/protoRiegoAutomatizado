class Tareas{ //clase creada controlar tiempos de activación de tareas
  public: //declaración de variables públicas
    unsigned long //tipo de dato asignado
                task_5s = 0,
                task_6s = 0,
                task_8s = 0,
                task_10s = 0,
                currentMillis = 0; //Ver el tiempo desde que empezo en arduino
                
  public://Declaración métodos públicos
    void _higometroBomba (void); //tarea para control de bomba de acuerdo con medición de higometro
    void _dht11 (void); //tarea para control de medición de temperatura ambiental
    void _printLCD (void); //tarea para control de impresión de datos en pantalla LCD
    void _connectionMQTT (void); //tarea para control de conexión a MQTT
};

      /*--------Task que llama al higometro cada 5seg--------*/
/*--------Activa y desactiva la bomba mediante el relevador-------*/
void Tareas::_higometroBomba(){
  if (( currentMillis - task_5s)>= 5000){//Pasaron 5 segundos
      int humidity = sensors.humedad(); //Revisar sensor de humedad
      
  if(humidity > 4000 && humidity < 4096){ //si la tierra a medir esta seca, se activa el relé
    bombaOn = 1;
    /*~~~~~~~~~~~~~~~GUARDAR FECHA Y HORA DE ACTIVACIÓN DE BOMBA~~~~~~~~~~~~~~~~~~~~~~*/
    RTC.get_format_date();
    RTC.get_format_time();    
    diaBombaOn = RTC.fecha.c_str();
    tiempoBombaOn = RTC.tiempo.c_str();
    actuators.relayOn(); //activar relevador   
  }
  else { //si está humedo, relay se desactiva o no pasa nada xd
    actuators.relayOff();
    }
  task_5s = currentMillis;
  } 
}// * fin de método *

/*~~~~~~~~~~~~~~~LLAMAR A DHT11 CADA 6SEG~~~~~~~~~~~~~~~~~~~~~~*/
void Tareas::_dht11(){
  int temperature = sensors.temperatura(); //revisar sensor de temperatura ambiental
  if (( currentMillis - task_6s)>= 6000){//Pasaron 6 segundos
    Serial.println("temp: ");
    Serial.println(sensors.temperatura());
    if(temperature >= 35 && temperature <= 50){
      actuators.buzzer();
    } else{ 
      actuators.buzzerOff();
    }
    task_6s = currentMillis; //Tiempo pasado va a ser tiempo presente 
  }
}// * fin de método *

/*~~~~~~~~~~~~~~~IMPRESIÓN DE PANTALLA EN LCD~~~~~~~~~~~~~~~~~~~~~~*/
void Tareas::_printLCD(){
  if (( currentMillis - task_8s)>= 8000){ //pasaron 8s
    actuators.printLCD(); //mandar a llamar método de actuadores
    task_8s = currentMillis;
  }
}// * fin de método *

/*~~~~~~~~~~~~~~~TASK QUE RECONECTA Y PUBLICA CON MQTT~~~~~~~~~~~~~~~~~~~~~~*/
void Tareas::_connectionMQTT(){
  if (( currentMillis - task_10s)>= 10000){ //pasaron 10s
      mqtt.publish_MQTT ( ); //mandar a llamar método de publicación de MQTT
      MSD.JSON();//enviar JSON
    task_10s = currentMillis;
    bombaOn = 0; //reiniciar variable para evaluar activación de bomba
  }
}// * fin de método *
