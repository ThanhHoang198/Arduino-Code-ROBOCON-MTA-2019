#ifndef line_h
#define line_h
#include "Arduino.h"
extern int san;
#define green (1)
#define red (0)


extern int count1,count2,dem,dung,back_flag,stop_flag,dung_cheo1,dung_tam,dicheo,tha2,next_time,demcheo,back;

 class line
{ public:
 int white[8];
 int black[8];
 int sensorPins[8];
 int  sensorValues[8];
 int normalizedValues[8];



public:
 
line(int *white, int *black,int *sensorPins,int*sensorValues,int*normalizedValues);
int readSensors();
void normalizeSensors();
float Error_calculating();

void calibrateSensorsBlack();
void sendvalue();
};
#endif
