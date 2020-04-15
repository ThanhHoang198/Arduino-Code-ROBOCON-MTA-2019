#include <Arduino.h>
#include "PID.h"
#include "DCmotor.h"
#include "line.h"
#include "math.h"
#include "EEPROMAnything.h"
#include "data.h"


DCmotor m2(M2,6,7,5);                    //khai báo 4 động cơ hướng đối tượng (DCmotor.cpp)
DCmotor m1(M1,9,8,10);   //DC1
DCmotor m4(M4,48,36,4);
DCmotor m3(M3,38,40,3);   //DC2


int sensorPins_1[8]={0,1,2,3,4,5,6,7};               //mảng add vào dữ liệu line
int sensorPins_2[8]={8,9,10,11,12,13,14,15};


int  sensorValues[8];            //mảng tạm thời dùng chung, khi mõi line đọc sẽ ghi đè 
int normalizedValues[8];

 
struct DL DuLieu;             //struct Dữ Liệu (data.h) chứa các dải được đo và lưu vào ROM ***(calibrate.h)       + EEPROM.h(K CẦN CARE)

line line1(DuLieu.whiteline_1,DuLieu.blackline_1, sensorPins_1, sensorValues,normalizedValues);    //Khai báo hướng đối tượng 4 line
line line2(DuLieu.whiteline_2,DuLieu.blackline_2, sensorPins_2,sensorValues,normalizedValues);
line line3(DuLieu.whiteline_3,DuLieu.blackline_3, sensorPins_1, sensorValues,normalizedValues);
line line4(DuLieu.whiteline_4,DuLieu.blackline_4, sensorPins_2,sensorValues,normalizedValues);


void in(){                                    //in dải giá trị của mỗi line
            line1.sendvalue();
            line2.sendvalue();
            line3.sendvalue();
            line4.sendvalue();
         }


struct output                              //struct chứa vận tốc, dùng chung, được ghi đè sau mỗi lần tính
        {
            int left_F;
            int right_F;
            int left_B;
            int right_B;
        }out;


                                                                      //Các Tham số tính toán PID

        float lastError1,lastError2,integral_1,integral_2;
        unsigned long lastTime1,lastTime2;
        float Kd;
 
    int PIDController(float Kp,float Td,float error)
                      {           
                                  float derivative,integral ;

                                  float Ki=0.001;
                                 
                                 if(Td!=0)                                   //dung cho error 1
                                         { unsigned long now = millis();
                                           float timeChange = (float)(now - lastTime1); 
                                           derivative = (error - lastError1) / (timeChange/1000);   
//                                                                                      
                                           integral =  integral_1+(Ki * error * (timeChange/1000));
                                           integral_1=integral;
                                           
                                           lastError1= error; 
                                           lastTime1 = now;
                                           
                                         }
                                 
                                 else
                                         {                                          //dung cho error 2
                                          unsigned long now = millis();
                                          float timeChange = (float)(now - lastTime2); 
                                          derivative = (error - lastError2) / (timeChange/1000);
                                                                                     
                                          integral= integral_2 + (Ki * error * (timeChange/1000));
                                          integral_2  =integral;
                                                                   
                                           lastError2= error; 
                                           lastTime2 = now;     
                                         }
            
                                  integral  = constrain(integral, -10,10);        
                                                    
                              
                                 
                                  float y = Kp * error + Kd * derivative+integral; 
                               
                                  int output  =  constrain(y,-255,255);
                                   
                                
                                  return output;
                      }




//-------------------------------------------------------Hàm quét led------------------------------------------------------------------------------------------//

int linecheck;    //cờ báo vào quét led, =1 thì đang quét, =0 thì k0 quét

void quetled_doc()     
                {
                       linecheck=1;
                       digitalWrite(45,LOW); 
                       digitalWrite(49,LOW);
                       digitalWrite(43,HIGH);    
                       digitalWrite(47,HIGH);  
                                     
                      line1.readSensors();            
                      line1.normalizeSensors();          //có thể xử lí quét trong này           
                      line1.Error_calculating();  
                      
                      line2.readSensors();            
                      line2.normalizeSensors();          //có thể xử lí quét trong này           
                      line2.Error_calculating();  
              }



void quetled_ngang()
              {                        
                      linecheck=1;    
                      digitalWrite(43,LOW); 
                      digitalWrite(47,LOW);
                      digitalWrite(45,HIGH);    
                      digitalWrite(49,HIGH); 
                      
                         
                      line3.readSensors(); 
                      line3.normalizeSensors();                              
                      line3.Error_calculating();   

                      line4.readSensors();            
                      line4.normalizeSensors();          //có thể xử lí quét trong này           
                      line4.Error_calculating();                                                                
                }


//-----------------------------------------Hàm tính toán vận tốc-----------------------------------------------------------------------------------------------//

            unsigned long previousMilis= 0;     
            int output1,output2,direct;   
            float error1,error2;
            int flag=0;

struct output V_calculate(int base,int maxspeed,int chieu)
{  
    unsigned long currentMilis = millis();
    
     if(flag==0)
    { 
           if (currentMilis - previousMilis >=20 )          //thời gian gọi lại hàm pid
            {        
                 previousMilis=currentMilis;        

                 if(chieu==doc)                                //trường hợp tiến lùi
                    {  
                        linecheck=0;
                        digitalWrite(45,LOW);                 //bật tắt line tương ứng
                        digitalWrite(49,LOW);
                        digitalWrite(43,HIGH);    
                        digitalWrite(47,HIGH); 
                                           
                        line1.readSensors();                   //đọc và xử lý số liệu line        (2 bánh trước)
                        line1.normalizeSensors();
                                             
                       error1=line1.Error_calculating();        //tính toán sai lêch 
                       output1=PIDController(7,1,error1);     //tính toán đầu ra qua PID
  
                       line2.readSensors();                                              //(2 bánh sau)
                       line2.normalizeSensors();
                       
                       error2=line2.Error_calculating();
                       output2=PIDController(7,0,error2); 
                    }

               if(chieu==ngang)                                //trường hợp rẽ trái phải
  
                    {   
                        linecheck=0;
                        digitalWrite(43,LOW); 
                        digitalWrite(47,LOW);
                        digitalWrite(45,HIGH);    
                        digitalWrite(49,HIGH); 
  
                        line3.readSensors();              
                        line3.normalizeSensors();                              
                 
                        error1=line3.Error_calculating();                        
                        output1=PIDController(8,1,error1);
                
                        line4.readSensors(); 
                        line4.normalizeSensors();   
                        
                        error2=line4.Error_calculating();   
                        output2 =PIDController(8,0,error2);
                    } 

//                    Serial.print(error1);
//                  Serial.print(" ");
//                  Serial.println(error2);
                   

          //Tính toán vận tốc

                      int left_F = base-output1;                    //vận tốc 2 bánh trước 
                      int right_F = base+output1;
                      
                     out.left_F=constrain( left_F,20,maxspeed);
                     out.right_F=constrain(right_F,20,maxspeed);              
                                  
                     int left_B = base-output2;                      //vận tốc 2 bánh sau
                     int right_B = base+output2;
                    
                     out.left_B=constrain(left_B,20,maxspeed);       //hàm giới hạn tốc độ
                     out.right_B=constrain(right_B,20,maxspeed); 
                    
                   
                }

    }
                  
       else
               {
                 if(chieu==doc)
                  quetled_ngang();         //quét led tìm điểm dừng ở ngã tư tại đây

                 if(chieu==ngang)
                  quetled_doc();         //quét led tìm điểm dừng ở ngã tư tại đây
             
//               
                 out.left_B=40;            //lúc này đồng thời giảm tốc độ
                 out.right_B=40;
                 out.left_F=40;
                 out.right_F=40;            
                                        
               }
                                                    
                      return out;          //trả về vận tốc để bơm vào động cơ    
                         
}




//-----------------------------------------------------------------------------Các Hàm Di Chuyển----------------------------------------------------------------------------//


    void stopp()
                  {
                      m1.setBrake();
                      m2.setBrake();
                      m3.setBrake();
                      m4.setBrake(); 
                  }

      void forward_cham()          
                  { ham=1; 
                    Kd=4;       
                    direct=1;

                    V_calculate(100,120,1);
                        
                   m2.Updatespeed(out.left_F,0);        //2 bánh trước
                   m3.Updatespeed(out.right_F,1);         
                   m1.Updatespeed(out.left_B,0);           
                   m4.Updatespeed(out.right_B,1);   
                  }
                 
                  
      
          
       void di_mu()
       {   
         if(san==green)
           {
          m1.Updatespeed(100,0); 
          m2.Updatespeed(100,1);               
         
          m4.Updatespeed(100,0);   //line       
          m3.Updatespeed(100,1);   //line 4

           }
        else
          {
          m1.Updatespeed(100,1); 
          m2.Updatespeed(100,0);               
         
          m4.Updatespeed(100,1);   //line       
          m3.Updatespeed(100,0);   //line 4  

          }
           
          dem=0;
       }

               

      void turn_left()
                    { ham=-2;
                      Kd=7; 
                      direct=-2;
                      if(dem==0)
                      {
                      V_calculate(130,200,0);
                     
                      m1.Updatespeed(out.left_F,0);         
                      m4.Updatespeed(out.left_B,0);   //line 4
                     
                      m2.Updatespeed(out.right_F,1);
                      m3.Updatespeed(out.right_B,1);   //line 4       
                      }
                       if(dem==1)
                      {
                      V_calculate(100,200,0);
                     
                      m1.Updatespeed(out.left_F,0);         
                      m4.Updatespeed(out.left_B,0);   //line 4
                     
                      m2.Updatespeed(out.right_F,1);
                      m3.Updatespeed(out.right_B,1);   //line 4       
                      }
                       if(dem==2)
                      {
                      V_calculate(70,200,0);
                     
                      m1.Updatespeed(out.left_F,0);         
                      m4.Updatespeed(out.left_B,0);   //line 4
                     
                      m2.Updatespeed(out.right_F,1);
                      m3.Updatespeed(out.right_B,1);   //line 4       
                      }
                       if(dem>=3)
                      {
                      V_calculate(40,200,0);
                     
                      m1.Updatespeed(out.left_F,0);         
                      m4.Updatespeed(out.left_B,0);   //line 4
                     
                      m2.Updatespeed(out.right_F,1);
                      m3.Updatespeed(out.right_B,1);   //line 4       
                      }
                      
                                  
                    }

                    int gap;
    void turn_leftcham()
                    { ham=-2;
                      Kd=7; 
                      direct=-2;
                     
                      if(dem<=1)
                      { if(gap==0)
                          {
                          V_calculate(120,200,0);
                         
                          m1.Updatespeed(out.left_F,0);         
                          m4.Updatespeed(out.left_B,0);   //line 4
                         
                          m2.Updatespeed(out.right_F,1);
                          m3.Updatespeed(out.right_B,1);   //line 4  
                          }  

                         else
                         {
                          if(dem==0)
                            {  V_calculate(100,200,0);
                             
                              m1.Updatespeed(out.left_F,0);         
                              m4.Updatespeed(out.left_B,0);   //line 4
                             
                              m2.Updatespeed(out.right_F,1);
                              m3.Updatespeed(out.right_B,1);   //line 4 
                            }
                            if(dem==1)
                             {
                             V_calculate(70,200,0);
                     
                              m1.Updatespeed(out.left_F,0);         
                              m4.Updatespeed(out.left_B,0);   //line 4
                             
                              m2.Updatespeed(out.right_F,1);
                              m3.Updatespeed(out.right_B,1);   //line 4
                             }
                                                   
                         }
                    }
                    else
                    {
                         V_calculate(70,200,0);
                     
                      m1.Updatespeed(out.left_F,0);         
                      m4.Updatespeed(out.left_B,0);   //line 4
                     
                      m2.Updatespeed(out.right_F,1);
                      m3.Updatespeed(out.right_B,1);   //line 4    
                    }
                    
                    }
                     
      
      void turn_right()
                   {   Kd=7; 
                       direct=2;
                       ham=2;
                    if(dem==0)
                       {
                       V_calculate(130,200,0);
                       
                       m1.Updatespeed(out.right_F,1); 
                       m4.Updatespeed(out.right_B,1);  //line 4
                       
                       m3.Updatespeed(out.left_B,0);     //line 4
                       m2.Updatespeed(out.left_F,0);
                       }
                       if(dem==1)
                       {
                      
                        V_calculate(100,200,0);
                       
                       m1.Updatespeed(out.right_F,1); 
                       m4.Updatespeed(out.right_B,1);  //line 4
                       
                       m3.Updatespeed(out.left_B,0);     //line 4
                       m2.Updatespeed(out.left_F,0);

                       
                      
                       }
                       if(dem==2)
                       {
                        V_calculate(70,200,0);
                       
                       m1.Updatespeed(out.right_F,1); 
                       m4.Updatespeed(out.right_B,1);  //line 4
                       
                       m3.Updatespeed(out.left_B,0);     //line 4
                       m2.Updatespeed(out.left_F,0);
                       
                       }
                                if(dem>=3)
                       {
                        V_calculate(40,200,0);
                       
                       m1.Updatespeed(out.right_F,1); 
                       m4.Updatespeed(out.right_B,1);  //line 4
                       
                       m3.Updatespeed(out.left_B,0);     //line 4
                       m2.Updatespeed(out.left_F,0);
                       
                       }
                                 
                    } 
      void turn_rightcham()
                   {    Kd=7; 
                        ham=2;
                       direct=2;
                       
                       if(dem<=1)
                       {
                        if(gap==0)
                        {
                           V_calculate(120,200,0);
                           
                           m1.Updatespeed(out.right_F,1); 
                           m4.Updatespeed(out.right_B,1);  //line 4
                           
                           m3.Updatespeed(out.left_B,0);     //line 4
                           m2.Updatespeed(out.left_F,0);
                        }
                        else
                        {

                          {
                             V_calculate(80,200,0);
                           
                           m1.Updatespeed(out.right_F,1); 
                           m4.Updatespeed(out.right_B,1);  //line 4
                           
                           m3.Updatespeed(out.left_B,0);     //line 4
                           m2.Updatespeed(out.left_F,0);
                          }
                          
                          
                        }
                       
                       
                       }
                       else
                       {
                         V_calculate(70,200,0);
                       
                       m1.Updatespeed(out.right_F,1); 
                       m4.Updatespeed(out.right_B,1);  //line 4
                       
                       m3.Updatespeed(out.left_B,0);     //line 4
                       m2.Updatespeed(out.left_F,0);
                           
                        
                       }
                               
                    } 

              

    void tien_bong()
                  {  
                    Kd=7; 
                   
                   direct=1;
                   if(dem==0)
                 { 
                   V_calculate(90,200,1);
                        
                  m2.Updatespeed(out.left_F,0);   //line 1
                  m1.Updatespeed(out.left_B,0);
                  
                  m3.Updatespeed(out.right_F,1);      //line 1
                  m4.Updatespeed(out.right_B,1); 
                 }
            
                 else
                 {

                  V_calculate(35,200,1);
                        
                  m2.Updatespeed(out.left_F,0);   //line 1
                  m1.Updatespeed(out.left_B,0);
                  
                  m3.Updatespeed(out.right_F,1);      //line 1
                  m4.Updatespeed(out.right_B,1); 
               
                 }
                                  
                }
    
    void ghi_bong()
                  {                                     
                  m2.Updatespeed(70,0);   //line 1
                  m1.Updatespeed(70,0);
                  
                  m3.Updatespeed(70,1);      //line 1
                  m4.Updatespeed(70,1);               
                  }
   
    void lui_cham()               //lùi sau khi thả bóng
                  { direct=-1;       
                    m2.Updatespeed(80,1);  //line 1
                    m3.Updatespeed(80,0);   
              
                    m1.Updatespeed(80,1); 
                    m4.Updatespeed(80,0); 
                    
                    quetled_ngang();       
                   }   
        
     void forward()
                 {  Kd=2;       
                   direct=1;
                   V_calculate(80,130,1);
                        
                   m2.Updatespeed(out.left_F,0);        //2 bánh trước
                   m3.Updatespeed(out.right_F,1);         
                   m1.Updatespeed(out.left_B,0);           
                   m4.Updatespeed(out.right_B,1);   
                  }
       void forward_gap()
       {            Kd=2;       
                   direct=1;
                   if(dem<2)
                   {
                   V_calculate(70,110,1);
                        
                   m2.Updatespeed(out.left_F,0);        //2 bánh trước
                   m3.Updatespeed(out.right_F,1);         
                   m1.Updatespeed(out.left_B,0);           
                   m4.Updatespeed(out.right_B,1);  
                   }
                   else 
                    {
                       V_calculate(60,50,1);
                        
                   m2.Updatespeed(out.left_F,0);        //2 bánh trước
                   m3.Updatespeed(out.right_F,1);         
                   m1.Updatespeed(out.left_B,0);           
                   m4.Updatespeed(out.right_B,1);  
                    }
                    
       }
       void lui_sut1()                    //chạy đến cột
                    { next_time=1200;
                      Kd=7; 
                     direct=-1;
                     V_calculate(70,200,1);
              
                     back_flag=1;
                     m2.Updatespeed(out.right_F,1);  //line 1
                     m3.Updatespeed(out.left_F,0);   
              
                     m1.Updatespeed(out.right_B,1); 
                     m4.Updatespeed(out.left_B,0); 
                    }

       void lui_sut()                    //chạy đến cột
                    { next_time=200;
                     Kd=7; 
                     direct=-1;
                     V_calculate(80,200,1);
              
                     back_flag=1;
                     
                     m2.Updatespeed(out.right_F,1);  //line 1
                     m3.Updatespeed(out.left_F,0);   

                     m1.Updatespeed(out.right_B,1); 
                     m4.Updatespeed(out.left_B,0); 
                    }

     
       void ghi_cot()
                     { 
                      m2.Updatespeed(70,1);   //line 1
                      m1.Updatespeed(70,1);
                      
                      m3.Updatespeed(70,0);      //line 1
                      m4.Updatespeed(70,0);      
                     
//                     Kd=7;  
//                     direct=-1;
//                     V_calculate(70,120,1);
//                                 
//                     m2.Updatespeed(out.right_F,1);  //line 1
//                     m3.Updatespeed(out.left_F,0);   
//              
//                     m1.Updatespeed(out.right_B,1); 
//                     m4.Updatespeed(out.left_B,0); 
//                                           
                       }
      void backward()
                  { Kd=2; 
                    direct=-1;
                   V_calculate(80,150,1);
                      
                  m2.Updatespeed(out.right_F,1);  //line 1
                  m3.Updatespeed(out.left_F,0);   
            
                  m1.Updatespeed(out.right_B,1); 
                  m4.Updatespeed(out.left_B,0); 
                  }    





   unsigned long time_xoay,time_cheo;
   int co_xoay,dao;
   extern int co_cheo;
 
   
   void xoay()
             {   if(san==green)
                {  
                 m1.Updatespeed(70,0); 
                 m4.Updatespeed(70,0);  //line 4
                 
                 m3.Updatespeed(70,0);     //line 4
                 m2.Updatespeed(70,0);
                }
                else
                { m1.Updatespeed(70,1); 
                 m4.Updatespeed(70,1);  //line 4
                 
                 m3.Updatespeed(70,1);     //line 4
                 m2.Updatespeed(70,1);
                }
                
          
                 if(co_xoay==0)
                            {
                            time_xoay=millis();
                            co_xoay=1;
                            }
                
                 if(millis()-time_xoay>=800)
                            quetled_doc();
             }


   void di_cheo()
             {   
              if(san==green)
                {          
                  m2.Updatespeed(110,0); 
                  m4.Updatespeed(110,1); 
                       
                  m3.setBrake();
                  m1.setBrake();
                }
                else
                 { m3.Updatespeed(110,1); 
                   m1.Updatespeed(110,0); 
                   m2.setBrake();
                   m4.setBrake();
                 }
            
                 dicheo=1;
                 if(co_cheo==0)
                          {
                             time_cheo=millis();
                             co_cheo=1;
                          }
                                           
                 if(millis()-time_cheo>=700)
                            quetled_doc();
                     
               }


    void xoay_goc()
            {     
                 m1.Updatespeed(80,1); 
                 m4.Updatespeed(80,0); 
              
               if(san==green)
                {
                m2.Updatespeed(80,0);  //line 1
                m3.Updatespeed(80,0);                               
                }
                
                else
                {                                     
                  m2.Updatespeed(80,1); 
                  m3.Updatespeed(80,1); 
                }
          
            }
          
   void dao_goc()
            {    m1.Updatespeed(80,1); 
                 m4.Updatespeed(80,0); 
              
               if(san==green)
                {
                m2.Updatespeed(80,1);  //line 1
                m3.Updatespeed(80,1);                               
                }
                
                else
                {                                     
                  m2.Updatespeed(80,0); 
                  m3.Updatespeed(80,0); 
                }
                            
                  dao=1;
                  quetled_doc();
            
            }


unsigned long xung;
int check_xung;
float quang_duong;

void dem_xung()
{
    xung++;
   quang_duong = (xung)*42.7/200;
    
    if(quang_duong>=200) //1639
     {  check_xung=1; 
        detachInterrupt(5);     
     }
 
}

int ham;
int enable;
   void cheo_mu()
        {       ham=3;
           if(enable==0)
           {
            attachInterrupt(5,dem_xung,FALLING);
            enable=1;
           }
        
           if(san==red)
                    {     
                        m2.Updatespeed(180,0); 
                        m4.Updatespeed(180,1); 
                             
                        m3.setBrake();
                        m1.setBrake();
                      }
                      else
                       {
                         m3.Updatespeed(180,1); 
                         m1.Updatespeed(180,0); 
                         m2.setBrake();
                         m4.setBrake();
                       }
             
          if(check_xung)
                   {
                    tha2=1;      
                    quetled_ngang();
                   }
                   
                    
        }
int v=200;

        void ham_tien()
        {         m2.Updatespeed(v,1);  //line 1
                  m3.Updatespeed(v,0);   
            
                  m1.Updatespeed(v,1); 
                  m4.Updatespeed(v,0); 

          
        }
        void ham_lui()
        {

                  m2.Updatespeed(v,0);        //2 bánh trước
                   m3.Updatespeed(v,1);         
                   m1.Updatespeed(v,0);           
                   m4.Updatespeed(v,1); 
        }

        void ham_trai()
        {
                       m1.Updatespeed(v,1); 
                       m4.Updatespeed(v,1);  //line 4
                       
                       m3.Updatespeed(v,0);     //line 4
                       m2.Updatespeed(v,0);
        }

        void ham_phai()
        {
                      m1.Updatespeed(v,0);         
                      m4.Updatespeed(v,0);   //line 4
                     
                      m2.Updatespeed(v,1);
                      m3.Updatespeed(v,1);   //line 4       

          
        }
        void ham_cheo()
        {
                     //  digitalWrite(42,1);
                 if(san==red)
                 {
                       m2.Updatespeed(v,1); 
                        m4.Updatespeed(v,0); 
                             
                        m3.setBrake();
                        m1.setBrake();
                 }
                 else
                 {     
                         m3.Updatespeed(180,0); 
                         m1.Updatespeed(180,1); 
                         m2.setBrake();
                         m4.setBrake();

                  
                 }

          
        }
 void ham_nguoc()
 {
       if(ham==1)
       ham_tien();
       if(ham==-1)
       ham_lui();
       if(ham==-2)
       ham_trai();
       if(ham==2)
       ham_phai();
       if(ham==3)
       ham_cheo();
       delay(150);
       stopp();
       delay(100);
       
 }
