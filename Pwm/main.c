#include "inc/tm4c123gh6pm.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "pwm.h"
#include "libdesign.h"

void delayMs(int n);

int x = 15999;

int main(){

    /*Enable PWM Module 0*/
    PWM_Module_RM(PWM_MODULE_0,ENABLE);

    /*Enable Port B Clock Gating Control*/
    GPIO_Module_RM(GPIO_PORTB,ENABLE);

    /*The system clock is the source for the PWM clock*/
    RCC_PWM_Clock(SYSTEM_CLOCK);

    /* PB6 alternative function for M0PWM0 */
    GPIO_AF_Select(GPIO_PORT_B, AS_PIN_6, APB_BUS, WRITE_MODE);


/*4. Configure the PMCn fields in the GPIOPCTL register to assign the PWM signals to the appropriate pins*/

    GPIO_PORTB_PCTL_R &= ~0x0F000000;
    GPIO_PORTB_PCTL_R |= 0x04000000;

    // Enable the GPIO pins (p.682)
    GPIO_PORTB_DEN_R |= (1u << 6);

/*6. Configure the PWM generator for countdown mode with immediate updates to the parameters */

    /*6.1 Write the PWM0CTL register with a value of 0x0000.0000*/

    PWM0_0_CTL_R = 0x00000000;

    /*6.2 Write the PWM0GENA register with a value of 0x0000.008C*/

    PWM0_0_GENA_R = 0x0000008C;

    /*6.3 Write the PWM0GENB register with a value of 0x0000.080C*/

    //PWM0_0_GENB_R = 0x0000080C;
    //PWM0_0_GENB_R= 0x0000008C;
/*7. Set the period. For a 25-KHz frequency, the period = 1/25,000, or 40 microseconds. The PWM
clock source is 10 MHz; the system clock divided by 2. Thus there are 400 clock ticks per period.
Use this value to set the PWM0LOAD register. In Count-Down mode, set the LOAD field in the PWM0LOAD
register to the requested period minus one */

    /*7.1 Write the PWM0LOAD register with a value of 0x0000.018F (399)*/

    //PWM0_0_LOAD_R = 0x0000018F;  /*( SYS_CLOCK_HZ / 2xDesired-frequency ) - 1  -> (20MHz / 5KHz) - 1 = 399*/
    PWM0_0_LOAD_R = 16000;

/*8. Set the pulse width of the MnPWM0 pin for a 25% duty cycle*/

    /*8.1 Write the PWM0CMPA register with a value of 0x0000.012B (299)*/

    //PWM0_0_CMPA_R = 0x0000012B; /*((1 - Desired-duty) x (SYS_CLOCK_HZ / 2xDesired-freq.))-1  ->   ((1 - 0.25) x (20Mhz/5Khz)) - 1 = 299*/
    //PWM0_0_CMPA_R = 15999;
/*9. Set the pulse width of the MnPWM1 pin for a 75% duty cycle*/

    /*9.1 Write the PWM0CMPB register with a value of 0x0000.0063 (99)*/

   // PWM0_0_CMPB_R = 0x00000063; /*((1 - Desired-duty) x (SYS_CLOCK_HZ / 2xDesired-freq.))-1  ->   ((1 - 0.75) x (20Mhz/5Khz)) - 1 = 99*/
    PWM0_0_CMPB_R = 15999;
/*10. Start the timers in PWM generator 0*/

    /*10.1 Write the PWM0CTL register with a value of 0x0000.0001*/

    PWM0_0_CTL_R = (1u << 0); // The PWM generation block is enabled and produces PWM signals

/*11. Enable PWM outputs*/

    /*11.1 Write the PWMENABLE register with a value of 0x0000.0003*/

    /*The generated pwm0A' signal is passed to the MnPWM0 pin and
      the generated pwm0B' signal is passed to the MnPWM1 pin*/
    //PWM0_ENABLE_R = ((1U<<0) | (1U<<1));
    PWM0_ENABLE_R = (1U<<0);
    //int x;

    /*while(1){

           for(x = 299; x >= 1 ; x-=1){

               PWM0_0_CMPA_R = x;
               delayms(20);
           }
           delayms(50);

           for(x = 1; x <= 299; x+=1){

               PWM0_0_CMPA_R = x;
               delayms(20);
           }
           delayms(50);

       }

   }*/

    for(;;) {
        x = x - 100;

        if (x <= 0)
            x = 16000;

        PWM0_0_CMPA_R = x;

        delayMs(20);
    }
}


    /* delay n milliseconds (16 MHz CPU clock) */
    void delayMs(int n)
    {
        int i, j;

        for(i = 0 ; i < n; i++)
            for(j = 0; j < 3180; j++)
                {}  /* do nothing for 1 ms */
    }
