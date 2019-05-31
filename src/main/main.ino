#include "Engine.h"
#include "Encoder.h"
#include "Kompas.h"

#define engines Engines::getInstance()
#define encoders Encoders::getInstance()
#define compas Kompas::getInstance()

int16_t x = 0, y = 0;

// szybszy kompas tak chociaż 4ks/s
// przy tym kompasie co mamy wybieramy jakosc pomiaru czy szybkosc działania układu

// problem z usrednieniem w okolicach 0/360 stopni (czesc pomiarow ma wartosc bliska 360 a czesc bliska 0 stopni)
// rozwiazanie 1 : arcus sinus
// wady : zakres od -90 do 90 stopni - problemy z odejmowaniem
// rozwiazanie 2 : sinus i cosinus

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{   
    compas.measure(x, y);
    char bufx[] = {(x >> 8) & 0xFF, x & 0xFF};
    char bufy[] = {(y >> 8) & 0xFF, y & 0xFF};
    Serial.write(bufx, 2);
    Serial.write(bufy, 2);
    
    /*float startAngle = compas.avgRadian(200);
    float currAngle, deltaAngle;
  
    engines.accelerate(SIDE_LEFT, FORWARD, 128);
    engines.accelerate(SIDE_RIGHT, BACKWARD, 128);

    do
    {
       currAngle = compas.avgRadian(10);
       deltaAngle = fabs(startAngle - currAngle);
       Serial1.println(deltaAngle);
    }
    while(deltaAngle <= HALF_PI / 2.0);
    
    engines.stopImmediately(SIDE_BOTH);
    */
}
