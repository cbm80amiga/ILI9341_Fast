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

void setup(void) 
{
  Serial.begin(9600);
  lcd.init();
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE,BLUE);
  int xt=(SCR_WD-11*6)/2, yt=(SCR_HT-8)/2;
  lcd.setCursor(xt, yt);
  lcd.println("HELLO WORLD");
  lcd.drawRect(xt-10,yt-10,11*6+20,8+20,GREEN);
 }

void loop()
{
}

