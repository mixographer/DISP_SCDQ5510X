/*
 DispSCDQ554xx - Driver for Osram 4-Character 5x5 Dot Matrix Display
 Version 0.2 2013-03-06
 Copyright 2013 Patrik Thalin
 For details, see http://www.thalin.se
 
 The following Osram display devices are supported:
 * SCDQ5541X (Yellow)
 * SCDQ5542X (Super-red),
 * SCDQ5543X (Green)
 * SCDQ5544X (High Efficiency Green)

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
 
#include "Arduino.h"
#include "DispSCDQ554xx.h"

DispSCDQ554xx::DispSCDQ554xx(const int loadPin, const int sdataPin, const int sdclkPin)
{
  mLoadPin = loadPin;
  mSdataPin = sdataPin;
  mSdclkPin = sdclkPin;
  mBrightness = 6; 
}

void DispSCDQ554xx::begin()
{
  pinMode(mLoadPin,  OUTPUT);
  pinMode(mSdataPin, OUTPUT);
  pinMode(mSdclkPin, OUTPUT);
  writeByte(0xC0);
  writeByte(0xF0 | mBrightness); 
}

void DispSCDQ554xx::writeByte(const char a) {
  digitalWrite(mLoadPin, LOW); 
  for (int b = 0; b <= 7; b++) {
    digitalWrite(mSdataPin, bitRead(a, b));
    digitalWrite(mSdclkPin, HIGH);
    digitalWrite(mSdclkPin, LOW);
    }
  digitalWrite(mLoadPin, HIGH); 
}

 char DispSCDQ554xx::ReverseRow(char oldbyte) 
{ 
  char newbyte = 0;
  int i,j ;
  for ( i=0,  j=4; i<5; ) { // adjust values for nibbles
    bitWrite(newbyte, i++, bitRead(oldbyte, j--)); // adjust bitRead offset for nibbles
  } 
    return newbyte;    
} 

int DispSCDQ554xx::write(const  int ch, const unsigned long data, const char orientation) {
  char tmp = 0; 
  if ((ch > 4) || (ch < 0))
    return -1;
  
  writeByte(0xA0|ch);
  if (1 == orientation) { // 180 deg upside down 
    for (int row=0; row <= 4; row++) {
      writeByte((4-row<<5) | ((unsigned long)0x1f & ReverseRow(data >> (5*row))));
    }
  } 
  else if (2 == orientation) { // 90 deg
    for (int row=0; row <= 4; row++) {
      tmp = 0;
      for (int col=0; col <= 4; col++) {
        tmp |= ((unsigned long)0x01 & (data >> (5*col + 4-row))) << col;
      }        
      writeByte((row<<5) | ((unsigned long)0x1f & tmp));  
    }
  }
  else if (3 == orientation) { // 270 deg
    for (int row=0; row <= 4; row++) {
      tmp = 0;
      for (int col=0; col <= 4; col++) {
        tmp |= ((unsigned long)0x01 & (data >> (5*col + row))) << col;
      }      
      writeByte((row<<5) | ((unsigned long)0x1f & ReverseRow(tmp)));  
    }
  }
  else { // 0 deg Normal
    for (int row=0; row <= 4; row++) {
      writeByte((row<<5) | ((unsigned long)0x1f & (data >> (5*row))));
    }
  }
  return 0;
}

int DispSCDQ554xx::write(const  int ch, const unsigned long data) {
  return write(ch, data, 0);
}

int DispSCDQ554xx::clear() {
  writeByte(0xC0);
  writeByte(0xF0 | mBrightness);
  return 0;
}

int DispSCDQ554xx::clear(const int ch) {
  if ((ch > 4) || (ch < 0))
   return -1;
  writeByte(0xA0|ch);
  for (int row=0; row <= 4; row++) {
      writeByte(row <<5);
    }
  return 0;
}

int DispSCDQ554xx::setBrightness(const unsigned int b) {
  if (b > 6)
   return -1;
  mBrightness = b;
  writeByte(0xF0 | mBrightness);
  return 0;
}

int DispSCDQ554xx::sleep() {
   writeByte(0xFF); 
   return 0;
}

int DispSCDQ554xx::wake() {
  writeByte(0xF0 | mBrightness);
  return 0;
}
