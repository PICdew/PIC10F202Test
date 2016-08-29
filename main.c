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
    
	//GP0, GP1, GP2, GP*/MCLR
    TRIS = 0b1110; //Inputs = 1, GP0 = Output, TRIS = TRISGPIO
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
//#define pvalue 20

#define pmax 9

	uint8_t pwmValue = 1;
	
	uint8_t switchBuffer = 0;
	uint8_t switchValueOld = 0;
	
	switchValueOld = GPIO & 0b1110; //delet GP0, because this is no input
	switchValueOld = switchValueOld >> 1; //LSB right justified
	
	//int i = 0;
	uint8_t switchTimer = 0;
	
	//main loop
	while(1){
		/*
		switchBuffer = GPIO & 0b1110; //delet GP0, because this is no input
		switchBuffer = switchBuffer >> 1; //LSB right justified
		
		if(switchBuffer > switchValueOld){ //rotation to the right, higher value
			if(pwmValue < pmax){
				pwmValue++;
			}
		}
		else if(switchBuffer < switchValueOld){ //rotation to the left, lower value
			if(pwmValue > 0){
				pwmValue--;
			}
		}
		*/
		//pwmValue = (GPIO  & 0b00001110) >> 1;
		pwmValue = ((GPIO ^ 0xFF) & 0b00001110) >> 1;
		
/*
//Table Time ON vs Current:
0   50 mA
5  150
12 490
20 600
25 240 ???
30 380 ???
35 720 		
40 930  (always on)		
*/
#define ptotal 40
		
#define p0 0
#define p1 5 
#define p2 12 
#define p3 20
#define p4 25
#define p5 30
#define p6 35
#define p7 40
		
		//switchTimer = 0;
		switch(pwmValue){
			case 0:
				while(1){ 
					GP0 = 0;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					//__delay_us(p0);
					//GP0 = 0;
					__delay_us(ptotal-p0);
				}
				break;
			case 1:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p1);
					GP0 = 0;
					__delay_us(ptotal-p1);
				}
				break;
			case 2:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p2);
					GP0 = 0;
					__delay_us(ptotal-p2);
				}
				break;
			case 3:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p3);
					GP0 = 0;
					__delay_us(ptotal-p3);
				}
				break;
			case 4:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p4);
					GP0 = 0;
					__delay_us(ptotal-p4);
				}
				break;
			case 5:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p5);
					GP0 = 0;
					__delay_us(ptotal-p5);
				}
				break;
			case 6:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p6);
					GP0 = 0;
					__delay_us(ptotal-p6);
				}
				break;
			case 7:
				while(1){
					GP0 = 1;
					switchTimer++;
					if(switchTimer == 0){
						break;
					}
					__delay_us(p7);
					//GP0 = 0;
					__delay_us(ptotal-p7);
				}
				break;
			default:
				break;
		}
		
		/*
		GP0 = 1;
		for(i=0;i<pwmValue;i++){
			__delay_us(1);
		}
		GP0 = 0;
		for(i=0;i<(pmax-pwmValue);i++){
			__delay_us(1);
		}
		*/		
		
		//GP0 = 1;
		/*
		int i;
		for(i=0;i<pwmValue;i++){
			//asm("nop");
		}
		*/
		/*int i = 0;
		while(i<pwmValue){
			i++;
		}*/
		
		//GP0 = 0;
		/*
		for(i=0;i<(ptotal - pwmValue);i++){
			//asm("nop");
		}
		*/
		
		/*
		i = 0;
		while(i<pwmValue){
			i++;
		}
		*/
				
		/*
		GP0 = 1; //probably use HIGH-Impendance mode instead of PULL-HIGH: TRIS = 0b0001;
		//TRIS = 0b0001; //works, but rising edge is not steep because of the weak-pullup
		__delay_us(pvalue);

		GP0 = 0;  //TRISGIPIO = 0b0000;
		__delay_us(ptotal-pvalue);
		*/
    }
    
}
