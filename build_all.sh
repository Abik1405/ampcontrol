#!/bin/sh

for DISPLAY in KS0108 ST7920 SSD1306
do
	make clean
	make DISPLAY=${DISPLAY}
done

make clean
