#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "solo.h"
#include "patterns.h"

uint32_t Wheel(unsigned char WheelPos);

constexpr auto outline_pin{3u};
constexpr auto e_string_pin{5u};
constexpr auto b_string_pin{6u};
constexpr auto g_string_pin{0u};

Adafruit_NeoPixel outline = Adafruit_NeoPixel(3 * 60, outline_pin);
Adafruit_NeoPixel e_string = Adafruit_NeoPixel(20, e_string_pin);
Adafruit_NeoPixel b_string = Adafruit_NeoPixel(20, b_string_pin);
Adafruit_NeoPixel g_string = Adafruit_NeoPixel(20, g_string_pin);

auto time_step{0ull};
auto fret_events_idx{0u};
auto outline_events_idx{0u};
unsigned int const initial_brightness{50};
unsigned int const dim{25};

void setup() {
    randomSeed(0);
    outline.begin();
    e_string.begin();
    b_string.begin();
    g_string.begin();

    outline.setBrightness(initial_brightness);
    e_string.setBrightness(initial_brightness);
    b_string.setBrightness(initial_brightness);
    g_string.setBrightness(initial_brightness);

    outline.show();
    e_string.show();
    b_string.show();
    g_string.show();
}

void loop() {
    outline.clear();
    e_string.clear();
    g_string.clear();
    b_string.clear();

    auto const &current_outline_event = outline_events[outline_events_idx];
    auto const &next_outline_event = outline_events[outline_events_idx + 1];
    auto const &current_fret_event = fret_events[fret_events_idx];
    auto const &next_fret_event = fret_events[fret_events_idx + 1];

    if (current_fret_event.string_number == 1) {
        e_string.setPixelColor(current_fret_event.fret_number, Wheel(fret_events_idx));
    } else if (current_fret_event.string_number == 2) {
        b_string.setPixelColor(current_fret_event.fret_number, Wheel(fret_events_idx));
    } else if (current_fret_event.string_number == 3) {
        g_string.setPixelColor(current_fret_event.fret_number, Wheel(fret_events_idx));
    } else if (current_fret_event.string_number == 4) {
        // special case
        e_string.setBrightness(dim);
        e_string.setPixelColor(current_fret_event.fret_number, 255, 255, 0);

        b_string.setBrightness(dim);
        b_string.setPixelColor(current_fret_event.fret_number, 255, 255, 0);

        g_string.setBrightness(dim);
        g_string.setPixelColor(current_fret_event.fret_number, 255, 255, 0);
    }


    auto const current_outline_step = time_step - current_fret_event.onset;
    auto const current_outline_duration = next_outline_event.onset - current_fret_event.onset;
    outline.setBrightness(initial_brightness);
    switch (current_outline_event.midi_number) {
        case 61: {
            pulse(outline, current_outline_step, current_outline_duration, 255, 0, 0, 4);
            break;
        }
        case 62: {
            pulse(outline, current_outline_step, current_outline_duration, 0, 255, 0, 4);
            break;
        }
        case 63: {
            pulse(outline, current_outline_step, current_outline_duration, 0, 0, 255, 4);
            break;
        }
        case 64: {
            pulse(outline, current_outline_step, current_outline_duration, 255, 255, 0, 4);
            break;
        }
        case 65: {
            fade(outline, current_outline_step, current_outline_duration, 255, 0, 0);
            break;
        }
        case 66: {
            fade(outline, current_outline_step, current_outline_duration, 0, 255, 0);
            break;
        }
        case 67: {
            fade(outline, current_outline_step, current_outline_duration, 0, 0, 255);
            break;
        }
        case 68: {
            fade(outline, current_outline_step, current_outline_duration, 255, 255, 0);
            break;
        }
        case 69: {
            sparkle(outline, current_outline_step, current_outline_duration, 255, 255, 0, 16, 32);
            break;
        }
        case 70: {
            rainbow_chaser(outline, current_outline_step, current_outline_duration);
            break;
        }
        case 71: {
            reverse_rainbow_chaser(outline, current_outline_step, current_outline_duration);
            break;
        }
        case 72: {
            flair(outline, current_outline_step, current_outline_duration, 255, 0, 0);
            break;
        }
        case 73: {
            flair(outline, current_outline_step, current_outline_duration, 0, 255, 0);
            break;
        }
        case 74: {
            flair(outline, current_outline_step, current_outline_duration, 0, 0, 255);
            break;
        }
        case 75: {
            flair(outline, current_outline_step, current_outline_duration, 255, 255, 0);
            break;
        }
        case 76: {
            outline.setBrightness(dim);
            for (auto i{0}; i < outline.numPixels(); ++i) {
                outline.setPixelColor(i, 255, 255, 0);
            }
            break;
        }
    }

    outline.show();
    e_string.show();
    b_string.show();
    g_string.show();

    delayMicroseconds(ms_per_dt * 1000);

    ++time_step;
    if (time_step == next_outline_event.onset) {
        outline_events_idx++;
    }
    if (time_step == next_fret_event.onset) {
        fret_events_idx++;
    }
}

uint32_t Wheel(unsigned char WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
