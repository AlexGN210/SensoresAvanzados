#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
int timer=0; int carro=0;
float velocidad=0;
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
  //Serial.print("Pascales: "); Serial.println(pascals); // Imprime la presión atmosférica en pascales.
  //Serial.print(pascals / 3377); Serial.println(" Pulgadas (Hg)"); // Imprime la presión atmosférica en pulgadas de mercurio.
  
  if (pascals > 767){
   timer=timer+1;
   /*
   velocidad=(0.02/timer)*40;
   Serial.print("Velocidad= "); Serial.print(velocidad,6);Serial.println(" m/s");
   Serial.print("Velocidad= "); Serial.print(velocidad*3600,6);Serial.println(" m/hrs");
   Serial.println("////////");//Separador de información
   */
    if (timer%2>0){
      carro=carro+1;//Contador de la variable del carro.
      Serial.print("Paso "); Serial.print(carro); Serial.println(" carro");//Imprime el resultado.
    }
  }
  /*else if(pascals <= 767){
    timer=0;
  }
  */
  delay(25);
}
