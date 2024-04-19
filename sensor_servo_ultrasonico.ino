#include <Servo.h>
int cm=0;
long distancia,duracion;
int posicion1=90;
int posicion2=-90;
int led=10;
Servo miServo;
#define Pecho 3 //Echo al pin 6
#define Ptrig 2 //Trig pin 7


void setup() {
  Serial.begin (9600);  
 pinMode(Pecho, INPUT);  
 pinMode(Ptrig, OUTPUT);
 pinMode(led, OUTPUT);
 miServo.attach (9);        

}

void loop() {
 
  digitalWrite (Ptrig,LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig,HIGH);
  delayMicroseconds(100);
  digitalWrite(Ptrig,LOW);

  duracion= pulseIn(Pecho, HIGH);
  distancia =(duracion/2)/29;
  Serial.println(distancia);    

  if (distancia >=60 || distancia <=0){  
    Serial.println("---");      
  }
  else {
    Serial.print(distancia);              
    Serial.println("cm");                  
    digitalWrite(10,LOW);                    
  }

  if (distancia <=10 && distancia >=1){
    digitalWrite(led,HIGH);
    delay(500); 
    miServo.write(posicion1);              
    Serial.println("hay un obstaculo");
    delay(2000);
    digitalWrite(led,LOW);
    miServo.write(posicion2); 
  } 
  else
  {
    delay(500);
    miServo.write(posicion2);
    
  }
  delay(300);      
 
}