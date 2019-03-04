#include <Adafruit_NeoPixel.h>


static auto const radius{3.f};

Adafruit_NeoPixel::Adafruit_NeoPixel(uint16_t n, uint8_t p) {
    circles.resize(n);
    for (auto &circle : circles) {
        circle.setRadius(radius);
        circle.setFillColor(sf::Color::Black);
    }
}

void Adafruit_NeoPixel::begin() const {

}

void Adafruit_NeoPixel::show() const {

}

void Adafruit_NeoPixel::clear() {
    for (auto &circle : circles) {
        circle.setFillColor(sf::Color::Black);
    }
}


void Adafruit_NeoPixel::setPixelColor(uint16_t const n, uint8_t const r, uint8_t const g, uint8_t const b) {
    sf::Color color(static_cast<sf::Uint8>(brightness * r),
                    static_cast<sf::Uint8>(brightness * g),
                    static_cast<sf::Uint8>(brightness * b));
    circles[n].setFillColor(color);
}

uint16_t Adafruit_NeoPixel::numPixels() const {
    return static_cast<uint16_t>(circles.size());
}

void Adafruit_NeoPixel::setBrightness(uint8_t const brightness) {
    this->brightness = static_cast<double>(brightness) / 100.0;
}

void Adafruit_NeoPixel::setPixelColor(uint16_t const n, uint32_t const c) {
    // c = 255 should be 255, 0, 0
    // c = 0 should be
    auto const r = static_cast<sf::Uint8>(c >> 16);
    auto const g = static_cast<sf::Uint8>(c >> 8);
    auto const b = static_cast<sf::Uint8>(c);
    sf::Color const color(static_cast<sf::Uint8>(brightness * r),
                          static_cast<sf::Uint8>(brightness * g),
                          static_cast<sf::Uint8>(brightness * b));
    circles[n].setFillColor(color);
}

uint32_t Adafruit_NeoPixel::Color(uint8_t const r, uint8_t const g, uint8_t const b) {
    return ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
}
