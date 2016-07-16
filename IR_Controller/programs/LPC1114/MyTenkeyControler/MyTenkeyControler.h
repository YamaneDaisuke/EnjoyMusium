/**
 * @file    MytenkeyControler.h
 * @brief   I2C接続されたPIC16F690からボタン情報の読み出し and EEPROMの読み書きを行うクラス
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
#ifndef _MYTENKEYCONTROLER_H
#define _MYTENKEYCONTROLER_H
#include <mbed.h>

#define I2C_FREQUENCY 400000
#define MY_TENKEY_ADD 0x92

//i2c command list
#define WRITE_EEPROM      21
#define READ_EEPROM       22
#define READ_BUTTON_STATE 23
#define WHO_ARE_YOU       24

/** MytenkeyControler.h
 *  I2C接続されたPIC16F690からボタン情報の読み出し and EEPROMの読み書きを行うクラス
 *
 */
class MyTenkeyControler
{
public :
    /**
     * Constructor.
     * @param sda serial data pin
     * @param scl serial clock pin
     */
    MyTenkeyControler(PinName sda, PinName scl);
    /**
     * Constructor.
     * @param i2c reference to i2c bus object.
     */
    MyTenkeyControler(I2C& i2c);

    /**
     * deconstructor
     */
    ~MyTenkeyControler();

    char who_are_you();

    /**
     * read Tenkey's stat by I2C.
     * @return Tenkey's status.
     */
    unsigned short read_buttons_state();

    /**
     * This function read data in PIC16f690's eeprom by I2C.
     * The read-out data are stored in pointer selected by the user.
     * @param uint8_t regi_number : pointer of eeprom's registory. (0-15)
     * @param char    *buf        : Readed data is stored in this pointer.
     * @param int     buf_size    : Not used.
     */
    int read_eeprom_data(uint8_t regi_number, char *buf, int buf_size);


    /** This function write 16 bytes data to pic's eeprom.
     * @param uint8_t regi_number : pointer of eeprom's registry.(0-15)
     * @param char    *buf        : Data to be written.
     * @param int     buf_size    : length of data. (byte)
     */
    int write_eeprom_data(uint8_t regi_number, char *buf, int buf_size);

    /// Tenkey's stat
    unsigned short stat;

private :
    I2C *i2c;
    char buff[3];
};

#endif