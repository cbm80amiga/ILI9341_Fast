// ILI9341 library example
// (c) 2020 Pawel A. Hernik

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

#include "bitmap.h"

#define BARWD 24
uint16_t colorBar[BARWD];

void setup(void) 
{
  Serial.begin(9600);
  lcd.init();
  lcd.fillScreen(BLACK);

  int i,j;
  for(j=0;j<SCR_HT/32;j++) 
    for(i=0;i<SCR_WD/32;i++)
      lcd.drawImageF(i*32,j*32,32,32,mario);
  delay(4000);

  for(i=0;i<BARWD/2;i++) {
    colorBar[i]         = RGBto565(i*256/(BARWD/2),0,i*256/(BARWD/2));
    colorBar[i+BARWD/2] = RGBto565((BARWD/2-i)*255/(BARWD/2),0,(BARWD-i)*255/(BARWD/2));
  }
  for(i=0;i<SCR_WD;i++) {
    lcd.drawImage(i,0,1,BARWD,colorBar);
    lcd.drawImage(i,SCR_HT-BARWD,1,BARWD,colorBar);
  }
  for(i=BARWD;i<SCR_HT-BARWD;i++) {
    lcd.drawImage(0,i,BARWD,1,colorBar);
    lcd.drawImage(SCR_WD-BARWD,i,BARWD,1,colorBar);
  }
  delay(4000);
}

void loop()
{
  lcd.drawImageF(random(SCR_WD+1-32),random(SCR_HT+1-32),32,32,mario);
}

