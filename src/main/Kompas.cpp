#include <Wire.h>
#include <Arduino.h>
#include "Kompas.h"
#include "Consts.h"

Kompas::Kompas()
{
    pinMode(COMPAS_RDY, INPUT);
    attachInterrupt(digitalPinToInterrupt(COMPAS_RDY), Kompas::readyInterrupt, RISING);
    
    Wire.begin();
    this->writeRegister(0x0A, 0x80);
    delay(100);
    this->writeRegister(0x0B, 0x01);
    
    uint8_t mode = MODE_CONTINOUS | ODR_10HZ | RNG_8G | OSR_512;
    this->writeRegister(0x09, mode);
}

void Kompas::writeRegister(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(QMC_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void Kompas::readyInterrupt()
{
    getInstance().readyState = true;
}

void Kompas::measure(int16_t& x, int16_t& y)
{
    while(!readyState);
    readyState = false;
    
    Wire.beginTransmission(QMC_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();
    
    Wire.requestFrom(QMC_ADDRESS, (uint8_t)6);
    int16_t z;
    
    // kolejność LSB, MSB
    x = (int16_t)Wire.read();
    x |= (int16_t)(Wire.read() << 8);
  
    y = (int16_t)Wire.read();
    y |= (int16_t)(Wire.read() << 8);

    z = (int16_t)Wire.read();
    z |= (int16_t)(Wire.read() << 8);
}

float Kompas::measureAngle()
{
    int16_t x, y;
    measure(x, y);
    
    return azimuth(y, x);
}

float Kompas::avgAngle(uint8_t samples)
{
    float angle = 0.0f;
    uint8_t calibrationIndex = 0;
    
    do
    {
        angle += measureAngle();
        calibrationIndex++;
    }while(calibrationIndex < samples);
   
    angle /= (float)samples;
    return angle;
}

double Kompas::avgRadian(uint8_t samples)
{
    int16_t x = 0, y = 0;
    double sinus = 0.0f;
    uint8_t calibrationIndex = 0;
    
    do
    {
        measure(x, y);
        sinus += y/sqrt(pow(x, 2)+pow(y, 2));
        calibrationIndex++;
    }while(calibrationIndex < samples);
   
    sinus /= (double)samples;
    float radians = asin(sinus);
    return radians;
}

float Kompas::azimuth(int16_t a, int16_t b)
{
    float azimuth = atan2(a,b) * 180.0/PI;
    return azimuth < 0 ? 360 + azimuth:azimuth;
}
