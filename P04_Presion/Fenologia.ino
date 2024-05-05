#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 mpl = Adafruit_MPL3115A2();

float unidades_calor = 0.0;
float temperatura = 0.0;


void setup() {
  Serial.begin(9600);
  if (!mpl.begin()) {
    Serial.println("Error al inicializar el sensor MPL3115A2");
    while (1);
  }
}

void loop() {
  temperatura = mpl.getTemperature();

unidades_calor += (temperatura)-10;

Serial.print("Unidades caloríficas: ");
Serial.println(unidades_calor);
  if (unidades_calor < 12.89 ) {
    Serial.println("La planta de frijol está en la fase de Germinación.");

  } else if (unidades_calor >= 12.89 && unidades_calor < 64.41) {
    Serial.println("La planta de frijol está en la fase de Emergencia.");

  } else if (unidades_calor >= 64.41 && unidades_calor < 91.33) {
    Serial.println("La planta de frijol está en la fase de Pre floración");

  } else if (unidades_calor >= 91.33 && unidades_calor < 99.31) {
    Serial.println("La planta de frijol está en la fase de Floración.");

  } else if (unidades_calor >= 99.31 && unidades_calor < 112.77) {
    Serial.println("La planta de frijol está en la fase de Formación de la vaina.");

  } else if (unidades_calor >= 112.77 && unidades_calor < 153.24) {
    Serial.println("La planta de frijol está en la fase de Llenado de las vainas.");

  } else if (unidades_calor >= 153.24) {
    Serial.println("La planta de frijol está en la fase de Maduración.");
  }
delay(10000);

}
