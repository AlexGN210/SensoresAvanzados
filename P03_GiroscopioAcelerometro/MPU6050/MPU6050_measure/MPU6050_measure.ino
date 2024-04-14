#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

// A5SCL, A4SDA
int pitch=0;
int roll=0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
 
  // Inicializar el sensor MPU6050
  mpu.initialize();
 
  // Configurar el rango de escala del giroscopio y acelerómetro
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
}
void loop() {
  // Leer los datos del sensor
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
  // Convertir los datos en unidades de medida
  float accelX = ax / 16384.0; // Sensibilidad del acelerómetro para el rango de ±2g
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;
 
  float gyroX = gx / 131.0; // Sensibilidad del giroscopio para el rango de ±250°/s
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;
 
  /*----- Angulos pich and roll a partir de un acelerometro*/
  pitch = -(atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))*180.0)/M_PI;
  roll = ((atan2(accelY, accelZ)*180.0)/M_PI);
  /* Pasamos los grados a valores de 0 a 1023 con la finalidad de no tener negativos*/
  roll=map(roll,-180,180,0,1023);
  pitch=map(pitch,-180,180,0,1023);
 
  trama(pitch,roll);
 
  delay(200); // Esperar un poco antes de la próxima lectura
}

void trama(int value1, int value2){
  Serial.print("<");
 
  if (value1 > 999) {
    Serial.print(value1);
  }else if (value1 > 99) {
    Serial.print("0");
    Serial.print(value1);
  }else if(value1>9){
    Serial.print("00");
    Serial.print(value1);
  }else{
    Serial.print("000");
    Serial.print(value1);
    }
  Serial.print(",");
 
  if (value2 > 999) {
    Serial.print(value2);
  }else if (value2 > 99) {
    Serial.print("0");
    Serial.print(value2);
  }else if(value2>9){
    Serial.print("00");
    Serial.print(value2);
  }else{
    Serial.print("000");
    Serial.print(value2);
    }
  Serial.println(">");
  }