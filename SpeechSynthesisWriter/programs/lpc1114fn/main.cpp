#include "BufferedSerial.h"
#include "MyBuffer.h"
#include "SerialController.h"
#include "ATP3011.h"
#define MAX_RX_BUFF_SIZE 256
#define THRESHOLD_HIGH 0.8
#define THRESHOLD_LOW 0.7


BufferedSerial pc(USBTX, USBRX, 256, 1);
SerialController serialController(&pc);
ATP3011 atp3011(dp5, dp27);
short headAdd[16] = {0x040};
DigitalOut led(dp14);
DigitalOut PCs[4] = {dp17,dp24,dp25,dp26};
AnalogIn analogIn(dp13);
Ticker flipper;
Ticker analogReader;
char textBuffer[1024] = {0};
char preflag = 0;
char prerand = 0;
char randam = 0;

void flip()
{
    led = !led;
}

void readAnalogIn()
{
    randam = rand() & 0x0f;
    if(serialController.getStat() != SerialController::WAIT) {
        return;
    }
    if(!preflag && analogIn.read() >= THRESHOLD_HIGH) {
        preflag = 1;
        led = 1;
    }
    if(preflag && analogIn < THRESHOLD_LOW) {
        led = 0;
        while(randam == 0x0f || randam == prerand) {
            randam = rand()& 0x0f;
        };
        prerand = randam;
        PCs[0] = randam & 0x01;
        PCs[1] = (randam>>1) & 0x01;
        PCs[2] = (randam>>2) & 0x01;
        PCs[3] = (randam>>3) & 0x01;

        preflag = 0;
    }

}


int main()
{
    pc.baud(9600);
    analogReader.attach(&readAnalogIn, 0.1);
    while(pc.readable()) { //バッファクリア
        pc.getc();
    }

    while(1) {
        while(!pc.readable());
        char result = serialController.readLine();
        if(result) // Can't read line
            continue;
        if(serialController.getStat() == SerialController::WAIT) {
            serialController.readCmd();
            pc.printf("ACK\r\n");

            if(serialController.getStat() == SerialController::TALK_TEST) {
                serialController.readLine();
                char rx[256] = {0};
                serialController.split(rx);
                atp3011.synthe(rx);
                serialController.reset();
            } else if(serialController.getStat() == SerialController::WRITE_MEMORY) {
                //serialController.writeBuffData();
                led = 1;
                short add = 0x040;
                while(1) {
                    serialController.readLine();
                    char re[10] = {0};
                    char rx[256] = {0};
                    serialController.split(re);
                    if(!strcmp(re,"END")) {
                        pc.printf("ACK\r\n");
                        break;
                    }
                    serialController.split(rx);
                    strcpy(&textBuffer[add],rx);
                    add += strlen(rx)+1;
                    pc.printf("ACK\r\n");
                    //pc.printf("%d ",rx[0]);
                    led = !led;
                }
                char head = 1;
                for(int i=0x040; i<0x400; i++) {
                    //pc.putc(textBuffer[i]);
                    if(textBuffer[i] == 0x00) {
                        headAdd[head] = i+1;
                        head++;
                        i++;
                        if(head >= 15)break;
                    }
                }
                led = 0;
                serialController.reset();
            } else if(serialController.getStat() == SerialController::WRITE_EEPROM) {
                //pc.printf("%d|\r\n",headAdd[14]+strlen(&textBuffer[headAdd[14]]));
                flipper.attach(&flip,0.2);
                if(atp3011.writeEEPROM(0x040,&textBuffer[0x040],headAdd[14]+strlen(&textBuffer[headAdd[14]])-0x40+1)) {
                    pc.printf("ACK\r\n");
                } else {
                    pc.printf("ERROR|FaildWritingEEPROM\r\n");
                }
                flipper.detach();
                led = 0;
                serialController.reset();

            } else if(serialController.getStat() == SerialController::READ_MEMORY) {
                led = 1;
                for(int i = 0; i < 15; i++) {
                    if(!headAdd[i] || !textBuffer[headAdd[i]]) {
                        pc.printf("ERROR| Null Data\r\n");
                    }
                    pc.printf("%d|%s\r\n",i,&textBuffer[headAdd[i]]);
                    led = !led;
                    wait(0.5);
                }
                pc.printf("END\r\n");
                serialController.reset();
                led = 0;
            } else if(serialController.getStat() == SerialController::READ_EEPROM) {
                led = 1;
                flipper.attach(&flip,0.2);
                if(!atp3011.readEEPROM(0x000,textBuffer,0x3FF)) {
                    pc.printf("ERROR|Can't Read EEPROM!\r\n");
                }
                char head = 1;
                for(int i=0x040; i<0x400; i++) {
                    //pc.putc(textBuffer[i]);
                    if(textBuffer[i] == 0x00) {
                        headAdd[head] = i+1;
                        head++;
                        i++;
                        if(head >= 16)break;
                    }
                }
                flipper.detach();
                for(int i = 0; i < 15; i++) {
                    pc.printf("%d|%s\r\n",i,&textBuffer[headAdd[i]]);
                    led = !led;
                    wait(1);
                }
                pc.printf("END\r\n");
                serialController.reset();
                led = 0;
            } else if(serialController.getStat() == SerialController::DEBUG_READ_MEMORY) {
                led = 1;
                for(int i = 0; i < 0x3FF; i++) {
                    pc.printf("%03X:%02X\r",i,textBuffer[i]);
                    wait(0.2);
                }
                pc.printf("END\r\n");
                serialController.reset();
                led = 0;
            } else if(serialController.getStat() == SerialController::DEBUG_READ_EEPROM) {
                led = 1;
                flipper.attach(&flip,0.2);
                atp3011.readEEPROM(0x000,textBuffer,0x3FF);
                char head = 1;
                for(int i=0x040; i<0x400; i++) {
                    //pc.putc(textBuffer[i]);
                    if(textBuffer[i] == 0x00) {
                        headAdd[head] = i+1;
                        head++;
                        i++;
                        if(head >= 16)break;
                    }
                }
                flipper.detach();
                for(int i = 0; i < 0x3FF; i++) {
                    pc.printf("%03X:%02X\r",i,textBuffer[i]);
                    wait(0.2);
                }
                pc.printf("END\r\n");
                serialController.reset();
                led = 0;
            }
        }
    }
}
