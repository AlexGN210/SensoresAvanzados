const int sensorPin = A0; // Pin analógico donde está conectado el sensor
const float R0 = 10.0;    // Valor de la resistencia de carga (en kOhm)

void setup() {
  Serial.begin(9600); // Inicializamos la comunicación serie a 9600 bps
  Serial.println("");
  Serial.println("  CO    Etanol      Hidrógeno   Amoníaco    Metano");//Imprimimos los datos que se van a medir

}

void loop() {
  int sensorValue = analogRead(sensorPin); // Leemos el valor analógico del sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Convertimos el valor analógico a voltaje (0-5V)
  
  // Calcular la resistencia del sensor
  float RS = ((5.0 * R0) / voltage) - R0;

  // Aquí utilizamos valores de sensibilidad teóricos para cada gas.
  // En una aplicación real, es posible que necesites calibrar el sensor.
    
  float COppm       = calculateConcentration(RS, 60.0); // Monóxido de carbono (CO). Sustituir 60.0 por el valor adecuado 
  float ethanolppm  = calculateConcentration(RS, 15.0); // Etanol. Sustituir 15.0 por el valor adecuado  
  float hydrogenppm = calculateConcentration(RS, 70.0); // Hidrógeno. Sustituir 70.0 por el valor adecuado
  float ammoniappm  = calculateConcentration(RS, 10.0); // Amoníaco. Sustituir 10.0 por el valor adecuado
  float methanepmm  = calculateConcentration(RS, 30.0); // Metano. Sustituir 30.0 por el valor adecuado
  
  // Imprimimos los valores en el monitor serie
  Serial.print(COppm);Serial.print(",\t");
  Serial.print(ethanolppm);Serial.print(",\t      "); 
  Serial.print(hydrogenppm);Serial.print(",\t  "); 
  Serial.print(ammoniappm);Serial.print(",\t     "); 
  Serial.println(methanepmm);
  delay(1000); // Esperamos 1 segundo antes de la siguiente lectura
}

/*
  Función para calcular la concentración de un gas específico.
  RS: resistencia del sensor en kOhm
  a: coeficiente específico del gas (se debe obtener de la hoja de datos del sensor)
*/
float calculateConcentration(float RS, float a) {
  return a * pow(RS, -1.0); // Esta es una fórmula simplificada, debe ajustarse con la calibración
}
