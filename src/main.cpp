#include <Arduino.h>
#include <Servo.h>
#include <math.h>

int Serv1 = 3;
float a = 5.12;
float b = 5.32;
;
double angle;

Servo serv;

void setup() {
  serv.attach(Serv1);
 
}

void loop() {
  for(float x = 4; x<=8; x+=.1){
  angle = acos((sq(a)+sq(b)-sq(x))/(2*a*b));
  angle =  angle * 180 / 3.14;
  serv.write(angle);
  delay(100);
  }
}
