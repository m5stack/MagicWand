#ifndef _LED_SHOW_H_
#define _LED_SHOW_H_

#include <M5StickC.h>


class ledShow
{
    public:
        ledShow();
        void init();
        void mode0(void);
        void mode1(void);
        void mode2(void);
        void set_brightness(uint16_t brt);
        const uint8_t get(void);

    public:
        uint8_t _led_num;
        uint8_t _led_pin;


    private:
    private:
    

};


#endif