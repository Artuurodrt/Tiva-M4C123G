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
  * Register: Pulse Width Modulator Run Mode Clock Gating Control (RCGCPWM)
  *
  * Parameters   : Module - PWM Module 0/ PWM Module 1
  *                Enable - PWM Module (Enabled(1)/Disabled(0))
  *
  * Return Value : Nothing
  *
  * Description:
  *
  *    The PWM_Module_RM function, provides software the capability
  *    to enable/disable a clock for the PWM modules in Run mode.
  */
void PWM_Module_RM(_Bool Module, _Bool Enable);


/*
 * Register: General-Purpose Input/Output Run Mode Clock Gating Control (RCGCGPIO)
 *
 * Parameters   : Port - GPIO Port
 *                 | 1 - Port A |
 *                 | 2 - Port B |
 *                 | 3 - Port C |
 *                 | 4 - Port D |
 *                 | 5 - Port E |
 *                Enable - Provide a clock to GPIO Port (Enabled(1)/Disabled(0))
 *
 * Return Value : Nothing
 *
 * Description:
 *
 *    The GPIO_Module_RM function, provides software the capability
 *    to enable/disable a clock for the GPIO modules in Run mode.
 */
void GPIO_Module_RM(uint8_t Port, _Bool Enable);






#endif /* PWM_H_ */
