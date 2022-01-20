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

#ifndef PWM_H_
#define PWM_H_

#define SYSCTL_RCGCPWM_R        (*((volatile uint32_t *)0x400FE640))

 /*
  *
  * Parameters   : Module - PWM Module 0/ PWM Module 1
  *                Enable - PWM Module (Enabled/Disabled)
  *
  * Return Value : Nothing
  *
  * Description:
  *
  *    The PWM_Module_RM function, provides software the capability
  *    to enable/disable a clock for the PWM modules in Run mode.
  *
  */
void PWM_Module_RM(bool Module, bool Enable){

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



#endif /* PWM_H_ */
