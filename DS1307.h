/*
  DS1307.h - Library to simplify interacting with the DS1307 RTC.
  Created by Derek Runberg of SparkFun Electronics, December 7th, 2015.
  Released into the public domain.
*/
#ifndef DS1307_h
#define DS1307_h

#include "Arduino.h"
#include "Wire.h"
class DS1307
{
  public:
    DS1307();
    void begin();
    void pollClock();
    void setTime(byte s_second, byte s_minute, byte s_hour, byte s_weekDay,byte s_monthDay, byte s_month, byte s_year);
    int getSeconds();
    int getMinute();
    int getHour();
    int getWeekday();
    int getMonthDay();
    int getMonth();
    int getYear();
    String getTimeStamp();
   private:
    byte bcdToDec(byte val);
    byte decToBcd(byte val);
};

#endif
