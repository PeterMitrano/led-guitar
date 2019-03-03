constexpr uint32_t OFF{0};

void pulse(Adafruit_NeoPixel &string, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b, unsigned int offset, unsigned int n=4) {
  for (auto i{0}; i < string.numPixels(); ++i) {
    if ((i + offset) % n == 0) {
      if (step < duration / 2) {
        string.setPixelColor(i, r, g, b);
      }
      else {
        string.setPixelColor(i, OFF);
      }
    }
    else {
      string.setPixelColor(i, OFF);
    }
  }
}

void fade(Adafruit_NeoPixel &string, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b) {
  auto const intensity = (step * 255) / duration;
  for (auto i{0}; i < string.numPixels(); ++i) {
    string.setPixelColor(i, intensity*r, intensity*g, intensity*b);
  }
}

void flair(Adafruit_NeoPixel &string, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b) {
  auto const leds_per_step =  string.numPixels() / step;
  for (auto i{0}; i < string.numPixels(); ++i) {
    if (i <= leds_per_step * step) {
      string.setPixelColor(i, r, g, b);
    }
    else {
      string.setPixelColor(i, OFF);
    }
  }
}

void rainbow_chaser(Adafruit_NeoPixel &string, uint16_t step, uint16_t duration) {
}

void reverse_rainbow_chaser(Adafruit_NeoPixel &string, uint16_t step, uint16_t duration) {
}

void sparkle(Adafruit_NeoPixel &string, uint16_t step, uint16_t duration, uint8_t r, uint8_t g, uint8_t b, unsigned int sparkled_per_quarter, unsigned int num_sparkles) {
  if (step % sparkled_per_quarter == 0) {
    for (auto i{0}; i < string.numPixels(); ++i) {
      string.setPixelColor(i, r, g, b);
    }
    for (auto i{0}; i < num_sparkles; ++i) {
      auto const random_on_pixel = random(0, string.numPixels());
      string.setPixelColor(random_on_pixel, 255, 255, 255);
    }
  }
}
