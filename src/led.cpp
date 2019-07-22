#include "led_show.h"
#include "led.h"
#include "capture.h"

extern Capture capture;
ledShow ledStrip;

void led_display(void)
{
    if(capture.rateY >= 40){  
        ledStrip.mode0();
        capture.rateY = 0; 
    }
    if(capture.poseX==span)
    {
        ledStrip.mode0();
        capture.poseX=one_dir;
    }
    if(capture.rateX<-30)
    {
        ledStrip.mode1();
        capture.rateX=0;
    }
    if(capture.rateX>30)
    {
        ledStrip.mode2();
        capture.rateX=0;
    }


}
