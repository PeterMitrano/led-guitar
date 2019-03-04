#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <vector>

#define NEO_KHZ800 0x0000
#define NEO_GRB  ((1 << 6) | (1 << 4) | (0 << 2) | (2))


struct Adafruit_NeoPixel {

    explicit Adafruit_NeoPixel(uint16_t n, uint8_t p = 6);

    void begin() const;

    void show() const;

    void clear();

    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);

    void setPixelColor(uint16_t n, uint32_t c);

    void setBrightness(uint8_t brightness);

    uint16_t numPixels() const;

    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b);

    // "PRIVATE"
    std::vector<sf::CircleShape> circles;
    double brightness{1.0};

};