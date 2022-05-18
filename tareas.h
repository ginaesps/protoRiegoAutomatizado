class Tareas{
  public:
  unsigned long 
                task_4s = 0,
                task_5s = 0,
                task_6s = 0,
                task_8s = 0,
                task_10s = 0,
                currentMillis = 0; //Ver el tiempo desde que empezo en arduino
  public:
  
    //Declaración de las task
    void _4s (void);
    void _5s (void);
    void _6s (void);
    void _8s (void);
    void _10s (void);
};

/*--------Task que llama al flujometro cada 4seg--------*/
void Tareas::_4s(){
  if (( currentMillis - task_4s)>= 4000){
    Serial.println("flujometro: ");
    Serial.println(sensors.CDF());
    task_4s = currentMillis;
  }
}

      /*--------Task que llama al higometro cada 5seg--------*/
/*--------Activa y desactiva la bomba mediante el relevador-------*/
void Tareas::_5s(){
  if (( currentMillis - task_5s)>= 5000){//Pasaron 5 segundos
      int humidity = sensors.humedad(); //Revisar sensor de humedad
      Serial.println("humedad: ");
      Serial.println(sensors.humedad());
  if(humidity == 4095){
    //esta seco se activa el relé
    actuators.relayOn();
    //sensors.CDF(); Se plantea que se mida el flujo cuando este activada la bomba
  }
  else {
    //esta humedo se desactiva o no pasa nada xd
    actuators.relayOff();
    }
  task_5s = currentMillis;
  } 
}

/*--------Task que llama al DHT11 cada 6seg-------*/
void Tareas::_6s(){
  int temperature = sensors.temperatura(); //revisar sensor de temperatura ambiental
  if (( currentMillis - task_6s)>= 6000){//Pasaron 6 segundos
    Serial.println("temp: ");
    Serial.println(sensors.temperatura());
    if(temperature >= 25){
      actuators.buzzer();
    } else{ 
      actuators.buzzerOff();
    }
    task_6s = currentMillis; //Tiempo pasado va a ser tiempo presente 
  }
}

/*--------Task que llama a imprimir en la LCD cada 8 seg--------*/
void Tareas::_8s(){
  if (( currentMillis - task_8s)>= 8000){
    actuators.printLCD();
    task_8s = currentMillis;
  }
}

/*--------Task que reconecta y publica con MQTT--------*/
void Tareas::_10s(){
  if (( currentMillis - task_10s)>= 10000){
   long now = millis();
      if (now - lastMsg > 5000) {
         lastMsg = now;
         mqtt.reconnect_MQTT ( );
         mqtt.publish_MQTT ( );
         MSD.JSON();
        }
    task_10s = currentMillis;
  }
}
