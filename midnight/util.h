#pragma once

constexpr auto num_string_leds{20u};
constexpr auto num_outline_leds{3 * 60u};

struct OutlineEvent {
    uint16_t onset;
    uint16_t duration;
    uint8_t midi_number;
};

struct FretEvent {
    uint16_t onset;
    uint16_t duration;
    uint8_t string_number;
    uint8_t fret_number;
};

struct WheelColor {
    uint8_t r{0u};
    uint8_t g{0u};
    uint8_t b{0u};

    WheelColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

WheelColor Wheel(unsigned char WheelPos, double brightness = 1.0);
