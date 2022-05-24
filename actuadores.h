#define rele 2 //definir pin para relay
  const byte pinBuzzer = 17; //pin para buzzer, se crea como const byte para que este envíe el pulso al buzzer
  byte salida = 10; //pin para buzzer que va de 0-255 y que en conjunto con apagarBuzzer genera oscilaciones cuadradas
  byte apagarBuzzer = 0; //pin bandera para controlar activación de buzzer 
  
class Actuadores{ //clase creada controlar (des)activación de actuadores
  public: //variables públicas

  public: //Metodos públicos
  void relayOn (void); //método para activación de relay
  void relayOff (void); //método para desactivación de relay
  void buzzer (void); //método para activación de buzzer
  void buzzerOff (void); //método para desactivación de buzzer
  void LCD_init(void); //método para inicialización de pantalla LCD
  void printLCD (void); //método para impresión de datos en pantalla LCD
};

/*~~~~~~~~~~~~~~~(DES)ACTIVACIÓN DE RELEVADOR~~~~~~~~~~~~~~~~~~~~~~*/
void Actuadores::relayOn(void){
  digitalWrite(rele,LOW);
}

void Actuadores::relayOff(void){
  digitalWrite(rele,HIGH);
}

/*~~~~~~~~~~~~~~~(DES)ACTIVACIÓN DE BUZZER~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Actuadores::buzzer (void){
  pinMode(pinBuzzer, OUTPUT);
  analogWrite(pinBuzzer, salida);
}

void Actuadores::buzzerOff (void){
  pinMode(pinBuzzer, OUTPUT);
  analogWrite(pinBuzzer, apagarBuzzer);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~LCD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Actuadores:: LCD_init(void){ //activación de luces para pantalla LCD
  lcd.init();
  lcd.backlight(); //activación de colores de fondo
}// * fin de método *

void Actuadores:: printLCD(void){ //configuración de posiciones para impresión de info en pantalla LCD
 lcd.setCursor(0,0); //posicionamiento en esquina superior izquierda
 lcd.print ("L/m: "); //impresión de caudal de flujo en dicha posición
 lcd.print (sensors.CDF()); //recuperación de medición de caudal de flujo
 lcd.setCursor(10,0); //posicionamiento cercano a esquina superior derecha
 lcd.print ("T: "); //impresión de temperatura en dicha posición
 lcd.print (sensors.temperatura()); //recuperación de medición de temperatura
 lcd.setCursor(0,1); //posicionamiento en esquina inferior izquierda
 lcd.print ("Hum: "); //impresión de humedad en dicha posición
 lcd.print (sensors.humedad()); //recuperación de medición de humedad
 
}// * fin de método *
