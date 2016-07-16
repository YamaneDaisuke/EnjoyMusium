/* 
 * File:   main.c
 * Author: Yamaned
 *
 * Created on 2015/04/24, 14:38
 */


#include <pic.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>


#pragma config FOSC = HS   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

#define HALF_MIN 31
#define TMR0TIME -195
#define _XTAL_FREQ 20000000
#define NUMBER_OF_BUTTONS 12
#define MAX_BUF_SIZE 16

// i2c_command list
#define WRITE_EEPROM      21
#define READ_EEPROM       22
#define READ_BUTTON_STATE 23
#define WHO_ARE_YOU       24


typedef enum {
    UNDEF = 0,
    NEC   = 1,
    AEHE  = 2,
    SONY  = 3
}FORMAT;

typedef enum {
    READ_EEROOM_DATA,
    READ_BUTTON_STAT,
    ANS_MY_ADDRESS,
    OTHERWISE
}READ_COMMAND_LIST;

typedef struct {
    char format;
    char length;
    char data[6];
}DATA_STRUCTURE;

void InitPORT(void);
void InitTMR0(void);
void InitI2C(void);
void write_eeprom(char *data);
void read_eeprom(char *output);

static void interrupt isr(void);

unsigned int cnt=0;
unsigned char number_low=0;
unsigned char number_high=0;
const char addr = 0x92;
static unsigned char address_flag, i2c_command, seg_data[16], buf_index, buf_counter, buf_flag; //i2c_command is number of registroy
unsigned char reader_flag,buttons_stat[16];

int main(int argc, char** argv) {
    InitTMR0();
    InitPORT();
    InitI2C();
    while(1){
        //read status of buttons.
        buttons_stat[0]  = ~PORTC;
        buttons_stat[1]  = ~PORTA & 0x07;
        buttons_stat[1] |= !PORTBbits.RB7 << 3;
        __delay_ms(20);
    }
    return (EXIT_SUCCESS);
}

void write_eeprom(char *data)
{
    unsigned char head_add = buf_index*16;
    if(buf_index>16)return;
    for(buf_counter=0;buf_counter < MAX_BUF_SIZE; buf_counter++)
    {
        eeprom_write(head_add+buf_counter,data[buf_counter]);
    }
}

void read_eeprom(char *output)
{
    unsigned short head_add = buf_index*0x10;
    unsigned short add;
    if(buf_index>=16)return;
    for(buf_counter=0;buf_counter < MAX_BUF_SIZE; buf_counter++)
    {
        add = head_add + buf_counter;
        output[buf_counter] = eeprom_read(add);
    }
}


/*
 * Initilize PORT and TRIS registor
 */
void InitPORT(void)
{
    ANSEL = 0x00;   //All ports are Digital pin
    ANSELH = 0x00;
    PORTA = 0x00;   //clear all port
    PORTB = 0x00;
    PORTC = 0x00;
    TRISA = 0x00;  //clear all port tris ( all port set output pin )
    TRISB = 0x00;
    TRISC = 0x00;
    TRISA |= 0x07; // RA0, RA2 and RA3 set the input pin.
    TRISB |= 0x80; // RB7 set the input pin.
    TRISC |= 0xff; // All port set the input pin.
}

/*
 * Initilize registor which be used I2C comunicate.
 */
void InitI2C(void)
{
    INTCONbits.GIE = 0;
    PORTB &= 0xAF;  //clear SCL and SDA
    TRISB |= 0x50;  //SCL and SDA are inputs
    SSPMSK = 0xFE;  //7bits address mode
    SSPSTAT  = 0x00;    //clear i2c status
    SSPCON   = 0x36;    //i2c srave mode (use SSPCONbits.CKP)
    SSPADD = addr;      //set i2c address (0x92)
    INTCONbits.PEIE = 1;//Allow preferal interrupt.
    PIE1bits.SSPIE = 1; //Allow ssp module interrupt.
    INTCONbits.GIE = 1; //Allow interrupt.
}

/*
 * Initilize registor which be used Timer0 module.
 */
void InitTMR0(void)
{
    cnt = 0;
    OPTION_REG = 0x07;
    TMR0 = TMR0TIME;	//10ms timer
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
}


static void interrupt isr(void)
{
    unsigned int stat;
    unsigned char dat;
    unsigned char add;

    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

    //python write word
    //i2c.write_word_data (address, command, data)
    //sequesnce:
    //1: state 1, buf contains address
    //2: state 2, buf contains command
    //3: state 2, first byte
    //4: state 2, second byte
    //state 5 gets called at end of message

    //python to read word from pic
    //i2c.read_word_data (address, command)
    //sequence:
    //1: state 1, buf contains address
    //2: state 2, buf contains command
    //3: state 3, first byte
    //4: state 4, second byte
    //state 5 gets called at end of message

    if (SSPIF == 1) //i2c interupt
    {
        if (SSPOV == 1)
        {
            SSPOV = 0;  //clear overflow
            dat = SSPBUF;
        }
        else
        {
            stat = SSPSTAT;             //get ssp module's status.
            stat = stat & 0b00101101;
            //find which state we are in
            //state 1 Master just wrote our address
            if ((stat ^ 0b00001001) == 0) //S=1 && RW==0 && DA==0 && BF==1
            {
                /*
                for (i=0; i<BUF_SIZE; ++i) //clear buffer
                    buf[i] = 0;
                buf_index = 0;  //clear buffer index
                */
                add = SSPBUF;   //read address so we know later if read or write
                address_flag=1;
                buf_flag = 0;
            }
            //state 2 Master just wrote data
            else if ((stat ^ 0b00101001) == 0) //S=1 && RW==0 && DA==1 && BF==1
            {
                dat = SSPBUF;   //read buffer

                // if master wrote command
                if(address_flag==1){
                    i2c_command = dat; //set command

                    // flag and counter clear
                    address_flag=0;
                    buf_counter = 0xff;
                    reader_flag = OTHERWISE;

                    switch (i2c_command){
                        case WRITE_EEPROM :
                            write_eeprom(seg_data);
                            break;
                        case READ_EEPROM :
                            read_eeprom(seg_data);
                            reader_flag = READ_EEROOM_DATA;
                            break;
                        case READ_BUTTON_STATE :
                            reader_flag = READ_BUTTON_STAT;
                            break;
                        case WHO_ARE_YOU :
                            reader_flag = ANS_MY_ADDRESS;
                            break;
                        default :
                            buf_index = i2c_command -1;
                            buf_counter = 0;
                            break;
                    }

                 // if master wrote data
                }else{
                    if(buf_counter < MAX_BUF_SIZE){
                        seg_data[buf_counter]=dat;
                        buf_counter++;
                        buf_flag=1;
                    }
                }

            }

            //state 3 Master want to read, just wrote address
            else if ((stat ^ 0b00001100) == 0) //S=1 && RW==1 && DA==0 && BF==0
            {

                add = SSPBUF; //keep the address
                WCOL = 0;   //clear write collision flag
                buf_counter = 0; //clear buf conter
                switch (reader_flag){
                    case READ_EEROOM_DATA :
                        dat = seg_data[buf_counter]; //low byte
                        SSPBUF = dat & 0x00FF; //send eeprom data
                        buf_counter++;
                        break;
                    case READ_BUTTON_STAT :
                        dat = buttons_stat[buf_counter];
                        SSPBUF = dat & 0x00FF; //send buttons's status data
                        buf_counter++;
                        break;
                    case ANS_MY_ADDRESS :
                        dat = addr;
                        SSPBUF = dat & 0x00FF;
                        break;
                    default :
                        break;
                }
                
            }
            //state 4 Master want to read, last byte was already data
            else if ((stat ^ 0b00101100) == 0) //S=1 && RW==1 && DA==1 && BF==0
            {
                if (buf_counter >= MAX_BUF_SIZE){ //When read out byte of array
                    buf_counter = 0;
                    reader_flag = OTHERWISE;
                }
                WCOL = 0;   //clear write collision flag
                switch (reader_flag){
                    case READ_EEROOM_DATA :
                        dat = seg_data[buf_counter]; //low byte
                        SSPBUF = dat & 0x00FF; //send eeprom data
                        buf_counter++;
                        break;
                    case READ_BUTTON_STAT :
                        dat = buttons_stat[buf_counter];
                        SSPBUF = dat & 0x00FF;//send buttons's status data
                        buf_counter++;
                        break;
                    default :
                        break;
                }                
            }
            //state 5 Master sends NACK to end message
            else if ((stat ^ 0b00101000) == 0) //S=1 && RW==0 && DA==1 && BF==0
            {
                dat = SSPBUF;
            }
            else //undefined, clear buffer
            {
                dat = SSPBUF;
            }
        }
    CKP = 1; //release the clk
    SSPIF = 0; //clear interupt flag
    }

    if(INTCONbits.T0IF){    //timer0_interrupt
        INTCONbits.T0IF = 0;
        TMR0 = TMR0TIME;
        cnt ++;			//counter
    }

}

