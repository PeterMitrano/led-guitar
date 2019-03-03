#pragma once

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

uint32_t Wheel(unsigned char WheelPos);
