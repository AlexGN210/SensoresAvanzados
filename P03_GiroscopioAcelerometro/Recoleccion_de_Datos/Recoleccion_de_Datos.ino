#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int pitch=0;
int roll=0;

unsigned long past_time=0;

void setup()
{
  Serial.begin(9600);
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
}
 

void loop()
{  
    if(millis()-past_time>=100)
  {
    
  Vector normAccel = mpu.readNormalizeAccel();
  pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  roll = ((atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI);

  pitch=map(pitch,-180,180,0,1023);
  roll=map(roll,-180,180,0,1023);
  
  trama(pitch,roll);
  
  past_time=millis();
  }

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
  Serial.print(">");
  Serial.println("\t");
  }
