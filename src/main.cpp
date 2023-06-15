#include <Arduino.h>
#include <Servo.h>
#include <math.h>

int kneePin = 3;
int hipPin = 5;

int smooth;
int prev =0;

float a = 2.67;
float b = 2.67;
float c;

double angle;

Servo knee;
Servo hip;

int xPin = A0;
int ypin = A1;

int x;
int y;

int sample = 20;
int minChange = 10;

int prevX;
int prevY;

double kneeAngle(float a,float b, float c){

  
  double angle = sq(a)+sq(b)-sq(c);
  angle = angle/(2*a*b);
  angle = acos(angle)*180/PI;

  return angle;
}


//Angle for hip given a=b
double hipAngle(double c, double x){
  double angle = atan(x/c);
  angle = angle*180/PI;
  return angle;
}


void setup() {
  knee.attach(kneePin);
  hip.attach(hipPin);

  pinMode(xPin,INPUT);
  pinMode(ypin,INPUT);
  knee.write(0);
  hip.write(0);

  Serial.begin(9600);


}


void loop() {
  x = analogRead(xPin);
  y= analogRead(ypin);
  // Serial.print("X: ");
  // Serial.print(x);
  // Serial.print("  Y: ");
  //   Serial.println(y);

    for(int i =0; i<=sample; i++){
         x += analogRead(xPin);
         y += analogRead(ypin);

    }
    x = x/sample;
    y = y/sample;

    if(abs(x-prevX)>minChange){       
        prevX =x;
    }
if(abs(y-prevY)>minChange){     
      prevY=y;
      c = prevY*.0048;
    }

    Serial.println(kneeAngle(a,b,c));
    

    knee.write(kneeAngle(a,b,c));
    hip.write(hipAngle(c,prevX*.0048));
    
    
  delay(100);

   
}

