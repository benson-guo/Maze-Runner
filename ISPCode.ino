#include <Servo.h>
//Traffic light/ Pedestrian
int trafficLightState;
int red1 = 13; //
int yellow1 = 12;
int green1 = 11;
int red2 = 10;
int yellow2= 9;
int green2 = 8;

//IR Sensor
int irSensorState = 0;
int analogIRRead = 1;
int limit = 975;

// Motor
int trafficGateState = 90;
boolean forward = false;
int motor = 6;
int motorPower = 5;
int count = 0;
int count2;

Servo myservo;

//Light detector
int analogLightRead = A0;

// Lamps
int lamp1 = 4; // Controlled by light detector
int lamp2 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(red1,OUTPUT);
  pinMode(yellow1,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(yellow2,OUTPUT);
  pinMode(green2,OUTPUT);
  
  pinMode(motorPower,OUTPUT);
  digitalWrite(motorPower,HIGH);
  myservo.attach(motor);
  myservo.write(trafficLightState); // InitialState 
  
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  trafficLight();
  trafficGate();
  lightDetector();
  delay(5);
}

void trafficLight() { // 6 second loop
  if (trafficLightState <= 200) {
    digitalWrite(green1,HIGH);
    digitalWrite(red1,LOW);
    
    digitalWrite(yellow2,LOW);
    digitalWrite(red2,HIGH);
  } else if (trafficLightState <= 300) {
    digitalWrite(green1,LOW);
    digitalWrite(yellow1,HIGH);
  } else if (trafficLightState <= 500) {
    digitalWrite(yellow1,LOW);
    digitalWrite(red1,HIGH);
    
    digitalWrite(green2,HIGH);
    digitalWrite(red2,LOW);
  } else if (trafficLightState <= 600) {
    
    digitalWrite(green2,LOW);
    digitalWrite(yellow2,HIGH);
  }
  else { // trafficLightState > 6000
   trafficLightState = 0;
  }
  
  
 trafficLightState++;
}

void trafficGate() {
      myservo.write(trafficGateState);
  int val = analogRead(analogIRRead);
  Serial.println(val);
  /*
  Serial.println(trafficGateState);
  Serial.println(count);
  Serial.println(forward);
  Serial.println("_");
  */
  
   if (trafficGateState <= 0 && forward)
  {
    if (val < limit)
    {
    if (count2 < 6)
        count2++;
      else {
     forward = false; 
        count2 =0;
      }
    }
    else
    count2 = 0;
  }
  
    if (trafficGateState != 90)
  {
    if (forward && trafficGateState > 0)
      trafficGateState--; 
    else
    {
        trafficGateState++;
      
    }
    return;
  }
  

  if (val >= limit && trafficGateState == 90 && !forward)
  {
     if (count < 15)
     {
       count++;
   }
     else {
        forward = true;
        trafficGateState = 89;
        count = 0;
     } 
  }

  /*
  int count = 0;
  int val = analogRead(irRead);
  Serial.println(val);
  if (val <= limit && pos == 90)  {
    if (count >= 15)
    {
      count = 0;
      
    digitalWrite(13,LOW);   
    for(pos = 90; pos>=1; pos-=1)     // goes from 90 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(5);                       // waits 15ms for the servo to reach the position 
    } 
    }
    else
    {
       count++; 
    }
  }
  else if (val > limit && pos == 0)  {
    digitalWrite(13,HIGH);
      for(pos = 0; pos < 90; pos += 1)  // goes from 0 degrees to 90 degrees 
      {                                  // in steps of 1 degree 
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(5);                       // waits 15ms for the servo to reach the position 
      }    
  }
  */
}

void lightDetector() {
  int LDRReading = analogRead(analogLightRead);
  if (LDRReading < 10) {
    digitalWrite(4,HIGH);
  } else {
    digitalWrite(4,LOW);
  }
}
