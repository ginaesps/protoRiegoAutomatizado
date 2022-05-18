#include "DHT.h"
#define DHTPIN 4     // pin digital conectado a dht11
#define DHTTYPE DHT11   
  DHT dht(DHTPIN, DHTTYPE); //inicialización del sensor
float t = dht.readTemperature(); //lectura de temperatura en °C

#define sensor_hum 15
#define PinSensor 16 //pin para caudal de flujo

class Sensores { 
public:   

   //Metodos de los sensores
   int humedad ( void );
   float CDF (void);
   void giroscopio (void);
   int temperatura (void);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCIONES GLOBALES PARA FLUJÓMETRO~~~~~~~~~~~~~~*/
volatile int Contador; //variable que cuenta los pulsos
 void pulso (void){
    Contador++;
  }
  
long funcion(void) //obtiene la frecuencia
{
  long cantidad;
  Contador = 0;  
  interrupts();
  delay(100);  //Se inician las interrupciones y se cuentan los pulsos
  noInterrupts();//se suspenden las interrupciones
  cantidad=10*Contador; // pulsos por segundo
  return cantidad;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODO HUMEDAD~~~~~~~~~~~~~~*/
int Sensores::humedad (void){ 
  int humidity = analogRead(sensor_hum);
  Serial.println(humidity);
  return humidity;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODO FLUJOMETRO~~~~~~~~~~~~~~*/
float Sensores::CDF (void){ //Metodo Caudal de flujo
   
 float frecuencia=funcion(); //frecuencia de los pulsos
 float Caudal=frecuencia/7.5; //calculamos el caudal en L/m

  Serial.print ("Litros por  minuto: ");
  Serial.println (Caudal);
  return Caudal;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODO GIROSCOPIO~~~~~~~~~~~~~~*/
void Sensores::giroscopio(void){ //Metodo giroscopio
  //if(esta su pos?)-> no pasa nada/apaga el buzzer
  //else -> activar buzzer
  Serial.println ("giroscopio");
}

void Sensores::temperatura(void){
  if (isnan(t)) { //en caso de que la medición de temperatura detecte algo que no sea un número, la medición del DHT11 está fallando
    Serial.println(F("Fallo en intento de lectura de sensor DHT11"));
    return;
  }

  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}
