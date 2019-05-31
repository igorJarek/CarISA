#include "Engine.h"

Engines::Engines()
{
    pinMode(LEFT_PWM, OUTPUT);
    pinMode(LEFT_IN1, OUTPUT);
    pinMode(LEFT_IN2, OUTPUT);
  
    pinMode(RIGHT_PWM, OUTPUT);
    pinMode(RIGHT_IN1, OUTPUT);
    pinMode(RIGHT_IN2, OUTPUT);
}

void Engines::setEngineState(e_EngineSide side, e_EngineState state, uint8_t speed)
{
    uint64_t firstSide = side & 0xFFFFFFFF;
    uint64_t secondSide = (side >> 32) & 0xFFFFFFFF;

    digitalWrite((firstSide >> 16) & 0xFF, (state >> 0) & 0x1);
    digitalWrite((firstSide >>  8) & 0xFF, (state >> 1) & 0x1);
    analogWrite(firstSide & 0xFF, speed);
    
    if(secondSide != 0)
    {
        digitalWrite((secondSide >> 16) & 0xFF, (state >> 0) & 0x1);
        digitalWrite((secondSide >>  8) & 0xFF, (state >> 1) & 0x1);
        analogWrite(secondSide & 0xFF, speed);
    }
}

void Engines::accelerate(e_EngineSide side, e_EngineState state, uint8_t speed)
{ 
    currentSide = side;
    int delta = MAX_SPEED - speed;
    int step = delta / 10;

    for(int i = 0; i < 10; i++)
    {
        setEngineState(side, state, MAX_SPEED - (i * step));
        delay(10);
    }
}

void Engines::stopSoft()
{
    setEngineState(currentSide, SOFT_STOP, MIN_SPEED);
}

void Engines::stopSoft(e_EngineSide side)
{
    setEngineState(side, SOFT_STOP, MIN_SPEED);
}

void Engines::stopImmediately()
{
    setEngineState(currentSide, FAST_STOP, MAX_SPEED);
}

void Engines::stopImmediately(e_EngineSide side)
{
    setEngineState(side, FAST_STOP, MAX_SPEED);
}
