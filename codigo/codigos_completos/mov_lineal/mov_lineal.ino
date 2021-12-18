#include <Servo.h>

const int US_Trigger = 2;
const int US_Echo = 3;
const int pin_rueda_DER = 5;
const int pin_rueda_IZQ = 6;
const int IR_IZQ = 11;
const int IR_DER = 10;

long time_eco;
long dist;

Servo myservoD;
Servo myservoI;


void setup() {
  Serial.begin(9600);
  myservoD.attach(pin_rueda_DER);
  myservoI.attach(pin_rueda_IZQ);

  pinMode(pin_rueda_DER,OUTPUT);
  pinMode(pin_rueda_IZQ,OUTPUT);
  pinMode(IR_IZQ , INPUT);
  pinMode(IR_DER , INPUT);

  pinMode(US_Trigger, OUTPUT);
  pinMode(US_Echo, INPUT);
  digitalWrite(US_Trigger, LOW);

}

void loop() {

  int vel = 1;

  int value_izq = 0;
  int value_der = 0;
  value_izq = digitalRead(IR_IZQ);
  value_der = digitalRead(IR_DER);

  // ULTRASONIDO
  digitalWrite(US_Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_Trigger, LOW);
  
  time_eco = pulseIn(US_Echo, HIGH);
  dist = time_eco/59;

  int free_path = 1;
  if(dist < 11)
  {
    free_path = 0;
  }

  // SI HAY COLOR NEGRO EN LOS INFRARROJOS PARAMOS
  if(value_izq == 0 || value_der == 0)
  {
    myservoD.write(90);
    myservoI.write(90);
  }
  // SI NO, NOS MOVEMOS
  else if(value_izq == 1 && value_der == 1)
  {
    // SI HAY OBSTACULO ATACAMOS
    if(free_path == 0) // HAY OBSTACULO
    {
      Serial.print("Distancia: ");
      Serial.print(dist);
      Serial.print("cm");
      Serial.println();
      myservoD.write(180);
      myservoI.write(0);
    }
    // SI NO, NOS MOVEMOS TRANQUILOS
    else{
      myservoD.write(110);
      myservoI.write(70);
    }
  }
}
