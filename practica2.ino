#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

//Definiciones
char entry[6] = {'2','0','2','1','1','1'};
int key_counter = 0;
bool error = false;

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

void setup() {
  Serial1.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  if(key_counter<6){
    char key = keypad.getKey();
    if(key != NO_KEY){
      if(entry[key_counter]!=key){error=true;}
      Serial1.println(key);  
      key_counter++;
    } 
  }else{
    if(error){
      digitalWrite(9, HIGH);  
      key_counter = 0;
      error=false;
    }else{
      digitalWrite(4, HIGH);
    }
    delay(2000);
    digitalWrite(9, LOW);
    digitalWrite(4, LOW);
  }
  
}

int getFreeIndex(){
  for(int i = 0; i<5; i++){
    if(entry[i]== 'x'){
      return i;  
    }
  }  
  return 'n';
}
