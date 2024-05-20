#include <Adafruit_AHTX0.h>
#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

#define LM35_PIN A0 // Pin analógico utilizado para el sensor LM35
#define LM35_TEMP_FACTOR 0.488 // Factor de conversión para la temperatura del LM35
int contador;
/*
Esquema de conexiones:
Sensor AHT20:
SDA del sensor AHT20 -> A4
SCL del sensor AHT20 -> A5
VCC del sensor AHT20 -> 5V
GND del sensor AHT20 -> GND
Sensor MPL3115A2:
SDA del sensor MPL3115A2 -> A4
SCL del sensor MPL3115A2 -> A5 
VCC del sensor MPL3115A2 -> 5V
GND del sensor MPL3115A2 -> GND
Sensor LM35:
Pin central del LM35 -> Pin analógico A0
Pin lateral izquierdo del LM35 -> 5V
Pin lateral derecho del LM35 -> GND
*/
Adafruit_AHTX0 aht;
Adafruit_MPL3115A2 mpl = Adafruit_MPL3115A2();

void setup() {
  Serial.begin(9600);
  
  if (!aht.begin()) {
    Serial.println("No se pudo encontrar el sensor AHT20");
    while (1);
  }

  if (!mpl.begin()) {
    Serial.println("No se pudo encontrar el sensor MPL3115A2");
    while (1);
  }
  Serial.println("----------------------------------------------------------------------------------------------------------");
  Serial.println("Temperatura AHT20°C     Humedad AHT20 %     Temperatura MPL3115A2 °C     Temperatura LM35 °C    Timepo (s)");
}

void loop() {
  // Leer y mostrar la temperatura y humedad del sensor AHT20
  sensors_event_t humedad, temperatura;
  aht.getEvent(&humedad, &temperatura);
  //Serial.println("----------------------------------------------------------------------------------------------------------"); 
  //Serial.println("Temperatura AHT20°C     Humedad AHT20 %     Temperatura MPL3115A2 °C     Temperatura LM35 °C    Timepo (s)");

  // Leer y mostrar la temperatura del sensor AHT20
  Serial.print("\t"); Serial.print(temperatura.temperature);    Serial.print(",\t\t  ");
  Serial.print(humedad.relative_humidity);  Serial.print(",\t\t\t");

  // Leer y mostrar la temperatura del sensor MPL3115A2
  float temperature_mpl = mpl.getTemperature();
  Serial.print(temperature_mpl);            Serial.print(",\t\t\t");

  // Leer y mostrar la temperatura del sensor LM35
  int lm35_raw = analogRead(LM35_PIN);
  float temperature_lm35 = (lm35_raw * LM35_TEMP_FACTOR)+0.50;
  Serial.print(temperature_lm35);       Serial.print(",\t\t   ");
  contador =contador +2;
  Serial.println(contador);
  delay(1000); // Esperar 1 segundo antes de la próxima lectura
}

