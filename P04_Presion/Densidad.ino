#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

// Alimentado conectando Vin a 3-5V, GND a GND
// Utiliza I2C - conecta SCL al pin 5A, SDA al pin 4A
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2(); // Se crea un objeto de la clase Adafruit_MPL3115A2 llamado 'baro'.

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios.
  Serial.println("¡Prueba de Adafruit_MPL3115A2!"); // Imprime un mensaje en la consola serial.
}

void loop() {
  if (!baro.begin()) { // Verifica si el sensor no pudo inicializarse.
    Serial.println("No se pudo encontrar el sensor"); // Imprime un mensaje en la consola serial.
    return; // Sale de la función loop().
  }
  
  float pascals = baro.getPressure(); // Obtiene la presión atmosférica del sensor y la almacena en 'pascals'.
  // Nuestra página del clima presenta la presión en pulgadas (Hg)
  // Utiliza http://www.onlineconversion.com/pressure.htm para otras unidades
  Serial.print("Pascales: "); Serial.println(pascals); // Imprime la presión atmosférica en pascales.
  //Serial.print(pascals / 3377); Serial.println(" Pulgadas (Hg)"); // Imprime la presión atmosférica en pulgadas de mercurio.
  
  float altm = baro.getAltitude(); // Obtiene la altitud del sensor y la almacena en 'altm'.
  Serial.print("Metros: "); Serial.println(altm,3);  // Imprime la altitud en metros.

  float tempC = baro.getTemperature(); // Obtiene la temperatura del sensor y la almacena en 'tempC'.
  Serial.print("Temperatura: "); Serial.print(tempC,3); Serial.println(" *C");// Imprime la temperatura en grados Celsius.
  float densidad=( ((0.348444*pascals*100) - (29 *((0.00252*tempC) - 0.020582))) / (273.15+tempC)  )*0.01;//Fórmula de la densidad.
  float densidad2 = (24*((pascals*0.000145)/(273+tempC)))*100; //Otro opción de fórmula para la densidad.
  Serial.print("Densidad: "); Serial.print(densidad,3); Serial.println(" km/m^3"); //Imprime la densidad en km/m^3.
  //Serial.println(" Densidad2"); Serial.print(densidad2,5); 
  Serial.println("///////////////////////");//Separador de información
  delay(1000);
}
