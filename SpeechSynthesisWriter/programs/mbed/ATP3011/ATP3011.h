
#ifndef _ATP3011_H
#define _ATP3011_H
#include "mbed.h"

#define I2C_ADDR        (0x2E<<1)
#define STARTUP_TIME_MS 80
#define POLL_TIME_MS    10
#define EP_MSG_MIN      0x040
#define EP_MSG_MAX      0x3FF
#define EP_SPEED_MSB    0x003
#define EP_SPEED_LSB    0x002
#define EP_I2CADR       0x006
/**
 *  @class ATP3011
 *  @brief AquesTalk pico LSI I2C interface
 *
 *
 * Example:
 * @code
 *  #include "mbed.h"
 *  #include "ATP3011.h"
 *
 *  ATP3011 atp3011(p28, p29);
 *  char eeprom_buffer[1024];
 *
 *  int main()
 *  { 
 *      atp3011.readEEPROM(0x000,textBuffer,0x3FF);
 *      for(int i=0x000; i<0x400; i++) {
 *          printf("%03X:%c\r",i,textBuffer[i]);
 *      }
 *      while(1);
 *  }
 * @endcode
 */
class ATP3011
{
public:
    /** Create a AquesTalk pico LSI I2C interface
     * @param sda  I2C data pin
     * @param scl  I2C clock pin
     * @param addr I2C address
     */
    ATP3011(PinName sda, PinName scl, int addr = I2C_ADDR);

    /** Create a AquesTalk pico LSI I2C interface
     * @param *i2c I2C object pointer
     * @param addr I2C address
     */
    ATP3011(I2C *i2c, int addr = I2C_ADDR);

    bool isActive(int timeout_ms = 500);
    void synthe(const char* msg);
    void write(const char* msg);

    /** Read byte from ATP3011's EEPROM
     * @param add eeprom address (0x000-0x3FF)
     * @param *out output byte pointer
     * @return 0 if success, 1 otherwise
     */
    bool readEEPROM_Byte(short add, char *out);

    /** Read bytes from　ATP3011's EEPROM
     * @param add start address
     * @param *out output buffer
     * @param len read length
     * @return readed length if success, 0 otherwise
     */
    short readEEPROM(short add, char *out, short len);
    
    /** Write byte to ATP3011's EEPROM
     * @param add eeprom address (0x000-0x3FF)
     * @retrun 0 if success, 1 otherwise 
     */
    bool writeEEPROM_Byte(short add, char data);
    
    /** Read bytes from　ATP3011's EEPROM
     * @param add start address
     * @param *data pointer of data
     * @param len data length
     * @return writed length if success, 0 otherwise
     */
    short writeEEPROM(short add, char *data, short len);
    
    /** Set talk speed (50-300)
     * @param talk speed (50-300)
     * @return 0 if success, 1 otherwise
    */
    bool setTalkSpeed(short speed = 100);
    
    bool isBusy();
    
private:
    int _addr;
    I2C *_i2c;
    Timer _poll_wait;
};

#endif