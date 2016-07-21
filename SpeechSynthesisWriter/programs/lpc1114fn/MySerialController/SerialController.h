/**
 * @file    SerialController.h
 * @brief   2016年 エンジョイ科学館用プログラム
 * @author  D.Yamane
 * @version 1.0
 * @see
 *
 * Copyright (c) 2016
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _SERIALCONTROLLER_H
#define _SERIALCONTROLLER_H
#include <mbed.h>
#include "BufferedSerial.h"
/// SerialController Class
class SerialController
{


public :
    typedef enum {
        WAIT = 0,
        WRITE_MEMORY,
        WRITE_EEPROM,
        READ_MEMORY,
        READ_EEPROM,
        DEBUG_READ_MEMORY,
        DEBUG_READ_EEPROM,
        TALK_TEST,
        OTHERWISE
    } STATUS;

    /**
     * Constructor.
     * @param BufferedSerial serial pointer
     * @param unsigned short size is buff size (byre)
     */
    SerialController(BufferedSerial *serial, unsigned short size = 256);

    /// Initialize
    void init(void);

    /// reset status
    void reset(void);

    /** read line from stream (This function block)
    * @reaturn if success 0 otherwise 1
    */
    int readLine(void);

    /** read command
    * @return success 0 otherwise 1
    */
    int readCmd(void);
    
    /** write buff data to output pointer
    * @param out output buffer address
    */
    void writeBuffData(char *out);
    

    /** get first sentence from buffer
    * @param char* output buffer
    * @reaturn success 0 otherwise 1
    */
    int split(char* out);

    /// clear rxBuffer
    void clear(void);

    /// @return status
    char getStat(void);
    


public :
    char status;

private :
    BufferedSerial *pc;
    MyBuffer <char> *rxBuffer;
    unsigned short _size;
};

#endif