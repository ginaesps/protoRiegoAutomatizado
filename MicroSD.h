class MicroSD{ //clase creada para administrar el almacenamiento de información en MSD
  public: //variables públicas
    String filename = "", json_string = ""; //nombre de archivo y json_string contiene info a publicar en MQTT
    
  public: //métodos públicos
  void MicroSD_init (void); //inicialización de microSD
  void FileID (void); //nombreArchivo almacenado en MicroSD
  void JSON (void); //creación de JSON
  void JSON_SaveFile (DynamicJsonDocument*); //puntero a docJSON para almacenamiento sin limitación de tamaño
};

void MicroSD::MicroSD_init(void){
  while(!SD.begin(MICROSD_PIN)){//mientras no haya inicialización de pin para MSD, indicar fallo
    Serial.println(F("Fallo inicializacion de la MicroSD"));
  }
  Serial.println(F("Inicializacion de la MicroSD exitosa"));//si la inicialización de pin fue exitosa, enviar msj correspondiente por puerto serial
}// * fin de método *


void MicroSD::FileID(void){//nombrado de archivo c/ dia/mes/año.JSON
  RTC.get_time();//se manda a llamar método para obtención del tiempo en ese momento
  filename = "/";//asignación de caracter para creación de directorio raíz
  filename += RTC.dia; //agregar día
  filename += "-"; //agregar separador de dígitos
  filename += RTC.mes; //agregar mes
  filename += "-"; //agregar separador de dígitos
  filename += RTC.ano; //agregar año
  filename += EXTENSION; //agregar valor que va a determinar el tipo de archivo a almacenar
}// * fin de método *

void MicroSD::JSON(void){ //asignación de variables a campos declarados del JSON
  DynamicJsonDocument obj(1024);//creación de doc 1024 bytes para almacenamiento de mediciones
  obj["Humedad"] = sensors.humedad(); //asignación de valor obtenido de medición de humedad
  obj["Flujo"] = sensors.CDF(); //asignación de valor obtenido de medición de caudal de flujo
  int temp = sensors.temperatura(); //creación de variable para almacenar medición de temperatura ambiental
  if(temp >= 0 && temp <= 50) //si la temperatura está entre 0 y 50, entonces
    obj["Temperatura ambiental"] = temp; //guardar variables de temperatura en el JSON
  else //si no, entonces
    obj["Temperatura ambiental"] = "error"; //guardar string de error en campo de temperatura
  RTC.get_format_date(); //mandar a llamar método de formateo de fecha
  RTC.get_format_time(); //mandar a llamar método de formateo de hora
  obj["fecha"] = RTC.fecha.c_str(); //almacenamiento de fecha con función de conversión de char a string
  obj["tiempo"] = RTC.tiempo.c_str(); //almacenamiento de fecha con función de conversión de char a string
  if(bombaOn == 1){ //evaluar si la variable bandera de activación de bomba es positivo
    obj["tiempo de bomba"] = tiempoBombaOn; //almacenar variable de tiempo en momento de activación
    obj["dia de bomba"] = diaBombaOn; //almacenar variable de fecha en momento de activación
  } // * fin de ciclo *
  JSON_SaveFile(&obj); //guardar objeto en docJSON
} // * fin de método *

void MicroSD::JSON_SaveFile(DynamicJsonDocument*obj){ //almacenamiento de archivo
  FileID();
  json_string = "";
  MicroSD_File = SD.open(filename, FILE_APPEND); //función para abrir archivo de nombre provisto, o crearlo en su defecto
  if (MicroSD_File){ //si existe, entonces
    serializeJson(*obj, json_string); //serialización de documento
    MicroSD_File.print(json_string);//impresión de string obtenido del json
    MicroSD_File.println(","); 
    MicroSD_File.close(); //cierre de archivo
  } // * fin de ciclo *
}// * fin de método *
