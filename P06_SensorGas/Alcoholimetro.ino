const int sensorPin = A0; // Pin analógico donde está conectado el sensor
const float R0 = 10.0;    // Valor de la resistencia de carga (en kOhm)

void setup() {
  Serial.begin(9600); // Inicializamos la comunicación serie a 9600 bps
  Serial.println("");
  Serial.println("Etanol       BACpercent");

}

void loop() {
  int sensorValue = analogRead(sensorPin); // Leemos el valor analógico del sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Convertimos el valor analógico a voltaje (0-5V)
  
  // Calcular la resistencia del sensor
  float RS = ((5.0 * R0) / voltage) - R0;

  // Aquí utilizamos valores de sensibilidad teóricos para cada gas.
 
  float ethanolppm = calculateConcentration(RS, 15.0); // Sustituir 15.0 por el valor adecuado
  float BACpercent = calculateBACpercent(ethanolppm); //  Porcentaje de alcohol en la sangre

  Serial.print(ethanolppm); Serial.print(",\t\t"); Serial.println(BACpercent);
  delay(1000); // Esperamos 1 segundo antes de la siguiente lectura
}

/*
  Función para calcular la concentración de un gas específico.
  RS: resistencia del sensor en kOhm
  a: coeficiente específico del gas (se obtiene de la hoja de datos del sensor)
*/
float calculateConcentration(float RS, float a) {
  return a * pow(RS, -1.0);
}
// Función para obtener el porcentaje de alcohol en la sangre
float calculateBACpercent(float ethanolppm) { 
  return ethanolppm/250;
}