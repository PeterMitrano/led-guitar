#pragma once

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define INPUT_PULLUP 1

long int random(uint16_t a, uint16_t b);
void randomSeed(unsigned long seed);
void delayMicroseconds(unsigned long us);
void pinMode(unsigned int pin, unsigned int mode);
int digitalRead(unsigned int pin);
