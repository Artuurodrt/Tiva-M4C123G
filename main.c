#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"


// Accelerometer IMU 10 DOF
// Accelerometer Registers
#define CRL_REG1_A  0x20
#define CRL_REG2_A  0x21
#define CRL_REG3_A  0x22
#define CRL_REG4_A  0x23
#define OUT_X_L_A   0x28
#define OUT_X_H_A   0x29
#define OUT_Y_L_A   0x2A
#define OUT_Y_H_A   0x2B
#define OUT_Z_L_A   0x2C
#define OUT_Z_H_A   0x2D

// Accelerometer slave address IMU 10 DOF
#define I2C_Accelerometer_Slave_Address 0x19
#define I2C_giroscopio_Slave_Address 0x6B

#define RADTOGRAD 57.29577951308


typedef struct LSM303_Data_S
{
    float Ax;
    float Ay;
    float Az;

}LSM303_Data_T;

void setSlaveAddress(uint8_t slaveAddress);
void setMode(uint8_t mode);
void writeByte(uint8_t dataByte, uint8_t conditions);
void config_uart0(void);
void tx_car(char c);
void I2C0_Init(void);
static int I2C_wait_till_done(void);
char I2C0_Wr(int slaveAddr, char memAddr, char data);
char I2C0_Rd(int slaveAddr, char memAddr, int byteCount, char* data);
void Delay(unsigned long counter);
unsigned int LSM303_Init(void);
LSM303_Data_T LSM303_Accelerometer(void);




int main(){

    LSM303_Data_T LSM303_Data;
    char AX_Chr[10];
    char AY_Chr[10];
    char AZ_Chr[10];
    float Pitch, Roll, Yaw = 0.0;
    config_uart0();
    for(int i=0;i<417;i++);
    I2C0_Init();
    LSM303_Init();
    while(1){


        LSM303_Data = LSM303_Accelerometer();


        Pitch = RADTOGRAD*atan2f(-LSM303_Data.Ax,sqrtf(LSM303_Data.Ay*LSM303_Data.Ay+LSM303_Data.Az*LSM303_Data.Az));
        Roll = RADTOGRAD*atan2f(LSM303_Data.Ay,sqrtf(LSM303_Data.Ax*LSM303_Data.Ax+LSM303_Data.Az*LSM303_Data.Az));
        Yaw = RADTOGRAD*atan2f(sqrtf(LSM303_Data.Ax*LSM303_Data.Ax+LSM303_Data.Ay*LSM303_Data.Ay),LSM303_Data.Az);


        sprintf(AX_Chr, "%f", Pitch);
        sprintf(AY_Chr, "%f", Roll);
        sprintf(AZ_Chr, "%f", Yaw);

        for(int i=0;i<9;i++){
            tx_car(AX_Chr[i]);
        }

        tx_car(' ');
        for(int i=0;i<9;i++){
            tx_car(AY_Chr[i]);
        }
        tx_car(' ');
        for(int i=0;i<9;i++){
            tx_car(AZ_Chr[i]);
        }

        tx_car('\n');
        tx_car('\r');
        Delay(10);

    }



    return 0;
}



unsigned int LSM303_Init(void){
    I2C0_Wr(I2C_Accelerometer_Slave_Address, CRL_REG1_A, 0x47); // Enable the accelerometer
    I2C0_Wr(I2C_Accelerometer_Slave_Address, CRL_REG4_A, 0x08); //2G and HR

}

LSM303_Data_T LSM303_Accelerometer(void){

    char sensordata[1];
    unsigned int Axyz[6]={0};
    LSM303_Data_T  xyz_Data;
    int accX, accY, accZ;

    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_X_L_A, 1, sensordata);
    Axyz[0] = sensordata[0];
    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_X_H_A, 1, sensordata);
    Axyz[1] = sensordata[0];
    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_Y_L_A, 1, sensordata);
    Axyz[2] = sensordata[0];
    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_Y_H_A, 1, sensordata);
    Axyz[3] = sensordata[0];
    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_Z_L_A, 1, sensordata);
    Axyz[4] = sensordata[0];
    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_Z_H_A, 1, sensordata);
    Axyz[5] = sensordata[0];

    /*
    I2C0_Rd(I2C_Accelerometer_Slave_Address,OUT_X_L_A, 6, sensordata);

    for(int i=0;i<6;i++){
        Axyz[i] = sensordata[i];
    }*/


    accX = (int) ((int16_t) ((Axyz[1] << 8 ) | Axyz[0] ));
    accY = (int) ((int16_t) ((Axyz[3] << 8 ) | Axyz[2] ));
    accZ = (int) ((int16_t) ((Axyz[5] << 8 ) | Axyz[4] ));

    // Convert The Readings
    xyz_Data.Ax = (float)accX/256.0;
    xyz_Data.Ay = (float)accY/256.0;
    xyz_Data.Az = (float)accZ/256.0;


return xyz_Data;
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




void I2C0_Init(void){

//1. Enable the I2C clock using the RCGCI2C register in the System Control module.

 SYSCTL_RCGCI2C_R = SYSCTL_RCGCI2C_R0;//Using I2C module 0 (Enable and provide a clock to I2C module 0 in Run mode)

//2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register in the System
//Control module.

SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1;//enable clock on Port B
while((SYSCTL_PRGPIO_R & 0x02) == 0);//Wait for activation


//3. In the GPIO module, enable the appropriate pins for their alternate function using the
//GPIOAFSEL register.

GPIO_PORTB_AFSEL_R = (1 << 2) | (1 << 3);

GPIO_PORTB_DEN_R = (1 << 2) | (1 << 3);

//4. Enable the I2CSDA pin for open-drain operation.
GPIO_PORTB_ODR_R = (1 << 3);


//5. Configure the PMCn fields in the GPIOPCTL register to assign the I2C signals to the appropriate
//pins.

GPIO_PORTB_PCTL_R = (3 << 12) | (3 << 8);//put a 3 in PMC2 and PMC3 (pins PB2 and PB3)

//6. Initialize the I2C Master by writing the I2CMCR register with a value of 0x0000.0010.
I2C0_MCR_R = (1 << 4);


//7. Set the desired SCL clock speed of 100 Kbps by writing the I2CMTPR register with the correct
//value. The value written to the I2CMTPR register represents the number of system clock periods
//in one SCL clock period. The TPR value is determined by the following equation:
//TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
//TPR = (16MHz/(2*(6+4)*100000))-1;
//TPR = 7
//Write the I2CMTPR register with the value of 0x0000.0009.
I2C0_MTPR_R = (7 << 0);

}





void setSlaveAddress(uint8_t slaveAddress){
    I2C0_MSA_R = (slaveAddress<<1);
}

void setMode(uint8_t mode){

    if(mode == 0){
        I2C0_MSA_R &= ~(1<<0);//clear bit, transmitting data
    }
    else{
        I2C0_MSA_R |= (1<<0);// set bit, receiving data
    }

}

void writeByte(uint8_t dataByte, uint8_t conditions){

//Place data (byte) to be transmitted in the data register by writing the I2CMDR register with the
//desired data.

    I2C0_MDR_R = dataByte;

//10. Initiate a single byte transmit of the data from Master to Slave by writing the I2CMCS register
//with a value of 0x0000.0007 (STOP, START, RUN).
    I2C0_MCS_R= conditions;

//11. Wait until the transmission completes by polling the I2CMCS register's BUSBSY bit until it has
//been cleared.

    while((I2C0_MCS_R & (1 << 0))!= 0);

//12. Check the ERROR bit in the I2CMCS register to confirm the transmit was acknowledged.

    if((I2C0_MCS_R & (1 << 1)) != 0){

        if((I2C0_MCS_R & (1 << 4)) == 1){
            //lost arbitration
        }
        else{
            I2C0_MCS_R = (1 << 2);//send stop
            while((I2C0_MCS_R & (1 << 0)) != 0);
        }


    }

}



static int I2C_wait_till_done(void)
{
    while(I2C0_MCS_R & 1);   /* wait until I2C master is not busy */
    return I2C0_MCS_R & 0xE; /* return I2C error code, 0 if no error*/

}


char I2C0_Wr(int slaveAddr, char memAddr, char data)
{

    char error;

    /* send slave address and starting address */
    I2C0_MSA_R = slaveAddr << 1;
    I2C0_MDR_R = memAddr;
    I2C0_MCS_R =  0x03;                      /* S-(saddr+w)-ACK-maddr-ACK */



    error = I2C_wait_till_done();       /* wait until write is complete */
    if (error) return error;

    /* send data */
    I2C0_MDR_R = data;
    I2C0_MCS_R = 5;                      /* -data-ACK-P */
    error = I2C_wait_till_done();       /* wait until write is complete */
    while(I2C0_MCS_R & 0x40);            /* wait until bus is not busy */
    error = I2C0_MCS_R & 0xE;
    if (error) return error;

    return 0;       /* no error */
}


char I2C0_Rd(int slaveAddr, char memAddr, int byteCount, char* data)
{
     char error;

    if (byteCount <= 0){
        return -1;         /* no read was performed */
    }
    /* send slave address and starting address */
    I2C0_MSA_R = slaveAddr << 1;
    I2C0_MDR_R = memAddr;
    I2C0_MCS_R = 3;       /* S-(saddr+w)-ACK-maddr-ACK */
    error = I2C_wait_till_done();
    if (error)
        return error;

    /* to change bus from write to read, send restart with slave addr */
    I2C0_MSA_R = (slaveAddr << 1) + 1;   /* restart: -R-(saddr+r)-ACK */

    if (byteCount == 1)             /* if last byte, don't ack */
        I2C0_MCS_R = 7;              /* -data-NACK-P */
    else                            /* else ack */
        I2C0_MCS_R = 0xB;            /* -data-ACK- */
    error = I2C_wait_till_done();
    if (error) return error;

    *data++ = (uint8_t)I2C0_MDR_R;            /* store the data received */

    if (--byteCount == 0)           /* if single byte read, done */
    {
        while(I2C0_MCS_R & 0x40);    /* wait until bus is not busy */
        return 0;       /* no error */
    }

    /* read the rest of the bytes */
    while (byteCount > 1)
    {
        I2C0_MCS_R = 9;              /* -data-ACK- */
        error = I2C_wait_till_done();
        if (error) return error;
        byteCount--;
        *data++ = (uint8_t)I2C0_MDR_R;        /* store data received */
    }

    I2C0_MCS_R = 5;                  /* -data-NACK-P */
    error = I2C_wait_till_done();
    *data = (uint8_t)I2C0_MDR_R;              /* store data received */
    while(I2C0_MCS_R & 0x40);        /* wait until bus is not busy */

    return 0;       /* no error */
}


void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter*10000; i++);
}
