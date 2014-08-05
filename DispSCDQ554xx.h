/*
 DispSCDQ554xx - Driver for Osram 4-Character 5x5 Dot Matrix Display
 Version 0.2 2013-03-07
 Copyright 2013 Patrik Thalin
 For details, see http://www.thalin.se
 
 The following Osram display devices are supported:
 * SCDQ5541X (Yellow)
 * SCDQ5542X (Super-red),
 * SCDQ5543X (Green)
 * SCDQ5544X (High Efficiency Green)
 
 Version History:
 0.2 Added rotation 2013-03-07
 0.1 Intial version 2013-03-06

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef DispSCDQ554xx_h
#define DispSCDQ554xx_h

#define SCDQ_SYMBOL(B0, B1, B2, B3, B4) (  (((unsigned long)B4&0x1F)<<20) | (((unsigned long)B3&0x1F) <<15) | (((unsigned long)B2&0x1F)<<10) | (((unsigned long)B1&0x1F)<<5) | ((unsigned long)B0&0x1F) )

class DispSCDQ554xx
{
public:
  DispSCDQ554xx(const int loadPin, const int sdataPin, const int sdclkPin);
  void begin();
  int write(const int ch, const unsigned long data);
  int write(const int ch, const unsigned long data, const char orientation);
  int clear();
  int clear(const int ch);
  int setBrightness(const unsigned int b);
  int sleep();
  int wake();
  
private:
 char ReverseRow(char x);
 void writeByte(const char a);
 int mLoadPin;
 int mSdataPin;
 int mSdclkPin;
 unsigned int mBrightness;
}
;
#endif