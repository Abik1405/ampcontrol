#ifndef DISPLAY_H
#define DISPLAY_H

#include <inttypes.h>

#include "ds1307.h"
#include "audio/audio.h"

/* Graphics (ks0108-based) or character (ks0066-based) display selection  */
#if !defined(KS0108) && !defined(KS0066) && !defined(LS020) && !defined(PCF8574) && !defined(ST7920)
#define ST7920
#endif

#if defined(KS0108)
#include "display/ks0108.h"
#elif defined(KS0066)
#include "display/ks0066.h"
#elif defined(LS020)
#include "display/ls020.h"
#elif defined(PCF8574)
#include "display/pcf8574.h"
#elif defined(ST7920)
#include "display/st7920.h"
#endif

/* Spectrum output mode */
#define SP_MODE_STEREO			0
#define SP_MODE_MIXED			1

/* Timers fo different screens */
#define DISPLAY_TIME_TEST		15
#define DISPLAY_TIME_GAIN		3
#define DISPLAY_TIME_TIME		3
#define DISPLAY_TIME_TIME_EDIT	10
#define DISPLAY_TIME_FM_RADIO	5
#define DISPLAY_TIME_CHAN		2
#define DISPLAY_TIME_AUDIO		3
#define DISPLAY_TIME_SP			3
#define DISPLAY_TIME_BR			3

#define BACKLIGHT_ON			1
#define BACKLIGHT_OFF			0

/* Data stored in user characters */
#define LCD_LEVELS				0
#define LCD_BAR					1

#define DISP_MIN_BR                    0
#define DISP_MAX_BR                    32

/* Display modes */
enum {
	MODE_STANDBY,
	MODE_SPECTRUM,
	MODE_FM_RADIO,

	MODE_VOLUME,
	MODE_BASS,
#if defined(TDA7439)
	MODE_MIDDLE,
#endif
	MODE_TREBLE,
#if defined(TDA7439)
	MODE_PREAMP,
#elif defined(TDA7313) || defined(TDA7318)
	MODE_FRONTREAR,
#endif
	MODE_BALANCE,

	MODE_GAIN,

	MODE_TIME,
	MODE_TIME_EDIT,
	MODE_MUTE,
	MODE_LOUDNESS,
	MODE_TEST,

	MODE_BR
};

/* Type of string printed (regular/eeprom/flash) */
#define STR_REG			0
#define STR_EEP			1
#define STR_PGM			2

#define STR_BUFSIZE		16

uint8_t getDefDisplay();
void setDefDisplay(uint8_t value);

void displayInit();
void clearDisplay();

uint8_t *mkNumString(int16_t number, uint8_t width, uint8_t lead, uint8_t radix);

void showRC5Info(uint16_t rc5Buf);
void showRadio(void);
void showBoolParam(uint8_t value, const uint8_t *parLabel, uint8_t **txtLabels);

void showBrWork(uint8_t **txtLabels, uint8_t *buf);
void changeBrWork(int8_t diff);

void showSndParam(sndParam *param, uint8_t **txtLabels);

void showTime(uint8_t **txtLabels);
void drawSpectrum(uint8_t *buf);

void setWorkBrightness(void);
void setStbyBrightness(void);

void loadDispParams(void);
void saveDisplayParams(void);

void switchSpMode();

#endif /* DISPLAY_H */
