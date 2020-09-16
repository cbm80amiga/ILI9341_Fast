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
  font.init(customRect, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values
  font.setFont(&rre_chicago_20x24);
  font.setScale(1,2); font.setSpacing(3);
  font.setColor(WHITE);
}

const int fht = 48;

void rainbow()
{
  for(int i=0;i<SCR_HT;i+=4) {
    uint8_t r,g,b;
    lcd.rgbWheel(i*512L/240,&r,&g,&b);
    lcd.fillRect(0,i,SCR_WD,4,RGBto565(r,g,b));
  }
}

void loop()
{
  lcd.fillScreen(RGBto565(120,60,30));
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"ILI9341 modes");
  delay(2000);

  /*
  // idle is not implemented
  rainbow();
  font.setColor(BLACK);
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Idle mode OFF");
  lcd.idleDisplay(false); delay(2000);
  rainbow();
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Idle mode ON");
  lcd.idleDisplay(true); delay(4000);
  rainbow();
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Idle mode OFF");
  lcd.idleDisplay(false); delay(2000);
  */

  rainbow();
  font.setColor(WHITE,BLACK);
  lcd.fillRect(30,(SCR_HT-60)/2,240-60,60,BLACK);
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Invert OFF");
  lcd.invertDisplay(false); delay(2000);
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2," Invert ON ");
  lcd.invertDisplay(true); delay(4000);
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Invert OFF");
  lcd.invertDisplay(false); delay(2000);

  font.setColor(WHITE);
  lcd.fillScreen(RGBto565(180,0,180));
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Sleep mode in 2s");
  delay(2000);
  //lcd.enableDisplay(false); 
  lcd.sleepDisplay(true); delay(4000);
  lcd.sleepDisplay(false); 
  //lcd.enableDisplay(true);

  lcd.fillScreen(RGBto565(180,0,180));
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Display on/off");
  delay(2000);
  lcd.enableDisplay(false);  delay(4000);
  lcd.enableDisplay(true);  delay(1000);

  lcd.fillScreen(RGBto565(180,0,180));
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Partial display");
  font.setColor(YELLOW);
  font.printStr(ALIGN_CENTER,6,"Top");
  font.printStr(ALIGN_CENTER,SCR_HT-50,"Bottom");
  font.setColor(WHITE);
  delay(2000);
  lcd.setPartArea(60*1, SCR_HT-60*1); lcd.partialDisplay(true); delay(4000);
  lcd.setPartArea(SCR_HT-60*1, 60*1); lcd.partialDisplay(true); delay(4000);
  lcd.partialDisplay(false);
  delay(1000);

  lcd.fillScreen(RGBto565(180,0,0));
  font.printStr(ALIGN_CENTER,(SCR_HT-fht)/2,"Sw reset ...");
  delay(2000);
  lcd.resetDisplay();  delay(2000);
  lcd.init();
  lcd.fillScreen(RGBto565(0,0,180));
  font.printStr(0,0,"After reset"); delay(2000);

}

