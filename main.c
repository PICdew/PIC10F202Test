/*
PIC10F202Test - A test programm fo the PIC10F202 microcontroller
Copyright (C) 2016-2016 Simon Wyss <wysi94@gmail.com>

This file is part of PIC10F202Test.

PIC10F202Test is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PIC10F202Test is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with PIC10F202Test.  If not, see <http://www.gnu.org/licenses/>.
*/

//Attention: Programm Space in Flash set to 0..1FE in Project settings
//because the last row is used for the oscal calibration value


// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = OFF       // Master Clear Enable (GP3/MCLR pin function  is MCLR)

//#include <10F202.h> 
#include <xc.h>

#define _XTAL_FREQ 4000000

//#pragma FOSC4_bit FC

//asm( " org     0x000 " );
//asm( " movwf   0xFC " );

//defines
#define nCHANWAKE	7  //nGPWU
#define nWEAKPULL	6	//GPPU
#define T0CKIPIN	5	//T0CS
#define T0NEGEDGE	4	//T0SE
#define PRESCALWDT  3  //PSA

void main(void)
{
    asm("MOVLW 0xFE");  //FC = 100.3, F0 = 97.3, FA=100.02, FE = 1.0005MHz OSC/4 Clock-out, LSB = FOSC4 don't set!
    asm("MOVWF OSCCAL");
    
	//GP0, GP1, GP2, GP*/MCLR
    TRIS = 0; //set All Pins as Output, TRIS = TRISGPIO
	//ENABLE: weak-pullups, Timer0 intosc source, Prescaler for WDT - no Prescaler for Timer0
	OPTION = (1<<nCHANWAKE)|(0<<nWEAKPULL)|(0<<T0CKIPIN)|(0<<T0NEGEDGE)|(1<<PRESCALWDT); 
	
	//set INTOSC/4 Output on GP2
	//OSCCAL |= 0b00000001;
	//or:
	//FOSC4 = 1;
	//1.0006052 MHz INTOSC/4 was reached with OSCAL = 0xFF
	
	//PWM for FAN: 25kHz, Dutycycle 0 to 100%
	//25kHz = 40us = 0.04ms
	
	//4MHz INTOSC, CPU = 1MHZ, = 1us
	
	//8-Bit Timer init:
	GP0 = 0;
#define pvalue 20
#define ptotal 40
	
	//main loop
	while(1){
       /*
		GP0 = 1;
       __delay_ms(20);
       GP0 = 0;
       __delay_ms(20);
	   */
		
		
		GP2 = 1; //probably use HIGH-Impendance mode instead of PULL-HIGH: TRIS = 0b0001;
		//TRIS = 0b0001; //works, but rising edge is not steep because of the weak-pullup
		__delay_us(pvalue);
		/*
		int i = 0; //Total 40 cycles for PWM
		while(i<10){
			i++; //one increment = 1 instruction -> 10 = 10us
		}
		*/
		GP2 = 0;  //TRISGIPIO = 0b0000;
		//TRIS = 0b0000;
		__delay_us(ptotal-pvalue);
		/*
		i = 0;
		while(i<30){
			i++;
		}
		*/
    }
    
}
