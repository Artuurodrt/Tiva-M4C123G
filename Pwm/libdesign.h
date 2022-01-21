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

#ifndef LIBDESIGN_H_
#define LIBDESIGN_H_

/*GPIO Modules
 * Function: GPIO_Module_RM
 */
#define GPIO_PORTA 0x01
#define GPIO_PORTB 0x02
#define GPIO_PORTC 0x04
#define GPIO_PORTD 0x08
#define GPIO_PORTE 0x10
#define GPIO_PORTF 0x20

/*Enable/Disable*/
#define ENABLE 0x01
#define DISABLE 0x00

/*PWM Module
 * Function: PWM_Module_RM
 */
#define PWM_MODULE_0 0x00
#define PWM_MODULE_1 0x01

/*PWM Clock (RCC Register - USEPWMDIV)
 * Function: RCC_PWM_Clock
 */
#define SYSTEM_CLOCK 0x00
#define PWM_CLOCK_DIVISOR 0x01


/* PWM Unit Clock Divisor (RCC Register - PWMDIV)
 * Function: RCC_PWM_Clock_Div
 *
                         Divisor*/
#define DIV_2 0x00    /*   /2   */
#define DIV_4 0x01    /*   /4   */
#define DIV_8 0x02    /*   /8   */
#define DIV_16 0x03   /*   /16  */
#define DIV_32 0x04   /*   /32  */
#define DIV_64 0x05   /*   /64  */
#define DIV2_64 0x06  /*   /64  */
#define DIV3_64 0x07  /*   /64  */





#endif /* LIBDESIGN_H_ */
