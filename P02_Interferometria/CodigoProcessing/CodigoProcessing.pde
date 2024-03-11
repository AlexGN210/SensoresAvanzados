import processing.serial.*;

Serial myPort;  // El puerto serial
int lf = 10;    // Linefeed en ASCII
String myString = null;
float x, y, angle; //funciones para la impresión en la ventana.
float num, num2;
int i = 0;

void setup() {
  // Listar todos los puertos seriales disponibles
  println(Serial.list());
  // Abrir el puerto que estás usando con la velocidad que deseas:
  myPort = new Serial(this, Serial.list()[1], 9600); // Aquí se elige el puerto COM  
                                                     // del arduino.
  
  
  //Código para la ventana para la impresión de los datos.
  size(820, 410); //Tamaño de la ventana.
  noSmooth();
  background(0); //color
  translate(410, 205); //Tamaño para la impresión de los datos 
  stroke(255);    //tipografía
  strokeWeight(2);  // Grosor de la línea
}

void draw() {
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      String[] q = splitTokens(myString, ",");   
      
      num = float(q[0]);  // Convertir a float
      num2 = float(q[1]);  // Convertir a float
      
      // Convertir de coordenadas polares a cartesianas
      angle = num * 0.0174533;
      x = (cos(angle) * num2 + 410); // Coordenadas para la impresión en el eje X
      y = (410 - sin(angle) * num2); // Coordenadas para obtener una impresión en la parte superior
      
    }
    if (num == 0 )
    {
      background(0);    
      translate(410, 205);
    }
    // Dibujar puntos solo si el ángulo está en el rango de 0 a 180 grados.
    if (angle >= 0 && angle <= PI) {
      point(x, y);
    }
  }
  myPort.clear();
}
