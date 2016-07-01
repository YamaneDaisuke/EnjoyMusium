#include "MyTenkeyControler.h"
#include <mbed.h>

/**
 * Constructor.
 * @param sda serial data pin
 * @param scl serial clock pin
 */
MyTenkeyControler::MyTenkeyControler(PinName sda, PinName scl)
{
    i2c = new I2C(sda, scl);
    i2c->frequency(I2C_FREQUENCY);
}
/**
 * Constructor.
 * @param i2c reference to i2c bus object.
 */
MyTenkeyControler::MyTenkeyControler(I2C& i2c)
{
    MyTenkeyControler::i2c = &i2c;
}

/**
 * deconstructor
 */
MyTenkeyControler::~MyTenkeyControler()
{
}

char MyTenkeyControler::who_are_you()
{
    buff[0] = WHO_ARE_YOU;
    if(i2c->write(MY_TENKEY_ADD , buff, 1) == -1)return 0xff;
    wait_us(50);
    i2c->read(MY_TENKEY_ADD,buff,1);
    return buff[0];
}

/**
 * Tenkey state reader by I2C protocol.
 * return value is Tenkey's status.
 */
unsigned short MyTenkeyControler::read_buttons_state()
{
    buff[0]=READ_BUTTON_STATE;
    if(i2c->write(MY_TENKEY_ADD , buff, 1) == -1);
    wait_us(50);
    i2c->read(MY_TENKEY_ADD,buff,2);
    stat  = buff[0];
    stat |= (short)(buff[1])<<8;
    return stat;
}

/**
 * This function read data in PIC16f690's eeprom by I2C protocol.
 * The read-out data are stored in pointer selected by the user.
 * *Parameter*
 * uint8_t regi_number : pointer of eeprom's registory. (0-15)
 * char    *buf        : Readed data is stored in this pointer.
 * int     buf_size    : Not used.
 */
int MyTenkeyControler::read_eeprom_data(uint8_t regi_number, char *buf, int buf_size)
{
    if(regi_number >= 16)return -1;
    buff[0] = READ_EEPROM;
    buff[1] = regi_number+1;
    if(i2c->write(MY_TENKEY_ADD, &buff[1], 1) == -1) return -1;
    wait_us(50);
    if(i2c->write(MY_TENKEY_ADD,     buff, 1) == -1) return -1;
    wait_us(200);
    i2c->read (MY_TENKEY_ADD, buf, 16);
    return 0;
}

/* This function to write 16 bytes data to pic's eeprom.
 * * parameter *
 * uint8_t regi_number : pointer of eeprom's registry.(0-15)
 * char    *buf        : Data to be written.
 * int     buf_size    : length of data. (byte)
 */
int MyTenkeyControler::write_eeprom_data(uint8_t regi_number, char *buf, int buf_size)
{
    char send[17],cnt;
    if(regi_number >= 16)return -1;
    send[0] = regi_number+1;
    for(cnt = 0; cnt < buf_size; cnt++) {
        send[cnt+1] = buf[cnt];
    }
    if(i2c->write(MY_TENKEY_ADD , send, buf_size+1) == -1) return -1;
    buff[0] = WRITE_EEPROM;
    if(i2c->write(MY_TENKEY_ADD , buff,          1) == -1) return -1;
    wait_ms(200);
    return 0;
}
