#include <Arduino.h>
#include "DCmotor.h"


DCmotor::DCmotor(uint8_t motor_number,int DGT_PIN1,int DGT_PIN2,int PWM_PIN)    //constructor
{
  this->motor_number=motor_number;
  this->DGT_PIN1=DGT_PIN1;
  this->DGT_PIN2=DGT_PIN2;
  this->PWM_PIN=PWM_PIN;

  pinMode(DGT_PIN1,OUTPUT);
  pinMode(DGT_PIN2,OUTPUT);
  pinMode(PWM_PIN,OUTPUT);
  
}
 DCmotor::setBrake()
 {    digitalWrite(DGT_PIN1,LOW);
      digitalWrite(DGT_PIN2,LOW);
      analogWrite(PWM_PIN,0);
  
 }
 
 DCmotor::Updatespeed(int pwm_val,int motor_direction )
{
     
  if(pwm_val==0)
  
  {  
    setBrake(); 
  }
  
  else{             
                if(motor_direction==CW)
                
                {
                  
                  digitalWrite(DGT_PIN1,HIGH);
                  digitalWrite(DGT_PIN2,LOW);
                  analogWrite(PWM_PIN,abs(pwm_val));
////                  
//                  Serial.print(motor_number);
//                  Serial.print(": ");
//                  Serial.println(pwm_val);
////                   
           
                }
               
              
              else
               {  digitalWrite(DGT_PIN1,LOW);
                  digitalWrite(DGT_PIN2,HIGH);
                  analogWrite(PWM_PIN,abs(pwm_val));
                  
//                   Serial.print(motor_number);
//                  Serial.print(": ");
//                  Serial.println(pwm_val);
////             
             }
      }
 }




  
  
