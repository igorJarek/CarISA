#include "Engine.h"
#include "Encoder.h"
#include "Kompas.h"
#include "UltrasonicSensor.h"

/*
 * Wymagana bilbioteka eFLL 1.1.1
 * https://github.com/zerokol/eFLL
 */

#include <Fuzzy.h>

#define engines Engines::getInstance()
#define encoders Encoders::getInstance()
#define compas Kompas::getInstance()
#define sensors UltrasonicSensor::getInstance()
#define DEBUG_SERIAL

Fuzzy* fuzzy = new Fuzzy();

// Front Sensor Set
FuzzySet* frontDistanceNear = new FuzzySet(0, 0, 7.5, 10);
FuzzySet* frontDistanceOk = new FuzzySet(7.5, 10, 10, 7.5);
FuzzySet* frontDistanceFar = new FuzzySet(10, 12.5, 500, 500);

// Engines LEFT Set
FuzzySet* engineLeftSlow = new FuzzySet(64, 64, 64, 64);
FuzzySet* engineLeftOk = new FuzzySet(128, 128, 128, 128);
FuzzySet* engineLeftAccelerate = new FuzzySet(192, 192, 192, 192);

// Engines RIGHT Set
FuzzySet* engineRightSlow = new FuzzySet(64, 64, 64, 64);
FuzzySet* engineRightOk = new FuzzySet(128, 128, 128, 128);
FuzzySet* engineRightAccelerate = new FuzzySet(192, 192, 192, 192);

void printValue(String s, int value)
{
    #ifdef DEBUG_BLUETOOTH
      Serial1.print(s + " : ");
      Serial1.println(value);
    #endif

    #ifdef DEBUG_SERIAL
      Serial.print(s + " : ");
      Serial.println(value);
    #endif
}

void setup() 
{
	  #ifdef DEBUG_BLUETOOTH
      Serial1.begin(9600);
	  #endif

    #ifdef DEBUG_SERIAL
      Serial.begin(115200);
    #endif

    randomSeed(analogRead(0));

    // Input - front sensor
    FuzzyInput* frontDistance = new FuzzyInput(1);

    frontDistance->addFuzzySet(frontDistanceNear);
    frontDistance->addFuzzySet(frontDistanceOk);
    frontDistance->addFuzzySet(frontDistanceFar);
    fuzzy->addFuzzyInput(frontDistance);

    // Output - engine LEFT
    FuzzyOutput* engineLeft = new FuzzyOutput(1);
  
    engineLeft->addFuzzySet(engineLeftSlow);
    engineLeft->addFuzzySet(engineLeftOk);
    engineLeft->addFuzzySet(engineLeftAccelerate);
    fuzzy->addFuzzyOutput(engineLeft);

    // Output - engine RIGHT
    FuzzyOutput* engineRight = new FuzzyOutput(2);
  
    engineRight->addFuzzySet(engineRightSlow);
    engineRight->addFuzzySet(engineRightOk);
    engineRight->addFuzzySet(engineRightAccelerate);
    fuzzy->addFuzzyOutput(engineRight);


    FuzzyRuleAntecedent* ifDistanceNear = new FuzzyRuleAntecedent(); 
    ifDistanceNear->joinSingle(frontDistanceNear);

    FuzzyRuleConsequent* then1 = new FuzzyRuleConsequent(); 
    then1->addOutput(engineLeftSlow);
    then1->addOutput(engineRightAccelerate);
}

void loop() 
{
    printValue("f : ", sensors.getDistance(FRONT));
    delay(50);
}
