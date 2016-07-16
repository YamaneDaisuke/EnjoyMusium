#ifndef AQM0802A_H
#define AQM0802A_H

#include "mbed.h"

#define AQM0802A_ADDR     0x7C     // I2C slave address
#define AQM0802A_COLS     8
#define AQM0802A_ROWS     2
#define AQM0802A_MAX_COLS (1 << 6)
#define AQM0802A_MAX_ROWS (1 << 2)
#define AQM0802A_CMD_WAIT 27       // wait time after sent lcd command (us)
#define I2C_FREQUENCY     400000   // I2C bus speed (uses only constructor of AQM0802A(PinName, PinName))

/**
 * Akizuki I2C 8x2 Character LCD AQM0802A driver class.<br />
 * 秋月 I2C 8x2 小型キャラクタLCD AQM0802A用 ドライバクラスです。<br />
 * &nbsp;http://akizukidenshi.com/catalog/g/gK-06795/<br />
 * Copyright(C)2014 T.Hoshino<br />
 * <br />
 * CAUTION: My English is very poor, it might be wrong. (I rely on Google Translate almost.)
 * <ul>
 *  <li>Stream 継承なので、printf() 等も利用可能です。<br />
 *      This class inherits Stream, Its public methods (printf() etc.) are also available.</li>
 *  <li>文字コード '\\r'(0x0D) の出力でカーソル位置は行頭に移動します。<br />
 *      When you output the character code '\\r'(0x0D), the cursor position is move to the beginning of line.</li>
 *  <li>文字コード '\\n'(0x0A) の出力でカーソル位置は次の行の先頭に移動します。<br />
 *      When you output the character code '\\n'(0x0A), the cursor position is move to the beginning of next line.</li>
 * </ul>
 * @code
//----------------------------------------
// Sample code for ST Nucleo F401RE
//----------------------------------------
#include <mbed.h>
#include <AQM0802A.h>

AQM0802A lcd(D14, D15); // <-- this !
Ticker   ticker;

void tick() {
    static int count = 0;
    lcd.cls();
    lcd.printf("Hello\n %d", count++);
}

int main() {
    ticker.attach(&tick, 0.1);
    while(1) {
    }
}
 * @endcode
 * ご自由にお使いいただけますが、無保証です。使用は自己責任でどうぞ。<br />
 * The use of this is free, but no warranty. please use at your own risk.<br />
 */
class AQM0802A : public Stream {
  public:
    /**
     * Constructor.
     * @param sda serial data pin
     * @param scl serial clock pin
     */
    AQM0802A(PinName sda, PinName scl);

    /**
     * Constructor.
     * @param i2c reference to i2c bus object.
     */
    AQM0802A(I2C &i2c);

    /**
     * Clear screen. 画面をクリアします。<br />
     * After clear screen, the cursor position will be changed to {x:0, y:0}.<br />
     * 画面クリア後、カーソル位置は {x:0, y:0} に変更されます。<br />
     * @see #home()
     */
    void cls();

    /**
     * Set cursor to home position. カーソル位置をホームポジションに移動します。<br />
     * The cursor position will be changed to {x:0, y:0}. At that time, it does not clear the screen display.<br />
     * カーソル位置を {x:0, y:0} に変更します。その際、画面表示はクリアしません。<br />
     * @see #cls()
     */
    void home();

    /**
     * Change the contrast of the screen. 画面のコントラストを変更します。<br />
     * Practical range in about 20-40, the initial value is 32.
     * 実用的な範囲は20～40ぐらいで、初期値は32です。<br />
     * Only the lower 6 bits are valid. 下位6ビットのみ有効です。
     * @param contrast 0(bright) to 63(dark). The initial value is 32.
     */
    void setContrast(int contrast);

    /**
     * Change the cursor position to {x, y}. 指定位置 {x, y} にカーソルを移動します。<br />
     * The position of left top is {0, 0}. Right bottom is {7, 1}.
     * 左上は {0, 0}、右下は{7, 1} です。
     * @param x 0 to 7 : Column position of the cursor.
     * @param y 0 to 1 : Row position of the cursor.
     */
    void setCursor(int x, int y);

  protected:
    virtual int _putc(int);
    virtual int _getc(){ return 0; }

  private:
    I2C* i2c;
    uint8_t x;
    uint8_t y;

    void lcd_init();
    void lcd_cmd(uint8_t cmd);
    void lcd_data(char data);
};

#endif