#define trigPin 13 // Wire to Trig
#define echoPin 12 // Wire to ECHO
#define STEP 11 // Wire to STEP
#define DIR 8 //Wire to DIR
#define START 5 //Wire to START Pushbutton or DAQ 
#define STOP 6 // Wire to STOP Pushbutton or DAQ
#define SOLENOID 7 //Wire to Solenoid or DAQ
#define lightPin 0 // Wire to Photo resistor


int Distance = 0;  // Record the number of steps we've taken
boolean running = true;
boolean reverse = false;
boolean objectDetected = false;
void RunMotor(); 
boolean photoSensor();
int SonarLength();
int Max = 100;
int Min = 10;
int speed = 500;

void setup() // Sets up inputs and outputs
{                
  Serial.begin(9600);
  pinMode(STEP, OUTPUT);     
  pinMode(DIR, OUTPUT);
  pinMode(START,INPUT);//START
  pinMode(3, INPUT);//FORWARD
  pinMode(4, INPUT);//BACKWARD
  pinMode(STOP, INPUT);//STOP
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(SOLENOID,OUTPUT);
  pinMode(lightPin, INPUT);
 
  
  //Inital Settings
  digitalWrite(STEP,LOW);
  digitalWrite(DIR, LOW);
  digitalWrite(7,LOW);
  
}

void loop() 
{
  //speed = analogRead(A1);
  objectDetected = photoSensor();
 
  if (objectDetected == false)
  {
    digitalWrite(SOLENOID,LOW);
  }
  else 
  {
    digitalWrite(SOLENOID,HIGH);
  }
  if (digitalRead(START)== HIGH)
  {
    running = true;
  } 
  else
  {
    running = false;
  }
  
  if (running == true)
  {
   
    RunMotor();
  }
  else
  {
    
  }
   
}

int SonarLength()
{
  int l, duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH); //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  l = (duration/2) / 29.1;
  return(l);
}

void RunMotor()
{
 digitalWrite(STEP, HIGH);
 delayMicroseconds(speed);          
 digitalWrite(STEP,LOW); 
 delayMicroseconds(speed);
}  

boolean photoSensor()
{
   Serial.println(analogRead(A1)); //Write the value of the photoresistor to the serial monitor.
    if (analogRead(lightPin) <= 500)
    {
      return(false);
    }
    else
    {
      return(true);
    }
    
}

