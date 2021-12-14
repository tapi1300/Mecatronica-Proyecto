#include <Servo.h>

const int pin_rueda_DER = 5;
const int pin_rueda_IZQ = 6;

Servo myservoD;
Servo myservoI;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //iniciar puerto serie
  myservoD.attach(pin_rueda_DER);
  myservoI.attach(pin_rueda_IZQ);
}

void loop() {

  myservoD.write(180);  // set servo to mid-point
  myservoI.write(0);  // set servo to mid-point

}
