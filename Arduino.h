#pragma once

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

long int random(uint16_t a, uint16_t b);
void randomSeed(unsigned long seed);
void delayMicroseconds(unsigned long us);