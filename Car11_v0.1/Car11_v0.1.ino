#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ECHO 9
#define TRIGGER 8
#define SERVO 10
#define BUTTON_STOP_PIN 2  
#define BUTTON_START_PIN 3

volatile bool buttonStopPressed = false;
volatile bool buttonStartPressed = false;


float ultrasonicDistance()
{
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  
  long duration = pulseIn(ECHO, HIGH);
  
  float distance_cm = duration * 0.0343 / 2.0;

  return distance_cm;
}


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(BUTTON_STOP_PIN, INPUT_PULLUP);  
  pinMode(BUTTON_START_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_STOP_PIN), buttonStopInterrupt, FALLING); 
  attachInterrupt(digitalPinToInterrupt(BUTTON_START_PIN), buttonStartInterrupt, FALLING); 
  
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  Serial.println("Hallo");
}

void loop() {

  
  if(buttonStartPressed) {
    // FORWARD
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);



    buttonStartPressed = false;
  }

  if(buttonStopPressed){
    //    STOP
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
      
    buttonStopPressed = false;
    
    }
    float ultradistance = ultrasonicDistance();
    Serial.println(ultradistance);
    if(ultradistance <= 25)
    {
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
      
    }
    else  
    {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
      
    }



  
}

void buttonStartInterrupt(){

  Serial.println("STARTINTERRUPT");
  buttonStartPressed = true;
}


void buttonStopInterrupt() {

  Serial.println("STOPINTERRUPT");
  buttonStopPressed = true;
}
