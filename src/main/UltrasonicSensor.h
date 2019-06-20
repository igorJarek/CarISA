#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

enum e_UltrasonicSensor : uint8_t
{
    FRONT = 0,
    LEFT  = 1,
    RIGHT = 2,
    BACK  = 3
};

class UltrasonicSensor
{
    public:
        static UltrasonicSensor& getInstance()
        {
            static UltrasonicSensor instance;
            return instance;  
        }

        uint16_t getDistance(e_UltrasonicSensor side);
        
    private:
        UltrasonicSensor();
        UltrasonicSensor(const UltrasonicSensor &);
        
        uint16_t measureSoundSpeed(uint8_t trigger_pin, uint8_t echo_pin);

        uint16_t d[4][5] = {{0}};
        uint16_t sum[4] = {0};
        uint16_t id[4] = {0};
        uint16_t dist[4] = {0};
};

#endif // ULTRASONIC_HPP
