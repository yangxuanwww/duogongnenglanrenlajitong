#include <Servo.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>


#define humanHotSensor 2//PIR传感器D4
#define SERVOPIN SDA//舵机
#define servo_pin SDA

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created
int pos = 0;    // variable to store the servo position
bool humanHotState = true;
void setup()
{
  myservo.attach(servo_pin); 
 Serial.begin(9600);
 pinMode(humanHotSensor, INPUT);// attaches t     he servo on pin SDA to the servo object
 
  
}
void loop()
{
  humanHotState = digitalRead(humanHotSensor);
 if (humanHotState) {

    Serial.println("ok");
    for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
    { // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(0.1);                       // waits 15ms for the servo to reach the position
    }
    delay(3000);
   for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  
}
  else
  {Serial.println("err"); }

}


