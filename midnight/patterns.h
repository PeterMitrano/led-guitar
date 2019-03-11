#include <math.h>

void
pulse(CRGB *strip, uint16_t step, uint16_t, uint8_t r, uint8_t g, uint8_t b, unsigned int n = 4) {
    auto const intensity = 1;
    for (uint16_t i{0u}; i < num_outline_leds; ++i) {
        if ((i + (step / 2)) % n == 0) {
            strip[i].setRGB(static_cast<uint8_t>(intensity * r),
                            static_cast<uint8_t>(intensity * g),
                            static_cast<uint8_t>(intensity * b));
        } else {
            strip[i].setRGB(0, 0, 0);
        }
    }
}

void fade(CRGB *strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b) {
    auto const intensity = static_cast<double>(step) / duration;
    for (uint16_t i{0u}; i < num_outline_leds; ++i) {
        strip[i].setRGB(static_cast<uint8_t>(intensity * r),
                        static_cast<uint8_t>(intensity * g),
                        static_cast<uint8_t>(intensity * b));
    }
}

void flair(CRGB *strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b) {
    auto const leds_at_step = num_outline_leds * step / duration;
    for (int i{0u}; i < num_outline_leds; ++i) {
        auto d_to_center = i - 102;
        if (d_to_center < -90) {
            d_to_center = 180 + d_to_center;
        }
        d_to_center = abs(d_to_center);
        if (d_to_center <= leds_at_step) {
            strip[i].setRGB(r, g, b);
        } else {
            strip[i].setRGB(0, 0, 0);
        }
    }
}

void rainbow_chaser(CRGB *strip, uint16_t step, uint16_t duration) {
    auto const p = static_cast<unsigned int>(step * num_outline_leds / duration) * 2;
    for (uint16_t i{0u}; i < num_outline_leds; ++i) {
        auto const wheel_idx = static_cast<uint8_t>(i * 255 / num_outline_leds + p);
        auto const color = Wheel(wheel_idx);
        strip[i].setRGB(color.r, color.g, color.b);
    }
}

void reverse_rainbow_chaser(CRGB *strip, uint16_t step, uint16_t duration) {
    auto const p = static_cast<unsigned int>(step * num_outline_leds / duration) * 2;
    for (uint16_t i{0u}; i < num_outline_leds; ++i) {
        auto const wheel_idx = static_cast<uint8_t>(i * 255 / num_outline_leds - p);
        auto const color = Wheel(wheel_idx);
        strip[i].setRGB(color.r, color.g, color.b);
    }
}

void sparkle(CRGB *strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b,
             unsigned int steps_per_sparkle, unsigned int num_sparkles) {
    // set the non-sparkling LEDs
    for (uint16_t i{0u}; i < num_outline_leds; ++i) {
        strip[i].setRGB(r, g, b);
    }
    // set the sparkles
    if (step % steps_per_sparkle == 0) {
        for (uint16_t i{0u}; i < num_sparkles; ++i) {
            auto const random_on_pixel = static_cast<uint16_t>(random(0u, num_outline_leds - 1u));
            strip[random_on_pixel].setRGB(255, 255, 255);
        }
    }
}
