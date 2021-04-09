//RPM lights for SR-21
//Schulich Racing
//Author: Gustavo Da Costa


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_PIN 7 //depending on what pins available

#define LED_COUNT 16

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//initializing colours being used for the strip here
uint32_t no_color = strip.Color(  0, 0, 0);
uint32_t white = strip.Color(255,   255,   255);
uint32_t yellow = strip.Color(  255, 255,   0);
uint32_t red = strip.Color( 255, 0, 0);
uint32_t blue = strip.Color(0, 0, 225);


#include <SPI.h>

#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

const int LED        = 8;
boolean ledON        = 1;

void setup() {
  SERIAL_PORT_MONITOR.begin(115200);
  pinMode(LED, OUTPUT);

  while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
      SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
      delay(100);
  }
  SERIAL_PORT_MONITOR.println("CAN init ok!");

  strip.begin();           //INITIALIZE NeoPixel strip object
  strip.show();            //Turn OFF all pixels ASAP
  strip.setBrightness(30); //Set BRIGHTNESS to about 1/5 (max = 255)

}

void loop() {
 // put your main code here, to run repeatedly:
 unsigned char len = 0;
 unsigned char buf[8];
 unsigned short range;
 int x;

 if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
     CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

     unsigned long canId = CAN.getCanId();

     SERIAL_PORT_MONITOR.println("-----------------------------");
     SERIAL_PORT_MONITOR.println("get data from ID: 0x");
     SERIAL_PORT_MONITOR.println(canId, HEX);

     for (int i = 0; i < len; i++) { // print the data
          SERIAL_PORT_MONITOR.print(buf[i]);
          SERIAL_PORT_MONITOR.print("\t");
          if (ledON && i == 0) {

                digitalWrite(LED, buf[i]);
                ledON = 0;
                delay(500);
           } else if ((!(ledON)) && i == 4) {

                 digitalWrite(LED, buf[i]);
                 ledON = 1;
           }
       }
       SERIAL_PORT_MONITOR.println();
 }

 range = (buf[0] << 8) + buf[1];
 inc_shift_blue(det_range(range));
 
}

int det_range(unsigned short range)
{
      int x;
      if(range <= 1500)
      {
       x = 0;
      }
      if(range > 1500 && range <= 2000)
      {
       x = 1;
      }
      if(range > 2000 && range <= 2966)
      {
       x = 2;
      }
      if(range > 2966 && range <= 3932)
      {
       x = 3;
      }
      if(range > 3932 && range <= 4898)
      {
       x = 4;
      }
      if(range > 4898 && range <= 5864)
      {
       x = 5;
      }
      if(range > 5864 && range <= 6830)
      {
       x = 6;
      }
      if(range > 6830 && range <= 7796)
      {
       x = 7;
      }
      if(range > 7796 && range <= 8762)
      {
       x = 8;
      }
      if(range > 8762 && range <= 9728)
      {
       x = 9;
      }
      if(range > 9728 && range <= 10694)
      {
       x = 10;
      }
      if(range > 10694 && range <= 11660)
      {
       x = 11;
      }
      if(range > 11660 && range <= 12626)
      {
       x = 12;
      }
      if(range > 12626 && range <= 13592)
      {
       x = 13;
      }
      if(range > 13592 && range <= 14558)
      {
       x = 14;
      }
      if(range > 14558 && range <= 15524)
      {
       x = 15;
      }
      if(range > 15524 && range <= 16000)
      {
       x = 16;
      }
      if(range > 16000 && range <= 16500)
      {
       x = 17;
      }
      return x;
}


//code for rpm ranges below
//PROMISES: rpm ranges will update the number of LEDs lit at a given moment. White LEDs will be for low ranges,
//yellow for mid ranges, red for high ranges, and all LEDs will be blink red when the car is at its max rpm, signaling to shift now.
//
//REQUIRES:depending on the signal recieved, the signal will convert be converted into an rpm, 
//rpm will be given a range value, and that range value will be sent into this function. A value
//wait value of required for the test, not sure about field application yet. Will probably be needed
//in order to not fry the LEDS.
void inc_shift_blue(int x){
  
  if (x == 0){
    strip.setPixelColor(15, no_color);
    strip.show();
    //delay(wait);
  }

  if (x >= 1 && x < 16){
    for(int i=15; i > (15 - x); i--){
      strip.setPixelColor(i, blue);
    }
    strip.show();
    //delay(wait);
  }

  if (x==16){
    shift_now(red);
  }
  
  if (x==17){
    over_rev(red, 125);
  }
  
  strip.clear();
}

//code for when car's RPMs are at max
//PROMISES: all lights will be red
//
//REQUIRES: a color input (in this case Red) and a delay input for testing
//and to prevent LEDs from frying.
void shift_now(uint32_t color){
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i , color);
  }
  strip.show();
  //delay(wait);
}


//code for when car's RPMs are over max
//PROMISES: all lights will be blink red
//
//REQUIRES: a color input (in this case Red) and a delay input for testing
//and to prevent LEDs from frying.
void over_rev(uint32_t color, int wait){
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i , color);
  }
  strip.show();
  delay(wait);
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i , no_color);
  }
  strip.show();
  delay(wait);
}
