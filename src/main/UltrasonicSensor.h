#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

class UltrasonicSensor
{
    public:
        static UltrasonicSensor& getInstance()
        {
            static UltrasonicSensor instance;
            return instance;  
        }

        int getFrontDist();
        
    private:
        UltrasonicSensor();
        UltrasonicSensor(const UltrasonicSensor &);
        
        int measureSoundSpeed(int trigger_pin, int echo_pin);
};

#endif // ULTRASONIC_HPP
