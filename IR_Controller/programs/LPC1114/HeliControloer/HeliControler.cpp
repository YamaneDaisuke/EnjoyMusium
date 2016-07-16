#include "HeliControler.h"

HeliControler::HeliControler(PinName U_D)
{
    AMoter = new AnalogIn(U_D);
    Init();
}
HeliControler::HeliControler(PinName U_D, PinName L_F)
{
    AMoter = new AnalogIn(U_D);
    ARotate = new AnalogIn(L_F);
    Init();
}
HeliControler::HeliControler(AnalogIn& U_D)
{
    AMoter = &U_D;
    Init();
}
HeliControler::HeliControler(AnalogIn& U_D, AnalogIn& L_F)
{
    AMoter = &U_D;
    ARotate = &L_F;
    Init();
}

void HeliControler::Init(void)
{
    led = 0;
    led_flag = 0;
    U_D = 0;
    L_R = 0x0f;
    L_R_CV = 0x0f;
    F_B = 0x03;
    channel = 0;
    bitlength = 23;
}

int HeliControler::pairing(uint8_t *buf, char flag)
{
    int tmp=0;
    int led=0x01;
    tmp |= (channel & 0x03) << 21;
    tmp |= (led  & 0x07) << 3;
    tmp = tmp << 1;
    for(char i = 0; i < 3; i++) {
        buf[i] = (tmp >> (8 * (2-i))) &0xff;
    }
    return bitlength;
}

int HeliControler::update(short stat, uint8_t *buf)
{
    int tmp=0;
    L_R = 0x0f;
    F_B = 0x03;
    U_D = AMoter->read_u16() >> 11;
    //if(ARotate);
    led = 0;

    if(channel > 3) {
        return -1;
    }
    if(stat & 0x02) { // ch2 ON
        F_B -= 0x03;
    }
    if(stat & 0x80) { //ch8 ON
        F_B += 0x04;
    }
    if(stat & 0x08) { //ch4 ON
        L_R -= 0x0f;
    }
    if(stat & 0x20) { //ch6 ON
        L_R += 0x10;
    }
    if(stat & 0x40 && !L_R_CV_flag) { //ch7 ON
        L_R_CV-=1;
        L_R_CV_flag = 1;
        if(L_R_CV<=0)
            L_R_CV = 0;
    }
    if(stat & 0x100 && !L_R_CV_flag) { //ch9 ON
        L_R_CV+=1;
        L_R_CV_flag = 1;
        if(L_R_CV>=0x1f)
            L_R_CV = 0x1f;
    }
    if(!(stat & 0x100) && !(stat & 0x40))
        L_R_CV_flag = 0;
    if(stat & 0x10 && !led_flag) { //ch5 ON
        led_flag = 1;
        led = 0x07;
    } else {
        led = 0x00;
    }

    if(!(stat & 0x10))
        led_flag = 0;
    tmp = 0;
    tmp |= (channel & 0x03) << 21;
    tmp |= (U_D  & 0x1f) << 16;
    tmp |= (L_R  & 0x1f) << 11;
    tmp |= (~L_R_CV & 0x1f) << 6;
    tmp |= (led  & 0x07) << 3;
    tmp |= (F_B  & 0x07);
    tmp = tmp << 1;
    for(char i = 0; i < 3; i++) {
        buf[i] = (tmp >> (8 * (2-i))) &0xff;
    }
    return bitlength;
}

