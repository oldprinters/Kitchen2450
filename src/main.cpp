#include <Arduino.h>
#include "Timer.h"
#include "alarm.h"

Timer tRadar(100);

const uint8_t ledR{27};
const uint8_t ledG{26};
const uint8_t ledB{25};
Alarm ledAlR(ledR);
Alarm ledAlG(ledG);
Alarm ledAlB(ledB);

//------------------------------------------------------------------------------------------------------------
void testLeds()  {
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  delay(500);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
  delay(500);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, HIGH);
  delay(500);
  digitalWrite(ledB, LOW);
}
//------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200); //Feedback over Serial Monitor
  Serial.println(F("=========================== ptr =="));
  delay(500);
  Serial2.begin (256000, SERIAL_8N1, 16, 17); //UART for monitoring the radar
  delay(500);
  // pinMode(ledR, OUTPUT);
  // pinMode(ledG, OUTPUT);
  // pinMode(ledB, OUTPUT);
  // testLeds();
}
//------------------------------------------------------------------------------------------------------------
void outByte(uint8_t n){
  if(n < 10)
    Serial.print("0");
  Serial.print(n, HEX);
}
//------------------------------------------------------------------------------------------------------------
void outHexArray(uint8_t *byteArray, int size = 26){
  for (int i = 0; i < size; i++) {
    outByte(byteArray[i]);
    if(i % 2 > 0)
      Serial.print(" ");
  }
  Serial.println();
}
//------------------------------------------------------------------------------------------------------------
int16_t outObject(uint8_t* byteArray, int &i, bool outOn = true ){
  bool sign{0};
  int16_t x1 = (byteArray[i++] + 256 * byteArray[i++]);
  if (x1 && 0x8000){
    sign  =  1;
    x1 &= 0x7fff;
  }
  // Serial.print("x = ");
  // Serial.print(sign?"-":" ");
  // Serial.print(x1);
  int y1 = (byteArray[i++] + 256 * byteArray[i++]);
  if (y1 && 0x8000){
    sign  =  1;
    y1 &= 0x7fff;
  } else sign = 0;
    // Serial.print("\ty = ");
    // Serial.print(sign?"-":" ");
    // Serial.print(y1);
  int s1 = byteArray[i++] + 256 * byteArray[i++];
  if (s1 && 0x8000){
    sign  =  1;
    s1 &= 0x7fff;
  } else sign = 0;
    // Serial.print("\ts = ");
    // Serial.print(sign?"-":" ");
    // Serial.print(s1);
  int d1 = byteArray[i++] + 256 * byteArray[i++];
  if(d1 != 360 && d1 != 0 && outOn){
    Serial.print("\td = ");
    Serial.print(d1);
  }
  int l = sqrt(pow(x1,2) + pow(y1,2));
  if(outOn){
    Serial.print(" l = ");
    Serial.print(l);
    Serial.print(";\t");
  }
  return l;
}
//------------------------------------------------------------------------------------------------------------
int getRadar(){
  int i = 0;
  while(Serial2.available()){
    if (Serial2.read()==0xAA && Serial2.read()==0xFF) {
      // Serial.print("Radar: ");
      uint8_t byteArray[28];
      int nBytes = Serial2.readBytes(byteArray,28);
      // Serial.print(nBytes);
      // Serial.print(": ");
      int16_t* intArray = reinterpret_cast<int16_t*>(byteArray+2);
      // outHexArray(byteArray+2, 24);
      // outHexArray(byteArray, 28);
      i = 2;
      int16_t l1 = outObject(byteArray,  i, false);
      int16_t l2 = outObject(byteArray,  i, false);
      int16_t l3 = outObject(byteArray,  i, false);
      ledAlR.setDuration(l1);
      ledAlG.setDuration(l2);
      ledAlB.setDuration(l3);
      // if(l1 > 0)digitalWrite(ledR, HIGH);
      // else digitalWrite(ledR, LOW);
      // if(l2 > 0)digitalWrite(ledG, HIGH);
      // else digitalWrite(ledG, LOW);
      // if(l3 > 0)digitalWrite(ledB, HIGH);
      // else digitalWrite(ledB, LOW);
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
  ledAlR.cycle();
  ledAlG.cycle();
  ledAlB.cycle();
  // put your main code here, to run repeatedly:
}
