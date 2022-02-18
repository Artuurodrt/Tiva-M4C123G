#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

void config_uart0(void);
void tx_car(char c);


void Delay(unsigned long counter);




int main(){

    char data_Chr[10];
    float data;
    config_uart0();
    for(int i=0;i<417;i++);

    while(1){
        data = 200.0;
        sprintf(data_Chr, "%f", data);
        for(int i=0;i<5;i++){
            tx_car(data_Chr[i]);
        }
        tx_car('\r');
        tx_car('\n');


        Delay(10);

    }

    return 0;
}


void config_uart0(void){

    SYSCTL_RCGCUART_R |= 0x01;  /* enable clock to UART0 */
    while((SYSCTL_PRUART_R & 0x01) == 0);//Wait for activation
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R0;
    while((SYSCTL_PRGPIO_R & 0x01) == 0);//Wait for activation
    UART0_CTL_R &= ~(0x01); //UART0 deactivated UARTEN = 0
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PUR_R |= ~(0x03);
    GPIO_PORTA_PDR_R |= ~(0x03);
    GPIO_PORTA_DIR_R |= ~(0x01); //Input PA0
    GPIO_PORTA_DIR_R |= ~(0x02); //Output PA1
    GPIO_PORTA_PCTL_R |= (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_DEN_R |= 0x03;
    UART0_IBRD_R = (UART0_IBRD_R & ~0xFFFF) + 104;
    UART0_FBRD_R = (UART0_FBRD_R & ~0x3F) + 11;
    UART0_LCRH_R = (UART0_LCRH_R & ~0xFF) | 0x70;
    UART0_CTL_R &= ~0x20; //HSE=0
    UART0_CTL_R |=0x301;  //UARTEN = 1, RXE=1, TXE=1
}

void tx_car(char c){

    while((UART0_FR_R & UART_FR_TXFF) != 0);
    UART0_DR_R = c;
}



void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter*10000; i++);
}
