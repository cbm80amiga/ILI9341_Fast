// ILI9341 library example
// (c) 2020 Pawel A. Hernik
// Color gauges and progress bars
// YouTube videos:
// https://youtu.be/rdL3qHEnd4Q
// https://youtu.be/x94y-qH2RBs

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
#include "rre_bold13x20.h"
#include "rre_5x8.h"

RREFont font;

// needed for RREFont library initialization, define your fillRect
void customRect(int x, int y, int w, int h, int c) { return lcd.fillRect(x, y, w, h, c); }

//#include "bold13x20digtop_font.h"
//#include "small4x6_font.h"

int cx,cy;
int sx,sy;
int xs0,ys0,xe0,ye0;
int xs1,ys1,xe1,ye1;
uint16_t bgCol;
int i;
char buf[20];

// ------------------------------------------------
#define MAXSIN 255
const uint8_t sinTab[91] PROGMEM = {
0,4,8,13,17,22,26,31,35,39,44,48,53,57,61,65,70,74,78,83,87,91,95,99,103,107,111,115,119,123,
127,131,135,138,142,146,149,153,156,160,163,167,170,173,177,180,183,186,189,192,195,198,200,203,206,208,211,213,216,218,
220,223,225,227,229,231,232,234,236,238,239,241,242,243,245,246,247,248,249,250,251,251,252,253,253,254,254,254,254,254,
255
};

int fastSin(int i)
{
  while(i<0) i+=360;
  while(i>=360) i-=360;
  if(i<90)  return(pgm_read_byte(&sinTab[i])); else
  if(i<180) return(pgm_read_byte(&sinTab[180-i])); else
  if(i<270) return(-pgm_read_byte(&sinTab[i-180])); else
            return(-pgm_read_byte(&sinTab[360-i]));
}

int fastCos(int i)
{
  return fastSin(i+90);
}

// ------------------------------------------------

void drawGauge1(int level)
{
  cx=SCR_WD/2;
  cy=SCR_HT/2;
  int rx0=90, ry0=90;
  int rx1=120, ry1=120;
  int mina=-75;
  int maxa=180+75;
  for(int i=mina; i<maxa; i+=15) {
    sx = fastCos(i-180);
    sy = fastSin(i-180);
    xs0 = cx+sx*rx0/MAXSIN;
    ys0 = cy+sy*ry0/MAXSIN;
    xe0 = cx+sx*rx1/MAXSIN;
    ye0 = cy+sy*ry1/MAXSIN;
    sx = fastCos(i-180+10);
    sy = fastSin(i-180+10);
    xs1 = cx+sx*rx0/MAXSIN;
    ys1 = cy+sy*ry0/MAXSIN;
    xe1 = cx+sx*rx1/MAXSIN;
    ye1 = cy+sy*ry1/MAXSIN;
    int l=100*(i-mina)/(maxa-mina);
    if(l<level) {
      lcd.fillTriangle(xs0,ys0,xe0,ye0,xe1,ye1, lcd.rgbWheel(512L*l/100));
      lcd.fillTriangle(xs1,ys1,xe1,ye1,xs0,ys0, lcd.rgbWheel(512L*l/100));
    } else {
      lcd.fillTriangle(xs0,ys0,xe0,ye0,xe1,ye1, RGBto565(60,60,60));
      lcd.fillTriangle(xs1,ys1,xe1,ye1,xs0,ys0, RGBto565(60,60,60));
    }
  }
  snprintf(buf,10," %d ",level);
  font.setFont(&rre_Bold13x20);
  font.setCharMinWd(13);
  font.setColor(WHITE,BLACK);
  font.printStr(ALIGN_CENTER,SCR_HT/2-10,buf);
}

void drawGauge2(int level)
{
  cx=SCR_WD/2;
  cy=SCR_HT-1-20;
  int rx0=120;
  int rx1=rx0-6;
  int rx2=rx1-8;
  int mina=40;
  int maxa=180-40;
  int lastx,lasty;
  static int xs0Old=0,ys0Old=0,xs1Old=0,ys1Old=0,xe0Old=0,ye0Old=0,xe1Old=0,ye1Old=0;
  for(int i=mina; i<=maxa; i+=10) {
    sx = fastCos(i-180);
    sy = fastSin(i-180);
    xs0 = cx+sx*rx0/MAXSIN;
    ys0 = cy+sy*rx0/MAXSIN;
    xe0 = cx+sx*rx1/MAXSIN;
    ye0 = cy+sy*rx1/MAXSIN;
    lcd.drawLine(xs0,ys0,xe0,ye0,BLACK);
    if(i>mina) lcd.drawLine(xs0,ys0,lastx,lasty,BLACK);
    lastx=xs0;
    lasty=ys0;
    xs0 = cx+sx*rx2/MAXSIN;
    ys0 = cy+sy*rx2/MAXSIN;
    snprintf(buf,4,"%d",(i-mina)/10);
    font.setFont(&rre_5x8);
    font.setColor(RGBto565(150,150,150));
    font.printStr(i==maxa?xs0-4:xs0-2,ys0-2,buf);
  }

  int a = map(level,0,100,mina,maxa);
  rx1 = rx0-12;
  sx = fastCos(a-180);
  sy = fastSin(a-180);
  xs0 = cx+(sx*rx1+MAXSIN/2)/MAXSIN;
  ys0 = cy+(sy*rx1+MAXSIN/2)/MAXSIN;
  rx1 = rx0-42;
  sx = fastCos(a-180);
  sy = fastSin(a-180);
  xs1 = cx+(sx*rx1+MAXSIN/2)/MAXSIN;
  ys1 = cy+(sy*rx1+MAXSIN/2)/MAXSIN;
  rx1 = rx0-42;
  sx = fastCos(a-180-8);
  sy = fastSin(a-180-8);
  xe0 = cx+(sx*rx1+MAXSIN/2)/MAXSIN;
  ye0 = cy+(sy*rx1+MAXSIN/2)/MAXSIN;
  sx = fastCos(a-180+8);
  sy = fastSin(a-180+8);
  xe1 = cx+(sx*rx1+MAXSIN/2)/MAXSIN;
  ye1 = cy+(sy*rx1+MAXSIN/2)/MAXSIN;

  lcd.drawLine(xs1Old,ys1Old,cx,cy,bgCol);
  lcd.fillTriangle(xs0Old,ys0Old,xe0Old,ye0Old,xe1Old,ye1Old,bgCol);
  lcd.drawLine(xs1,ys1,cx,cy,BLACK);
  lcd.fillTriangle(xs0,ys0,xe0,ye0,xe1,ye1,RED);
  lcd.fillCircle(cx,cy,2,BLACK);
  xs0Old=xs0; ys0Old=ys0; xs1Old=xs1; ys1Old=ys1;
  xe0Old=xe0; ye0Old=ye0; xe1Old=xe1; ye1Old=ye1;
}

void drawGauge3(int level)
{
  cx=SCR_WD/2;
  cy=SCR_HT/2;
  int rx0=120;
  int rx1;
  int mina=0;
  int maxa=270;
  int lastx,lasty;
  static int xs0Old=0,ys0Old=0;
  for(int i=mina; i<=maxa; i+=3) {
    sx = fastCos(i-270);
    sy = fastSin(i-270);
    xs0 = cx+sx*rx0/MAXSIN;
    ys0 = cy+sy*rx0/MAXSIN;
    if(i>mina) lcd.drawLine(xs0,ys0,lastx,lasty,WHITE);
    lastx=xs0;
    lasty=ys0;
  }
  for(int i=mina; i<=maxa; i+=9) {
    sx = fastCos(i-270);
    sy = fastSin(i-270);
    xs0 = cx+sx*rx0/MAXSIN;
    ys0 = cy+sy*rx0/MAXSIN;
    if(i%27==0) rx1=rx0-14; else rx1=rx0-7;
    xe0 = cx+sx*rx1/MAXSIN;
    ye0 = cy+sy*rx1/MAXSIN;
    lcd.drawLine(xs0,ys0,xe0,ye0,WHITE);
  }

  int a = map(level,0,100,mina,maxa);
  rx1=rx0-18;
  sx = fastCos(a-270);
  sy = fastSin(a-270);
  xs0 = cx+sx*rx1/MAXSIN;
  ys0 = cy+sy*rx1/MAXSIN;
  lcd.drawLine(xs0Old,ys0Old,cx,cy,BLACK);
  lcd.drawLine(xs0,ys0,cx,cy,RED);
  lcd.fillCircle(cx,cy,2,RED);
  xs0Old=xs0; ys0Old=ys0;

  lcd.fillRect(SCR_WD-13*3-2,SCR_HT-20,13*3+2,20,BLACK);
  snprintf(buf,10,"%d",level);
  font.setFont(&rre_Bold13x20);
  font.setCharMinWd(13);
  font.setColor(WHITE);
  font.printStr(ALIGN_RIGHT,SCR_HT-20,buf);
}

void drawGauge4(int level)
{
  cx=SCR_WD-1;
  cy=SCR_HT-1;
  long rx0=240-4, ry0=240-4;
  long rx1=rx0-40, ry1=ry0-40;
  long rx2=rx0+4, ry2=ry0+4;
  int mina=0;
  int maxa=90;
  for(int i=mina; i<=maxa; i+=5) {
    sx = fastCos(i-180);
    sy = fastSin(i-180);
    xs0 = cx+sx*rx0/MAXSIN;
    ys0 = cy+sy*ry0/MAXSIN;
    xe0 = cx+sx*rx1/MAXSIN;
    ye0 = cy+sy*ry1/MAXSIN;
    if(i>mina) {
      if(i<=level) {
        lcd.fillTriangle(xs0,ys0,xe0,ye0,xe1,ye1, lcd.rgbWheel(85*2*(90-i)/90));
        lcd.fillTriangle(xs1,ys1,xe1,ye1,xs0,ys0, lcd.rgbWheel(85*2*(90-i)/90));
      } else {
        lcd.fillTriangle(xs0,ys0,xe0,ye0,xe1,ye1, RGBto565(60,60,60));
        lcd.fillTriangle(xs1,ys1,xe1,ye1,xs0,ys0, RGBto565(60,60,60));
      }
    }
    xs1 = xs0; ys1 = ys0;
    xe1 = xe0; ye1 = ye0;
    xe0 = cx+sx*rx2/MAXSIN;
    ye0 = cy+sy*ry2/MAXSIN;
    lcd.drawLine(xs0,ys0,xe0,ye0, YELLOW);
  }
  lcd.fillRect(SCR_WD-(13*3+2)*1,SCR_HT-20,(13*3+2)*1,20,BLACK);
  snprintf(buf,10,"%d",level);
  font.setFont(&rre_Bold13x20);
  font.setCharMinWd(13);
  font.setColor(WHITE);
  font.printStr(ALIGN_RIGHT,SCR_HT-20,buf);
}

void drawBar(int level)
{
  int i=level*SCR_WD/100;
  int ht=31;
  lcd.fillRect(0,20,i,ht,lcd.rgbWheel(85*2*level/100));
  lcd.fillRect(i,20,SCR_WD-i,ht,RGBto565(60,60,60));

  for(i=0;i<SCR_WD;i+=24) {
    //uint16_t col = (i<level*SCR_WD/100) ? lcd.rgbWheel(85*2*i/SCR_WD) : RGBto565(60,60,60);
    uint16_t col = (i<level*SCR_WD/100) ? lcd.rgbWheel(150*i/SCR_WD) : RGBto565(60,60,60);
    lcd.fillRect(i,SCR_HT-20-ht,20,ht,col);
  }
  
  snprintf(buf,10," %d ",level);
  font.setFont(&rre_Bold13x20);
  font.setCharMinWd(13);
  font.setColor(WHITE,BLACK);
  font.printStr(ALIGN_CENTER,SCR_HT/2-10,buf);
}

int barLev[16]={0};
int barLevOld[16]={0};
int barLevSet[16]={0};
int barDec[16]={0};

void drawEqBars()
{
  int w=16;
  for(int i=0;i<16;i++) {
    if(barLev[i]<barLevOld[i]) lcd.fillRect(i*w,SCR_HT-1-barLevOld[i],w-1,barLevOld[i]-barLev[i],BLACK);
    uint8_t r,g,b;
    lcd.rgbWheel(85*6*i/16,&r,&g,&b);
    int br=barLev[i];
    if(br<30) br=30; else
    if(br>100) br=127; else br=30+(127-30)*(br-30)/(100-30);
    lcd.fillRect(i*w,SCR_HT-1-barLev[i],w-1,barLev[i],RGBto565(r*br/127,g*br/127,b*br/127));
    barLevOld[i]=barLev[i];
  }
  
  for(int i=0;i<16;i++) {
    if(!barDec[i]) {
      if(barLev[i]>barLevSet[i]) {
        barLev[i]-=4;
        if(barLev[i]<barLevSet[i]) { barLev[i]=barLevSet[i]; barDec[i]=1; } 
      } else {
        barLev[i]+=4;
        if(barLev[i]>barLevSet[i]) { barLev[i]=barLevSet[i]; barDec[i]=1; } 
      }
    } else {
      barLev[i]--;
      if(barLev[i]<0) barLev[i]=0;
    }
  }
  int r=random(16);
  barLevSet[r]=random(10,SCR_HT); barDec[r]=0;
  if(r>0)  { barLevSet[r-1]=7*barLevSet[r]/10; barDec[r-1]=0; }
  if(r<15) { barLevSet[r+1]=7*barLevSet[r]/10; barDec[r+1]=0; }
}

unsigned long ms,tm=15000;

void setup(void) 
{
  Serial.begin(9600);
  lcd.init();
  lcd.fillScreen(BLACK);
  font.init(customRect, SCR_WD, SCR_HT); // custom fillRect function and screen width and height values
  font.setFont(&rre_5x8);
  font.setColor(GREEN);
  font.printStr(ALIGN_CENTER,SCR_HT/2-3,"GAUGES DEMO");
  //delay(2000);
}

void loop() 
{
  lcd.fillScreen(BLACK);
  ms=millis();
  while(millis()-ms<tm) {
    for(i=0;i<=100;i+=5) { drawGauge1(i); delay(10); }
    delay(250);
    for(i=100;i>=0;i-=5) { drawGauge1(i); delay(10); }
    delay(250);
  }

  lcd.fillScreen(BLACK);
  ms=millis();
  while(millis()-ms<tm) {
    for(i=0;i<=100;i+=5) { drawBar(i); delay(30); }
    delay(250);
    for(i=100;i>=0;i-=5) { drawBar(i); delay(30); }
    delay(250);
  }

  bgCol=RGBto565(220,220,220);
  lcd.fillScreen(bgCol);
  ms=millis();
  while(millis()-ms<tm) {
    for(i=0;i<=100;i+=2) { drawGauge2(i); delay(10); }
    delay(450);
    for(i=100;i>=0;i-=2) { drawGauge2(i); delay(10); }
    delay(450);
  }

  lcd.fillScreen(BLACK);
  ms=millis();
  while(millis()-ms<tm) {
    drawEqBars(); delay(5);
  }

  lcd.fillScreen(BLACK);
  ms=millis();
  while(millis()-ms<tm) {
    for(i=0;i<=100;i+=2) { drawGauge3(i); delay(20); }
    delay(450);
    for(i=100;i>=0;i-=2) { drawGauge3(i); delay(20); }
    delay(450);
  }

  lcd.fillScreen(BLACK);
  ms=millis();
  while(millis()-ms<tm) {
    for(i=0;i<=90;i+=5) { drawGauge4(i); delay(5); }
    delay(450);
    for(i=90;i>=0;i-=5) { drawGauge4(i); delay(5); }
    delay(450);
  }
}


