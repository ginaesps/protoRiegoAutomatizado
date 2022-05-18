#define TEMP_TIME 3000 // Constante y el tiempo

class Tareas{
  public:
  unsigned long 
                task_2s = 0,
                task_3s = 0,
                task_4s = 0,
                task_5s = 0,
                task_6s = 0,
                task_10s = 0,
                currentMillis = 0; //Ver el tiempo desde que empezo en arduino
  public:
  
    //Declaración de las task
    void _2s (void);
    void _3s (void);
    void _4s (void);
    void _5s (void);
    void _6s (void);
    void _10s (void);
};

/*--------Task que llama a imprimir en la LCD cada 2 seg--------*/
void Tareas::_2s(){
  if (( currentMillis - task_3s)>= 3000){
  actuators.printLCD();
  task_2s = currentMillis;
  }
}

/*--------Task que llama al giroscopio cada 3seg--------*/
void Tareas::_3s(){// Verificar si pasan 3 segundos
  if (( currentMillis - task_3s)>= TEMP_TIME){//Pasaron 3 segundos o TEMP_TIME
  sensors.giroscopio(); // Revisar pos del giroscopio
  task_3s = currentMillis; //Tiempo pasado va a ser tiempo presente 
}
}

/*--------Task que llama al flujometro cada 4seg--------*/
void Tareas::_4s(){
  if (( currentMillis - task_4s)>= 4000){
  Serial.println("soy el flujometro");
  sensors.CDF();
  task_4s = currentMillis;
  }
}

      /*--------Task que llama al higometro cada 4seg--------*/
/*--------Activa y desactiva la bomba mediante el relevador-------*/
void Tareas::_5s(){
  if (( currentMillis - task_5s)>= 5000){//Pasaron 5 segundos
    Serial.println("humedad");
  int humidity = sensors.humedad(); //Revisar sensor de humedad
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
  if (( currentMillis - task_6s)>= 6000){//Pasaron 6 segundos
    Serial.println("temperatura ambiental");
    int temperature = sensors.temperatura(); //revisar sensor de temperatura ambiental
    if(temperature >= 32){
      actuators.buzzer();
    } else{ 
      actuators.buzzerOff();
    }
    task_6s = currentMillis; //Tiempo pasado va a ser tiempo presente 
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
