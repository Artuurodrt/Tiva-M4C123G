/*MIT License

Copyright (c) [2022] [Arturo de los Rios]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "inc/tm4c123gh6pm.h"
#include <stdint.h>

#define PORTA 0x01
#define PORTB 0x02
#define PORTC 0x04
#define PORTD 0x08
#define PORTE 0x10
#define PORTF 0x20


void PWM_Module_RM(_Bool Module, _Bool Enable){

    if(Module == 1u){
        if(Enable == 1u){
            SYSCTL_RCGCPWM_R |= (1u << 1);
        }
        else{
            SYSCTL_RCGCPWM_R &= ~(0x00000010);
        }

    }
    else{
        if(Enable == 1u){
            SYSCTL_RCGCPWM_R |= (1u << 0);
        }
        else{
            SYSCTL_RCGCPWM_R &= ~(0x00000001);
        }
    }
}


void GPIO_Module_RM(uint8_t Port, _Bool Enable){

    uint8_t Port_Converted = 0;

   if((Port == PORTA)|(Port == PORTB)|(Port == PORTC)|(Port == PORTD)|(Port == PORTE)|(Port == PORTF)){

    Port_Converted = (1u << Port-1);

    if(Enable == 1u){
    SYSCTL_RCGCGPIO_R |= Port;
    }
    else{
        SYSCTL_RCGCGPIO_R &= ~Port;
    }
   }
}







