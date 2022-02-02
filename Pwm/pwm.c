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

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "libdesign.h"

#define PORTA 0x01
#define PORTB 0x02
#define PORTC 0x04
#define PORTD 0x08
#define PORTE 0x10
#define PORTF 0x20

#define PORTA_GPIO_APB_ADDRESS 0x40004000
#define PORTB_GPIO_APB_ADDRESS 0x40005000
#define PORTC_GPIO_APB_ADDRESS 0x40006000
#define PORTD_GPIO_APB_ADDRESS 0x40007000
#define PORTE_GPIO_APB_ADDRESS 0x40024000
#define PORTF_GPIO_APB_ADDRESS 0x40025000

#define PORTA_GPIO_AHB_ADDRESS 0x40058000
#define PORTB_GPIO_AHB_ADDRESS 0x40059000
#define PORTC_GPIO_AHB_ADDRESS 0x4005A000
#define PORTD_GPIO_AHB_ADDRESS 0x4005B000
#define PORTE_GPIO_AHB_ADDRESS 0x4005C000
#define PORTF_GPIO_AHB_ADDRESS 0x4005D000

#define GPIO_CTL_OFFSET 0x52C
#define GPIO_DEN_OFFSET 0x51C








void PWM_Module_RM(_Bool Module, _Bool Enable){

    if(Module == 1u){
        if(Enable == ENABLE){
            SYSCTL_RCGCPWM_R |= (1u << 1);
        }
        else{
            SYSCTL_RCGCPWM_R &= ~(0x00000010);
        }

    }
    else{
        if(Enable == ENABLE){
            SYSCTL_RCGCPWM_R |= (1u << 0);
        }
        else{
            SYSCTL_RCGCPWM_R &= ~(0x00000001);
        }
    }
}


void GPIO_Module_RM(uint8_t Port, _Bool Enable){


   if((Port == PORTA)|(Port == PORTB)|(Port == PORTC)|(Port == PORTD)|(Port == PORTE)|(Port == PORTF)){

    if(Enable == ENABLE){
    SYSCTL_RCGCGPIO_R |= Port;
    }
    else{
        SYSCTL_RCGCGPIO_R &= ~Port;
    }
   }
}


void RCC_PWM_Clock(_Bool Pwm_Clock){

    if(Pwm_Clock == SYSTEM_CLOCK){
        SYSCTL_RCC_R &= ~0x00100000;
    }
    else{
        SYSCTL_RCC_R |=  0x00100000;
    }

}

void RCC_PWM_Clock_Div(uint8_t Pwm_Div){
    if(Pwm_Div <= 0x07){
        SYSCTL_RCC_R &= ~( (1u << 17) | (1u << 18) | (1u << 19) ); /*Clear PWMDIV bits - (PWMDIV) divides by 2 (000)*/
        SYSCTL_RCC_R |= (Pwm_Div << 17);
    }
}

void GPIO_AF_Select(uint8_t Port, uint8_t associated_Pin, _Bool Bus, _Bool Mode){

    if(Mode == WRITE_MODE){
    /*GPIO AFSEL PORT A*/
    if(Port == GPIO_PORT_A){
        (Bus == APB_BUS) ?  (GPIO_PORTA_AFSEL_R |= associated_Pin) : (GPIO_PORTA_AHB_AFSEL_R |= associated_Pin);
         }
    /*GPIO AFSEL PORT B*/
    else if(Port == GPIO_PORT_B){
        (Bus == APB_BUS) ?  (GPIO_PORTB_AFSEL_R |= associated_Pin) : (GPIO_PORTB_AHB_AFSEL_R |= associated_Pin);
        }
    /*GPIO AFSEL PORT C*/
    else if(Port == GPIO_PORT_C){
        (Bus == APB_BUS) ?  (GPIO_PORTC_AFSEL_R |= associated_Pin) : (GPIO_PORTC_AHB_AFSEL_R |= associated_Pin);
        }
    /*GPIO AFSEL PORT D*/
    else if(Port == GPIO_PORT_D){
        (Bus == APB_BUS) ?  (GPIO_PORTD_AFSEL_R |= associated_Pin) : (GPIO_PORTD_AHB_AFSEL_R |= associated_Pin);
        }
    /*GPIO AFSEL PORT E*/
    else if(Port == GPIO_PORT_E){
        (Bus == APB_BUS) ?  (GPIO_PORTE_AFSEL_R |= associated_Pin) : (GPIO_PORTE_AHB_AFSEL_R |= associated_Pin);
        }
    /*GPIO AFSEL PORT F*/
    else if(Port == GPIO_PORT_F){
        (Bus == APB_BUS) ?  (GPIO_PORTF_AFSEL_R |= associated_Pin) : (GPIO_PORTF_AHB_AFSEL_R |= associated_Pin);
        }
    }
    else{
     /*Clear bits of GPIO AFSEL PORT A*/
     if(Port == GPIO_PORT_A){
        (Bus == APB_BUS) ?  (GPIO_PORTA_AFSEL_R &= ~(associated_Pin)) : (GPIO_PORTA_AHB_AFSEL_R &= ~(associated_Pin));
         }
     /*Clear bits of GPIO AFSEL PORT B*/
     else if(Port == GPIO_PORT_B){
        (Bus == APB_BUS) ?  (GPIO_PORTB_AFSEL_R &= ~(associated_Pin)) : (GPIO_PORTB_AHB_AFSEL_R &= ~(associated_Pin));
         }
     /*Clear bits of GPIO AFSEL PORT C*/
     else if(Port == GPIO_PORT_C){
        (Bus == APB_BUS) ?  (GPIO_PORTC_AFSEL_R &= ~(associated_Pin)) : (GPIO_PORTC_AHB_AFSEL_R &= ~(associated_Pin));
         }
     /*Clear bits of GPIO AFSEL PORT D*/
     else if(Port == GPIO_PORT_D){
        (Bus == APB_BUS) ?  (GPIO_PORTD_AFSEL_R &= ~(associated_Pin)) : (GPIO_PORTD_AHB_AFSEL_R &= ~(associated_Pin));
         }
     /*Clear bits of GPIO AFSEL PORT E*/
     else if(Port == GPIO_PORT_E){
        (Bus == APB_BUS) ?  (GPIO_PORTE_AFSEL_R &= ~(associated_Pin)) : (GPIO_PORTE_AHB_AFSEL_R &= ~(associated_Pin));
         }
     /*Clear bits of GPIO AFSEL PORT F*/
     else if(Port == GPIO_PORT_F){
        (Bus == APB_BUS) ?  (GPIO_PORTF_AFSEL_R &= ~(associated_Pin)) : (GPIO_PORTF_AHB_AFSEL_R &= ~(associated_Pin));
         }
    }
}


void GPIO_Port_Ctl(uint8_t Port,uint8_t PMCn, uint8_t Field,_Bool Bus){

    uint32_t GPIO_PORTX_PCTL_R = 0x00;

    if( Port == GPIO_PORT_A || Port == GPIO_PORT_B || Port == GPIO_PORT_C || Port == GPIO_PORT_D
     || Port == GPIO_PORT_E || Port == GPIO_PORT_F ){

      if(Bus == APB_BUS){
        switch(Port){
        case GPIO_PORT_A:
            GPIO_PORTX_PCTL_R = PORTA_GPIO_APB_ADDRESS + GPIO_CTL_OFFSET;
        break;
        case GPIO_PORT_B:
            GPIO_PORTX_PCTL_R = PORTB_GPIO_APB_ADDRESS + GPIO_CTL_OFFSET;
        break;
        case GPIO_PORT_C:
            GPIO_PORTX_PCTL_R = PORTC_GPIO_APB_ADDRESS + GPIO_CTL_OFFSET;
        break;
        case GPIO_PORT_D:
            GPIO_PORTX_PCTL_R = PORTD_GPIO_APB_ADDRESS + GPIO_CTL_OFFSET;
        break;
        case GPIO_PORT_E:
            GPIO_PORTX_PCTL_R = PORTE_GPIO_APB_ADDRESS + GPIO_CTL_OFFSET;
        break;
        case GPIO_PORT_F:
            GPIO_PORTX_PCTL_R = PORTF_GPIO_APB_ADDRESS + GPIO_CTL_OFFSET;
        break;
        default:
        break;
        }
      }
      else{
          switch(Port){
          case GPIO_PORT_A:
              GPIO_PORTX_PCTL_R = PORTA_GPIO_AHB_ADDRESS + GPIO_CTL_OFFSET;
          break;
          case GPIO_PORT_B:
              GPIO_PORTX_PCTL_R = PORTB_GPIO_AHB_ADDRESS + GPIO_CTL_OFFSET;
          break;
          case GPIO_PORT_C:
              GPIO_PORTX_PCTL_R = PORTC_GPIO_AHB_ADDRESS + GPIO_CTL_OFFSET;
          break;
          case GPIO_PORT_D:
              GPIO_PORTX_PCTL_R = PORTD_GPIO_AHB_ADDRESS + GPIO_CTL_OFFSET;
          break;
          case GPIO_PORT_E:
              GPIO_PORTX_PCTL_R = PORTE_GPIO_AHB_ADDRESS + GPIO_CTL_OFFSET;
          break;
          case GPIO_PORT_F:
              GPIO_PORTX_PCTL_R = PORTF_GPIO_AHB_ADDRESS + GPIO_CTL_OFFSET;
          break;
          default:
          break;
          }
      }
            if(PMCn == PMC0){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x0000000F;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC0);
            }
            else if(PMCn == PMC1){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x000000F0;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC1);
            }
            else if(PMCn == PMC2){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x00000F00;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC2);
            }
            else if(PMCn == PMC3){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x0000F000;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC3);
            }
            else if(PMCn == PMC4){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x000F0000;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC4);
            }
            else if(PMCn == PMC5){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x00F00000;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC5);
            }
            else if(PMCn == PMC6){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0x0F000000;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC6);
            }
            else if(PMCn == PMC7){
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) &= ~0xF0000000;
                (*((volatile  uint32_t*)GPIO_PORTX_PCTL_R)) |= (Field<<PMC7);
            }
      }

}


void GPIO_Digital_Enable(uint8_t Port, uint8_t Pin, _Bool Bus, _Bool Enable){

    uint32_t GPIO_PORTX_DEN_R = 0x00;

    if( Port == GPIO_PORT_A || Port == GPIO_PORT_B || Port == GPIO_PORT_C || Port == GPIO_PORT_D
         || Port == GPIO_PORT_E || Port == GPIO_PORT_F ){

        if(Bus == APB_BUS){
            switch(Port){
               case GPIO_PORT_A:
                   GPIO_PORTX_DEN_R = PORTA_GPIO_APB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_B:
                   GPIO_PORTX_DEN_R = PORTB_GPIO_APB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_C:
                   GPIO_PORTX_DEN_R = PORTC_GPIO_APB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_D:
                   GPIO_PORTX_DEN_R = PORTD_GPIO_APB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_E:
                   GPIO_PORTX_DEN_R = PORTE_GPIO_APB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_F:
                   GPIO_PORTX_DEN_R = PORTF_GPIO_APB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               default:
               break;
          }
        }
        else{
            switch(Port){
               case GPIO_PORT_A:
                   GPIO_PORTX_DEN_R = PORTA_GPIO_AHB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_B:
                   GPIO_PORTX_DEN_R = PORTB_GPIO_AHB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_C:
                   GPIO_PORTX_DEN_R = PORTC_GPIO_AHB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_D:
                   GPIO_PORTX_DEN_R = PORTD_GPIO_AHB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_E:
                   GPIO_PORTX_DEN_R = PORTE_GPIO_AHB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               case GPIO_PORT_F:
                   GPIO_PORTX_DEN_R = PORTF_GPIO_AHB_ADDRESS + GPIO_DEN_OFFSET;
               break;
               default:
               break;
          }
        }

        if(Enable == ENABLE){
        (*((volatile  uint32_t*)GPIO_PORTX_DEN_R)) |= Pin;
        }
        else{
        (*((volatile  uint32_t*)GPIO_PORTX_DEN_R)) &= ~(Pin);
        }
    }
}


