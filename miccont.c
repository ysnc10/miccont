/*
 * File:   miccont.c
 * Author: hsnct
 */

#include <xc.h>
#include <pic16f628a.h>

// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC =  INTOSCIO  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, Resistor and Capacitor on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000
#define MIC_ID 12 //4bit 1100

/*unsigned int Baud_Rate_MASTER(long int baudrate){
     unsigned int x;
     x = (_XTAL_FREQ - baudrate*4)/(baudrate*4); //for master
     return x;
 }*/

void USART_Init(long int Baudrate)
{
    BRGH=1;
    unsigned int x;
    x = (_XTAL_FREQ - Baudrate*16)/(Baudrate*16); 
    SPBRG = x;                                    //Writing SPBRG Register 9600 BAUD RATE
    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
    SPEN = 1;                                     //Enables Serial Port
    TRISB1 = 1;                                   //As Prescribed in Datasheet
    TRISB2 = 1;                                   //As Prescribed in Datasheet
}
  
  
void Write(char data)
{
  TXEN = 1;                                     //Enables Transmission
  while(!TXIF);
  TXREG = data;
                                    
}
char TSR_Empty()
{
  return TRMT;
}

char ReceiveReady()
{
  return RCIF;
}
char Read()
{
  CREN=1;//Enables Continuous Reception
  if(OERR){
      CREN=0;
      CREN=1;
  }//RESET
  while(!RCIF);
  return RCREG;
  
}

unsigned char rx,tx;
int open1,open2,open3,open4;

void main(void) {
  
    TRISB0=0;
    TRISB4=1;
    TRISB5=1;
    TRISB6=1;
    TRISB7=1;
    USART_Init(9600);
    TRISA=0X00;
    CMCON=0X07;
    PORTA=0x00;
    RB0=0;
    rx=0xc5;
    Write(rx);

while(1){
    rx=Read();
    tx=rx;
    RA0=(rx%2);
    RA1=((rx>>1)%2);
    RA2=((rx>>2)%2);
    RA3=((rx>>3)%2);

    Write(tx);
   }
}
/*
     if(RB0){
        tx++;
        __delay_ms(1000);
    }
 */