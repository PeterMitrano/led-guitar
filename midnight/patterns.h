#include <math.h>

constexpr uint32_t OFF{0};

void
pulse(Adafruit_NeoPixel &strip, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b, unsigned int offset,
      unsigned int n = 4) {
    auto const intensity = pow(static_cast<double>(duration - step) / duration, 4);
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        if ((i + offset) % n == 0) {
//            auto const intensity = 1;
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
    auto const leds_per_step = strip.numPixels() / step;
    for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
        if (i <= leds_per_step * step) {
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
             unsigned int sparkled_per_quarter, unsigned int num_sparkles) {
    if (step % sparkled_per_quarter == 0) {
        for (uint16_t i{0u}; i < strip.numPixels(); ++i) {
            strip.setPixelColor(i, r, g, b);
        }
        for (uint16_t i{0u}; i < num_sparkles; ++i) {
            auto const random_on_pixel = random(0u, strip.numPixels());
            strip.setPixelColor(random_on_pixel, 255, 255, 255);
        }
    }
}
