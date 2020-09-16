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

void setup() 
{
  Serial.begin(9600);
  lcd.init();
}

void loop(void) 
{
  for(uint8_t rot = 0; rot < 4; rot++) {
    testText(rot);
    delay(2000);
  }
}

unsigned long testText(int rot)
{
  lcd.setRotation(rot);
  lcd.fillScreen(BLACK);
  lcd.setCursor(0, 0);
  lcd.setTextColor(BLUE);
  lcd.setTextSize(1);
  lcd.println("Hello World!");
  lcd.setTextColor(WHITE);
  lcd.print("Rotation = ");
  lcd.println(rot);
  lcd.setTextColor(YELLOW);
  lcd.setTextSize(2);
  lcd.println(1234.56);
  lcd.setTextColor(RED);
  lcd.setTextSize(3);
  lcd.println(0xDEAD, HEX);
  lcd.println();
  lcd.setTextColor(GREEN);
  lcd.setTextSize(4);
  lcd.println("Hello");
}


