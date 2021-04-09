// demo: CAN-BUS Shield, send data
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

const int ledHIGH    = 1;
const int ledLOW     = 0;
                           

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

//unsigned char stmp1[8] = {ledHIGH, 1, 2, 3, ledLOW, 5, 6, 7};
unsigned char stmp1[8] = {6, 64, 0, 0, 0, 0, 0, 0};
unsigned char stmp2[8] = {12, 40, 0, 0, 0, 0, 0, 0};
unsigned char stmp3[8] = {14, 16, 0, 0, 0, 0, 0, 0};
unsigned char stmp4[8] = {17, 80, 0, 0, 0, 0, 0, 0};
unsigned char stmp5[8] = {21, 80, 0, 0, 0, 0, 0, 0};
unsigned char stmp6[8] = {25, 80, 0, 0, 0, 0, 0, 0};
unsigned char stmp7[8] = {29, 126, 0, 0, 0, 0, 0, 0};
unsigned char stmp8[8] = {33, 102, 0, 0, 0, 0, 0, 0};
unsigned char stmp9[8] = {37, 78, 0, 0, 0, 0, 0, 0};
unsigned char stmp10[8] = {41, 54, 0, 0, 0, 0, 0, 0};
unsigned char stmp11[8] = {45, 33, 0, 0, 0, 0, 0, 0};
unsigned char stmp12[8] = {49, 6, 0, 0, 0, 0, 0, 0};
unsigned char stmp13[8] = {52, 138, 0, 0, 0, 0, 0, 0};
unsigned char stmp14[8] = {56, 114, 0, 0, 0, 0, 0, 0};
unsigned char stmp15[8] = {60, 90, 0, 0, 0, 0, 0, 0};
unsigned char stmp16[8] = {62, 78, 0, 0, 0, 0, 0, 0};
unsigned char stmp17[8] = {64, 66, 0, 0, 0, 0, 0, 0};
//unsigned char stmp18[8] = {162, 11, 0, 0, 0, 0, 0, 0};





void loop() {
    SERIAL_PORT_MONITOR.println("In loop");
    // send data:  id = 0x70, standard frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x70, 0, 8, stmp1);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x71, 0, 8, stmp2);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x72, 0, 8, stmp3);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x73, 0, 8, stmp4);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x74, 0, 8, stmp5);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x75, 0, 8, stmp6);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x76, 0, 8, stmp7);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x78, 0, 8, stmp9);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x79, 0, 8, stmp10);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x80, 0, 8, stmp11);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x81, 0, 8, stmp12);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x82, 0, 8, stmp13);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x83, 0, 8, stmp14);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x84, 0, 8, stmp15);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x85, 0, 8, stmp16);
    delay(1000);                       // send data once per second
    CAN.sendMsgBuf(0x86, 0, 8, stmp17);
    delay(1000);                       // send data once per second
    //CAN.sendMsgBuf(0x87, 0, 8, stmp18);
    //delay(1000);                       // send data once per second


}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
