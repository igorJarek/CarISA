#include "Encoder.h"

Encoders::Encoders()
{
    pinMode(ENCODER_LEFT, INPUT);
    pinMode(ENCODER_RIGHT, INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), Encoders::encoderLeftInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), Encoders::encoderRightInterrupt, CHANGE);
}

void Encoders::encoderLeftInterrupt()
{
    getInstance().encoderLeftCounter++;
}

void Encoders::encoderRightInterrupt()
{
    getInstance().encoderRightCounter++;
}
