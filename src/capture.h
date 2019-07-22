#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include <M5StickC.h>


#define  GX gyroX 
#define  GY gyroY 
#define  GZ gyroZ
#define  AX  (accX *10.0f)
#define  AY  (accY *10.0f)
#define  AZ  (accZ *10.0f)

#define GxOffset -0.427
#define GyOffset 3.29
#define GzOffset -13.92
#define M_PI 3.14159265359	    
#define dt 0.01	


enum POSE{
    one_dir = 0,
    span = 2
};

enum rateStatus{
    Up = 1,
    Down = -1,
    Flat = 0
};


class Capture{
    public:
        Capture();
        rateStatus angularRate(float *a);
        void get_motion(void);
        void imu_filter(void);
        POSE* get_pose(void);


    public:
        int8_t rateX,rateY,rateZ;
        POSE poseX,poseY,poseZ;
        
        float AxArray[10], AyArray[10], AzArray[10] = {0};
        float angleX, angleY, angleZ;
        float gXRate, gYRate, gZRate;
        float forceMagnitudeApprox;
        uint8_t sampleCnt = 0;
        int rateFactor;
        rateStatus rateSta;

    private:
        void set_pose(POSE* p);


};

#endif
