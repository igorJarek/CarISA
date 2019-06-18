#include <Arduino.h>
#include "Consts.h"

UltrasonicSensor::UltrasonicSensor()
{
	pinMode(US_FRONT_TRIGGER_PIN, OUTPUT);
	pinMode(US_FRONT_ECHO_PIN, INPUT);
	digitalWrite(US_FRONT_TRIGGER_PIN, 0);
	
	pinMode(US_BACK_TRIGGER_PIN, OUTPUT);
	pinMode(US_BACK_ECHO_PIN, INPUT);
	digitalWrite(US_BACK_TRIGGER_PIN, 0);
	
	pinMode(US_LEFT_TRIGGER_PIN, OUTPUT);
	pinMode(US_LEFT_ECHO_PIN, INPUT);
	digitalWrite(US_LEFT_TRIGGER_PIN, 0);
	
	pinMode(US_RIGHT_TRIGGER_PIN, OUTPUT);
	pinMode(US_RIGHT_ECHO_PIN, INPUT);
	digitalWrite(US_RIGHT_TRIGGER_PIN, 0);
}

int UltrasonicSensor::measureSoundSpeed(int trigger_pin, int echo_pin)
{
	digitalWrite(trigger_pin, false);
	delayMicroseconds(2);

	digitalWrite(trigger_pin, true);
	delayMicroseconds(10);
	digitalWrite(trigger_pin, false);

	// zmierz czas przelotu fali dźwiękowej
	int duration = pulseIn(echo_pin, true, 50 * 1000);

	// przelicz czas na odległość (1/2 Vsound(t=20st.C))
	int distance = (int)((float)duration * 0.03438f * 0.5f);
	return distance;
}

int getFrontDist()
{
	int d[5] = {};
	int sum = 0;
	int id = 0;
		
	int dist = measureSoundSpeed(ultrasound_trigger_pin[(int)sensor], ultrasound_echo_pin[(int)sensor]);

	// średnia krocząca
	sum -= d[id];
	sum += d[id] = dist;
	id = (id + 1) % 5;
	dist = sum / 5;

	return dist;
}