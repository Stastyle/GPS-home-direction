#include <Arduino.h>
#include <QMC5883LCompass.h>
#include <Servo.h> 

#define servoPin 2

int a, oldA=0;

Servo Servo1;

QMC5883LCompass compass;

void setup() {
  Serial.begin(9600);
  Servo1.attach(servoPin);   // attach the servo to the used pin number 
  compass.init();
  compass.setSmoothing(10, true);

}

int invertMove(int aa){
  int err=0;
  if (aa>90){
    err=(aa-90);
    return 90-err;
  } 
  err=(90-aa);
  return 90+err;
}

void loop() {
  compass.read();            // Read compass values
  a = compass.getAzimuth();   // Return Azimuth reading

  
  Serial.print("A: ");
  Serial.print(a);
  Serial.print(" -- ");
  Serial.println(oldA);


if ((oldA - a)>1 || (a - oldA)>1){
  if (a > 180 && a <= 270) {
    Servo1.write(180);
  } else if (a > 270 && a <= 360)
   {Servo1.write(0);
  }  else {
    Servo1.write(invertMove(a));
    Serial.print(invertMove(a));
    Serial.println(" --> Moving!");
  }
  delay(abs(oldA-a)*2);
  oldA = a;
} 


  
  delay(100);
}