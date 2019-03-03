#include <math.h>

constexpr uint32_t OFF{0};

void
pulse(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b, unsigned int offset,
      unsigned int n = 4) {
    auto const intensity = 1;
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        if ((i + offset) % n == 0) {
            strip.setPixelColor(i,
                                static_cast<uint8_t>(intensity * r),
                                static_cast<uint8_t>(intensity * g),
                                static_cast<uint8_t>(intensity * b));
        } else {
            strip.setPixelColor(i, OFF);
        }
    }
}

void fade(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b) {
    auto const intensity = static_cast<double>(step) / duration;
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        strip.setPixelColor(i,
                            static_cast<uint8_t>(intensity * r),
                            static_cast<uint8_t>(intensity * g),
                            static_cast<uint8_t>(intensity * b));
    }
}

void flair(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b) {
    auto const leds_at_step = strip.numPixels() * step / duration;
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        auto d_to_center = i - 102;
        if (d_to_center < -90) {
            d_to_center = 180 + d_to_center;
        }
        d_to_center = abs(d_to_center);
        if (d_to_center <= leds_at_step) {
            strip.setPixelColor(i, r, g, b);
        } else {
            strip.setPixelColor(i, OFF);
        }
    }
}

void rainbow_chaser(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration) {
    auto const p = static_cast<unsigned int>(step * strip.numPixels() / duration) * 2;
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        auto const wheel_idx = static_cast<uint8_t>(i * 255 / strip.numPixels() + p);
        auto const color = Wheel(wheel_idx);
        strip.setPixelColor(i, color);
    }
}

void reverse_rainbow_chaser(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration) {
    auto const p = static_cast<unsigned int>(step * strip.numPixels() / duration) * 2;
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        auto const wheel_idx = static_cast<uint8_t>(i * 255 / strip.numPixels() - p);
        auto const color = Wheel(wheel_idx);
        strip.setPixelColor(i, color);
    }
}

void sparkle(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b,
             unsigned int steps_per_sparkle, unsigned int num_sparkles) {
    // set the non-sparkling LEDs
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        strip.setPixelColor(i, r, g, b);
    }
    // set the sparkles
    if (step % steps_per_sparkle == 0) {
        for (uint16_t i{0u}; i < num_sparkles; ++i) {
            auto const random_on_pixel = random(0u, strip.numPixels() - 1u);
            strip.setPixelColor(static_cast<uint16_t>(random_on_pixel), 255, 255, 255);
        }
    }
}
