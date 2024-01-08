#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define IR_SENSOR A0
#define SERVO 10
#define BUTTON_STOP_PIN 2  
#define BUTTON_START_PIN 3

#define MOTOR_STOP      0
#define MOTOR_START     1
#define MOTOR_FORWARD   2
#define MOTOR_BACKWARD  3
#define MOTOR_LEFT      4
#define MOTOR_RIGHT     5

volatile int state;



void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);  
  pinMode(BUTTON_START_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(BUTTON_STOP_PIN), buttonStopInterrupt, FALLING); 
  attachInterrupt(digitalPinToInterrupt(BUTTON_START_PIN), buttonStartInterrupt, FALLING); 
  
  
  digitalWrite(13, HIGH);


  Serial.println("Serial.println(Hallo);");
}

void loop() {
  Serial.println(state);
  switch (state){
    
    case MOTOR_STOP:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);    
      
      break;
    case MOTOR_START:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);

      break;
    case MOTOR_FORWARD:
  /*                                      REMOVE COMMENT WHEN SENSOR IMPLEMENTEDED
    if(sensorDistance >= 30)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);    
    }
    */
      break;
    case MOTOR_BACKWARD:

      break;
    case MOTOR_LEFT:

      break;
    case MOTOR_RIGHT:

      break;
      
    }
/*                                          START/STOP WITHOUT INTERRUPT
  if(digitalRead(BUTTON_STOP_PIN) == LOW)
  {
    Serial.println("STOPPRESSED");
    state = MOTOR_STOP;
  }

  if (digitalRead(BUTTON_START_PIN) == LOW)
  {
    Serial.println("STARTPRESSED");
    state = MOTOR_START;
  }

*/

}

void buttonStartInterrupt(){

  Serial.println("STARTINTERRUPT");
  state = MOTOR_START;
}


void buttonStopInterrupt() {

  Serial.println("STOPINTERRUPT");
  state = MOTOR_STOP;
}






  
