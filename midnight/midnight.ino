#include <Arduino.h>
#include <TimerOne.h>
#include <FastLED.h>

#include "util.h"
#include "solo.h"
#include "patterns.h"

constexpr auto outline_pin{9u};
constexpr auto e_string_pin{5u};
constexpr auto b_string_pin{6u};
constexpr auto g_string_pin{3u};
constexpr auto button_pin{7u};

CRGB outline[num_outline_leds];
CRGB e_string[num_string_leds];
CRGB g_string[num_string_leds];
CRGB b_string[num_string_leds];

auto time_step{0ull};
auto fret_events_idx{0u};
auto outline_events_idx{0u};
unsigned int const initial_brightness{10};
unsigned int const dim{10};
uint8_t fret_r = 0u, fret_g = 0u, fret_b = 255u;
unsigned long start_time{0ul};
bool started{false};

void setup() {
    Serial.begin(9600);
    randomSeed(0);

    Timer1.initialize(us_per_dt);
    Timer1.attachInterrupt(increment_time_step);

    FastLED.addLeds<NEOPIXEL, outline_pin>(outline, num_outline_leds);
    FastLED.addLeds<NEOPIXEL, e_string_pin>(e_string, num_string_leds);
    FastLED.addLeds<NEOPIXEL, g_string_pin>(g_string, num_string_leds);
    FastLED.addLeds<NEOPIXEL, b_string_pin>(b_string, num_string_leds);

    pinMode(button_pin, INPUT_PULLUP);

    FastLED.setBrightness(1);

    // wait until button is pressed...
    digitalWrite(13, HIGH);
    while (digitalRead(button_pin));
    digitalWrite(13, LOW);
    start_time = micros();
    started = true;
}

void increment_time_step() {
    if (!started) {
        return;
    }

    auto const &current_outline_event = outline_events[outline_events_idx];
    auto const &current_fret_event = fret_events[fret_events_idx];

    if (fret_events_idx >= fret_events_size) {
//        e_string.clear();
//        g_string.clear();
//        b_string.clear();
    } else {
        auto const current_fret_step = time_step - current_fret_event.onset + 1;
        for (uint16_t i{0u}; i < num_string_leds; ++i) {
            auto const c = Wheel(static_cast<unsigned char>(i * 255 / num_string_leds), 0.2);
            e_string[i].setRGB(c.r, c.b, c.g);
            g_string[i].setRGB(c.r, c.b, c.g);
            b_string[i].setRGB(c.r, c.b, c.g);
        }
        if (current_fret_event.fret_number == 21) {
            constexpr auto speedup_factor{2.0};
            for (uint16_t i{0u}; i < min(current_fret_step * speedup_factor, num_string_leds); ++i) {
                e_string[num_string_leds-i].setRGB(255, 255, 255);
                b_string[num_string_leds-i].setRGB(255, 255, 255);
                g_string[num_string_leds-i].setRGB(255, 255, 255);
            }
        } else if (current_fret_event.string_number < 4) {
            auto const f = 19 - current_fret_event.fret_number;
            e_string[f].setRGB(255, 255, 255);
            g_string[f].setRGB(255, 255, 255);
            b_string[f].setRGB(255, 255, 255);
        } else if (current_fret_event.string_number == 4) {
            // special case
            for (uint16_t i{0u}; i < num_string_leds; ++i) {
                e_string[i].setRGB(dim, dim, 0);
                b_string[i].setRGB(dim, dim, 0);
                g_string[i].setRGB(dim, dim, 0);
            }
        }
    }

    if (outline_events_idx >= outline_events_size) {
//        outline.clear();
    } else {
        auto const current_outline_step = time_step - current_outline_event.onset + 1;
        switch (current_outline_event.midi_number) {
            case 61: {
                fade(outline, current_outline_step, current_outline_event.duration, 255, 0, 0);
                break;
            }
            case 62: {
                fade(outline, current_outline_step, current_outline_event.duration, 0, 255, 0);
                break;
            }
            case 63: {
                fade(outline, current_outline_step, current_outline_event.duration, 0, 0, 255);
                break;
            }
            case 64: {
                fade(outline, current_outline_step, current_outline_event.duration, 255, 255, 0);
                break;
            }
            case 65: {
                pulse(outline, current_outline_step, current_outline_event.duration, 255, 0, 0);
                break;
            }
            case 66: {
                pulse(outline, current_outline_step, current_outline_event.duration, 0, 255, 0);
                break;
            }
            case 67: {
                pulse(outline, current_outline_step, current_outline_event.duration, 0, 0, 255);
                break;
            }
            case 68: {
                pulse(outline, current_outline_step, current_outline_event.duration, 255, 255, 0);
                break;
            }
            case 69: {
                sparkle(outline, current_outline_step, current_outline_event.duration, 0, 0, 255, 6, 60);
                break;
            }
            case 70: {
                rainbow_chaser(outline, current_outline_step, current_outline_event.duration);
                break;
            }
            case 71: {
                reverse_rainbow_chaser(outline, current_outline_step, current_outline_event.duration);
                break;
            }
            case 72: {
                flair(outline, current_outline_step, current_outline_event.duration, 255, 0, 0);
                break;
            }
            case 73: {
                flair(outline, current_outline_step, current_outline_event.duration, 0, 255, 0);
                break;
            }
            case 74: {
                flair(outline, current_outline_step, current_outline_event.duration, 0, 0, 255);
                break;
            }
            case 75: {
                flair(outline, current_outline_step, current_outline_event.duration, 255, 255, 0);
                break;
            }
            case 76: {
                for (uint32_t i{0u}; i < num_outline_leds; ++i) {
                    outline[i].setRGB(dim, dim, 0);
                }
                break;
            }
        }
    }

    FastLED.show();

    ++time_step;
    if (time_step == (current_outline_event.onset + current_outline_event.duration)) {
//        outline.clear();
        outline_events_idx++;
    }
    if (time_step == current_fret_event.onset + current_fret_event.duration) {
//        e_string.clear();
//        g_string.clear();
//        b_string.clear();
        fret_events_idx++;
        auto const fret_rgb = random(0u, 2u);
        if (fret_rgb == 0) {
            fret_r = 255;
            fret_g = 0;
            fret_b = 0;
        } else if (fret_rgb == 1) {
            fret_r = 0;
            fret_g = 255;
            fret_b = 0;
        } else if (fret_rgb == 2) {
            fret_r = 0;
            fret_g = 0;
            fret_b = 255;
        }
    }

}

void loop() {
    return;
}

WheelColor Wheel(unsigned char WheelPos, double brightness) {
    WheelPos = static_cast<unsigned char>(255 - WheelPos);
    if (WheelPos < 85) {
        return WheelColor{static_cast<uint8_t>((255 - WheelPos * 3) * brightness), 0,
                static_cast<uint8_t>(WheelPos * 3 * brightness)};
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return WheelColor{0, static_cast<uint8_t>(WheelPos * 3 * brightness),
                static_cast<uint8_t>((255 - WheelPos * 3) * brightness)};
    }
    WheelPos -= 170;
    return WheelColor{static_cast<uint8_t>(WheelPos * 3 * brightness),
            static_cast<uint8_t>((255 - WheelPos * 3) * brightness),
            0};
}
