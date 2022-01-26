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


/*GPIO Ports (GPIOAFSEL Register)*/
#define GPIO_PORT_A 0x01
#define GPIO_PORT_B 0x02
#define GPIO_PORT_C 0x03
#define GPIO_PORT_D 0x04
#define GPIO_PORT_E 0x05
#define GPIO_PORT_F 0x06

/*Bus (APB/AHB)*/
#define APB_BUS 0x00
#define AHB_BUS 0x01

/*GPIO Associated Pins (0-7)*/
#define AS_PIN_0 0x01
#define AS_PIN_1 0x02
#define AS_PIN_2 0x04
#define AS_PIN_3 0x08
#define AS_PIN_4 0x10
#define AS_PIN_5 0x20
#define AS_PIN_6 0x40
#define AS_PIN_7 0x80

/*Clear/Write Mode*/
#define WRITE_MODE 0x00
#define CLEAR_MODE 0x01


/*Port Mux Control (GPIOPCTL Register)*/

#define PMC0 0x00
#define PMC1 0x04
#define PMC2 0x08
#define PMC3 0x0C
#define PMC4 0x10
#define PMC5 0x14
#define PMC6 0x18
#define PMC7 0x1C

#endif /* LIBDESIGN_H_ */
