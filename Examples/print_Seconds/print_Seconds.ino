#include <DS1307.h>

#include <Wire.h>

DS1307 myClock;

void setup()
{
  myClock.begin();
  myClock.setTime(0,12,2,3,21,12,15); // 12/21/15 2:12:00
  Serial.begin(9600);
}
void loop()
{
  myClock.pollClock();
 Serial.println(myClock.getTimeStamp());
}
