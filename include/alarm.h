#ifndef ALARM_H
#define ALARM_H
#include "Timer.h"
class Alarm: Timer {
    uint16_t duration{500};
    uint8_t pin;
    int8_t ledStat{0};
    public:
    Alarm(int pin);
    void setDuration(uint16_t);
    void cycle();

};

#endif // ALARM_H
