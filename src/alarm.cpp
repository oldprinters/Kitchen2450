#include "alarm.h"
using namespace std;

//---------------------------------------------------------
Alarm::Alarm(int p): pin(p), Timer(500){
    // pin = p;
   pinMode(pin, OUTPUT);
}
//---------------------------------------------------------
void Alarm::cycle(){
    if(ledStat >= 0){
        // Serial.print(pin);
        // Serial.print(" ");
        // Serial.println(ledStat);
        if(getTimer()){
            setTimer(duration);
            ledStat = !ledStat?1: 0;
            digitalWrite(pin, ledStat);
        }
    }
}
//---------------------------------------------------------
void Alarm::setDuration(uint16_t l){
    if(l > 0){
        if(ledStat < 0)ledStat = 0;
        if(l < 1000)
            duration = 100;
        else if(l < 1500)
            duration  =  200;
        else if(l < 2000)
            duration = 300;
        else duration  =  500;
    } else {
        ledStat = -1;
    }
}