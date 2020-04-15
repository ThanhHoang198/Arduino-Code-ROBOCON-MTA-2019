 
#include "kCalendar.h"
#include <math.h>
#include"DCmotor.h"
#include"line.h"
#include"PID.h"
#include"calibrate.h"
#include"roep.h"
#include"LCD_MODE.h"


void setup()
{  setup_bong();
  digitalWrite(8,1);
  digitalWrite(9,1);
  digitalWrite(7,1);
  digitalWrite(6,1);
  digitalWrite(36,1);
  digitalWrite(48,1);
  digitalWrite(40,1);
  digitalWrite(38,1);
  EEPROM_readAnything(0,DuLieu);
  pinMode(29,INPUT);
  Serial.begin(9600);
  pinMode(42, OUTPUT);
  pinMode(31, INPUT);
  pinMode(47, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(45, OUTPUT); 
  pinMode(PT1,OUTPUT);
  pinMode(PT2,OUTPUT);
  pinMode(CT1,INPUT);
  pinMode(CT2,INPUT);
  pinMode(quang_hai,OUTPUT);
  pinMode(18,INPUT_PULLUP);
  

 chon_chienthuat();
  //clear_flag();
// calibrate();
////  
//in();
//  
}



void loop()

 {
   
//test(47,43);
 kCalendar::getInstance()->update();

}
