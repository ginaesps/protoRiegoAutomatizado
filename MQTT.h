class MQTT {
  
  public: //variables públicas
  
  public: //funciones públicas
    void subscribe_MQTT ( void ); //función para suscripción
    void publish_MQTT ( void ); //publicación de string de caracteres generado en MSD
    void reconnect_MQTT ( void ); //revisión de conexión a servidor MQTT
    void setup_WiFi ( void ); //configuración de conexión a wifi
    void set_MQTT_server ( void );//configuración de conexión a servidor MQTT
  };

void MQTT :: set_MQTT_server ( void ) {

  client.setServer ( MQTT_SERVER, MQTT_PORT );
  
}

void MQTT :: subscribe_MQTT ( void ) {
  
  //Serial.println ( F ( "Suscribiendo a Topic" ) );
  client.subscribe( TOPIC );
}

void MQTT :: publish_MQTT ( void ) {

  //String hola = "....";
  //Serial.println ( "Publicando información" );
  client.publish( TOPIC, MSD.json_string.c_str()); //envío de info para publicación con tema y json predefinidos
  
}

void MQTT :: reconnect_MQTT ( void ) {

  if ( ! client.connected ( ) ) { 

    while ( ! client.connected ( ) ) {
      
    Serial.print ( "Conectado nuevamente al servidor" );

    if ( client.connect ( "6D/E2" ) ) {
      
      Serial.println ( "Cliente conectado" );
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  }
  client.loop();
  
}

void MQTT :: setup_WiFi ( void ) {

  delay ( 10 );
  Serial.println ( "Configurando WiFi: " );
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD );
  
  
  while ( WiFi.status ( ) != WL_CONNECTED ) {
    
    delay ( 500 );
    Serial.print ( "." );
    
  }
  
  Serial.println ( "WiFi configurado con la IP: " );
  
}


void callback(char* topic, byte* pld, unsigned int length) { //función de callback para suscripción a TOPIC, muestra info enviada por puerto serial
  Serial.print("Message arrived on topic: ");
  Serial.print(TOPIC);
  Serial.print("datos");
  String msjt;//mjs a enviar
  for (int i = 0; i < length; i++) {
    Serial.print((char)pld[i]);
    msjt += (char)pld[i];
  }
  Serial.println();
}
