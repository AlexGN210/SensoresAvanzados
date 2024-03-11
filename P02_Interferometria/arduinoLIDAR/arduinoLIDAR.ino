#include <Wire.h>
#include <VL53L0X.h> //LIBRERIA DE AUTOR Pololu
#include <Servo.h>

VL53L0X sensor;
Servo myServo;

float Value = 8;   // Valor de retardo entre pasos o velocidad del servo entre cada ángulo en milisegundos
float angle = 0;    // Ángulo inicial

float maxdist = 300; // Distancia máxima del sensor

void setup() {
  //Inicio de comunicación con el serial, y los puertos para los servos.
  Serial.begin(9600);
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);

  myServo.attach(3); // Pin del servo 
  myServo.write(0); // Prueba para los ángulos
  delay(5000);
  myServo.write(90); // Prueba para los ángulos
  delay(5000);
}

void loop() {

  // Mover el servo gradualmente, leer la distancia y mandar al puerto serial.
  for (int pos = 0; pos <= 180; pos +=1) {
    myServo.write(pos); //función para recorrer el servo
    delay(Value); //retardo para el sensor entre ángulo

    int r = sensor.readRangeSingleMillimeters(); //ya que el LIDAR es mejor utilizando una distancia de ref para detectar objetos,
    if (r > maxdist) {                           //es simplemente para tener un punto máximo de dibujo en PROCESSING.
      r = maxdist;
    }

    // Envía los datos en el formato "angulo,distancia"
    Serial.print(angle);  // Se imprime el "ángulo"  por el servo pero por la función for
    Serial.print(",");
    Serial.print(filtroEMA(r)); // se imprime la corrección con el filtro EMA
    Serial.println(",");
  }

  // Mover el servo de regreso a la posición inicial
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos); //función para recorrer el servo
    delay(Value); //retardo para el sensor entre ángulo
    
    int r = sensor.readRangeSingleMillimeters();  
    if (r > maxdist) {  //ya que el LIDAR es mejor utilizando una distancia de ref para detectar objetos,
      r = maxdist;      //es simplemente para tener un punto máximo de dibujo en PROCESSING.
    }

    // Envía los datos en el formato "angulo,distancia"
    Serial.print(angle); // Se imprime el "ángulo"  por el servo pero por la función for
    Serial.print(",");
    Serial.print(filtroEMA(r));  // se imprime la corrección con el filtro EMA
    Serial.println(",");
  }
}

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