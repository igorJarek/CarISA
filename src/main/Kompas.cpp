
#include <Wire.h>
#include <Arduino.h>
#include "Kompas.h"

void Kompas::writeRegister(uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(QMC_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

void Kompas::reset(void)
{
	this->writeRegister(0x0A, 0x80); // dokumentacja
	delay(100);
	this->init();
}

void Kompas::init(void)
{
  Wire.begin();
	this->writeRegister(0x0B, 0x01); // dokumentacja (tryb resetu)
	
	// konfiguracja
	uint8_t mode = 0;
	mode |= MODE_CONTINOUS;
	mode |= ODR_10HZ;
	mode |= RNG_8G;
	mode |= OSR_512;
	this->writeRegister(0x09, mode);
}

void Kompas::measure(void)
{
	// ustaw się na rejestrze 0
	Wire.beginTransmission(QMC_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission();
	
	// czytaj 6 bajtów
	Wire.requestFrom(QMC_ADDRESS, (uint8_t)6);
	int16_t x, y, z;
	
	// kolejność LSB, MSB
	x = (int16_t)Wire.read();
	x |= (int16_t)(Wire.read() << 8);

	y = (int16_t)Wire.read();
	y |= (int16_t)(Wire.read() << 8);
  
	z = (int16_t)Wire.read();
	z |= (int16_t)(Wire.read() << 8);
	
	this->x = x;
	this->y = y;
	this->z = z;
	
	this->a = azimuth(y,x);
}

float Kompas::azimuth(int16_t a, int16_t b){
  float azimuth = atan2(a,b) * 180.0/PI;
  return azimuth < 0?360 + azimuth:azimuth;
}
