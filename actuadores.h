#define rele 2
  const byte pinBuzzer = 17;
  byte salida = 10; 
  byte apagarBuzzer = 0; 
  
class Actuadores{
  public:
  //Metodos de los actuadores
  void relayOn (void);
  void relayOff (void);
  void buzzer (void);
  void buzzerOff (void);
  void LCD_init(void);
  void printLCD (void);
};

/*--------------- Funciones del relevador ON/OFF -----------------*/
void Actuadores::relayOn(void){
  digitalWrite(rele,LOW);
}

void Actuadores::relayOff(void){
  digitalWrite(rele,HIGH);
}
/*----------------------------------------------------------------*/

void Actuadores::buzzer (void){
  pinMode(pinBuzzer, OUTPUT);
  analogWrite(pinBuzzer, salida);
}

void Actuadores::buzzerOff (void){
  pinMode(pinBuzzer, OUTPUT);
  analogWrite(pinBuzzer, apagarBuzzer);
}

/*--------------------------Funciones para LCD--------------------*/
void Actuadores:: LCD_init(void){
  lcd.init();
  lcd.backlight();
}

void Actuadores:: printLCD(void){
 lcd.setCursor(0,0);
 lcd.print ("L/m: ");
 lcd.print (sensors.CDF());
}
/*-----------------------------------------------------------------*/
