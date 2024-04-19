#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED, en píxeles
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED, en píxeles

#define DHTPIN 2         // Pin conectado al sensor DHT11
#define DHTTYPE DHT11
#define MQ_PIN A0        // Pin analógico conectado al sensor MQ para demostración
#define VENTILADOR_PIN 8 // Pin conectado al ventilador

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Crea un objeto de pantalla SSD1306 conectado a I2C
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(MQ_PIN, INPUT);
  pinMode(VENTILADOR_PIN, OUTPUT);
  Serial.begin(9600);

  // Inicializa la pantalla OLED con la dirección 0x3C para 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo la asignación de SSD1306"));
    while (true); // Se detiene el programa si la pantalla no se puede inicializar
  }

  delay(2000);         // Espera para la inicialización
  oled.clearDisplay(); // Limpia la pantalla

  oled.setTextSize(1);      // Establece el tamaño del texto
  oled.setTextColor(WHITE); // Establece el color del texto
  oled.setCursor(0, 0);     // Establece la posición inicial del cursor

  dht.begin();              // Inicializa el sensor de temperatura y humedad DHT11
}

void loop() {
  float humi  = dht.readHumidity();    // Lee la humedad
  float tempC = dht.readTemperature(); // Lee la temperatura
  int mq_value = analogRead(MQ_PIN);   // Lee el valor analógico del sensor MQ

  digitalWrite(VENTILADOR_PIN, LOW);

  // Verifica si alguna lectura falló
  if (isnan(humi) || isnan(tempC)) {
    oledDisplayCenter("Error al leer los datos");
  } else {
    String estadoAlcohol = mq_value > 300 ? "Alcohol detectado" : "No hay alcohol en el aire"; // Umbral ajustado para demostración
    String tempDisplay = "Temperatura: " + String(tempC, 1) + "C";
    String humiDisplay = "Humedad: " + String(humi, 1) + " %";

    // Enciende el ventilador si la temperatura es alta
    if (tempC > 23.0) {
      digitalWrite(VENTILADOR_PIN, HIGH);
    }

    // Muestra los datos en la pantalla
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.println(tempDisplay);
    oled.setCursor(0, 16); // Mueve el cursor a la siguiente línea
    oled.println(humiDisplay);
    oled.setCursor(0, 32); // Mueve el cursor a la tercera línea
    oled.println(estadoAlcohol);
    oled.display();
  }

  delay(2000); // Retraso entre lecturas
}

void oledDisplayCenter(String text) {
  int16_t x1, y1;
  uint16_t width, height;

  // Obtiene las dimensiones del texto para centrarlo
  oled.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);
  oled.clearDisplay(); // Limpia la pantalla
  oled.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2); // Establece la posición del cursor centrada
  oled.println(text); // Muestra el texto
  oled.display(); // Actualiza la pantalla
}
