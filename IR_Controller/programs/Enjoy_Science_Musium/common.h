#ifndef _COMMON_H
#define _COMMON_H
#include <mbed.h>
#include "ReceiverIR.h"
#include "TransmitterIR.h"
#include "AQM0802A.h"
#include "MyTenkeyControler.h"
#include "HeliControler.h"

//ピン定義
//DigitalOut led1(dp14);
DigitalOut led2(dp28);
DigitalIn  dipsw[4]= {dp26, dp25, dp18, dp17};
//ReceiverIR ir_rx(dp14);
TransmitterIR ir_tx(dp1);
I2C i2c(dp5,dp27);
AQM0802A lcd(i2c);
AnalogIn U_D(dp10);
MyTenkeyControler pic(i2c);
HeliControler heli(U_D);

typedef enum {
    TRANSMIT,
    RECEIVE,
    FLIGHT,
    DEBUG
} MODE;

int init_buff(char buff[16][16]);
int receive(RemoteIR::Format *format, uint8_t *buf, int bufsiz, ReceiverIR *ir_rx, int timeout = 1000);
int transmit(RemoteIR::Format format, uint8_t *buf, int bitlength, int timeout = 500);
void read_stat();
void display_format(RemoteIR::Format format);
void display_data(uint8_t *buf, int bitlength);
void display_mode(char mode);
char select_mode();
char select_ch();
void ADandButton_check(int timeout = 10);
void eeprom_check(char eeprom[16][16]);
void i2c_check();

int init_buff(char buff[16][16])
{
    char i;
    for(i=0; i<16; i++) {
        if(pic.read_eeprom_data(i,buff[i],16) == -1)return -1;
    }
    return 0;
}

/**
 * Receive.
 *
 * @param format Pointer to a format.
 * @param buf Pointer to a buffer.
 * @param bufsiz Size of the buffer.
 *
 * @return Bit length of the received data.
 */
int receive(RemoteIR::Format *format, uint8_t *buf, int bufsiz, ReceiverIR *ir_rx, int timeout)
{
    int cnt = 0;
    while (ir_rx->getState() != ReceiverIR::Received) {
        wait_ms(1);
        cnt++;
        if (timeout < cnt) {
            return -1;
        }
    }
    return ir_rx->getData(format, buf, bufsiz * 8);
}

/**
 * Transmit.
 *
 * @param format Format.
 * @param buf Pointer to a buffer.
 * @param bitlength Bit length of the data.
 *
 * @return Bit length of the received data.
 */
int transmit(RemoteIR::Format format, uint8_t *buf, int bitlength, int timeout)
{
    int cnt = 0;
    while (ir_tx.getState() != TransmitterIR::Idle) {
        wait_ms(1);
        cnt++;
        if (timeout < cnt) {
            NVIC_SystemReset();
            return -1;
        }
    }
    return ir_tx.setData(format, buf, bitlength);
}


void read_stat()
{
    pic.read_buttons_state();
}

void display_format(RemoteIR::Format format)
{
    lcd.setCursor(4, 0);
    switch (format) {
        case RemoteIR::UNKNOWN:
            lcd.printf("????");
            break;
        case RemoteIR::NEC:
            lcd.printf(" NEC");
            break;
        case RemoteIR::AEHA:
            lcd.printf("AEHA");
            break;
        case RemoteIR::SONY:
            lcd.printf("SONY");
            break;
    }
}


void display_data(uint8_t *buf, int bitlength)
{
    lcd.setCursor(0, 1);
    const int n = bitlength / 8 + (((bitlength % 8) != 0) ? 1 : 0);
    for (int i = 0; i < n; i++) {
        lcd.printf("%02X", buf[i]);
    }
    //for (int i = 0; i < 8 - n; i++) {
    //    lcd.printf("--");
    //}
}

void display_mode(char mode)
{
    lcd.setCursor(5,1);
    switch (mode) {
        case TRANSMIT:
            lcd.printf(" TX");
            break;
        case RECEIVE:
            lcd.printf(" RX");
            break;
        case FLIGHT:
            lcd.printf("FLY");
            break;
        case DEBUG:
            lcd.printf("DBG");
            break;
    }
}

char select_mode()
{
    char tmp = 0;
    for(char i = 2; i > 0; i--) {
        tmp = tmp<<1;
        if(!dipsw[i-1])
            tmp++;
    }
    switch (tmp) {
        case 0x00:
            tmp = TRANSMIT;
            break;
        case 0x01:
            tmp = RECEIVE;
            break;
        case 0x02:
            tmp = DEBUG;
            break;
        case 0x03:
            tmp = FLIGHT;
            break;
    }
    return tmp;

}

char select_ch()
{
    char tmp = 0;
    for(char i = 4; i > 2; i--) {
        tmp = tmp<<1;
        if(!dipsw[i-1])
            tmp++;
    }
    switch (tmp) {
        case 0x00:
            tmp = 0xff;
            break;
        case 0x01:
            tmp = 0x01; //ch1
            break;
        case 0x02:
            tmp = 0x02; //ch2
            break;
        case 0x03:
            tmp = 0x00; //ch3
            break;
        default :
            tmp = 0xff;
    }
    return tmp;

}

void i2c_check()
{
    char add = 0;
    lcd.cls();
    lcd.printf("DBG :I2C");
    add = pic.who_are_you();
    if(add == 0x92) {
        lcd.setCursor(0,1);
        lcd.printf("OK    %02x", add);
    } else {
        lcd.setCursor(0,1);
        lcd.printf("Fail  %02x", add);
        error("");
    }
    wait(1);
}

void eeprom_check(char eeprom[16][16])
{
    lcd.cls();
    lcd.printf("DBG :EEP");
    wait(1);
    for(char i = 0; i<16; i++) {
        lcd.cls();
        lcd.printf("EEPDATA");
        lcd.setCursor(0,1);
        lcd.printf("reg :%2x",i);
        wait(1);
        lcd.cls();
        lcd.setCursor(0,0);
        for(char j = 0; j<8; j++) {
            lcd.printf("%02x",eeprom[i][j]);
        }
        lcd.setCursor(0,1);
        for(char j = 8; j<16; j++) {
            lcd.printf("%02x",eeprom[i][j]);
        }
        wait(1);
    }
}

void ADandButton_check(int timeout)
{
    short status = 0;
    lcd.cls();
    lcd.printf("DBG :AD");
    lcd.setCursor(0,1);
    lcd.printf("and  BT");
    wait(1);
    for(int i = 0; i < timeout * 2; i++) {
        read_stat();
        status = pic.stat;
        lcd.cls();
        lcd.printf("BT: %04x",status);
        lcd.setCursor(0,1);
        lcd.printf("AD: %4.2f",U_D.read());
        wait(0.5);
    }

}
#endif