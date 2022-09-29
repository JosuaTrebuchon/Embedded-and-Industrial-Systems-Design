/*
 * fonts.h
 *
 * Library of fonts
 * Large: 8x8, normal: 5x7 and small: 4x7
 */
#ifndef FONTS_H_
#define FONTS_H_


#include <avr/pgmspace.h>

// Font 8x8 - Large
extern const unsigned char PROGMEM font8[95][8];

// Font 5x7 - normal
extern const unsigned char PROGMEM font5[95][5];

// Font 4x6 - Small
extern const unsigned char PROGMEM font4[95][4];


#endif /* FONTS_H_ */