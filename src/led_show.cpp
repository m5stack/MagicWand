#include <FastLED.h>
#include "led_show.h"

#define LED_NUM 92
#define LED_PIN 26


CRGB leds[LED_NUM]; //ledStrip.get()];
extern CFastLED FastLED;

ledShow::ledShow(){

}
const uint8_t ledShow::get(void)
{
    const uint8_t num = _led_num;
    return num;
}

void ledShow::init(void)
{
    FastLED.addLeds<WS2811,26, RGB>(leds,92);    
    FastLED.setBrightness(4);
}

void ledShow::mode0(void){

    for(int whiteLed = 0; whiteLed < 92; ) {
        leds[whiteLed] = CRGB::Blue;
        FastLED.show();
        delay(10);
        whiteLed+=2;
    }
    for(int whiteLed = 92; whiteLed >=0; ) {
            leds[whiteLed] = CRGB::Black;
            FastLED.show();
            delay(10);
            whiteLed-=2;
      }
}
void ledShow::mode1(void){

    for(int whiteLed = 0; whiteLed < 92; ) {
        leds[whiteLed] = CRGB::Green;
        FastLED.show();
        delay(10);
        whiteLed+=2;
    }
}
void ledShow::mode2(void){

    for(int whiteLed = 92; whiteLed >=0; ) {
            leds[whiteLed] = CRGB::Black;
            FastLED.show();
            delay(10);
            whiteLed-=2;
      }
}
