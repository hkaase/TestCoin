#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/Testcoin.png
ICON_DST=../../src/qt/res/icons/Testcoin.ico
convert ${ICON_SRC} -resize 16x16 Testcoin-16.png
convert ${ICON_SRC} -resize 32x32 Testcoin-32.png
convert ${ICON_SRC} -resize 48x48 Testcoin-48.png
convert Testcoin-16.png Testcoin-32.png Testcoin-48.png ${ICON_DST}

