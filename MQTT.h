class MQTT { //clase creada para administrar todas las funciones que puedes realizar mediante MQTT
  
  public: //variables públicas
  
  public: //métodos públicos
    void subscribe_MQTT ( void ); //suscripción de topics
    void publish_MQTT ( void ); //publicación de string de caracteres generado en MSD
    void reconnect_MQTT ( void ); //revisión de conexión a servidor MQTT
    void setup_WiFi ( void ); //configuración de conexión a wifi
    void set_MQTT_server ( void );//configuración de conexión a servidor MQTT
  };

void MQTT :: set_MQTT_server ( void ) { //método para asignación de parámetros de servidor a cliente

  client.setServer ( MQTT_SERVER, MQTT_PORT ); //asignaación de servidor y puerto de funcionamiento al cliente
  
}

void MQTT :: subscribe_MQTT ( void ) {
  
}

void MQTT :: publish_MQTT ( void ) { //método de asignación de tema y cuerpo de mensaje a publicar

  client.publish( TOPIC, MSD.json_string.c_str()); //envío de info para publicación con tema y json predefinidos
  
}

void MQTT :: reconnect_MQTT ( void ) { //método para evaluación de estado de conexión a red

  if ( ! client.connected ( ) ) { //si el cliente no está conectado, entonces

    while ( ! client.connected ( ) ) { //mientras el cliente no esté conectado
      
    Serial.print ( "Conectado nuevamente al servidor" ); //indicar mediante puerto serial reconexión

    if ( client.connect ( "6D/E2" ) ) { //si el cliente se conecta exitosamente, enviar nombre
      
      Serial.println ( "Cliente conectado" ); //imprimir en conexión serial conexión exitosa
      client.subscribe("Test_6D"); //suscripción de cliente a topic
      
    } else { //si la conexión no fue exitosa, entonces
      Serial.print("failed, rc="); //impresión de estado de fallo
      Serial.print(client.state()); //e impresión de número de error MQTT
      Serial.println(" try again in 5 seconds"); //impresión de delay
      delay(5000);//detención del programa por 5s
    }
  }
  }
  client.loop(); //repetición de sentencias hasta que el cliente se conecte exitosamente
  
}// * fin de método *

void MQTT :: setup_WiFi ( void ) { //método para configuración de red

  delay ( 10 ); //cada 10s realizar las siguientes sentencias
  Serial.println ( "Configurando WiFi: " ); //impresión de datos de red
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD ); //inicialización y asignación de SSID y password
  
  
  while ( WiFi.status ( ) != WL_CONNECTED ) { //evaluar que mientras el estado de conexión no exista
    
    delay ( 500 ); // cada medio segundo
    Serial.print ( "." ); //imprimir un punto para simular que está cargando
    
  }
  
  Serial.println ( "WiFi configurado con la IP: " ); //cuando se logre conectar, hacerlo saber mediante puerto serial
  
}// * fin de método *


void callback(char* topic, byte* pld, unsigned int length) { //función de callback para suscripción a TOPIC, muestra info enviada por puerto serial
  Serial.print("Message arrived on topic: ");//hacer saber que un mensaje llegó en determinado TOPIC
  Serial.print(TOPIC);//impresión de TOPIC
  Serial.print("datos");//a partir de aquí se imprimen los datos recibidos
  String msjt;//mjs a enviar
  for (int i = 0; i < length; i++) { //ciclo para unir todos los caracteres recibidos del payload
    Serial.print((char)pld[i]);
    msjt += (char)pld[i];
  }
  Serial.println();
}
