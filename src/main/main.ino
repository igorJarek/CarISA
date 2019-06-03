#include "Engine.h"
#include "Encoder.h"
#include "Kompas.h"

#define engines Engines::getInstance()
#define encoders Encoders::getInstance()
#define compas Kompas::getInstance()

// szybszy kompas tak chociaż 4ks/s
// przy tym kompasie co mamy wybieramy jakosc pomiaru czy szybkosc działania układu

// problem z usrednieniem w okolicach 0/360 stopni (czesc pomiarow ma wartosc bliska 360 a czesc bliska 0 stopni)
// rozwiazanie 1 : arcus sinus
// wady : zakres od -90 do 90 stopni - problemy z odejmowaniem
// rozwiazanie 2 : wektory

TODO : Sprawdzic i doregulowac obrot o 90 stopni (skreca za daleko np o 110 stopni), przejrzec dane z kompasu

void printValue(String s, float value)
{
      Serial.print(s + " : ");
      Serial.println(value, 7);
}

void setup() 
{
    //Serial.begin(115200);
    Serial1.begin(9600);
}

void loop() 
{
    uint32_t startEncoder = encoders.getRightCount();
    engines.accelerate(SIDE_BOTH, FORWARD, Engines::MAX_SPEED);
    while(encoders.getRightCount() <= startEncoder + 25);
    engines.stopImmediately(SIDE_BOTH);
    
    int16_t startX = 0, startY = 0;
    int16_t currX = 0, currY = 0;
    float deltaAngle = 0.0f, sumAngle = 0.0f;
    float maxEpsilon = 0.0f;
    compas.avgMeasure(200, startX, startY);
  
    engines.accelerate(SIDE_LEFT, FORWARD, 90);
    engines.accelerate(SIDE_RIGHT, BACKWARD, 110);

    do
    {
        compas.avgMeasure(5, currX, currY);
        int32_t iloczyn_skalarny = (startX*currX) + (startY*currY);
        float aLen = sqrt(pow(startX, 2) + pow(startY, 2));
        float bLen = sqrt(pow(currX, 2) + pow(currY, 2));
        float cosinus = iloczyn_skalarny / (aLen * bLen);
        deltaAngle = acos(cosinus) * (180.0/PI);
        //deltaAngle = deltaAngle >= 0.5 ? deltaAngle : 0.0f;   
        sumAngle += deltaAngle;
        Serial1.print(sumAngle);
        Serial1.print(" | ");
        Serial1.println(deltaAngle);
        
        startX = currX;
        startY = currY;
    }
    while(sumAngle < 89.0f);
    
    engines.stopImmediately(SIDE_BOTH);
    delay(1000);
}
