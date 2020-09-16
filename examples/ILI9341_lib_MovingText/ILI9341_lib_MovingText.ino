// ILI9341 library example
// (c) 2020 Pawel A. Hernik

// requires RRE Font library:
// https://github.com/cbm80amiga/RREFont

/*
 ILI9341 240x320 2.2" LCD pinout (header at the top, from left):
 #1 MISO  -> NC
 #2 LED   -> 3.3V
 #3 SCK   -> SCL/D13/PA5
 #4 SDI   -> MOSI/D11/PA7
 #5 DC    -> D8/PA1  or any digital
 #6 RESET -> D9/PA0  or any digital
 #7 CS    -> D10/PA2 or any digital
 #8 GND   -> GND
 #9 VCC   -> 3.3V
*/

#define SCR_WD   240
#define SCR_HT   320
#include <SPI.h>
#include <Adafruit_GFX.h>

#if (__STM32F1__) // bluepill
#define TFT_CS  PA2
#define TFT_DC  PA1
#define TFT_RST PA0
//#include <ILI9341_STM.h>
#else
#define TFT_CS 10
#define TFT_DC  8
#define TFT_RST 9
#include <ILI9341_Fast.h>
#endif

ILI9341 lcd = ILI9341(TFT_DC, TFT_RST, TFT_CS);

#include "RREFont.h"
#include "rre_chicago_20x24.h"

RREFont font;

// needed for RREFont library initialization, define your fillRect
void customRect(int x, int y, int w, int h, int c) { return lcd.fillRect(x, y, w, h, c); }

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.fillScreen(BLACK);

  font.init(customRect, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values
  font.setFont(&rre_chicago_20x24);

  int i;
  for(i=0;i<10;i++) {
    font.setColor(RGBto565(i*15,i*15,i*15));
    font.printStr(70+i,40+i,"Hello");
  }
  font.setColor(WHITE);
  font.printStr(70+i,40+i,"Hello");

  for(i=0;i<10;i++) {
    font.setColor(lcd.rgbWheel(0+i*8));
    font.printStr(60+i,120+i,"World");
  }
  font.setColor(WHITE);
  font.printStr(60+i,120+i,"World");
  delay(4000);
  lcd.fillScreen();
}

#define MAX_TXT 32
int tx[MAX_TXT];
int ty[MAX_TXT];
byte cur=0;
int numTxt=16;
int x=0,y=0;
int dx=6,dy=5;
int i,ii,cc=0;

void loop()
{
  x+=dx;
  y+=dy;
  if(x>SCR_WD-20) { dx=-dx; x=SCR_WD-20; }
  if(x<1)   { dx=-dx; x=0; }
  if(y>SCR_HT-20) { dy=-dy; y=SCR_HT-20; }
  if(y<1)   { dy=-dy; y=0; }
  int i=cur;
  //font.setColor(BLACK);
  //font.printStr(tx[i],ty[i],"Hello!");
  tx[cur]=x;
  ty[cur]=y;
  if(++cur>=numTxt) cur=0;
  for(i=0;i<numTxt;i++) {
    ii=i+cur;
    if(ii>=numTxt) ii-=numTxt;
    font.setColor(RGBto565(i*15,i*5,0));
    if(i==numTxt-1) font.setColor(WHITE);
    font.printStr(tx[ii],ty[ii],"Hello!");
    cc++;
  }
  delay(20);
}

