#include <M5StickC.h>
#include <math.h>
#include "capture.h"
#include "led_show.h"

extern float accX, accY, accZ, gyroX, gyroY, gyroZ;



Capture::Capture() {
}


void Capture::imu_filter(void)
{
    float pitchAcc, rollAcc, yawAcc;

    if(abs(gyroX-GxOffset)>20 && abs(gyroY-GyOffset)>20 && abs(gyroZ-GzOffset)>20)
    {
        gXRate = gyroX - GzOffset;
        angleX += gXRate * dt;
        gYRate = gyroY - GzOffset;
        angleY += gYRate * dt;
        gZRate = gyroZ - GzOffset;
        angleZ += gZRate * dt;

        forceMagnitudeApprox = abs(AX)+abs(AY)+abs(AZ);
        if(forceMagnitudeApprox>15)
        {
            //Serial.print(">15");
            pitchAcc = atan2f(accY, accZ) * 180 / M_PI;
            angleX = angleX * 0.98 + pitchAcc * 0.02;
    
        // Turning around the Y axis results in a vector on the X-axis
            rollAcc = atan2f(accX, accZ) * 180 / M_PI;
            angleY = angleY * 0.98 + rollAcc * 0.02;

        // Turning around the Y axis results in a vector on the X-axis
            yawAcc = atan2f(accX, accZ) * 180 / M_PI;
            angleZ = angleZ * 0.98 + yawAcc * 0.02;
        }
    }
    
    if(sampleCnt>=10)
    {
        sampleCnt=0;
        rateX = angularRate(AxArray);
        rateX *= rateFactor;
        rateY = angularRate(AyArray);
        rateY *= rateFactor;
        rateZ = angularRate(AzArray);
        rateZ *= rateFactor;
        Serial.printf("rateX: %d ,rateY: %d rateZ:%d \r\n", rateX,rateY,rateZ);
    }
    if(sampleCnt < 10)
    {
        AxArray[sampleCnt] = angleX;
        AyArray[sampleCnt] = angleY;
        AzArray[sampleCnt] = angleZ;
    }
    sampleCnt++;
}

rateStatus Capture::angularRate(float *a){
    // find the maximum minimum and their index 
    uint8_t i, max_idx, min_idx = 0;
    float max0, min0;
    max0 = a[0];
    min0 = a[9];

    for(i=0;i<10;i++){
       if(a[i]>=max0){
            max0 = a[i];
            max_idx=i;
        }   
        if(a[9-i]<=min0){
            min0 = a[9-i];
            min_idx = 9-i;
        }              
    }
    //Serial.printf("max:%2f, min: %2f, max_idx: %d, min_idx: %d ", max0, min0, max_idx, min_idx);
    if(max0!=min0)
    {
        if(max_idx>min_idx)
        rateSta = Up;
        if(max_idx<min_idx)
        rateSta = Down;
        rateFactor = abs(max0-min0);
        //Serial.printf("max_id: %d , min_id: %d \r\n",max_idx, min_idx);
    }
    else 
    rateSta = Flat;
    return rateSta;

}

void Capture::get_motion(void)
{
    uint8_t i;
    static uint8_t pSum,nSum,zSum ;
    static uint8_t cnt=0;
   static int RxArray[10],RyArray[10],RzArray[10];
    if(cnt<10)
    {
        RxArray[cnt]=rateX; RyArray[cnt]=rateY; RzArray[cnt]=rateZ;
        cnt++;
        return;
    }
    else
    cnt = 0;


    //------------X----------------
     pSum=0;nSum=0;zSum=0;
    for(i=0;i<10;i++){
        if(RxArray[i]>0)
            pSum++;
        else if(RxArray[i]<0)
            nSum++;
        else 
            zSum++;
    }
    //Serial.printf("pSum:%d, nSum:%d, zSum:%d \r\n", pSum,nSum,zSum);
    if(abs(pSum-nSum)<= 2 && zSum < 1)
    poseX = span;
    else 
    poseX = one_dir;
  //------------Y----------------
  pSum=0;nSum=0;zSum=0;
      for(i=0;i<10;i++){
        if(RyArray[i]>0)
            pSum++;
        else if(RyArray[i]<0)
            nSum++;
        else 
            zSum++;
    }
    if(abs(pSum-nSum)<= 2 && zSum < 1)
        poseY = span;
    else 
        poseY = one_dir;
     //-----------Z-----------------
     pSum=0;nSum=0;zSum=0;
      for(i=0;i<10;i++){
        if(RzArray[i]>0)
            pSum++;
        else if(RzArray[i]<0)
            nSum++;
        else 
            zSum++;
    }
    if(abs(pSum-nSum)<= 2 && zSum < 1)
        poseZ = span;
    else 
        poseZ = one_dir;

}




/* Complementary Filter  */
        //*pitch += ((float)gyrData[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
        //*roll -= ((float)gyrData[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis
        //float pitchAcc, rollAcc, yawAcc;
        // forceMagnitudeApprox = abs(AX)+abs(AY)+abs(AZ);
        // if(forceMagnitudeApprox>20)
        // {
        //     pitchAcc = atan2f(accY, accZ) * 180 / M_PI;
        //     angleX = angleX * 0.98 + pitchAcc * 0.02;
    
        // // Turning around the Y axis results in a vector on the X-axis
        //     rollAcc = atan2f(accX, accZ) * 180 / M_PI;
        //     angleY = angleY * 0.98 + rollAcc * 0.02;

        // // Turning around the Y axis results in a vector on the X-axis
        //     yawAcc = atan2f(accX, accZ) * 180 / M_PI;
        //     angleZ = angleZ * 0.98 + yawAcc * 0.02;
        // }










/*IMUfilter */
//Change the second parameter (which is a tuning parameter)
//to try and get optimal results. 
// IMUfilter imuFilter(0.01, 10);
 
// void capture(void) {
 
//     //Gyro and accelerometer values must be converted to rad/s and m/s/s
//     //before being passed to the filter.

    
//     if(abs(gyroX-GxOffset)>10 && abs(gyroY-GyOffset)>10 && abs(gyroZ-GzOffset)>10)
//     {
//         imuFilter.updateFilter(gyroX-GxOffset, gyroY-GyOffset, gyroZ-GzOffset, accX, accY, accZ);
//         imuFilter.computeEuler();
//         rst_cnt=0;
//     }


// }
// void print_filter(void)
// {
//     Serial.printf("%f, %f, %f \r\n", imuFilter.getRoll(), imuFilter.getPitch(), imuFilter.getYaw());
// }
// void filter_reset(void)
// {
//     rst_cnt++;
//     if(abs(gyroX-GxOffset)<10 && abs(gyroY-GyOffset)<10 
//     && abs(gyroZ-GzOffset)<10 && rst_cnt>6)
//     {
//         imuFilter.reset();
//         rst_cnt = 0;
//         Serial.printf("cnt:%d",rst_cnt);
//     }
    
// }