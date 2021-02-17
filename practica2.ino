#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

//Definiciones
char entry[6] = {'2','0','2','1','1','1'};
int key_counter = 0;
int error_counter = 0;
bool error = false;
bool rotated = false;
int distance;
/*ALARMA*/
int alarm = 5;

/*ULTRASONICO*/
int ultrasonic = 11;

/*SERVOMOTOR*/
//Pin del servomotor
int servo = 10;

//Posicion del servomotor
int servoPosition = 0;

//Instancia de la libreria 
Servo servomotor;

/*KEYPAD*/
// Se definen las filas y columnas del Keypad
const byte ROWS = 4;
const byte COLUMNS = 3;

//Definimos la estructura del keypad
char keys[ROWS][COLUMNS] ={
  '1','2','3',
  '4','5','6',
  '7','8','9',
  '*','0','#'
};

// Estructura de pines que van conectados al keypad
byte rowPins[ROWS] = {23,25,27,29};
byte columnPins[COLUMNS] = {49,51,53};
//Teclado
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, ROWS, COLUMNS);

/*PANTALLA LCD*/
const int rs = 13, en = 12, d4 = 39,
d5 = 37, d6 = 35, d7 = 33;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial1.begin(9600);
  pinMode(alarm,OUTPUT);
  servomotor.attach(servo);
  lcd.begin(16,2);
}

void loop() {/*
  lcd.clear();
  distance = 0.01723 * readUltrasonicDistance(ultrasonic, ultrasonic);
  if(distance<150){
    passwordMessage();
    ingresarPassword();
  }else{
   writeInitialMessage();
  }
  delay(400);*/
  ingresarPassword();
}

void writeInitialMessage(){
  lcd.print("CASA INTELIGENTE");
  //setCursor(x, y);
  lcd.setCursor(0,1);
  lcd.print("ACE1"); 
  delay(3000);
  lcd.setCursor(0,0); 
  lcd.clear();
  lcd.print("ACE1-A-G11-S1");
  delay(3000);
  lcd.setCursor(0,0); 
}

void welcomeMessage(){
  lcd.print("BIENVENIDO A");
  lcd.setCursor(0,1);
  lcd.print("CASA");
  delay(3000);
  lcd.setCursor(0,0); 
}

void errorMessage(){
  lcd.print("ERROR EN"); 
  lcd.setCursor(0,1); 
  lcd.print("CONTRASEA");
  
  delay(3000);
  lcd.setCursor(0,0); 
}

void alarmMessage(){
  lcd.print("ACCESO NO");
  lcd.setCursor(0,1); 
  lcd.print("AUTORIZADO");
  delay(3000);
  lcd.setCursor(0,0);
}

void passwordMessage(){
   lcd.print("INGRESE SU");
   lcd.setCursor(0,1);
   lcd.print("CONTRASENIA");
   delay(3000);
   lcd.setCursor(0,0); 
}

void ingresarPassword(){
   if(key_counter<6){
    char key = keypad.getKey();
    if(key != NO_KEY){
      if(entry[key_counter]!=key){error=true;}
      Serial1.print(key);  
      key_counter++;
    } 
  }else{
    if(error){
      if(error_counter<2){
        errorMessage();
        key_counter = 0;
        error=false;
        error_counter++;
      }else{
        digitalWrite(alarm, (millis() / 100) % 2); 
        alarmMessage();
      }
    }else{
      if(!rotated){
        welcomeMessage();
        girarServomotor();
      }
      error_counter = 0;
    }
    Serial1.println("\n");
    lcd.clear();
  }
}

void girarServomotor(){
  for(servoPosition = 0; servoPosition<90;servoPosition++){
    servomotor.write(servoPosition);
    delay(50);
  }  
  delay(1000);
  for(servoPosition = 90; servoPosition>=0;servoPosition--){
    servomotor.write(servoPosition);
    delay(50);
  }
  delay(1000);
  rotated = true;
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
