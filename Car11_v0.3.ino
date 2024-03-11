

#include <SharpIR.h>

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 10
#define ENB 11


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


int leftdistance;
int leftdistance_old;
int leftdistance_old2;
  
int rightdistance;
int rightdistance_old;
int rightdistance_old2;

int middistance;
int middistance_old;
int middistance_old2;

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

    drive(0,0);
    
    //motorR(0);
    //motorL(0);
      
   
    
   }
  

/** -------------------START--------------------**/
  while(buttonStartPressed == true) {

     leftdistance_old2 = leftdistance_old;
     leftdistance_old = leftdistance;
     leftdistance = leftsensor.getDistance();
   // int leftdistance_old = leftdistance;
   // int leftdistance_old2 = leftdistance_old; // TODO:: ALTE MESSUNGEN SPEICHERN, MITTELWERT BERECHNEN


     rightdistance_old2 = rightdistance_old;
     rightdistance_old = rightdistance;
     rightdistance = rightsensor.getDistance();
    //int rightdistance_old = rightdistance;
    //int rightdistance_old2 = rightdistance_old; // TODO:: ALTE MESSUNGEN SPEICHERN, MITTELWERT BERECHNEN


     middistance_old2 = middistance_old;
     middistance_old = middistance; 
     middistance = midsensor.getDistance();
    //int middistance_old = middistance;
    //int middistance_old2 = middistance_old; // TODO:: ALTE MESSUNGEN SPEICHERN, MITTELWERT BERECHNEN

    float averageLeft = calculateAverage(leftdistance, leftdistance_old, leftdistance_old2);
    float averageRight = calculateAverage(rightdistance, rightdistance_old, rightdistance_old2);
    float averageMid = calculateAverage(middistance, middistance_old, middistance_old2);


    Serial.print("DRIVE");
    navigateCourse(averageLeft, averageRight, averageMid);
    //drive(255,255);
    //motorR(255);
    //motorL(255);
    
    
    Serial.print("STARTWHILE");
    Serial.println();
/*
    Serial.print(" jetzige messung: ");
    Serial.print(leftdistance);
    Serial.print(" letzte messung: ");
    Serial.print(leftdistance_old);
    Serial.print(" vorletzte messung: ");
    Serial.print(leftdistance_old2);
    Serial.println();

    Serial.print(" leftdistance: ");
    Serial.print(averageLeft );
    //Serial.print(" rightdistance: ");
    //Serial.print(averageRight);
    //Serial.print(" middistance: ");
    //Serial.print(averageMid);
   
    Serial.println();

    */


 /*
    if(rightdistance < 20){


      left(64,32);
      
      }

     else if (leftdistance < 20){

      right(32,64);
      
      }

    else{
      forward(64,64); 
      
      }
*/
    
   /*
  if(middistance < 25 ){
    // STOP
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
      
    }
    */
    
  }



    
}



/*
void motorR(int speed){
  
  if(speed < 0)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    if(speed < -255) speed = -255;  // Deckelung
    analogWrite(ENA, -speed);
  }
  else if(speed > 0)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    if(speed > +255) speed = +255;  // Deckelung
    analogWrite(ENA, speed);
  }
  else // if(speed == 0)
  {
    analogWrite(ENA, 0); // Stopp den Motor sofort
  }
  Serial.print("RIGHT");
}

void motorL(int speed){
  
  if(speed < 0)
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
   
    if(speed < -255) speed = -255;  // Deckelung
    analogWrite(ENB, -speed);
    
  }
  else if(speed > 0)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    Serial.print("LEFTFRFRFR");
    if(speed > +255) speed = +255;  // Deckelung
    analogWrite(ENB, speed);
  }
  else // if(speed == 0)
  {
    analogWrite(ENB, 0); // Stopp den Motor sofort
    
  }
  Serial.print("LEFT");
}
*/


void drive(int leftspeed, int rightspeed){
  
  if(leftspeed < 0)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Serial.println("leftback");
    if(leftspeed < -255) leftspeed = -255;  // Deckelung
      analogWrite(ENA, -leftspeed);
  }
  else if(leftspeed > 0)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Serial.println("leftforward");
    if(leftspeed > +255) leftspeed = +255;  // Deckelung
     analogWrite(ENA, leftspeed);
  }
  else // if(speed == 0)
  {
    analogWrite(ENA, 0); // Stopp den Motor sofort
  }
  
  if(rightspeed < 0)
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    //Serial.println("rightback");
    if(rightspeed < -255) rightspeed = -255;  // Deckelung
    analogWrite(ENB, -rightspeed);
    
  }
  else if(rightspeed > 0)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    //Serial.println("rightforward");
    if(rightspeed > +255) rightspeed = +255;  // Deckelung
    analogWrite(ENB, rightspeed);
  }
  else // if(speed == 0)
  {
    analogWrite(ENB, 0); // Stopp den Motor sofort
    
  }
}

/*
void left(int left, int right){
  
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, left);
    analogWrite(ENB, right);  
}
 
void right(int left, int right){
  
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, left);
    analogWrite(ENB, right);
}
*/

// TODO: fahren, geschwindigkeitregelnn

void navigateCourse(float leftDist, float rightDist, float midDist) {
  if (midDist < 25) { 
    
    if (leftDist > rightDist) {
      //turnRight();
      drive(0,255);
    } 
    else {
     // turnLeft();
      drive(255,0);
    }

  } else if (leftDist < 20) { 
    //  steerRight();
     drive(200,255);

  } else if (rightDist < 20) { // Too close to right obstacle
     // steerLeft();
     drive(255,200);
  } else {
      drive(255, 255);
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
