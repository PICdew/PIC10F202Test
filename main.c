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

/*
//Table FAN San Ace 80: Time ON vs Current:
0   50 mA
5  150
12 490
20 600
25 
30 
35 720 		
40 930  (always on)		
*/

// CONFIG (FUSE-Bits)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = OFF       // Master Clear Enable (GP3/MCLR pin function  is MCLR)

#include <xc.h> //#include <10F202.h>, is included by xc.h
#include <stdint.h>

#define _XTAL_FREQ 4000000

//defines for OPTION register
#define nCHANWAKE	7  //nGPWU
#define nWEAKPULL	6	//GPPU
#define T0CKIPIN	5	//T0CS
#define T0NEGEDGE	4	//T0SE
#define PRESCALWDT  3  //PSA

//Pin-Out Hex Rotary Encoder/Switch
/* HEX-Switch	MCU
 * C			GND
 * 1			not connected (because GP0 is already used for PWM)
 * 2			GP1
 * 4			GP2
 * 8			GP3
 *  
 */

void main(void)
{
    asm("MOVLW 0xFE");  //FC = 100.3, F0 = 97.3, FA=100.02, FE = 1.0005MHz OSC/4 Clock-out, LSB = FOSC4 don't set!
    asm("MOVWF OSCCAL");
    
	//GP0, GP1, GP2, GP3/MCLR
    TRIS = 0b1110; //Inputs = 1, GP0 = Output, TRIS = TRISGPIO
	//ENABLE: weak-pullups, Timer0 intosc source, Prescaler for WDT - no Prescaler for Timer0
	//Attention: no Weak-Pullup available on GP2
	OPTION = (1<<nCHANWAKE)|(0<<nWEAKPULL)|(0<<T0CKIPIN)|(0<<T0NEGEDGE)|(1<<PRESCALWDT); 

	//PWM for FAN: 25kHz, Dutycycle 0 to 100%
	//25kHz = 40us = 0.04ms
	//at the moment used 7ms Period length, works also
	
	//GP0 output init
	GP0 = 0;

	uint8_t pwmValue = 1;
	int i = 0;
	
	//main loop
	while(1){
		//read Rotary switch into variable pwmValue, because LSB of Rotary Switch is unused, shift 1 right
		pwmValue = ((GPIO ^ 0xFF) & 0b00001110) >> 1;
		
		GP0 = 1;
		for(i=0;i<pwmValue;i++){
			__delay_ms(2);
		}
		GP0 = 0;
		for(i=0;i<(7-pwmValue);i++){
			__delay_ms(2);
		}
    }
}



