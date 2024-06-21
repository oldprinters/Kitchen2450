#include <Arduino.h>
#include "Timer.h"

Timer tRadar(1000);

//------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200); //Feedback over Serial Monitor
  Serial.println(F("=========================== ptr =="));
  delay(500);
  Serial2.begin (256000, SERIAL_8N1, 16, 17); //UART for monitoring the radar
  delay(500);
}
//------------------------------------------------------------------------------------------------------------
int getRadar(){
  int i = 0;
  while(Serial2.available()){
    if (Serial2.read()==0xAA && Serial2.read()==0xFF) {
      Serial.print("Radar: ");
      for (i = 0; i < 28; i++) {
        Serial.print(Serial2.read(), HEX);
        Serial.print(" ");
      }
      Serial.println();
      }
  }
  return i;
}
//------------------------------------------------------------------------------------------------------------
void loop() {
  if(tRadar.getTimer()){
    tRadar.setTimer();
    getRadar();
  }
  // put your main code here, to run repeatedly:
}
