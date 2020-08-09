/*
 * patterns.h
 * chris hamby
 * 
 * the "pattern" describes the data held in the led strip nodes
 * these macros provide names for the current program variable
*/

#ifndef STRIP_PATTERNS_H
#define STRIP_PATTERNS_H

#define OFF                 0x00


/* Pattern names */
#define NO_PATTERN          0x00
#define PATTERN1            0x01
#define PATTERN2            0x02
#define PATTERN3            0x03
#define ALL_WHITE           0x10
#define ALL_OFF             0x11
#define ICESPARKLE_PATTERN  0xA0
#define DEFAULT_PATTERN     PATTERN2

#endif