#include <Adafruit_NeoPixel.h>


static auto const radius{5.f};

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, uint8_t p) {
    sf::Color const grey{180, 180, 180};
    circles.resize(n);
    for (auto &circle : circles) {
        circle.setRadius(radius);
        circle.setFillColor(grey);
    }
}

void Adafruit_NeoPixel::begin() const {

}

void Adafruit_NeoPixel::show() const {

}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
    sf::Color color(static_cast<sf::Uint8>(r * brightness),
                    static_cast<sf::Uint8>(g * brightness),
                    static_cast<sf::Uint8>(b * brightness));
    circles[n].setFillColor(color);
}

uint16_t Adafruit_NeoPixel::numPixels() const {
    return static_cast<uint16_t>(circles.size());
}

void Adafruit_NeoPixel::setBrightness(uint8_t brightness) {
    this->brightness = brightness;
    for (auto &circle : circles) {
        auto color = circle.getFillColor();
        sf::Color new_color(static_cast<sf::Uint8>(color.r * brightness),
                            static_cast<sf::Uint8>(color.g * brightness),
                            static_cast<sf::Uint8>(color.b * brightness));
        circle.setFillColor(new_color);
    }
}

void Adafruit_NeoPixel::setPixelColor(uint16_t n, uint32_t c) {
    auto const r = c >> 16;
    auto const g = (c >> 8) & 8;
    auto const b = c & 8;
    sf::Color const color(static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b));
    circles[n].setFillColor(color);
}

uint32_t Adafruit_NeoPixel::Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
}
