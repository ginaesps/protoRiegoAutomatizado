#include "DHT.h" //inclusión de librería para manejo de sensor de temperatura ambiental
#define DHTPIN 4 //pin digital asignado a dht11
#define DHTTYPE DHT11 //definición de tipo de DHT que se está utilizando
  DHT dht(DHTPIN, DHTTYPE); //inicialización del sensor con paso de pin y tipo

#define sensor_hum 32 //pin asignado para sensor de humedad
#define PinCDF 16 //pin para caudal de flujo

class Sensores { //clase creada controlar mediciones de sensores
public: //declaración de variables públicas

public: //declaración de métodos públicos

   int humedad ( void ); //método para medición de humedad de tierra
   float CDF (void); //método para medición de caudal de flujo
   int temperatura (void); //método para medición de temperatura de ambiente
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCIONES GLOBALES PARA FLUJÓMETRO~~~~~~~~~~~~~~*/
volatile int Contador; //variable que cuenta los pulsos
 void pulso (void){ //cada que se mande a llamar este método, se va a aumentar en 1 la variable contador
    Contador++;
}// * fin de método *
  
long obtencionFrecuenciaCDF(void) { //obtención de frecuencia a la cual trabaja el caudal de flujo
  long cantidad; //declaración de variable para guardar valor final de cálculo
  Contador = 0; //limpiar variable
  interrupts(); //conteo de interrupciones
  delay(100);  //Se inician las interrupciones y se cuentan los pulsos
  noInterrupts();//se suspenden las interrupciones
  cantidad=10*Contador; // pulsos por segundo
  return cantidad;
}// * fin de método *

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODO HUMEDAD~~~~~~~~~~~~~~*/
int Sensores::humedad (void){ 
  int humidity = analogRead(sensor_hum); //declaración de variable que almacene la medición realizada por pin análogo de sensor de humedad
  return humidity;
}// * fin de método *

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODO FLUJOMETRO~~~~~~~~~~~~~~*/
float Sensores::CDF (void){ //Metodo Caudal de flujo
   
 float frecuencia=obtencionFrecuenciaCDF(); //frecuencia de los pulsos
 float Caudal=frecuencia/7.5; //calculamos el caudal en L/m, factor de conversion entre frecuencia y cauda=7.5, depende de parametros del sensor
  return Caudal;
}// * fin de método *

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~MÉTODO TEMPERATURA~~~~~~~~~~~~~~*/
int Sensores::temperatura(void){
  float t = dht.readTemperature(); //lectura de temperatura en °C
  if (isnan(t)|| t > 50) { //en caso de que la medición de temperatura detecte algo que no sea un número, la medición del DHT11 está fallando
    Serial.println(F("Fallo en intento de lectura de sensor DHT11"));
    return -1; //retorno de valor fuera de rango posible de sensor para indicar un mal funcionamiento
  }
  else{ //en caso de que la variable de almacenamiento de la temperatura, retornar el valor
  return t;
  }
}// * fin de método *
