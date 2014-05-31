#!/bin/sh

for AUDIOPROC in TDA7439 TDA7313 TDA7318
do
	for DISPLAY in KS0108 KS0066 LS020
	do
		for TUNER in TEA5767 TUX032
		do
			make AUDIOPROC=${AUDIOPROC} DISPLAY=${DISPLAY} TUNER=${TUNER}
			make AUDIOPROC=${AUDIOPROC} DISPLAY=${DISPLAY} TUNER=${TUNER} clean_var
		done
	done
done

make clean_const
