#include "led_show.h"
#include "led.h"
#include "capture.h"

extern uint8_t poseX, poseY, poseZ;
extern int8_t rateX,rateY,rateZ;
ledShow ledStrip;
void led_display(void)
{
    if(rateY >= 40){  
        ledStrip.mode0();
        rateY = 0; 
    }
    if(poseX==2)
    {
        ledStrip.mode0();
        poseX=0;
    }
    if(rateX<-30)
    {
        ledStrip.mode1();
        rateX=0;
    }
    if(rateX>30)
    {
        ledStrip.mode2();
        rateX=0;
    }


}
