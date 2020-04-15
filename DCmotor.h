#ifndef DCmotor_h 
#define DCmotor_h
#include "Arduino.h"

#define M1  (1)
#define M2  (2)
#define M3  (3)
#define M4  (4)

#define CCW  (0)
#define CW  (1)

class DCmotor
{
private:
 float sx;
 int DGT_PIN1;
  int DGT_PIN2;
 int PWM_PIN;
 uint8_t motor_number;


public:
bool check;
DCmotor(uint8_t motor_number,int DGT_PIN1,int DGT_PIN2, int PWM_PIN);
Updatespeed(int pwm_val,int motor_direction );  
setBrake();


};
#endif
