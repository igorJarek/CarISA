#include "Engine.h"
#include "Encoder.h"

Engines engines;
Encoders& encoders = Encoders::getInstance();

void setup() {
    Serial.begin(9600);
    engines.accelerate(SIDE_BOTH, FORWARD, 128);
}

void loop() {
    Serial.println(encoders.getLeftCount());
    Serial.println(encoders.getRightCount());
    delay(100);
}
