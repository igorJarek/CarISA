#include "Engine.h"
#include "Encoder.h"
#include "Kompas.h"

#define engines Engines::getInstance()
#define encoders Encoders::getInstance()
#define compas Kompas::getInstance()
#define DEBUG_BLUETOOTH

// szybszy kompas tak chociaż 4ks/s
// przy tym kompasie co mamy wybieramy jakosc pomiaru czy szybkosc działania układu

uint8_t encoderStraightCounter = 20;

void printValue(String s, float value)
{
      Serial1.print(s + " : ");
      Serial1.println(value, 7);
}

void setup() 
{
	#ifdef DEBUG_BLUETOOTH
    Serial1.begin(9600);
	#endif
}

void loop() 
{
    uint32_t startEncoder = encoders.getRightCount();
    engines.accelerate(SIDE_BOTH, FORWARD, Engines::MAX_SPEED);
    while(encoders.getRightCount() <= startEncoder + encoderStraightCounter);
    engines.stopImmediately(SIDE_BOTH);
    delay(500);
    
    float currAngle = 0.0f, deltaAngle = 0.0f;
    float startAngle =  compas.avgAngle(1);

    engines.accelerate(SIDE_LEFT, FORWARD, 128);
    engines.accelerate(SIDE_RIGHT, BACKWARD, 128);

    do
    {
        currAngle =  compas.avgAngle(1);
		deltaAngle = fabs(currAngle - startAngle);
        if(deltaAngle > 180.0f)
            deltaAngle = 360.0 - deltaAngle;

		#ifdef DEBUG_BLUETOOTH
		Serial1.print(startAngle);
		Serial1.print(" | ");
		Serial1.print(currAngle);
		Serial1.print(" | ");
		Serial1.println(deltaAngle);
		delay(50);
		#endif
    }
    while(deltaAngle < 90.0f);
    
    engines.stopImmediately(SIDE_BOTH);
    delay(500);
}
