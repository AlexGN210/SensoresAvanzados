#include <SoftwareSerial.h>

#include <TinyGPS.h>

/*
 Para el NEO 6m la velocidad es de 9600 baudios, además, las terminales son pin 4 (rx) y pin 3 (tx).
*/


TinyGPS gps;
SoftwareSerial ss(4, 3);

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);
static void print_int(unsigned long val, unsigned long invalid, int len);
static void print_date(TinyGPS &gps);
static void print_str(const char *str, int len);

void setup()
{
  Serial.begin(9600);
  
  Serial.println();
  Serial.println("Sats HDOP Latitud   Longitud   Fix  Fecha      Hora    Fecha Alt       Velocidad           Distancia      Chars Oraciones Checksum");
  Serial.println("          (grad)    (grad)     Age                     Age  (m)    ---  del GPS ----  ---- en México  ----  RX    RX        Fail");
  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");

  ss.begin(9600);
}

void loop()
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  static const double MEX_LAT = 51.508131, MEX_LON = -0.128002;
  
  print_int(gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5);
  print_str(",",1);
  print_int(gps.hdop(), TinyGPS::GPS_INVALID_HDOP, 5);
  print_str(",",1);
  gps.f_get_position(&flat, &flon, &age);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_str(",",1);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  print_str(",",1);
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  print_str(",",1);
  print_date(gps);
  print_str(",",1);
  print_float(gps.f_altitude(), TinyGPS::GPS_INVALID_F_ALTITUDE, 7, 2);
  print_str(",",1);
  print_float(gps.f_course(), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
  print_str(",",1);
  print_float(gps.f_speed_kmph(), TinyGPS::GPS_INVALID_F_SPEED, 6, 2);
  print_str(",",1);
  print_str(gps.f_course() == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(gps.f_course()), 6);
  print_str(",",1);
  print_int(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0xFFFFFFFF : (unsigned long)TinyGPS::distance_between(flat, flon, MEX_LAT, MEX_LON) / 1000, 0xFFFFFFFF, 9);
  print_str(",",1);
  print_float(flat == TinyGPS::GPS_INVALID_F_ANGLE ? TinyGPS::GPS_INVALID_F_ANGLE : TinyGPS::course_to(flat, flon, MEX_LAT, MEX_LON), TinyGPS::GPS_INVALID_F_ANGLE, 7, 2);
  print_str(",",1);
  print_str(flat == TinyGPS::GPS_INVALID_F_ANGLE ? "*** " : TinyGPS::cardinal(TinyGPS::course_to(flat, flon, MEX_LAT, MEX_LON)), 6);
  print_str(",",1);
  gps.stats(&chars, &sentences, &failed);
  print_int(chars, 0xFFFFFFFF, 6);
  print_str(",",1);
  print_int(sentences, 0xFFFFFFFF, 10);
  print_str(",",1);
  print_int(failed, 0xFFFFFFFF, 9);
  Serial.println();
  
//lo que hacen todas estas funciones es llamar a la librería, la cual divide cada una de las partes de la cadena y lo simplifica para solo imprimir ese dato
//que se solicitó como funcióin.

  smartdelay(60000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

//Esta funcion sirve para imprimir valores flotantes como lat, long, etc.
static void print_float(float val, float invalid, int len, int prec)
{
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartdelay(0);
}

//En este apartado se tiene una comparación al no estar recibiendo valores válidos, si los valores son iguales al 256, entonces se mandan carácteres "*".

static void print_int(unsigned long val, unsigned long invalid, int len)
{
  char sz[32];
  if (val == invalid)
    strcpy(sz, "*******");
  else
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartdelay(0);
}

//Con esta función se hace la segmentación de los datos de fecha.
static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("********** ******** ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  print_int(age, TinyGPS::GPS_INVALID_AGE, 5);
  smartdelay(0);
}
//Sirve para imprimir cadenas.
static void print_str(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartdelay(0);
}
