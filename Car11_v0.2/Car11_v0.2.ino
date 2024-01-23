

#include <SharpIR.h>

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 9
#define ENB 10

#define IR_LEFT A0

#define IR_MIDDLE A2
#define IR_MIDDLE_MODEL GP2Y0A02YK0F

#define IR_RIGHT A1
#define IR_SIDE_MODEL GP2Y0A21YK0F


#define BUTTON_STOP_PIN 2  
#define BUTTON_START_PIN 3

volatile bool buttonStopPressed = false;
volatile bool buttonStartPressed = false;

SharpIR leftsensor(SharpIR::IR_SIDE_MODEL, IR_LEFT);
SharpIR rightsensor(SharpIR::IR_SIDE_MODEL, IR_RIGHT);
SharpIR midsensor(SharpIR::IR_MIDDLE_MODEL, IR_MIDDLE);


float calculateAverage(int sensor1, int sensor2, int sensor3) {
    return (sensor1 + sensor2 + sensor3) / 3.0;
}


  



void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(13, OUTPUT);

  
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);  
  pinMode(BUTTON_START_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_STOP_PIN), buttonStopInterrupt, FALLING); 
  attachInterrupt(digitalPinToInterrupt(BUTTON_START_PIN), buttonStartInterrupt, FALLING); 
  
  digitalWrite(13, HIGH);
  Serial.begin(115200);
  Serial.println("Hallo");
}

void loop() {
/** ----------------------STOP--------------------**/
  while(buttonStopPressed == true){

    Serial.print("STOPWHILE");
    Serial.println();

 
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
      
   
    
   }
  

/** -------------------START--------------------**/
  while(buttonStartPressed == true) {

    int leftdistance_old2 = leftdistance_old;
    int leftdistance_old = leftdistance;
    int leftdistance = leftsensor.getDistance();
    //int leftdistance_old = leftdistance;
    //int leftdistance_old2 = leftdistance_old; TODO:: ALTE MESSUNGEN SPEICHERN, MITTELWERT BERECHNEN


    int rightdistance_old2 = rightdistance_old;
    int rightdistance_old = rightdistance;
    int rightdistance = rightsensor.getDistance();
    

    int middistance_old2 = middistance_old;
    int middistance_old = middistance; 
    int middistance = midsensor.getDistance();

    float averageLeft = calculateAverage(leftdistance, leftdistance_old, leftdistance_old2);
    float averageRight = calculateAverage(rightdistance, rightdistance_old, rightdistance_old2);
    float averageMid = calculateAverage(middistance, middistance_old, middistance_old2);

    
    
    Serial.print("STARTWHILE");


    Serial.print(" leftdistance: ");
    Serial.print(averageLeft );
    Serial.print(" rightdistance: ");
    Serial.print(averageRight);
    Serial.print(" middistance: ");
    Serial.print(averageMid);
    Serial.println();
/*
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    Serial.print("FAHRENNNNNNNNNNNNNNNNNNN");
    
*/    

   /*
  if(middistance < 25 ){
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
      
    }
*/
    
  }



    
}

void buttonStartInterrupt(){

  Serial.println("STARTINTERRUPT");
  buttonStartPressed = true;
  buttonStopPressed = false;
  
}


void buttonStopInterrupt() {

  Serial.println("STOPINTERRUPT");
  buttonStopPressed = true;
    buttonStartPressed = false;

}
