#include "Engine.h"
#include "Encoder.h"
#include "Kompas.h"

#define engines Engines::getInstance()
#define encoders Encoders::getInstance()
#define compas Kompas::getInstance()

const uint16_t encoderCount = 20;

float oldAlpha;
float newAlpha;
float deltaAlpha;
float avgAngle;
float max = 0.0f;
float min = 0.0f;

void setup() 
{
    Serial1.begin(9600);
}

void loop() 
{
    compas.measure();
    oldAlpha = compas.getAngle();
    compas.measure();
    newAlpha = compas.getAngle();
    deltaAlpha = newAlpha - oldAlpha;
    max = deltaAlpha > max ? deltaAlpha : max;
    min = deltaAlpha < min ? deltaAlpha : min;
    avgAngle = (newAlpha + oldAlpha) / 2.0;
    Serial1.println(max);
    Serial1.println(min);
    Serial1.println(avgAngle);
    Serial1.println();
  
    /*engines.accelerate(SIDE_LEFT, FORWARD, 255);
    engines.accelerate(SIDE_RIGHT, BACKWARD, 210);
    
    float oldAlpha;
    float newAlpha;
    float deltaAlpha;
    float sumAlpha=0;

    compas.measure();
    oldAlpha = compas.getAngle();

    do
    {
        compas.measure();
        newAlpha = compas.getAngle();
    
        deltaAlpha = abs(newAlpha - oldAlpha);
        if(deltaAlpha >= 180.0)
            deltaAlpha = 360.0 - deltaAlpha;
      
        sumAlpha += deltaAlpha;
        Serial1.println(sumAlpha);
    }
    while(abs(sumAlpha) <= 90.0);
    
    engines.stopImmediately(SIDE_RIGHT);
    engines.stopImmediately(SIDE_LEFT);
    
    delay(1000);*/

  
    /*engines.accelerate(SIDE_BOTH, FORWARD, Engines::MAX_SPEED);
    uint16_t startCount = encoders.getLeftCount();
    while(encoders.getLeftCount() - startCount <= encoderCount);
    engines.stopSoft();
    delay(1000);
    engines.accelerate(SIDE_LEFT, FORWARD, 255);
    engines.accelerate(SIDE_RIGHT, BACKWARD, 210);
    
    float oldAlpha;
    float newAlpha;
    float deltaAlpha;
    float sumAlpha=0;

    compas.measure();
    oldAlpha = compas.getAngle();

    do
    {
        compas.measure();
        newAlpha = compas.getAngle();
    
        deltaAlpha = abs(newAlpha - oldAlpha);
        if(deltaAlpha >= 180.0)
            deltaAlpha = 360.0 - deltaAlpha;
      
        sumAlpha += deltaAlpha;
        Serial1.println(sumAlpha);
        oldAlpha = newAlpha;
    }
    while(abs(sumAlpha) <= 90.0);
    
    engines.stopSoft(SIDE_RIGHT);
    engines.stopSoft(SIDE_LEFT);
    
    delay(1000);*/
}
