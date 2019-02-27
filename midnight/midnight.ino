#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

struct OutlineEvent {
  uint8_t onset;
  uint8_t midi_number;
};

struct FretEvent {
  uint8_t onset;
  uint8_t string_number;
  uint8_t fret_number;
};

#include "solo.h"

constexpr auto outline_pin{3u};
constexpr auto top_pin{5u};
constexpr auto middle_pin{6u};
constexpr auto bottom_pin{0u};

Adafruit_NeoPixel outline = Adafruit_NeoPixel(60, outline_pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel top = Adafruit_NeoPixel(60, top_pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel middle = Adafruit_NeoPixel(60, middle_pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottom = Adafruit_NeoPixel(60, bottom_pin, NEO_GRB + NEO_KHZ800);

auto time_step{0ull};
auto fret_events_idx{0u};
auto outline_events_idx{0u};

void setup() {
  outline.begin();
  top.begin();
  middle.begin();
  bottom.begin();

  unsigned int const initial_brightness{50};
  outline.setBrightness(initial_brightness);
  top.setBrightness(initial_brightness);
  middle.setBrightness(initial_brightness);
  bottom.setBrightness(initial_brightness);

  outline.show();
  top.show();
  middle.show();
  bottom.show();
}

void loop() {
  auto current_outline_event = outline_events[outline_events_idx];

  //  for(uint16_t i=0; i<outline.numPixels(); i++) {
  //    auto color = outline.Color(solo[0][i][0], solo[0][i][1], solo[0][i][2]);
  //    outline.setPixelColor(i, color);
  //  }
  //  for(uint16_t i=0; i<top.numPixels(); i++) {
  //    auto color = top.Color(solo[0][i][0], solo[0][i][1], solo[0][i][2]);
  //    top.setPixelColor(i, color);
  //  }
  //  for(uint16_t i=0; i<middle.numPixels(); i++) {
  //    auto color = middle.Color(solo[0][i][0], solo[0][i][1], solo[0][i][2]);
  //    middle.setPixelColor(i, color);
  //  }
  //  for(uint16_t i=0; i<bottom.numPixels(); i++) {
  //    auto color = bottom.Color(solo[0][i][0], solo[0][i][1], solo[0][i][2]);
  //    bottom.setPixelColor(i, color);
  //  }

  outline.show();
  top.show();
  middle.show();
  bottom.show();

  delayMicroseconds(us_per_dt);

  ++time_step;
  if (time_step == current_outline_event.onset) {
    outline_events_idx++;
  }
}

//// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
//for(uint16_t i=0; i<strip.numPixels(); i++) {
//strip.setPixelColor(i, c);
//strip.show();
//delay(wait);
//}
//}

//void rainbow(uint8_t wait) {
//uint16_t i, j;

//for(j=0; j<256; j++) {
//for(i=0; i<strip.numPixels(); i++) {
//strip.setPixelColor(i, Wheel((i+j) & 255));
//}
//strip.show();
//delay(wait);
//}
//}

//// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(uint8_t wait) {
//uint16_t i, j;

//for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//for(i=0; i< strip.numPixels(); i++) {
//strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//}
//strip.show();
//delay(wait);
//}
//}

////Theatre-style crawling lights.
//void theaterChase(uint32_t c, uint8_t wait) {
//for (int j=0; j<10; j++) {  //do 10 cycles of chasing
//for (int q=0; q < 3; q++) {
//for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//strip.setPixelColor(i+q, c);    //turn every third pixel on
//}
//strip.show();

//delay(wait);

//for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//strip.setPixelColor(i+q, 0);        //turn every third pixel off
//}
//}
//}
//}

////Theatre-style crawling lights with rainbow effect
//void theaterChaseRainbow(uint8_t wait) {
//for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
//for (int q=0; q < 3; q++) {
//for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
//}
//strip.show();

//delay(wait);

//for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//strip.setPixelColor(i+q, 0);        //turn every third pixel off
//}
//}
//}
//}

//// Input a value 0 to 255 to get a color value.
//// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//WheelPos = 255 - WheelPos;
//if(WheelPos < 85) {
//return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//}
//if(WheelPos < 170) {
//WheelPos -= 85;
//return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//}
//WheelPos -= 170;
//return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
