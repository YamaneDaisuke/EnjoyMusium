#include "AQM0802A.h"

AQM0802A::AQM0802A(PinName sda, PinName scl) {
    i2c = new I2C(sda, scl);
    i2c->frequency(I2C_FREQUENCY);
    lcd_init();
}

AQM0802A::AQM0802A(I2C& i2c) {
    AQM0802A::i2c = &i2c;
    lcd_init();
}

void AQM0802A::lcd_init() {
    static const char init_cmds[] = {
        0x38,
        0x39,
        0x04,
        0x14,
        0x70,
        0x5E,
        0x6C
    };
    wait_ms(40);
    for (int i = 0; i < sizeof(init_cmds); i++) {
        lcd_cmd(init_cmds[i]);
    }
    wait_ms(200);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    cls();
}

void AQM0802A::lcd_cmd(uint8_t dat) {
    char buf[] = { 0, dat };
    i2c->write(AQM0802A_ADDR, buf, sizeof(buf));
    wait_us(AQM0802A_CMD_WAIT);
}

void AQM0802A::lcd_data(char dat) {
    char buf[] = { 0x40, dat };
    i2c->write(AQM0802A_ADDR, buf, sizeof(buf));
    wait_us(AQM0802A_CMD_WAIT);
}

void AQM0802A::cls() {
    x = y = 0;
    lcd_cmd(0x01);
    wait_us(1080 - AQM0802A_CMD_WAIT);
}

void AQM0802A::home() {
    x = y = 0;
    lcd_cmd(0x02);
    wait_us(1080 - AQM0802A_CMD_WAIT);
}

void AQM0802A::setContrast(int contrast) {
    lcd_cmd(0x39);
    lcd_cmd(0x70 | ( contrast & 0xF));       // contrast Low
    lcd_cmd(0x5C | ((contrast >> 4) & 0x3)); // icon/booster/contrast High
    lcd_cmd(0x38);
}

void AQM0802A::setCursor(int x, int y) {
    AQM0802A::x = x;
    AQM0802A::y = y;
    lcd_cmd(0x80 |
        ((y & (AQM0802A_MAX_ROWS - 1)) << 6) |
         (x & (AQM0802A_MAX_COLS - 1))
    );
}

int AQM0802A::_putc(int value) {
    switch (value) {
        case '\b':
            if      (x > 0) setCursor(--x, y);
            else if (y > 0) setCursor(AQM0802A_MAX_COLS - 1, --y);
            else            setCursor(AQM0802A_MAX_COLS - 1, AQM0802A_MAX_ROWS - 1);
            break;
        case '\r':
            setCursor(0, y);
            break;
        default:
            if (value == '\n') {
                x = 0;
            } else {
                lcd_data(value);
                if (x < AQM0802A_MAX_COLS - 1) x++;
                else                           x = 0;
            }
            if (x == 0) {
                if (y < AQM0802A_MAX_ROWS - 1) y++;
                else                           y = 0;
                setCursor(0, y);
            }
            break;
    }
    return value;
}
