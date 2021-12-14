#include <Servo.h>

const int US_Trigger = 2;   //Pin digital 2 para el Trigger del sensor
const int US_Echo = 3;   //Pin digital 3 para el Echo del sensor
const int pin_rueda_DER = 5;
const int pin_rueda_IZQ = 6;
const int IR_IZQ = 11;
const int IR_DER = 10;

long time_eco; //timepo que demora en llegar el eco
long dist; //distancia en centimetros

Servo myservoD;
Servo myservoI;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //iniciar puerto serie
  myservoD.attach(pin_rueda_DER);
  myservoI.attach(pin_rueda_IZQ);

  pinMode(pin_rueda_DER,OUTPUT);
  pinMode(pin_rueda_IZQ,OUTPUT);
  pinMode(IR_IZQ , INPUT);  //definir pin como entrada
  pinMode(IR_DER , INPUT);  //definir pin como entrada

  pinMode(US_Trigger, OUTPUT); //pin como salida
  pinMode(US_Echo, INPUT);  //pin como entrada
  digitalWrite(US_Trigger, LOW);//Inicializamos el pin con 0

}

void loop() {

  int vel = 1;

  int value_izq = 0;
  int value_der = 0;
  value_izq = digitalRead(IR_IZQ);  //lectura digital de pin
  value_der = digitalRead(IR_DER);  //lectura digital de pin

  // ULTRASONIDO
  digitalWrite(US_Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(US_Trigger, LOW);
  
  time_eco = pulseIn(US_Echo, HIGH); //obtenemos el ancho del pulso
  dist = time_eco/59;             //

  int free_path = 1;
  if(dist < 11)
  {
    free_path = 0;
  }

  // SI HAY COLOR NEGRO EN LOS INFRARROJOS PARAMOS
  if(value_izq == 0 || value_der == 0)
  {
    myservoD.write(90);  // set servo to mid-point
    myservoI.write(90);  // set servo to mid-point
  }
  // SI NO, NOS MOVEMOS
  else if(value_izq == 1 && value_der == 1)
  {
    // SI HAY OBSTACULO ATACAMOS
    if(free_path == 0) // HAY OBSTACULO
    {
      Serial.print("Distancia: ");
      Serial.print(dist);      //Enviamos serialmente el valor de la distancia
      Serial.print("cm");
      Serial.println();
      myservoD.write(180);  // set servo to mid-point
      myservoI.write(0);  // set servo to mid-point
    }
    // SI NO, NOS MOVEMOS TRANQUILOS
    else{
      myservoD.write(110);  // set servo to mid-point
      myservoI.write(70);  // set servo to mid-point
    }
  }
}
