#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

String humanoid_robot ;    
Adafruit_PWMServoDriver humanoid = Adafruit_PWMServoDriver();

#define servoMIN 150  //min pulse of servos
#define servoMAX 600  //max pulse of servos

int angleToPulse(int ang)
{
   int pulse = map(ang,0, 180, servoMIN,servoMAX); 
   return pulse;
}

void setup() 
{
  humanoid.begin();
  Serial.begin(9600);
  humanoid.setPWMFreq(60);
  pinMode(LED_BUILTIN, OUTPUT);
  home();
}

void loop() 
{
  if (Serial.available() > 0) 
  {
    humanoid_robot = Serial.readStringUntil('\n');

    if (humanoid_robot == "greetings") 
    {
      right_arm_greetings();
      delay(500);
      home();
      //digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("Led on");
    }
    
    else if (humanoid_robot == "welcome") 
    {
      left_arm_motion();
      delay(500);
      home();
      //digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("Led on");
    }
    
    else if (humanoid_robot == "dance") 
    {
      both_hands();
      delay(500);
      home();
      //digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("Led on");
    }

    else
    {
     Serial.write("invald input");
    }
  }
}

void home()
{
  humanoid.setPWM(4, 0, angleToPulse(180)); // right shoulder
  delay(1000);
  humanoid.setPWM(5, 0, angleToPulse(160)); // right elbow
  delay(1000);
  humanoid.setPWM(6, 0, angleToPulse(90)); // right wrist
  delay(1000);
  humanoid.setPWM(8, 0, angleToPulse(0)); // left shoulder
  delay(1000);
  humanoid.setPWM(10, 0, angleToPulse(90)); // left wrist
  delay(1000);
  humanoid.setPWM(9, 0, angleToPulse(20)); // left elbow
  delay(1000);
}

void right_arm_greetings() 
{
 const int shoulderPin = 4;
 const int elbowPin = 5;
 const int wristPin = 6;

 // Move shoulder in steps of 10 from 180 to 0
 for (int pulse = angleToPulse(180); pulse >= angleToPulse(0); pulse -= 25) 
 {
   humanoid.setPWM(shoulderPin, 0, pulse);
   delay(100); // Adjust delay as needed for smooth movement
 }

 // Move elbow in steps of 5 from 160 to 120
 for (int pulse = angleToPulse(160); pulse >= angleToPulse(120); pulse -= 10) 
 {
   humanoid.setPWM(elbowPin, 0, pulse);
   delay(100); // Adjust delay as needed for smooth movement
 }

 // Existing wrist loop (unchanged)
 for (int i = 0; i < 3; ++i) 
 {
   humanoid.setPWM(wristPin, 0, angleToPulse(180));
   delay(1000);
   humanoid.setPWM(wristPin, 0, angleToPulse(90));
   delay(1000);
 }
}

void left_arm_motion() 
{
 // Constants for readability and easier modification
 const int shoulderPin = 8;
 const int elbowPin = 9;
 const int wristPin = 10;

 // Iterate through angles for shoulder and elbow
 for (int angle = 0; angle <= 90; angle += 10) 
 {
   humanoid.setPWM(shoulderPin, 0, angleToPulse(angle));
   delay(100); // Adjust delay as needed
 }

 for (int angle = 20; angle <= 60; angle += 5) 
 {
   humanoid.setPWM(elbowPin, 0, angleToPulse(angle));
   delay(100); // Adjust delay as needed
 }

 // Move wrist
 for (int i = 0; i < 3; ++i) 
 {
   humanoid.setPWM(wristPin, 0, angleToPulse(90));
   delay(1000);
   humanoid.setPWM(wristPin, 0, angleToPulse(0));
   delay(1000);
 }
humanoid.setPWM(wristPin, 0, angleToPulse(90));
delay(1000);
}

void both_hands()
{
  // Move shoulder in steps of 10 from 180 to 0
 for (int pulse = angleToPulse(180); pulse >= angleToPulse(0); pulse -= 25) 
 {
   humanoid.setPWM(4, 0, pulse); //right shoulder pin @ 4
   delay(100); // Adjust delay as needed for smooth movement
 }

  // Iterate through angles for shoulder and elbow
 for (int angle = 0; angle <= 180; angle += 10) 
 {
   humanoid.setPWM(8, 0, angleToPulse(angle)); //left shoulder pin @ 8
   delay(100); // Adjust delay as needed
 }

  for (int i = 0; i < 3; ++i) 
  {
    // Move arm (shoulder)
    humanoid.setPWM(6, 0, angleToPulse(180));
    delay(1000);
    humanoid.setPWM(6, 0, angleToPulse(90));

    // Move wrist simultaneously with arm movement (appears synchronous)
    humanoid.setPWM(10, 0, angleToPulse(90));
    delay(1000);
    humanoid.setPWM(10, 0, angleToPulse(0));
    delay(1000);
  }
  // Set final wrist position after arm movement is complete
  humanoid.setPWM(10, 0, angleToPulse(90));
  delay(1000);
}
