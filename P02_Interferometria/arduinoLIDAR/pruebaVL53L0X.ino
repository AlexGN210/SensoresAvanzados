#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600); //Inicio de comunicación serial.

//En este apartado realiza una prueba de la comunicación  I2C para ver si está correcamente conectado
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X")); 
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure; 
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!


    // EN ESTE APARTADO SE MANDAN LOS DATOS AL SERIAL Y PARA PODER OBSERVAR LA DIFERENCIA ENTRE EL FILTRO Y EL RESULTADO NORMAL
    // SE PONEN AMBAS SENTENCIAS Y LA ÚLTIMA CON EL FILTRO.
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    Serial.print("Distance (mm) EMA: ");  Serial.println(filtroEMA(measure.RangeMilliMeter));
  } else { 
    Serial.println(" out of range ");
  }
    
  delay(1000);
}


// FUNCIÓN DE FILTRO EMA, ESTE FILTRO TIENE UNA CONDICIÓN PARA QUE AL MOMENTO DE TENER ERRORES DE LECTURA DE APROX 8191 QUE ES EL MÁS COMÚN,
// SE IGNORA Y SE TOMA EL ÚLTIMO DATO. ASÍ AL MOMENTO DE MEDIR NO ALTERA EL RESULTADO Y SE ESTABILIZA MÁS RÁPIDO.

int salida = 0;

  int filtroEMA(float data){
  if(data!=8191){
  float alpha = 0.7;
  salida = ((alpha*data)+((1-alpha)*salida));
  }
  else
  {
  float alpha = 0.7;
  salida = ((alpha*salida)+((1-alpha)*salida));
  }
  return salida;
  } 


