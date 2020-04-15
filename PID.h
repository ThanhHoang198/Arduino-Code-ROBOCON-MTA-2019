
#ifndef PID_h
#define PID_h
#include "Arduino.h"
#define doc  (1)
#define ngang  (0)
extern int direct,ham,gap;
extern int flag;
extern int linecheck,dao;
extern float integral_1,integral_2;
struct output;
int PIDController(float Kp, float Td,float error);
struct output V_calculate(int base,int maxspeed,int chieu);
void forward_gap();
void cheo_mu();
void ham_nguoc();
void ghi_bong();
void tien_bong();

void ham_cheo();
void ham_tien();
void ham_lui();
void ham_trai();
void ham_phai();

void di_mu();
void xoay();
void lui_sut();
void lui_sut1();
void ghi_cot();
void lui_cham();
void xoay_goc();
void di_cheo();
void dao_goc(); 
void forward_cham();
void turn_leftcham();
void turn_rightcham();
 void forward();
 void stopp();
 void backward();
 void turn_left();
 void turn_right();
 void in();
#endif
