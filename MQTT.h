class MQTT {
  
  public: //variables públicas
  
  public: //funciones públicas
    void subscribe_MQTT ( void );
    void publish_MQTT ( void );
    void reconnect_MQTT ( void );
    void setup_WiFi ( void ); 
    void set_MQTT_server ( void );
  };

void MQTT :: set_MQTT_server ( void ) {

  client.setServer ( MQTT_SERVER, MQTT_PORT );
  
}

void MQTT :: subscribe_MQTT ( void ) {

  
}

void MQTT :: publish_MQTT ( void ) {

  String hola = "....";
  Serial.println ( "Publicando información" );
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
