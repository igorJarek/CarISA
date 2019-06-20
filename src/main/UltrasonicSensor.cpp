#include <Arduino.h>
#include "UltrasonicSensor.h"
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

uint16_t UltrasonicSensor::measureSoundSpeed(uint8_t trigger_pin, uint8_t echo_pin)
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

uint16_t UltrasonicSensor::getDistance(e_UltrasonicSensor side)
{
    if(side == FRONT)
        dist[side] = measureSoundSpeed(US_FRONT_TRIGGER_PIN, US_FRONT_ECHO_PIN);
    else if(side == LEFT)
        dist[side] = measureSoundSpeed(US_LEFT_TRIGGER_PIN, US_LEFT_ECHO_PIN);
    else if(side == RIGHT)
        dist[side] = measureSoundSpeed(US_RIGHT_TRIGGER_PIN, US_RIGHT_ECHO_PIN);
    else if(side == BACK)
        dist[side] = measureSoundSpeed(US_BACK_TRIGGER_PIN, US_BACK_ECHO_PIN);
  
    // średnia krocząca
    sum[side] -= d[side][id[side]];
    sum[side] += d[side][id[side]] = dist[side];
    id[side] = (id[side] + 1) % 5;
    dist[side] = sum[side] / 5;

    return dist[side];
}
