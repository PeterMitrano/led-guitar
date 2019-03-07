#include <random>
#include <iostream>
#include "Arduino.h"

std::mt19937 gen(0);

long int random(uint16_t a, uint16_t b) {
    std::uniform_int_distribution<uint16_t> dis(a, b);
    return dis(gen);
}

void randomSeed(unsigned long seed) {
    gen.seed(seed);
}

void delayMicroseconds(unsigned long us) {
    // this is mocked in the event loop, so do nothing here.
}

void pinMode(unsigned int pin, unsigned int mode) {
}

int digitalRead(unsigned int pin) {
    std::cout << "press enter...\n";
    std::cin.get();
    return 0;
}
