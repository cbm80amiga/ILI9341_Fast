# ILI9341_Fast
Fast SPI library for the ILI9341 240x320 TFT display

Significantly optimized for 16MHz AVR Arduino boards (2.5-3x faster than other libraries)

Achieved 6.9Mbps SPI transfer rate (at DIV2/16MHz clock)

YouTube video:

https://youtu.be/0RnzPXBY3SM

## Recent optimizations

After recent optimizations (more AVR assembler) all fill and copy operations work with max speed of about 7.1Mbps for 16MHz Arduino and the library flash memory usage is reduced by about 800-900 bytes

## Configuration

Use "define COMPATIBILITY_MODE" - then the library should work on all Arduino compatible boards
Remove above for the best performance on 16MHz AVR

Use "#define CS_ALWAYS_LOW" if CS pin is connected to the ground, it gives little better performance

Tested with **Arduino IDE 1.6.5 and Adafruit_GFX 1.5.6**

## Extra Features
- invertDisplay()
- sleepDisplay()
- enableDisplay()
- resetDisplay() - software reset
- partialDisplay() and setPartArea() - limiting display area for power saving
- setScrollArea() and setScroll() - smooth vertical scrolling
- very fast drawImage() from RAM
- fast drawImage() from flash (PROGMEM)

## Connections:

|LCD pin|LCD pin name|Arduino|
|--|--|--|
|#1| MISO|NC or MISO|
|#2| LED |3.3V|
|#3| SCK|SCL/D13|
|#4| SDI|MOSI/D11|
|#5| DC |D8 or any digital|
|#6| RESET|D9 or any digital|
|#7| CS |D10 or any digital|
|#8| GND|GND|
|#9| VCC|3.3V|
 
If you find it useful and want to buy me a coffee or a beer:

https://www.paypal.me/cbm80amiga
