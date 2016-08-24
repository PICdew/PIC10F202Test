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


// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = ON       // Master Clear Enable (GP3/MCLR pin function  is MCLR)

//#include <10F202.h> 
#include <xc.h>

#define _XTAL_FREQ 4000000


asm( " org     0x000 " );
asm( " movwf   0xFC " );



void main(void)
{
    
//GP0, GP1, GP2, GP*/MCLR
    TRISGPIO = 0;
    
    while(1){
        GP0 = 1;
       __delay_ms(500);
       GP0 = 0;
       __delay_ms(500);
    }
    
}
