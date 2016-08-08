#ifndef DISPLAY_H
#define DISPLAY_H

#include <inttypes.h>
#include "rtc.h"
#include "alarm.h"
#include "audio/audio.h"
#include "display/gdfb.h"

#define MIN_BRIGHTNESS			GD_MIN_BRIGHTNESS
#define MAX_BRIGHTNESS			GD_MAX_BRIGHTNESS
#define writeString(x)			gdWriteString(x)
#define displayClear()			gdClear()

/* Backlight state */
#define BACKLIGHT_ON			1
#define BACKLIGHT_OFF			0

/* Radio tuning mode */
#define MODE_RADIO_TUNE			1
#define MODE_RADIO_CHAN			0

/* String buffer */
#define STR_BUFSIZE				20

/* Spectrum output mode */
enum {
	SP_MODE_METER = 0,
	SP_MODE_STEREO,
	SP_MODE_MIXED,

	SP_MODE_END
};

enum {
	FALL_SPEED_LOW = 0,
	FALL_SPEED_MIDDLE,
	FALL_SPEED_FAST,

	FALL_SPEED_END
};

enum {
	LCD_LEVELS = 0,
	LCD_BAR,
	LCD_ALARM,

	LCD_END
};

enum {
	SYM_STEREO_DEGREE = 0,
	SYM_MUTE_CROSS,
	SYM_LOUDNESS_CROSS,
	SYM_SURROUND_CROSS,
	SYM_EFFECT_3D_CROSS,
	SYM_TONE_DEFEAT_CROSS,
	SYM_STEREO_MONO,

	SYM_END
};

void displayInit(void);

uint8_t **getTxtLabels(void);

void setDefDisplay(uint8_t value);
uint8_t getDefDisplay();

void nextRcCmd(void);
void switchTestMode(uint8_t index);
void showRcInfo(void);

void showTemp(void);

void showRadio(uint8_t tune);

void showMute(void);
void showLoudness(void);
void showSurround(void);
void showEffect3d(void);
void showToneDefeat(void);

void showBrWork(void);
void changeBrWork(int8_t diff);

void showSndParam(sndMode mode);

void showTime(void);
void showAlarm(void);
void showTimer(int16_t timer);

void switchSpMode(void);
void switchFallSpeed(void);
void showSpectrum(void);

void setWorkBrightness(void);
void setStbyBrightness(void);

void displayPowerOff(void);

#endif /* DISPLAY_H */
