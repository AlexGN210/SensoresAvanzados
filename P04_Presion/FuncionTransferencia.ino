#include <Adafruit_AHTX0.h>

// Librerías 
#include <Adafruit_MPL3115A2.h>
#include <DHT11.h>


// Variables
DHT11 dht11(2); // PIN Analógico 0
Adafruit_MPL3115A2 mpl;


void setup() {
  Serial.begin(9600);
  while(!Serial);
  //Serial.println("Adafruit_MPL3115A2 test!");

  if (!mpl.begin()) {
   // Serial.println("No se pudo conectar al sensor, verifique conexiones de cables.");
    while(1);
  }

  // set mode before starting a conversion
  //Serial.println("Configurando a modo barométrico (presión).");
  mpl.setMode(MPL3115A2_BAROMETER);
}

void loop() {
  // start a conversion
  //Serial.println("Comenzando conversión");
  mpl.startOneShot();

  // do something else while waiting
  //Serial.println("Contando mientras se espera...");
  float count = 0;
  while (!mpl.conversionComplete()) {
    count++;
  }
  //Serial.print("Listo, se contó hasta: "); Serial.println(count);
 int temperature = dht11.readTemperature();
  // now get results
  /*
  Serial.print("______________________________________________________");
  Serial.println();
  Serial.print("Presión = ");
  Serial.print(mpl.getLastConversionResults(MPL3115A2_PRESSURE));
  Serial.print(" Pascales");
  Serial.println();
  Serial.print("Temperatura MPL= ");
  Serial.print(mpl.getLastConversionResults(MPL3115A2_TEMPERATURE));
  Serial.println(" °C");
  Serial.print("Temperatura DHT11 = ");
  Serial.print(temperature);
  Serial.println(" °C");
*/

  if(temperature!=253){
  Serial.print("<");
  Serial.print(int(mpl.getLastConversionResults(MPL3115A2_TEMPERATURE)*100));
  Serial.print(",");
  Serial.print(int(temperature*100));
  Serial.print(">");
  Serial.println();
}
  delay(50);

}