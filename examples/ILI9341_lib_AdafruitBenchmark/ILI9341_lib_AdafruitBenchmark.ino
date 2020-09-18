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
//#include <Adafruit_ILI9341.h>
#endif

ILI9341 tft = ILI9341(TFT_DC, TFT_RST, TFT_CS);
//Adafruit_ILI9341 tft = Adafruit_ILI9341( TFT_CS, TFT_DC, TFT_RST);

// Color definitions
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
#define RGBto565(r,g,b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3)) 


// ------------------------------------------------
unsigned long FillScreenTest()
{
  unsigned long start = millis();
  for(int i=0;i<5;i++) {
    tft.fillScreen(RED);
    tft.fillScreen(GREEN);
    tft.fillScreen(BLUE);
    tft.fillScreen(YELLOW);
  }
  return millis()-start;
}

// ------------------------------------------------
unsigned long ClearScreenTest()
{
  unsigned long start = millis();
  for(int i=0;i<5*4;i++) 
    tft.fillScreen(BLACK);
  return millis()-start;
}
// ------------------------------------------------
const uint16_t imgF[] PROGMEM = {0xF800,0xF840,0xF8A0,0xF900,0xF960,0xF9C0,0xFA20,0xFA80,0xFAE0,0xFB40,0xFBA0,0xFC00,0xFC60,0xFCC0,0xFD20,0xFD80,0xFDE0,0xFE40,0xFEA0,0xFF00,0xFF60,0xFFC0,0xFFE0,0xEFE0,0xE7E0,0xD7E0,0xCFE0,0xBFE0,0xB7E0,0xA7E0,0x9FE0,0x8FE0,0x87E0,0x77E0,0x6FE0,0x5FE0,0x57E0,0x47E0,0x3FE0,0x2FE0,0x27E0,0x17E0,0xFE0,0x7E0,0x7E1,0x7E3,0x7E4,0x7E6,0x7E7,0x7E9,0x7EA,0x7EC,0x7ED,0x7EF,0x7F0,0x7F2,0x7F3,0x7F5,0x7F6,0x7F8,0x7F9,0x7FB,0x7FC,0x7FE,0x7FF,0x79F,0x73F,0x6DF,0x67F,0x61F,0x5BF,0x55F,0x4FF,0x49F,0x43F,0x3DF,0x37F,0x31F,0x2BF,0x25F,0x1FF,0x19F,0x13F,0xDF,0x7F,0x1F,0x81F,0x101F,0x201F,0x281F,0x381F,0x401F,0x501F,0x581F,0x681F,0x701F,0x801F,0x881F,0x981F,0xA01F,0xB01F,0xB81F,0xC81F,0xD01F,0xE01F,0xE81F,0xF81F,0xF81F,0xF81D,0xF81C,0xF81A,0xF819,0xF817,0xF816,0xF814,0xF813,0xF811,0xF810,0xF80E,0xF80D,0xF80B,0xF80A,0xF808,0xF807,0xF805,0xF804,0xF802,0xF801,
                                 0xF800,0xF840,0xF8A0,0xF900,0xF960,0xF9C0,0xFA20,0xFA80,0xFAE0,0xFB40,0xFBA0,0xFC00,0xFC60,0xFCC0,0xFD20,0xFD80,0xFDE0,0xFE40,0xFEA0,0xFF00,0xFF60,0xFFC0,0xFFE0,0xEFE0,0xE7E0,0xD7E0,0xCFE0,0xBFE0,0xB7E0,0xA7E0,0x9FE0,0x8FE0,0x87E0,0x77E0,0x6FE0,0x5FE0,0x57E0,0x47E0,0x3FE0,0x2FE0,0x27E0,0x17E0,0xFE0,0x7E0,0x7E1,0x7E3,0x7E4,0x7E6,0x7E7,0x7E9,0x7EA,0x7EC,0x7ED,0x7EF,0x7F0,0x7F2,0x7F3,0x7F5,0x7F6,0x7F8,0x7F9,0x7FB,0x7FC,0x7FE,0x7FF,0x79F,0x73F,0x6DF,0x67F,0x61F,0x5BF,0x55F,0x4FF,0x49F,0x43F,0x3DF,0x37F,0x31F,0x2BF,0x25F,0x1FF,0x19F,0x13F,0xDF,0x7F,0x1F,0x81F,0x101F,0x201F,0x281F,0x381F,0x401F,0x501F,0x581F,0x681F,0x701F,0x801F,0x881F,0x981F,0xA01F,0xB01F,0xB81F,0xC81F,0xD01F,0xE01F,0xE81F,0xF81F,0xF81F,0xF81D,0xF81C,0xF81A,0xF819,0xF817,0xF816,0xF814,0xF813,0xF811,0xF810,0xF80E,0xF80D,0xF80B,0xF80A,0xF808,0xF807,0xF805,0xF804,0xF802,0xF801};
uint16_t img[SCR_WD+16];
unsigned long DrawImageTest()
{
  for(int i=0;i<SCR_WD+16;i++) img[i] = tft.rgbWheel(500L*i/SCR_WD);
  unsigned long start = millis();
  for(int i=0;i<5*4;i++) for(int y=0;y<SCR_HT;y++) tft.drawImage(0,y,SCR_WD,1,img+(((y>>2)+i)&0xf));
  return millis()-start;
}
// ------------------------------------------------ 
unsigned long DrawImageFTest()
{
  unsigned long start = millis();
  for(int i=0;i<5*4;i++) for(int y=0;y<SCR_HT;y++) tft.drawImageF(0,y,SCR_WD,1,imgF+(((y>>2)+i)&0xf));
  return millis()-start;
}
// ------------------------------------------------ 
unsigned long orig[14]={ 8504,8505,2126420,256356,2364088,179228,119136,4416428,723324,1034904,517836,1835884,388904,4460568 };

unsigned long res[14];
void result(int i)
{
  Serial.print(res[i]);
  if(res[i]<1000000) Serial.print("\t");
  Serial.print("\t\t\t");
  Serial.print(100*orig[i]/res[i]);
  Serial.println("%");
}

void setup(void) 
{
  Serial.begin(9600);
  Serial.println(F("ILI9341 240x320"));
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("ILI9341 240x320");
  tft.println("Library Benchmark");
  tft.println("starts in 3s ...");
  delay(3000);

  Serial.println(F("Benchmark   Time (microseconds)"));

  res[0]=FillScreenTest();
  Serial.print(F("FillScreen Mbps          "));
  Serial.println(String(res[0])+"ms  "+String(1000*20.0/res[0])+"fps  "+String(20.0*SCR_WD*SCR_HT*16/res[0]/1000.0)+" Mbps\t"+100*orig[0]/res[0]+"%");

//for(int i=0;i<100;i++) tft.fillRect(i,i,SCR_WD-i*2,SCR_HT-i*2,tft.rgbWheel(i*10)); delay(1000);

  res[1]=ClearScreenTest();
  Serial.print(F("ClearScreen Mbps         "));
  Serial.println(String(res[1])+"ms  "+String(1000*20.0/res[1])+"fps  "+String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0)+" Mbps\t"+100*orig[1]/res[1]+"%");

  res[1]=DrawImageTest();
  Serial.print(F("DrawImage Mbps           "));
  Serial.println(String(res[1])+"ms  "+String(1000*20.0/res[1])+"fps  "+String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0)+" Mbps\t"+100*orig[1]/res[1]+"%"); 

  res[1]=DrawImageFTest();
  Serial.print(F("DrawImageF Mbps          "));
  Serial.println(String(res[1])+"ms  "+String(1000*20.0/res[1])+"fps  "+String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0)+" Mbps\t"+100*orig[1]/res[1]+"%"); 
  
  res[2]=testFillScreen();
  Serial.print(F("Screen fill              "));
  result(2);
  delay(500);

  res[3]=testText();
  Serial.print(F("Text                     "));
  result(3);
  delay(3000);

  res[4]=testLines(CYAN);
  Serial.print(F("Lines                    "));
  result(4);
  delay(500);

  res[5]=testFastLines(RED, BLUE);
  Serial.print(F("Horiz/Vert Lines         "));
  result(5);
  delay(500);

  res[6]=testRects(GREEN);
  Serial.print(F("Rectangles (outline)     "));
  result(6);
  delay(500);

  res[7]=testFilledRects(YELLOW, MAGENTA);
  Serial.print(F("Rectangles (filled)      "));
  result(7);
  delay(500);

  res[8]=testFilledCircles(10, MAGENTA);
  Serial.print(F("Circles (filled)         "));
  result(8);

  res[9]=testCircles(10, WHITE);
  Serial.print(F("Circles (outline)        "));
  result(9);
  delay(500);

  res[10]=testTriangles();
  Serial.print(F("Triangles (outline)      "));
  result(10);
  delay(500);

  res[11]=testFilledTriangles();
  Serial.print(F("Triangles (filled)       "));
  result(11);
  delay(500);

  res[12]=testRoundRects();
  Serial.print(F("Rounded rects (outline)  "));
  result(12);
  delay(500);

  res[13]=testFilledRoundRects();
  Serial.print(F("Rounded rects (filled)   "));
  result(13);
  delay(500);

  Serial.println(F("Done!"));
  Serial.println(F("Results:"));
  for(int i=0;i<14;i++) { Serial.print(res[i]); Serial.print(","); }
  Serial.println();
  
  int c1=YELLOW, c2=WHITE;
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.setTextColor(CYAN);
  tft.println("RESULTS:");

  tft.setTextSize(1);
  tft.println();
  tft.setTextColor(GREEN);
  tft.println(F("Benchmark     Time/us"));
  tft.setTextColor(c1); tft.print(F("FillScr Mbps  "));
  tft.setTextColor(c2); tft.println(String(res[0])+"ms "+String(20.0*SCR_WD*SCR_HT*16/res[0]/1000.0)+" Mbps");
  //tft.setTextColor(c2); tft.println(String(20.0*SCR_WD*SCR_HT*16/res[0]/1000.0));
  //tft.setTextColor(c1); tft.print(F("ClrScr        "));
  //tft.setTextColor(c2); tft.println(String(res[1])+"ms "+String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0)+" Mbps");
  //tft.setTextColor(c2); tft.println(String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0));
  tft.setTextColor(c1); tft.print(F("DrwImgF Mbps  "));
  tft.setTextColor(c2); tft.println(String(res[1])+"ms "+String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0)+" Mbps");
  //tft.setTextColor(c2); tft.println(String(20.0*SCR_WD*SCR_HT*16/res[1]/1000.0));
  tft.setTextColor(c1); tft.print(F("Screen fill   "));
  tft.setTextColor(c2); tft.println(res[2]);
  tft.setTextColor(c1); tft.print(F("Text          "));
  tft.setTextColor(c2); tft.println(res[3]);
  tft.setTextColor(c1); tft.print(F("Lines         "));
  tft.setTextColor(c2); tft.println(res[4]);
  tft.setTextColor(c1); tft.print(F("H/V Lines     "));
  tft.setTextColor(c2); tft.println(res[5]);
  tft.setTextColor(c1); tft.print(F("Rects O       "));
  tft.setTextColor(c2); tft.println(res[6]);
  tft.setTextColor(c1); tft.print(F("Rects F       "));
  tft.setTextColor(c2); tft.println(res[7]);
  tft.setTextColor(c1); tft.print(F("Circles F     "));
  tft.setTextColor(c2); tft.println(res[8]);
  tft.setTextColor(c1); tft.print(F("Circles O     "));
  tft.setTextColor(c2); tft.println(res[9]);
  tft.setTextColor(c1); tft.print(F("Tris O        "));
  tft.setTextColor(c2); tft.println(res[10]);
  tft.setTextColor(c1); tft.print(F("Tris F        "));
  tft.setTextColor(c2); tft.println(res[11]);
  tft.setTextColor(c1); tft.print(F("Round rects O "));
  tft.setTextColor(c2); tft.println(res[12]);
  tft.setTextColor(c1); tft.print(F("Round rects F "));
  tft.setTextColor(c2); tft.println(res[13]);
  tft.setTextColor(RED); tft.println(F("Done!"));
}

/*

--- below + opt setAddrWindow + writeMulti
ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          3478ms  5.75fps  7.07 Mbps 244%
ClearScreen Mbps         3479ms  5.75fps  7.06 Mbps 244%
DrawImage Mbps           3675ms  5.44fps  6.69 Mbps 231%
DrawImageF Mbps          4804ms  4.16fps  5.12 Mbps 177%
Screen fill              869884       244%
Text                     121828       210%
Lines                    913776       258%
Horiz/Vert Lines         72960        245%
Rectangles (outline)     48552        245%
Rectangles (filled)      1805840      244%
Circles (filled)         294596       245%
Circles (outline)        396932       260%
Triangles (outline)      200828       257%
Triangles (filled)       891092       206%
Rounded rects (outline)  152616       254%
Rounded rects (filled)   1824908      244%
Done!


--- Fast AVR + writeMulti + copyMulti:

ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          3477ms  5.75fps  7.07 Mbps 244%
ClearScreen Mbps         3478ms  5.75fps  7.07 Mbps 244%
DrawImage Mbps           3695ms  5.41fps  6.65 Mbps 230%
DrawImageF Mbps          4826ms  4.14fps  5.09 Mbps 176%
Screen fill              869904       244%
Text                     128088       200%
Lines                    983324       240%
Horiz/Vert Lines         73324        244%
Rectangles (outline)     49064        242%
Rectangles (filled)      1805948      244%
Circles (filled)         307728       235%
Circles (outline)        427460       242%
Triangles (outline)      215620       240%
Triangles (filled)       900716       203%
Rounded rects (outline)  161828       240%
Rounded rects (filled)   1828932      243%
Done!


--- Fast AVR + writeMulti:

ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          3477ms  5.75fps  7.07 Mbps 244%
ClearScreen Mbps         3478ms  5.75fps  7.07 Mbps 244%
DrawImage Mbps           4090ms  4.89fps  6.01 Mbps 207%
DrawImageF Mbps          4827ms  4.14fps  5.09 Mbps 176%
Screen fill              869904       244%
Text                     128088       200%
Lines                    983324       240%
Horiz/Vert Lines         73316        244%
Rectangles (outline)     49072        242%
Rectangles (filled)      1805992      244%
Circles (filled)         307724       235%
Circles (outline)        427468       242%
Triangles (outline)      215612       240%
Triangles (filled)       900708       203%
Rounded rects (outline)  161828       240%
Rounded rects (filled)   1828932      243%
Done!


--- Fast AVR old:

ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          3532ms  5.66fps  6.96 Mbps 240%
ClearScreen Mbps         3533ms  5.66fps  6.96 Mbps 240%
DrawImage Mbps           4090ms  4.89fps  6.01 Mbps 207%
DrawImageF Mbps          4826ms  4.14fps  5.09 Mbps 176%
Screen fill              883488       240%
Text                     129780       197%
Lines                    983324       240%
Horiz/Vert Lines         75212        238%
Rectangles (outline)     50532        235%
Rectangles (filled)      1834220      240%
Circles (filled)         323312       223%
Circles (outline)        427460       242%
Triangles (outline)      215844       239%
Triangles (filled)       922416       199%
Rounded rects (outline)  163016       238%
Rounded rects (filled)   1863564      239%
Done!

--- Fast in COMPATIBILITY mode - new:

ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          7149ms  2.80fps  3.44 Mbps 118%
ClearScreen Mbps         7148ms  2.80fps  3.44 Mbps 118%
DrawImage Mbps           6982ms  2.86fps  3.52 Mbps 121%
DrawImageF Mbps          7716ms  2.59fps  3.19 Mbps 110%
Screen fill              1787472      118%
Text                     279244       91%
Lines                    2637368      89%
Horiz/Vert Lines         153764       116%
Rectangles (outline)     104672       113%
Rectangles (filled)      3712456      118%
Circles (filled)         721304       100%
Circles (outline)        1151040      89%
Triangles (outline)      573508       90%
Triangles (filled)       1664728      110%
Rounded rects (outline)  412532       94%
Rounded rects (filled)   3783184      117%
Done!

--- Fast in COMPATIBILITY mode - old:

ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          6044ms  3.31fps  4.07 Mbps 140%
ClearScreen Mbps         6044ms  3.31fps  4.07 Mbps 140%
DrawImage Mbps           6980ms  2.87fps  3.52 Mbps 121%
DrawImageF Mbps          7714ms  2.59fps  3.19 Mbps 110%
Screen fill              1511196      140%
Text                     276932       92%
Lines                    2637380      89%
Horiz/Vert Lines         132280       135%
Rectangles (outline)     91440        130%
Rectangles (filled)      3138956      140%
Circles (filled)         678416       106%
Circles (outline)        1151036      89%
Triangles (outline)      571576       90%
Triangles (filled)       1498052      122%
Rounded rects (outline)  402724       96%
Rounded rects (filled)   3222412      138%
Done!

--- Original Adafruit:

ILI9341 240x320
Benchmark   Time (microseconds)
FillScreen Mbps          8504ms  2.35fps  2.89 Mbps 100%
ClearScreen Mbps         8505ms  2.35fps  2.89 Mbps 0%
DrawImage Mbps           8505ms  2.35fps  2.89 Mbps 0%
DrawImageF Mbps          8505ms  2.35fps  2.89 Mbps 0%
Screen fill              2126432      99%
Text                     256364       99%
Lines                    2364076      100%
Horiz/Vert Lines         179228       100%
Rectangles (outline)     119144       99%
Rectangles (filled)      4416444      99%
Circles (filled)         723332       99%
Circles (outline)        1034928      99%
Triangles (outline)      517836       100%
Triangles (filled)       1835860      100%
Rounded rects (outline)  388900       100%
Rounded rects (filled)   4460552      100%
Done!

*/
 

// ------------------------------------------------

void loop(void) 
{
}

// ------------------------------------------------

unsigned long testFillScreen() {
  unsigned long start = micros();
  //for (uint8_t i = 0; i < 12; i++) {
  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  //}
  return micros() - start;
}

// ------------------------------------------------
unsigned long testText() {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

// ------------------------------------------------
unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

// ------------------------------------------------
unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

// ------------------------------------------------
unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

// ------------------------------------------------
unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

// ------------------------------------------------
unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

// ------------------------------------------------
unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

// ------------------------------------------------
unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      RGBto565(0, 0, i));
  }

  return micros() - start;
}

// ------------------------------------------------
unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      RGBto565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      RGBto565(i, i, 0));
  }

  return t;
}

// ------------------------------------------------
unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, RGBto565(i, 0, 0));
  }

  return micros() - start;
}

// ------------------------------------------------
unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, RGBto565(0, i, 0));
  }

  return micros() - start;
}
// ------------------------------------------------

