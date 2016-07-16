#include <mbed.h>
#include "common.h"

//Optimize
#pragma O3
#pragma Otime

void transmit_mode(char eeprom_data[16][16]);
void receive_mode(char eeprom_data[16][16]);
void flight_mode();
void debug_mode(char eeprom[16][16]);

int main()
{
    char eeprom_data[16][16]= {0};
    unsigned char mode = TRANSMIT;
    for(char c = 0 ; c < 4; c++)
        dipsw[c].mode(PullUp); //PullUpに設定

    //モードを取得
    mode = select_mode();
    //フライトモードかつPICの接続が確認できたら即フライトモードを実行
    if(mode == FLIGHT && pic.who_are_you() == MY_TENKEY_ADD)
        flight_mode();

    lcd.cls();
    lcd.setCursor(0,0);
    lcd.printf("Now\nLoading.");
    led2=1;
    wait(1); //わざと待機

    /*init_buff():PICのEEPROMデータの読み出し関数*/
    if(init_buff(eeprom_data) == -1 || pic.who_are_you() != MY_TENKEY_ADD) { //読み込み失敗又はPICの接続が確認できない時
        lcd.cls();
        lcd.printf("Init");
        lcd.setCursor(0,1);
        lcd.printf("    Fail");
        while(1); //無限ループ
    }

    lcd.cls();
    lcd.setCursor(0,0);
    lcd.printf("Complete");
    wait(0.5);
    lcd.setCursor(0,1);
    lcd.printf("MODE ");
    display_mode(mode);
    wait(1);
    lcd.cls();
    led2=0;


    switch(mode) {
        case TRANSMIT :
            transmit_mode(eeprom_data);
            break;
        case RECEIVE  :
            receive_mode(eeprom_data);
            break;
        case FLIGHT  :
            flight_mode();
            break;
        case DEBUG   :
            debug_mode(eeprom_data);
            break;
        default :
            break;
    }

    //下は本来実行され
    while(1) {
        lcd.printf("ERROR!!");
        error("");
    }
}


void transmit_mode(char eeprom_data[16][16])
{
    char cnt;
    unsigned short status = 0, prestatus = 0, mask = 0;
    RemoteIR::Format format;
    uint8_t send_data[16][16];

    for(char i=0; i < 16; i++) {
        for(char j=0; j<16; j++) {
            //char型からuint8_t型へ変換
            send_data[i][j] = eeprom_data[i][j];
        }
    }

    lcd.cls();
    lcd.printf("TX >");

    while(1) {

        status = pic.read_buttons_state();
        mask = status ^ prestatus;
        if(mask) prestatus = status;
        status = status & mask;

        if(status) {
            for(cnt = 0; cnt < 9; cnt++) {
                if((status >> cnt) & 0x01) {
                    switch(send_data[cnt][0]) {
                        case RemoteIR::NEC:
                            format = RemoteIR::NEC;
                            break;
                        case RemoteIR::AEHA:
                            format = RemoteIR::AEHA;
                            break;
                        case RemoteIR::SONY:
                            format = RemoteIR::SONY;
                            break;
                        case RemoteIR::HELI:
                            format = RemoteIR::HELI;
                            break;
                        default :
                            continue;
                    }

                    led2 = 1;
                    //データ送信
                    transmit(format,&send_data[cnt][2],eeprom_data[cnt][1]);
                    wait_ms(50);
                    display_format(format);
                    display_data(&send_data[cnt][2],eeprom_data[cnt][1]);
                    wait_ms(200);
                    led2 = 0;
                    lcd.cls();
                    lcd.printf("TX >");
                }
            }
        }
    }
}

void receive_mode(char eeprom_data[16][16])
{
    ReceiverIR ir_rx(dp14); //割り込みイベントがコンストラクタに書かれていたので、ここでクラスを作成
    uint8_t buff[17]= {0};
    uint8_t reg;
    int bitlength, n;
    short status,prestatus = 0, cnt;
    RemoteIR::Format format;

    lcd.printf("RX >");
    while(1) {
        do {
            //1秒間受信を待つ
            bitlength = receive(&format, buff, 17, &ir_rx, 1000);
            //受信失敗したら
        } while(bitlength < 3);

        led2 = 1;
        status = pic.read_buttons_state();
        if(status) {
            prestatus = status;

            //押されたボタンの番号を取得
            for(reg=0; reg<9; reg++) {
                if(status&0x01)break;
                status = status >> 1;
            }
            if(reg>=9)continue;

            //受信内容を表示
            lcd.cls();
            lcd.printf("RX >");
            display_format(format);
            display_data(buff,bitlength);
            wait(1);

            lcd.cls();
            lcd.printf("SW%d on",reg);
            wait(0.5);
            lcd.setCursor(0,1);
            lcd.printf("Writing");
            cnt = 0;
            //ボタンが押されている時間を計測(最大約3秒)
            while(!(prestatus ^ pic.read_buttons_state())) {
                cnt++;
                if(cnt > 1800)break; //wait about 3 sec
            }

            if(cnt > 1800) {   //3秒以上押された場合
                //書き込むデータ作成
                eeprom_data[reg][0] = format;
                eeprom_data[reg][1] = bitlength;
                n = bitlength / 8 + (((bitlength % 8) != 0) ? 1 : 0);
                for(char i = 0; i < n; i++) {
                    eeprom_data[reg][i+2] = buff[i];
                }

                //データ書き込み
                if(pic.write_eeprom_data(reg, &eeprom_data[reg][0] , n+2) == -1) {
                    lcd.cls();
                    lcd.printf("Writing");
                    lcd.setCursor(0,1);
                    lcd.printf("Failed");
                    error("");
                }
                //print result
                lcd.cls();
                lcd.printf("Write:%2x",bitlength);
                lcd.setCursor(0,1);
                lcd.printf("Complete");
                wait(1.5);
            } else {
                lcd.cls();
                lcd.printf("Chancel");
                for(char i = 0; i < 4; i++) {
                    led2 = !led2;
                    wait(0.2);
                }
                wait(1);
            }
            lcd.cls();
            lcd.printf("RX >");
        }
        led2 = 0;
    }
}

void flight_mode()
{
    int bitlength;
    uint8_t buff[4] = {0};
    short status = 0;

    //チャンネル読み込み
    heli.channel = select_ch();
    if(heli.channel == 0xff) {
        lcd.printf("ChSelect");
        lcd.setCursor(0,1);
        lcd.printf("error");
        error("");
    }
    if(!heli.channel)
        lcd.printf("MODE:FLY\nCH3");
    else
        lcd.printf("MODE:FLY\nCH%d",heli.channel);
    led2 = 0;

    bitlength = heli.pairing(buff);
    //ペアリング信号送信
    for(char i = 0; i < 5; i++) {
        wait_ms(20);
        transmit(RemoteIR::HELI,buff,bitlength, 100);
        wait_ms(50);
    }

    while(1) {
        read_stat();
        status = pic.stat;
        bitlength = heli.update(status, buff);
        wait_ms(50);
        transmit(RemoteIR::HELI,buff,bitlength, 100);
        //Use Display
        display_data(buff,bitlength);
        wait_ms(50);
        led2 = !led2;
    }
}



void debug_mode(char eeprom[16][16])
{
    char ch = select_ch();
    while(1) {
        switch(ch) {
            case 0x01: //ch1 (i2c test)
                i2c_check();
                break;
            case 0x02: //ch2 (eeprom check)
                eeprom_check(eeprom);
                break;
            case 0x00: //ch3 (analog in and tenkey check)
                ADandButton_check(20);
                break;
            default:
                i2c_check();
                eeprom_check(eeprom);
                ADandButton_check();
                break;
        }
    }
}
