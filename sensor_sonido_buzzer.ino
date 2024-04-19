const int pinSensorS = A0;  // Pin analógico para el sensor de sonido
int umbralSonido = 50;          // Umbral inicial
const int pinBuzzer = 10;

void setup() {
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  
  int valorSonido = analogRead(pinSensorS);
  
  // Imprimir el valor del sensor 
  Serial.print("Valor del sensor de sonido: ");
  Serial.println(valorSonido);

  // Calibración: ajustar el umbral 
  if (valorSonido > umbralSonido) {
    digitalWrite(pinBuzzer, HIGH); // Activar el buzzer
    delay(2000);//ajusta el tiempo que suena el buzzer
    //digitalWrite(Buzzer, LOW);
    Serial.println("Sonido detectado"); // validar que detecto un valor mayor al umbral 
  }
  digitalWrite(pinBuzzer, LOW);
  delay(500); 
}