#include "ATP3011.h"

ATP3011::ATP3011(PinName sda, PinName scl, int addr)
{
    _i2c = new I2C(sda, scl);
    _addr = addr;
    _poll_wait.reset();
    _poll_wait.start();
}

ATP3011::ATP3011(I2C *i2c, int addr)
{
    _addr = addr;
    _i2c = i2c;
    _poll_wait.reset();
    _poll_wait.start();
}

bool ATP3011::isActive(int timeout_ms)
{
    wait_ms(STARTUP_TIME_MS);
    Timer t;
    t.reset();
    t.start();
    while(t.read_ms() < timeout_ms) {
        _poll_wait.reset();
        if (_i2c->write(_addr, NULL, 0) == 0) {
            return true;
        }
        wait_ms(POLL_TIME_MS);
    }
    return false;
}

void ATP3011::synthe(const char* msg)
{
    /*while(isBusy()) {
        ;
    }*/
    write(msg);
    wait_ms(10);
    write("\r");
}

void ATP3011::write(const char *msg)
{
    _i2c->write(_addr, msg, strlen(msg));
    _poll_wait.reset();
}

bool ATP3011::writeEEPROM_Byte(short add, char data)
{
    char msg[7]= "#W";
    char address[4] = {0};
    char sdata[3] = {0};
    sprintf(address, "%03X",add);
    sprintf(sdata,   "%02X",data);
    strcat(msg,address);
    strcat(msg,sdata);
    strcat(msg,"\r");
    _i2c->write(_addr, msg, strlen(msg));
    wait_ms(POLL_TIME_MS);
    _i2c->read(_addr, msg, 1);
    wait_ms(POLL_TIME_MS);
    if(msg[0] != '>')
        return 1;
    return 0;
}

short ATP3011::writeEEPROM(short add, char* data, short len)
{
    if(add+len > EP_MSG_MAX) {
        return 0;
    }
    short endAdd = add + len;
    while(add < endAdd) {
        if(writeEEPROM_Byte(add, *data))
            return 0;
        add++;
        data++;
    }
    //writeEEPROM_Byte(add, 0x00);
    return len;
}

bool ATP3011::readEEPROM_Byte(short add, char* out)
{
    char msg[7] = "#R";
    char address[4] = {0};
    sprintf(address, "%03X", add);
    strcat(msg,address);
    strcat(msg,"\r");

    _i2c->write(_addr, msg, strlen(msg));
    _poll_wait.reset();
    wait_ms(POLL_TIME_MS);

    _i2c->read(_addr, msg, 5);
    _poll_wait.reset();
    wait_ms(POLL_TIME_MS);
    if(msg[2] != '>') {
        return 1;
    }
    msg[2]=0;
    *out = strtol(msg,NULL,16);
    return 0;
}

short ATP3011::readEEPROM(short add, char *out, short len)
{
    if(add+len > EP_MSG_MAX)
        return 0;
    short endAdd = add+len;
    while(add < endAdd) {
        if(add > EP_MSG_MAX)
            return 0;
        if(readEEPROM_Byte(add, out)) {
            return 0;
        }
        add++;
        out++;
    }
    return len;
}

bool ATP3011::setTalkSpeed(short speed)
{
    return writeEEPROM_Byte(EP_SPEED_LSB, speed & 0x00FF) || writeEEPROM_Byte(EP_SPEED_MSB, speed >> 8);
}

bool ATP3011::isBusy()
{
    if (POLL_TIME_MS > _poll_wait.read_ms()) {
        return true;
    }
    _poll_wait.reset();
    char c = 0x00;
    if (_i2c->read(_addr, &c, 1) != 0) {
        return false;
    }
    return c == '*' || c == 0xff;
}