/**
 * @file    HeliControler.h
 * @brief   株式会社CCB社のナノファルコンαを操作するためのクラスです。
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
#ifndef _HELICONTROLER_H
#define _HELICONTROLER_H
#include <mbed.h>

/** Helicopter control class.
 *  株式会社CCB社のナノファルコンαを操作するためのクラスです。
 *
 */
class HeliControler
{
public :
    
    /// Constructor
    HeliControler(PinName U_D);
    /// Constructor
    HeliControler(PinName U_D, PinName L_F);
    /// Constructor
    HeliControler(AnalogIn& U_D);
    /// Constructor
    HeliControler(AnalogIn& U_D, AnalogIn& L_F);
    
    /** pairing with helicopoter
     * @param *buf Store IR frame
     */
    int pairing(uint8_t *buf, char flag = 0);
    
    /**　make frame of Helicopter
     * @param stat button's status
     * @param *buf Store IR frame
     */
    int update(short stat, uint8_t *buf);

private:
    /// Initilizing All methods
    void Init(void);
    
public :
    /// channel of helicopter
    char channel;
    
private :
    char bitlength;
    AnalogIn *AMoter;
    AnalogIn *ARotate;
    AnalogIn *AMove;
    char led,led_flag,L_R_CV_flag;
    int U_D,L_R,L_R_CV,F_B;
    char buff[4];
};

#endif