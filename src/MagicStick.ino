
#include <FastLED.h>
#include <TaskScheduler.h>
#include "capture.h"
#include "led_show.h"
#include "led.h"

// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();
void printLog(void);

float accX, accY, accZ;
float gyroX,gyroY,gyroZ;

//Tasks
Task t1(10, TASK_FOREVER, &t1Callback);
Task t2(100, TASK_FOREVER, &t2Callback);
Task t3(90, TASK_FOREVER, &t3Callback);
Task t4(100, TASK_FOREVER, &t4Callback);

extern float angleX, angleY, angleZ;
extern ledShow ledStrip;
extern int poseX, poseY, poseZ;

Scheduler runner;
Capture capture;

void t1Callback() {
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ); 
  capture.imu_filter(); 
  //Serial.print(angleX);
  // Serial.print("    ");
  // Serial.print(angleY);
  // Serial.print("    ");
  // Serial.print(angleZ);
  //Serial.print("   \r\n");
}

void t2Callback() {
    capture.get_motion();
}
void t3Callback(){
    led_display();
}
void t4Callback(){
    //printLog();
}
void setup() {
  // M5 init
  M5.begin();
  Serial.begin(115200); 
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 15);
// Pin init
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
// FastLED init
  ledStrip.init();

// Scheduler init
  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);
  runner.addTask(t4);

  delay(5000);
  t1.enable();
  t2.enable();
  t3.enable();
  t4.enable();
  
}

void loop() {
runner.execute();

//imu_getData();
}


void printLog(void)
{
  Serial.printf("  AX: %f , AY: %f , AZ: %f \r\n", AX,AY,AZ);
  Serial.printf("  GX: %f , GY: %f , GZ: %f \r\n", GX,GY,GZ);
}