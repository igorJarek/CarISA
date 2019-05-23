/*
	Created by Igor Jarek
	Politechnika Łódzka 2019
*/

#ifndef Encoders_h
#define Encoders_h

#include "Arduino.h"
#include "Consts.h"

class Encoders;
extern Encoders encoders;

class Encoders
{
	  public:
        Encoders();
        uint32_t getLeftCount() { return encoderLeftCounter; }
        uint32_t getRightCount() { return encoderRightCounter; }

    private:
      static void encoderLeftInterrupt();
      static void encoderRightInterrupt();

      uint32_t encoderLeftCounter = 0;
      uint32_t encoderRightCounter = 0;
};

#endif // Encoders_h
