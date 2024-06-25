#ifndef ALARM_H
#define ALARM_H
#include "Timer.h"
class Alarm: Timer {
    uint16_t duration;
    uint8_t pin;
    public:
    Alarm(int pin, int dur);
    void setup();
    void loop();

};

#endif // ALARM_H
