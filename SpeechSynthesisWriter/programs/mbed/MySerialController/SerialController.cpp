#include "SerialController.h"

SerialController::SerialController(BufferedSerial *serial, unsigned short size)
{
    pc = serial;
    _size = size;
    rxBuffer = new MyBuffer<char>(_size);
    init();
}

/// Initialize. set status WAIT, and Clear Rx buffer
void SerialController::init(void)
{
    status = WAIT;
    rxBuffer->clear();
}

/// reset status
void SerialController::reset(void)
{
    status = WAIT;
    rxBuffer->clear();
}

/** read line from stream (This function block)
* @reaturn if success 0 otherwise 1
*/
int SerialController::readLine(void)
{
    short length = 0;
    while(1) {
        while(!pc->readable());
        char rx = pc->getc();
        length ++;
        if(length >= _size) {
            pc->puts("ERROR|Buffer Overflow\r\n");
            rxBuffer->clear();
            while(pc->readable())pc->getc();
            return 1;
        }
        if(rx == '\n')
            break;
        rxBuffer->put(rx);
    }
    return 0;
}

/** read command
* @return success 0 otherwise 1
*/
int SerialController::readCmd(void)
{
    char cmd[20] = {0};
    split(cmd);
    if(status != SerialController::WAIT) return 1;
    if(!strcmp(cmd, "WRITE_MEMORY")) {
        status = SerialController::WRITE_MEMORY;
    } else if(!strcmp(cmd, "WRITE_EEPROM")) {
        status = SerialController::WRITE_EEPROM;
    } else if(!strcmp(cmd, "READ_MEMORY")) {
        status = SerialController::READ_MEMORY;
    } else if(!strcmp(cmd, "READ_EEPROM")) {
        status = SerialController::READ_EEPROM;
    }else if(!strcmp(cmd, "DEBUG_READ_EEPROM")) {
        status = SerialController::DEBUG_READ_EEPROM;
    }else if(!strcmp(cmd, "DEBUG_READ_MEMORY")) {
        status = SerialController::DEBUG_READ_MEMORY;
    }else if(!strcmp(cmd, "TALK_TEST")) {
        status = SerialController::TALK_TEST;
    } else {
        pc->puts("ERROR|Unknown Cmd\r\n");
        reset();
        return 1;
    }
//    pc.printf("ACK\r\n");
    clear();
    return 0;
}

/** write buff data to output pointer
* @param out output buffer address
*/
void SerialController::writeBuffData(char *out)
{
    while(rxBuffer->available()) {
        *out = rxBuffer->get();
        out++;
    }
}


/** get first sentence from buffer
* @param char* output buffer
* @reaturn success 0 otherwise 1
*/
int SerialController::split(char* out)
{
    char *p = out;
    while(p) {
        if(rxBuffer->available()) {
            *p = rxBuffer->get();
        } else {
            return 1;
        }
        if(*p == '|' || *p == '\n' || *p == '\r') {
            *p = 0;
            return 0;
        }
        p++;
    }
    return 1;
}

/// clear rxBuffer
void SerialController::clear(void)
{
    rxBuffer->clear();
}

/// @return status
char SerialController::getStat(void)
{
    return status;
}


