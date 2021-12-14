const int sensorPin = 10;
//const int sensorPin = 11;

void setup() {
  Serial.begin(9600);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
}
 
void loop(){
  int value = 0;
  value = digitalRead(sensorPin );  //lectura digital de pin
 
  Serial.print(value);
  Serial.print("\t");
  if(value == 0)
  {
  Serial.println("Detectado obstaculo");
  }
  delay(1000);
}
