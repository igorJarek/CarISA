/*
	Created by Igor Jarek
	Politechnika Łódzka 2019
*/

#ifndef Engines_h
#define Engines_h

#include "Arduino.h"
#include "Consts.h"

enum e_EngineSide : uint64_t
{
	  SIDE_LEFT  = LEFT_IN1  << 16 | LEFT_IN2  << 8 | LEFT_PWM,
	  SIDE_RIGHT = RIGHT_IN1 << 16 | RIGHT_IN2 << 8 | RIGHT_PWM,
    SIDE_BOTH  = SIDE_LEFT << 32 | SIDE_RIGHT
};

enum e_EngineState : uint8_t
{
	  FORWARD   = 1 << 1 | 0 << 0,
	  BACKWARD  = 0 << 1 | 1 << 0,
    FAST_STOP = 0 << 1 | 0 << 0,
    SOFT_STOP = 1 << 1 | 1 << 0
};

class Engines
{
	  public:
        enum 
        { 
            MIN_SPEED = 0,
            MAX_SPEED = 0xFF
        };

        static Engines& getInstance()
        {
            static Engines instance;
            return instance;  
        }
   
		    void accelerate(e_EngineSide side, e_EngineState state, uint8_t speed);
        void stopSoft();
        void stopSoft(e_EngineSide side);
        void stopImmediately();

    private:
        Engines();
        Engines(const Engines &);
        
        void setEngineState(e_EngineSide side, e_EngineState state, uint8_t speed);
        e_EngineSide currentSide;
};

#endif // Engines_h
