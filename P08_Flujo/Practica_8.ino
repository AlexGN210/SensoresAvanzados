#define sensorPin 2 // Definimos el pin donde está conectado el caudalímetro
volatile int contadorPulsos = 0; // Variable para contar los pulsos del caudalímetro
unsigned long tiempoPrevio = 0; // Variable para almacenar el tiempo previo

/*Conexiones
VCC (rojo): Conectar a 5V de Arduino.
GND (negro): Conectar a GND de Arduino.
Signal (amarillo): Conectar a un pin digital de Arduino; el pin 2.
*/

// Intervalo de tiempo para calcular el caudal
const unsigned long intervaloTiempo = 1000; // 1 segundo

void setup() { 
  Serial.begin(9600); // Iniciamos la comunicación serial 
  pinMode(sensorPin, INPUT); // Configuramos el pin del sensor como entrada
  attachInterrupt(digitalPinToInterrupt(sensorPin), contarPulsos, RISING); // Asociamos una interrupción al pin del sensor
  Serial.println("   "); //Dejamos un espacio en blanco para que se vea cool el inicio del monitor serial ;)
}

void loop() {
  unsigned long tiempoActual = millis(); // Obtenemos el tiempo actual
  // Si ha pasado un segundo

  if (tiempoActual - tiempoPrevio >= intervaloTiempo) {    
    detachInterrupt(digitalPinToInterrupt(sensorPin)); // Desactivamos las interrupciones temporalmente para evitar inconsistencia en el conteo   
    calcularCaudal();// Llamamos a la función para calcular e imprimir el caudal
    contadorPulsos = 0; // Reiniciamos el contador de pulsos
    tiempoPrevio = tiempoActual; // Actualizamos el tiempo previo
    attachInterrupt(digitalPinToInterrupt(sensorPin), contarPulsos, RISING); // Volvemos a activar las interrupciones
  }
}

// Función para contar los pulsos del caudalímetro
void contarPulsos() {
  contadorPulsos++;
}

// Función para calcular el caudal en "L/min" y "m³/min", además de mostrar los resultados en el monitor serial.
void calcularCaudal() {
  // Calculamos el caudal en litros por minuto
  float caudalLitros = contadorPulsos / 7.5; // 7.5 pulsos por segundo para 1 L/min

  // Convertimos el caudal a metros cúbicos por minuto
  float caudalMetrosCubicos = caudalLitros / 1000.0; // 1000 litros = 1 m³
  // Mostramos el resultado en el monitor serial 
  Serial.print("Pulsos: ");Serial.print(contadorPulsos);Serial.print(",  ");
  Serial.print("Caudal: ");Serial.print(caudalLitros);Serial.print(" L/min,   ");
  Serial.println(caudalMetrosCubicos);Serial.println(" m³/min");
}
