class DS1307_RTC{ //clase creada para administrar métodos para obtención de tiempo
  public: //variables públicas
    uint8_t hora, minuto, segundo, dia, mes;
    uint16_t ano;
    String fecha, tiempo;
  public: //métodos públicos
  void rtc_init (void); //inicialización de RTC
  void get_time (void); //obtención de tiempo
  void get_format_time (void); //formateo de medición de tiempo obtenido
  void get_format_date (void); //formateo de medición de fecha obtenida
};

void DS1307_RTC::rtc_init(void){ //evaluación de estado de inicialización de RTC
  while(!rtc.begin()){ //mientras el RTC no haya iniciado correctamente
    Serial.println("Error de reconocimiento del RTC"); //imprimir error de reconocimiento en puerto serial
    delay(10); //repetir cada 10s
  }// * fin de ciclo *
  Serial.println("Inicio correcto de RTC"); //una vez que se haya inicializado adecuadamente
}// * fin de método *

void DS1307_RTC::get_time(void){ //almacenamiento de valores que van a componer el tiempo y fecha
  
  DateTime now = rtc.now(); //creación de variable tipo DateTime que almacena valor retornado por función que recupera fecha y hora de dispositivo en que se está ejecutando en ese momento
  ano = now.year(); //almacenamiento de año
  mes = now.month(); //almacenamiento de mes
  dia = now.day(); //almacenamiento de día
  hora = now.hour(); //almacenamiento de hora
  minuto = now.minute(); //almacenamiento de minuto
  segundo = now.second(); //almacenamietno de segundo
}// * fin de método *

void DS1307_RTC::get_format_date(void){ //evaluación de dígitos para almacenamiento de fecha. ej: 01/12/23
  get_time (); //llamar función para obtención de fecha y hora en ese momento
  fecha = "";//inicialización de variable en blanco
  if (dia < 10) fecha += "0"; //si el valor de día es mayor a 10, entonces agregar un cero al inicio
  fecha += dia; //y posteriormente el valor
  fecha += "/"; //agregar separador para mes
  if (mes < 10) fecha += "0"; //si el valor de mes es menor a 10, entonces agregar un 0 al inicio
  fecha += mes; //y posteriormente agregar valor correspondiente
  fecha += "/"; //agregar separador para año
  fecha += ano; //agregar valor de año
}// * fin de método *

void DS1307_RTC::get_format_time(void){ //evaluación de dígitos para almacenamiento de hora, ej: 10:20:03
  get_time (); //llamar función para obtención de fecha y hora en ese momento
  tiempo = ""; //inicialización de variable en blanco
  if (hora < 10) tiempo += "0"; //si el valor de la hora es menor a 10, agregar 0 al inicio
    tiempo += hora; //agregar valor de hora
    tiempo += ":"; //agregar separador para minutos
  
  if (minuto < 10) tiempo += "0"; //si el valor de minutos es menor a 10, entonces agregar 0 al inicio
    tiempo += minuto; //agregar valor de minutos
    tiempo += ":"; //agregar separador para segundos
  
  if (segundo < 10) tiempo += "0"; //si el valor de segundos es menor a 10, entonces agregar 0 al inicio
    tiempo += segundo; //agregar valor de segundos
} // * fin de método *
