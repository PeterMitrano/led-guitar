#include <random>
#include "Arduino.h"

std::mt19937 gen(0);

long int random(int a, int b) {
    std::uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

void randomSeed(unsigned long seed) {
    gen.seed(seed);
}

void delayMicroseconds(unsigned long us) {
    // this is mocked in the event loop, so do nothing here.
}
