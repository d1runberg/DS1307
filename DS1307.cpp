#include "Arduino.h"
#include "DS1307.h"

#define DS1307_ADDRESS 0x68
byte zero = 0x00;

int _second;
 int _minute;
 int _hour;
 int _weekDay;
 int _monthDay;
 int _month;
 int _year;


DS1307::DS1307()
{

}

void DS1307::begin()
{
   Wire.begin();
}

void DS1307::setTime(byte s_second, byte s_minute, byte s_hour, byte s_weekDay,byte s_monthDay, byte s_month, byte s_year)
{
   s_second =      45; //0-59
   s_minute =      40; //0-59
   s_hour =        0; //0-23
  s_weekDay =     2; //1-7
  s_monthDay =    1; //1-31
  s_month =       3; //1-12
  s_year  =       11; //0-99

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);

  Wire.write(decToBcd(s_second));
  Wire.write(decToBcd(s_minute));
  Wire.write(decToBcd(s_hour));
  Wire.write(decToBcd(s_weekDay));
  Wire.write(decToBcd(s_monthDay));
  Wire.write(decToBcd(s_month));
  Wire.write(decToBcd(s_year));

  Wire.write(zero); //start

  Wire.endTransmission();

}

void DS1307::pollClock()
{
   // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);

  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  _second = bcdToDec(Wire.read());
  _minute = bcdToDec(Wire.read());
  _hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  _weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  _monthDay = bcdToDec(Wire.read());
  _month = bcdToDec(Wire.read());
  _year = bcdToDec(Wire.read());

}
int DS1307::getSeconds()
{
   return _second;
}

int DS1307::getMinute()
{
   return _minute;
}

int DS1307::getHour()
{
   return _hour;
}

int DS1307::getMonth()
{
   return _month;
}

int DS1307::getWeekday()
{
   return _weekDay;
}

int DS1307::getYear()
{
   return _year;
}

int DS1307::getMonthDay()
{
   return _monthDay;
}

String DS1307::getTimeStamp()
{
   String _stamp = String(getYear());
   _stamp += "-";
   _stamp += String(getMonth());
   _stamp += "-";
   _stamp += String(getMonthDay());
   _stamp += "T";
   _stamp += String(getHour());
   _stamp += ":";
   _stamp += String(getMinute());
   _stamp += ":";
   _stamp += String(getSeconds());
   _stamp += "Z";

   return _stamp;
}

byte DS1307::bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

byte DS1307::decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}
