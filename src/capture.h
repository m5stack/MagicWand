#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include <M5StickC.h>


#define  GX gyroX 
#define  GY gyroY 
#define  GZ gyroZ
#define  AX  (accX *10.0f)
#define  AY  (accY *10.0f)
#define  AZ  (accZ *10.0f)





enum POSE{
    idle = 0,
    toLeft = 1,
    toRight,
    forward,
    backward
};
enum rateStatus{
    Up = 1,
    Down = -1,
    Peak =2,
    Valley=-2,
    Flat = 0
};
struct move_raw{
    uint16_t acc[3];
    uint16_t gyro[3];
};


class movement{
    public:
        void get_mm_data(void);

    public:
        POSE pose0;
        POSE pose1;
        POSE pose2;

};

void capture(void);
void print_filter(void);
void filter_reset(void);
rateStatus angularRate(float *a);
void get_motion(void);

#endif
