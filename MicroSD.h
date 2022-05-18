class MicroSD{
  public:
    String filename = "", json_string = ""; //json_string contiene info a publicar en MQTT
    
  public:
  void MicroSD_init (void);
  void FileID (void); //nombreArchivo almacenado en MicroSD
  void JSON (void); //función para crear JSON
  void JSON_SaveFile (DynamicJsonDocument*); //puntero a docJSON para almacenamiento sin limitación de tamaño
};

void MicroSD::MicroSD_init(void){
  while(!SD.begin(MICROSD_PIN)){//mientras no haya inicialización de pin para MSD, indicar fallo
    Serial.println(F("Fallo inicializacion de la MicroSD"));
  }
  Serial.println(F("Inicializacion de la MicroSD exitosa"));
}

void MicroSD::FileID(void){//nombrado de archivo c/ dia/mes/año.JSON
  RTC.get_time();
  filename = "/";
  //if (RTC.dia < 10) filename += "0"; //filename 0 filename + "0"
  filename += RTC.dia;
  filename += "-";
  //if (RTC.mes < 10) filename += "0"; //filename 0 filename + "0"
  filename += RTC.mes;
  filename += "-";
  filename += RTC.ano;
  filename += EXTENSION;
}

void MicroSD::JSON(void){
  DynamicJsonDocument obj(1024);//creación de doc para almacenamiento de mediciones
  obj["Humedad"] = sensors.humedad();
  obj["Flujo"] = sensors.CDF();
  obj["Temperatura ambiental"] = sensors.temperatura();
  RTC.get_format_date();
  RTC.get_format_time();
  obj["fecha"] = RTC.fecha.c_str();
  obj["tiempo"] = RTC.tiempo.c_str();
  JSON_SaveFile(&obj); //guardar objeto en docJSON
}

void MicroSD::JSON_SaveFile(DynamicJsonDocument*obj){
  FileID();
  json_string = "";
  MicroSD_File = SD.open(filename, FILE_APPEND);
  if (MicroSD_File){
    serializeJson(*obj, json_string);
    MicroSD_File.print(json_string);
    MicroSD_File.println(",");
    MicroSD_File.close();
  }
}
