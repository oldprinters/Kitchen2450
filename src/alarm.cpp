#include "alarm.h"
using namespace std;

//---------------------------------------------------------
Alarm::Alarm(int p, int dur): Timer(dur){
    pin = p;
   duration = dur;
   pinMode(pin, OUTPUT);

}