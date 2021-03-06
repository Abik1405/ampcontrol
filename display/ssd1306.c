#include "ssd1306.h"

#include "../pins.h"

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

static uint8_t fb[SSD1306_BUFFERSIZE];

static const uint8_t initSeq[] PROGMEM = {
    SSD1306_DISPLAY_OFF,
    SSD1306_SETDISPLAYCLOCKDIV,
    0xF0,
    SSD1306_SETMULTIPLEX,
    0x3F,
    SSD1306_SETDISPLAYOFFSET,
    0x00,
    SSD1306_SETSTARTLINE | 0x00,
    SSD1306_MEMORYMODE,
    SSD1306_MEMORYMODE_HORISONTAL,
    SSD1306_SEGREMAP_ON,
    SSD1306_COMSCANDEC,
    SSD1306_SETCOMPINS,
    0x12,
    SSD1306_SETCONTRAST,
    0xFF,
    SSD1306_SETPRECHARGE,
    0x1F,
    SSD1306_SETVCOMDETECT,
    0x40,
    SSD1306_ENTDISPLAY_RAM,
    SSD1306_NORMALDISPLAY,
    SSD1306_CHARGEPUMP,
    0x14,
    SSD1306_DISPLAY_ON,
};

static const uint8_t dispAreaSeq[] PROGMEM = {
    SSD1306_COLUMNADDR,
    0x00,
    0x7F,
    SSD1306_PAGEADDR,
    0x00,
    0x07,
};

static void _I2CWriteByte(uint8_t data)
{
    uint8_t i = 0;

    // Data bits
    for (i = 0; i < 8; i++) {
        if (data & 0x80)
            IN(SSD1306_SDA);    // Pullup SDA = 1
        else
            OUT(SSD1306_SDA);   // Active SDA = 0
        _delay_us(1);
        IN(SSD1306_SCK);        // Pullup SCL = 1
        _delay_us(1);
        OUT(SSD1306_SCK);       // Active SCL = 0
        data <<= 1;
    }
    // ACK bit
    IN(SSD1306_SDA);            // Pullup SDA = 1
    _delay_us(1);
    IN(SSD1306_SCK);            // Pullup SCL = 1
    _delay_us(1);
    OUT(SSD1306_SCK);           // Active SCL = 0
}

static void _I2CStart(uint8_t addr)
{
    IN(SSD1306_SCK);            // Pullup SCL = 1
    IN(SSD1306_SDA);            // Pullup SDA = 1
    _delay_us(1);
    OUT(SSD1306_SDA);           // Active SDA = 0
    _delay_us(1);
    OUT(SSD1306_SCK);           // Active SCL = 0

    _I2CWriteByte(addr);
}

static void _I2CStop()
{
    OUT(SSD1306_SCK);           // Active SCL = 0
    OUT(SSD1306_SDA);           // Active SDA = 0
    _delay_us(1);
    IN(SSD1306_SCK);            // Pullup SCL = 1
    _delay_us(1);
    IN(SSD1306_SDA);            // Pullup SDA = 1
}

static void ssd1306SendCmd(uint8_t cmd)
{
    _I2CWriteByte(cmd);
}

static void ssd1306SetDdrIn()
{
    // Set ports as inputs
    IN(DISP_D0);
    IN(DISP_D1);
    IN(DISP_D2);
    IN(DISP_D3);
    IN(DISP_D4);
    IN(DISP_D5);
    IN(DISP_D6);
    IN(DISP_D7);
    // Add pullup resistors
    SET(DISP_D0);
    SET(DISP_D1);
    SET(DISP_D2);
    SET(DISP_D3);
    SET(DISP_D4);
    SET(DISP_D5);
    SET(DISP_D6);
    SET(DISP_D7);
}

uint8_t ssd1306GetPins()
{
    uint8_t ret = 0x00;

    if (READ(DISP_D0)) ret |= (1 << 0);
    if (READ(DISP_D1)) ret |= (1 << 1);
    if (READ(DISP_D2)) ret |= (1 << 2);
    if (READ(DISP_D3)) ret |= (1 << 3);
    if (READ(DISP_D4)) ret |= (1 << 4);
    if (READ(DISP_D5)) ret |= (1 << 5);
    if (READ(DISP_D6)) ret |= (1 << 6);
    if (READ(DISP_D7)) ret |= (1 << 7);

    return ~ret;
}

void ssd1306Init()
{
    uint8_t i;

    _I2CStart(SSD1306_I2C_ADDR);
    _I2CWriteByte(SSD1306_I2C_COMMAND);

    for (i = 0; i < sizeof(initSeq); i++)
        ssd1306SendCmd(pgm_read_byte(&initSeq[i]));

    _I2CStop();

    // Set display D0..D7 ports as inputs with pull-up
    ssd1306SetDdrIn();
}

ISR (TIMER0_OVF_vect)
{
    // 2MHz / (256 - 56) = 10000Hz
    TCNT0 = 56;

    ADCSRA |= 1 << ADSC;                        // Start ADC every interrupt
}

void ssd1306UpdateFb()
{
    uint16_t i;
    uint8_t *fbP = fb;

    _I2CStart(SSD1306_I2C_ADDR);
    _I2CWriteByte(SSD1306_I2C_COMMAND);

    for (i = 0; i < sizeof(dispAreaSeq); i++)
        ssd1306SendCmd(pgm_read_byte(&dispAreaSeq[i]));

    _I2CStop();

    _I2CStart(SSD1306_I2C_ADDR);
    _I2CWriteByte(SSD1306_I2C_DATA_SEQ);

    for (i = 0; i < SSD1306_BUFFERSIZE; i++)
        _I2CWriteByte(*fbP++);

    _I2CStop();
}

void ssd1306DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    uint8_t bit;
    uint8_t *fbP;

    if (x >= 128)
        return;
    if (y >= 64)
        return;

    fbP = &fb[(y >> 3) * 128 + x];

    bit = 1 << (y & 0x07);

    if (color)
        *fbP |= bit;
    else
        *fbP &= ~bit;
}

void ssd1306Clear()
{
    uint16_t i;
    uint8_t *fbP = fb;

    for (i = 0; i < SSD1306_BUFFERSIZE; i++)
        *fbP++ = 0x00;
}

void ssd1306SetBrightness(uint8_t br)
{
    uint8_t rawBr = 255;

    if (br < SSD1306_MAX_BRIGHTNESS)
        rawBr = br * 8;

    _I2CStart(SSD1306_I2C_ADDR);
    _I2CWriteByte(SSD1306_I2C_COMMAND);

    ssd1306SendCmd(SSD1306_SETCONTRAST);
    ssd1306SendCmd(rawBr);

    _I2CStop();
}
