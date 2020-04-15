#ifndef LCD_MODE_H
#define LCD_MODE_H

#include "kCalendar.h"
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,20,4);
//-------------------------------------------setup LCD-----------------------------------------------------------------------------------------//
int MOV = 34;
int DOWN = 28;
int START = 32 ;
int count=1;
int a,co=1;
char arrow[8] = {0x00, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00};

//-------------------------------------------------------setup PITONG SERVO-------------------------------------------------------------------------------//
#include <Servo.h>     
Servo myservo1;  
Servo myservo2;         

int servoPin1 = 12;   
int servoPin2 = 13;  
int PT1 = 22 ;// len xuong
int PT2 = 25 ; // ra vao     
int SPK =42;
int CT1 = 37;
int CT2 =39;
int quang_hai=23;

int tha_xong;


      void setup_bong()
            {
            //----------------SETUP-SERVO-------------------
                   myservo1.attach(servoPin1) ; 
                   myservo1.write(0);
                   delay(1000);
                  digitalWrite(12,0);
                  myservo1.detach() ;
                    
                  myservo2.attach(servoPin2) ;
                  myservo2.write(150); 
                  delay(1000);
                  digitalWrite(13,0);
                
                   
                
             
            //---------------SETUP-PITTONG--------------------
                digitalWrite(PT1,HIGH);
                digitalWrite(PT2,HIGH); 
                digitalWrite(quang_hai,HIGH); 
            }


//---------------------------------------------------------------------------------PHẦN CHỤP BÓNG--------------------------------------------------------------------------------------//


        int chup;
        
        void mo_ong()
                {
                   myservo2.attach(servoPin2) ;  
                   myservo2.write(40);
                    delay(500);
                
                    digitalWrite(13,0);
  
                 
                   chup=1;
          
                 }
        void ha_ong()
                  {
                   digitalWrite(PT1,LOW); 
                   chup=1;           
                  }
        
        void  nang_ong()
                  {
                   digitalWrite(PT1,HIGH); 
                   chup=1; 
                  }


//------------------------------------------------------------------------------------PHẦN THẢ BÓNG-----------------------------------------------------------------------------------------------

        void khoa_ong()
              {    delay(1000);
                   myservo2.attach(servoPin2) ;                    
                   myservo2.write(150);
                   delay(1000);
                   
                   chup=1;
                   digitalWrite(13,0);
                   
          
               }
        
        void nang()
                { digitalWrite(PT2,LOW);
                    tha_xong=1;  
                }
        
        
        void tha_rieng()
                { myservo2.attach(servoPin2) ;    
                  myservo2.write(0);
                      delay(300);
                      
                      digitalWrite(13,0);
                   
                      tha_xong=1;
                 
                }

                
        void tha_2bong()
        {     
                myservo1.attach(servoPin1) ;                    
                myservo1.write(180);
              
                myservo2.write(0);
                 delay(300);
          
                digitalWrite(12,0);
                myservo1.detach() ;  
                digitalWrite(13,0);
               
                tha_xong=1;
               
        }
        
        void thu_ong()
                {
                 digitalWrite(PT2,HIGH); 
                 tha_xong=1;
                  
                }

        

 //--------------------------------------------------------------------------PHẦN SÚT BÓNG-----------------------------------------------------------------------------------------------------//
 
        extern int da_sut;
        int da_sut;
        
        void sut()
                {
                 
                 digitalWrite(quang_hai,LOW); 
                 da_sut=1;
                  
                }
        
        void thu()
                {
                 
                 digitalWrite(quang_hai,HIGH); 
                 da_sut=1;
                  
                }
        
        bool check_sut()
                {
                if(da_sut==1)
                {  da_sut=0;
                  return true;
                }
                return false;
                         
                }
        

//--------------------------------------------------------------------------Setup_san--------------------------------------------------------------------//



int mode;

      bool CT_1()
                      { if(digitalRead(CT1)==0) 
                      {
                       
                        return true;
                      }
                                  
                         return false;                       
                      }
          
      bool CT_2()
                      { if(digitalRead(CT2)==0)
                        {digitalWrite(42,HIGH);
                        delay(20);
                      digitalWrite(42,0);   
                       return true; }
                                   
                          return false;                     
                      }

          
      bool check_cot()
                       { if(stop_flag==0) return false;
                              else{
                              digitalWrite(42,HIGH);
                                                                       delay(20);
                                                                       digitalWrite(42,0);
                            return true;  }
                       }

      bool check_lui()
                        {  if(dung==0) return false;
                           else{
                              dung=0;
                            return true;
                           }
                        }

       bool check_tam()
                        {  if(dung_tam==0) return false;

                            else{
                              dung_tam=0;
                              return true;
                            }
                        }
                        
      bool check_cheo()
                        {  if(dung_cheo1==0) return false;
                           else{
                            
                             dung_cheo1=0;
                            return true;
                           }
                        }


      unsigned long moc_thoigian;
      int batdau;
        
     bool check_time()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=1000)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }
     
     bool check_timengan()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=700)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }
    bool check_timengan3()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=300)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }
          bool check_timengan4()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=400)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }
      bool check_timengan2()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=200)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }

     bool check_time1()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=500)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }

     bool check_time2()
                         {
                              if(batdau==0)
                                { moc_thoigian=millis();
                                  batdau=1; 
                                }
                            if(millis()-moc_thoigian>=800)
                                {  batdau=0;
                                  return true;
                                
                                }
                                return false;
                          
                         }
      bool check_tha()
                          { if(tha_xong==1)
                                {  
                                
                                  tha_xong=0;
                                  return true;
                                }
                            return false;
                          
                          }
      bool check_chup()
                            {
                               if(chup==1)
                               {     chup=0;
                                return true;
                           
                               }
                             return false;
                              
                            }


      bool checkcheo_mu()
      {
            if(demcheo==0)
            return false;
            return true;

        
      }



     int chon_san()
                      {
                         if(digitalRead(35)==1)    //chọn màu sân
                              {     san=green;
                                    lcd.setCursor(0,0);
                                    lcd.print("San Xanh Duoc Chon"); 
                              }
                              
                         else
                              {
                                     san=red;  
                                     lcd.setCursor(0,0);
                                     lcd.print("San Do Duoc Chon"); 
                              }      
                          return san;
                      }

   
     void addJob_left(int sec)
                      {
                             if(san==green)
                              kCalendar::getInstance()->addJob(turn_left,sec);
                            
                             if(san==red)
                               kCalendar::getInstance()->addJob(turn_right,sec); 
                      }
        
     void addJob_leftcham(int sec)
                      {
                             if(san==green)
                              kCalendar::getInstance()->addJob(turn_leftcham,sec);
                            
                             if(san==red)
                               kCalendar::getInstance()->addJob(turn_rightcham,sec); 
                      }
                      

    //------------------------------SÚT QUẢ 1------------------------------------------------------------------------//
                  
     void sut_qua1()
                      {                
  
                  kCalendar::getInstance()->addJob(lui_sut1,check_cot);
                  kCalendar::getInstance()->addJob(stopp,check_timengan4);  
                  //gap cột dừng            
                  kCalendar::getInstance()->addJob(ghi_cot,CT_2); 
                  kCalendar::getInstance()->addJob(sut,check_sut);                  
                  kCalendar::getInstance()->addJob(stopp,check_timengan3);               //sút xong dừng   
                  kCalendar::getInstance()->addJob(thu,check_sut);
                  
                      }
      
      //---------------------------------------SÚT QUẢ 2-----------------------------------------------------------------//
                 
     void sut_qua2()
                 {
                 kCalendar::getInstance()->addJob(forward,check_timengan);                //tiến 1 đoạn dừng
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                 
                 kCalendar::getInstance()->addJob(di_cheo,check_cheo);                    //đi chéo xong dừng
                  kCalendar::getInstance()->addJob(stopp,check_timengan3);
                  
                 kCalendar::getInstance()->addJob(lui_sut,check_cot);                     //gap cột dừng
                 kCalendar::getInstance()->addJob(stopp,check_timengan4);
                 
                 kCalendar::getInstance()->addJob(ghi_cot,CT_2);
                 
                 kCalendar::getInstance()->addJob(xoay_goc,check_time1);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);                    //xoay xong dừng
                 kCalendar::getInstance()->addJob(sut,check_sut); 
                                                     
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);                     
                 kCalendar::getInstance()->addJob(thu,check_sut);
                 kCalendar::getInstance()->addJob(dao_goc,check_tam);                         //đảo góc xong dừng
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                 }

       //-------------------------------------------SÚT QUẢ 3-------------------------------------------------------------//
      void sut_qua3()
                {                      
                 kCalendar::getInstance()->addJob(forward,check_timengan4);
               
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                  
                 kCalendar::getInstance()->addJob(di_cheo,check_cheo);
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);
                 
                 kCalendar::getInstance()->addJob(lui_sut,check_cot);
                 kCalendar::getInstance()->addJob(stopp,check_timengan4);    
                              
                 kCalendar::getInstance()->addJob(ghi_cot,CT_2); 
                               
                 kCalendar::getInstance()->addJob(xoay_goc,check_time2);  
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                                      
                 kCalendar::getInstance()->addJob(sut,check_sut);                      
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);    
                                  
                 kCalendar::getInstance()->addJob(thu,check_sut);  
                                
                 kCalendar::getInstance()->addJob(dao_goc,check_tam);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                                      
                 kCalendar::getInstance()->addJob(forward,6);          
                }


      void gap_bong()
                {
                  kCalendar::getInstance()->addJob(mo_ong,check_chup);                  
                  kCalendar::getInstance()->addJob(forward_gap,CT_1);  
                  kCalendar::getInstance()->addJob(stopp,check_timengan2);
                  
                  kCalendar::getInstance()->addJob(ha_ong,check_chup);
                  kCalendar::getInstance()->addJob(khoa_ong,check_chup); 
                  kCalendar::getInstance()->addJob(nang_ong,check_chup);
                 
                  kCalendar::getInstance()->addJob(backward,1);                 
                }
                      
       void tha2bong()
       {   
           kCalendar::getInstance()->addJob(nang,check_tha); 
           kCalendar::getInstance()->addJob(tien_bong,CT_1); 
           kCalendar::getInstance()->addJob(stopp,check_timengan2);    
           kCalendar::getInstance()->addJob(ghi_bong,CT_1);
           kCalendar::getInstance()->addJob(stopp,check_timengan2);                  
           kCalendar::getInstance()->addJob(tha_2bong,check_tha);
           kCalendar::getInstance()->addJob(stopp,check_timengan2);
           kCalendar::getInstance()->addJob(lui_cham,check_lui);
           kCalendar::getInstance()->addJob(stopp,check_timengan2);                 
           kCalendar::getInstance()->addJob(thu_ong,check_tha);  
                                           
        }
//-----------------------------------------------------------------------------------CÁC MODE THI ĐẤU------------------------------------------------------------------------------------------


void MODE_1()
            {     mode=1;
           
                  kCalendar::getInstance()->initialize();              
                  
            }
                  
  
  void MODE_2()

              {    mode=2;
          
                  kCalendar::getInstance()->initialize();
                  kCalendar::getInstance()->addJob(cheo_mu,check_lui);     
                  addJob_leftcham(3); 
                  tha2bong();
                  kCalendar::getInstance()->addJob(xoay,check_lui);
                  kCalendar::getInstance()->addJob(stopp,check_timengan2);
                  sut_qua1();
                  sut_qua2();
                  sut_qua3();            
                                             
              }
              
              
    void MODE_3()
              {  
                  mode=3;
                  kCalendar::getInstance()->initialize();
                  kCalendar::getInstance()->addJob(forward_cham,2);
                  addJob_left(4);
                  tha2bong();
                  kCalendar::getInstance()->addJob(xoay,check_lui);
                  kCalendar::getInstance()->addJob(stopp,check_timengan2);
                  sut_qua1();
                  sut_qua2();
                  sut_qua3();                  
                                  
                 }

  void  MODE_4()
             {    
                 mode=4;
                 kCalendar::getInstance()->initialize();
                 kCalendar::getInstance()->addJob(forward_cham,2);
                 
                 addJob_left(4);
                 
                 kCalendar::getInstance()->addJob(xoay,check_lui);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                 
                 kCalendar::getInstance()->addJob(lui_sut,check_cot);                     //gap cột dừng
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);
                 
                 kCalendar::getInstance()->addJob(ghi_cot,CT_2);
                 
                 kCalendar::getInstance()->addJob(xoay_goc,check_time1);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);                    //xoay xong dừng
                 kCalendar::getInstance()->addJob(sut,check_sut); 
                                                     
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);                     
                 kCalendar::getInstance()->addJob(thu,check_sut);
                 kCalendar::getInstance()->addJob(dao_goc,check_tam);                         //đảo góc xong dừng
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                 
                 sut_qua3();           
             }


   void MODE_5()
               {   mode=5;
                    kCalendar::getInstance()->initialize();                  

                  kCalendar::getInstance()->addJob(forward_cham,1);            
                  kCalendar::getInstance()->addJob(xoay,check_lui);
                  kCalendar::getInstance()->addJob(stopp,check_timengan2);
               
                 kCalendar::getInstance()->addJob(lui_sut,check_cot);
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);    
                              
                 kCalendar::getInstance()->addJob(ghi_cot,CT_2); 
                               
                 kCalendar::getInstance()->addJob(xoay_goc,check_time2);  
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                                      
                 kCalendar::getInstance()->addJob(sut,check_sut);                      
                 kCalendar::getInstance()->addJob(stopp,check_timengan3);    
                                  
                 kCalendar::getInstance()->addJob(thu,check_sut);  
                                
                 kCalendar::getInstance()->addJob(dao_goc,check_tam);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);
                                      
                 kCalendar::getInstance()->addJob(forward,6);      
               }
            
    void MODE_6()

              {    mode=6;
                   gap=1;
                  kCalendar::getInstance()->initialize();
                  
                  gap_bong();
                 
                  addJob_leftcham(2);     
                                                        
                 kCalendar::getInstance()->addJob(tien_bong,CT_1); 
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);    
                 kCalendar::getInstance()->addJob(ghi_bong,CT_1);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);                  
                 kCalendar::getInstance()->addJob(tha_rieng,check_tha);
                 kCalendar::getInstance()->addJob(lui_cham,check_lui);
                 kCalendar::getInstance()->addJob(stopp,check_timengan2);                                                                                                                         
                                            
                  addJob_leftcham(2);
                                          
   
                  kCalendar::getInstance()->addJob(xoay,check_lui);
                  kCalendar::getInstance()->addJob(stopp,check_timengan2);
                  sut_qua1();
                  sut_qua2();
                  sut_qua3();   
                                
              }




 
      int  Readbutton()
                      {
                          if(digitalRead(MOV)==0)
                            {
                              while(digitalRead(MOV)==0);
                                count--;        
                            }
                         
                          if(digitalRead(DOWN)==0)
                            {
                                while(digitalRead(DOWN)==0);
                                count++;  
                            }
                            return count;  
                      }


 
        void settingmode()
        {   
        
                while(co){
                    
                          Readbutton();
                          
                          if(count==7)
                          count=1;
                          if(count==0)
                          count=6; 
                         
                        if(count==1)
                        { 
                                      
                                                             
                                      
                                      lcd.setCursor(0,1);
                                       lcd.write(0);           
                                       lcd.setCursor(1,1);
                                       lcd.print("FULL");
                                      
                                       lcd.setCursor(0,2);
                                       lcd.print(" ");
                                       lcd.setCursor(1,2);
                                       lcd.print("GAP");

                                       lcd.setCursor(0,3);
                                       lcd.print(" ");  
                                       lcd.setCursor(1,3);
                                       lcd.print("B123");

                                       lcd.setCursor(6,1);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,1);
                                       lcd.print("B23");

                                       lcd.setCursor(6,2);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,2);
                                       lcd.print("B3");

                                       lcd.setCursor(6,3);
                                       lcd.print(" ");
                                       lcd.setCursor(7,3);
                                       lcd.print("Gap bong rieng");
        //            
                                      if(digitalRead(START)==0)
                                      {
                                        lcd.clear();
                                        while(digitalRead(START)==0);
                                        lcd.setCursor(0,2);
                                        lcd.print("CHIEN THUAT MAC DINH !!!");
                                         MODE_1();
                                        break;
                                      }
                        }
                         if(count==2)
                        { 
                                        lcd.setCursor(0,1);
                                       lcd.print(" ");             
                                       lcd.setCursor(1,1);
                                       lcd.print("FULL");
                                      
                                       lcd.setCursor(0,2);
                                       lcd.write(0);
                                       lcd.setCursor(1,2);
                                       lcd.print("GAP");

                                       lcd.setCursor(0,3);
                                       lcd.print(" ");  
                                       lcd.setCursor(1,3);
                                       lcd.print("B123");

                                       lcd.setCursor(6,1);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,1);
                                       lcd.print("B23");

                                       lcd.setCursor(6,2);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,2);
                                       lcd.print("B3");
        //                             
                                         lcd.setCursor(6,3);
                                       lcd.print(" ");
                                       lcd.setCursor(7,3);
                                       lcd.print("Gap bong rieng");
                                       
                                      if(digitalRead(START)==0)
                                       {
                                        lcd.clear();
                                        while(digitalRead(START)==0);
                                        lcd.setCursor(0,2);
                                        lcd.print("DANG GAP THA !!!");
                                         MODE_2();
                                        break;
                                       }
                        }
        
                         if(count==3)
                        { 
                                       lcd.setCursor(0,1);
                                       lcd.print(" ");         
                                       lcd.setCursor(1,1);
                                       lcd.print("FULL");
                                      
                                       lcd.setCursor(0,2);
                                       lcd.print(" ");
                                       lcd.setCursor(1,2);
                                       lcd.print("GAP");

                                       lcd.setCursor(0,3);
                                       lcd.write(0);    
                                       lcd.setCursor(1,3);
                                       lcd.print("B123");

                                       lcd.setCursor(6,1);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,1);
                                       lcd.print("B23");

                                       lcd.setCursor(6,2);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,2);
                                       lcd.print("B3");

                                        lcd.setCursor(6,3);
                                       lcd.print(" ");
                                       lcd.setCursor(7,3);
                                       lcd.print("Gap bong rieng");
                                       
                                      if(digitalRead(START)==0)
                                       {
                                        lcd.clear();
                                        while(digitalRead(START)==0);
                                        lcd.setCursor(0,2);
                                        lcd.print("DANG SUT 123 !!!");
                                        MODE_3();
                                        break;
                                       }
                        }

                        
                         if(count==4)
                        { 
                                       lcd.setCursor(0,1);
                                       lcd.print(" ");         
                                       lcd.setCursor(1,1);
                                       lcd.print("FULL");
                                      
                                       lcd.setCursor(0,2);
                                       lcd.print(" ");
                                       lcd.setCursor(1,2);
                                       lcd.print("GAP");

                                       lcd.setCursor(0,3);
                                        lcd.print(" ");
                                         
                                       lcd.setCursor(1,3);
                                       lcd.print("B123");

                                       lcd.setCursor(6,1);
                                       lcd.write(0); 
                                       lcd.setCursor(7,1);
                                       lcd.print("B23");

                                       lcd.setCursor(6,2);
                                       lcd.print(" "); 
                                       lcd.setCursor(7,2);
                                       lcd.print("B3");

                                        lcd.setCursor(6,3);
                                       lcd.print(" ");
                                       lcd.setCursor(7,3);
                                       lcd.print("Gap bong rieng");
                                       
                                      if(digitalRead(START)==0)
                                       {
                                        lcd.clear();
                                        while(digitalRead(START)==0);
                                        lcd.setCursor(0,2);
                                        lcd.print("DANG SUT QUA 23");
                                        MODE_4();
                                        break;
                                       }
                        }
                        
                        
                         if(count==5)
                        { 
                                       lcd.setCursor(0,1);
                                       lcd.print(" ");         
                                       lcd.setCursor(1,1);
                                       lcd.print("FULL");
                                      
                                       lcd.setCursor(0,2);
                                       lcd.print(" ");
                                       lcd.setCursor(1,2);
                                       lcd.print("GAP");

                                       lcd.setCursor(0,3);
                                        lcd.print(" ");
                                         
                                       lcd.setCursor(1,3);
                                       lcd.print("B123");

                                       lcd.setCursor(6,1);
                                       lcd.print(" ");
                                       lcd.setCursor(7,1);
                                       lcd.print("B23");

                                       lcd.setCursor(6,2);
                                        lcd.write(0); 
                                       lcd.setCursor(7,2);
                                       lcd.print("B3");

                                       
                                       lcd.setCursor(6,3);
                                       lcd.print(" ");
                                       lcd.setCursor(7,3);
                                       lcd.print("Gap bong rieng");
                                       
                                      if(digitalRead(START)==0)
                                       {
                                        lcd.clear();
                                        while(digitalRead(START)==0);
                                        lcd.setCursor(0,2);
                                        lcd.print("DANG SUT QUA 3 !!!");
                                        MODE_5();
                                        break;
                                       }
                        }
                           if(count==6)
                        { 
                                       lcd.setCursor(0,1);
                                       lcd.print(" ");         
                                       lcd.setCursor(1,1);
                                       lcd.print("FULL");
                                      
                                       lcd.setCursor(0,2);
                                       lcd.print(" ");
                                       lcd.setCursor(1,2);
                                       lcd.print("GAP");

                                       lcd.setCursor(0,3);
                                        lcd.print(" ");
                                         
                                       lcd.setCursor(1,3);
                                       lcd.print("B123");

                                       lcd.setCursor(6,1);
                                       lcd.print(" ");
                                       lcd.setCursor(7,1);
                                       lcd.print("B23");

                                       lcd.setCursor(6,2);
                                        lcd.print(" ");
                                       lcd.setCursor(7,2);
                                       lcd.print("B3");

                                        lcd.setCursor(6,3);
                                        lcd.write(0); 
                                       lcd.setCursor(7,3);
                                       lcd.print("Gap bong rieng");
                                      if(digitalRead(START)==0)
                                       {
                                        lcd.clear();
                                        while(digitalRead(START)==0);
                                        lcd.setCursor(0,2);
                                        lcd.print("DANG GAP BONG RIENG !!!");
                                        MODE_6();
                                        break;
                                       }
                        }
                                                                    
                }
            
        }
        

           



                  void chon_chienthuat()
                                          {    lcd.init(); 
                                               lcd.backlight(); 
                                               chon_san();
                                               lcd.createChar(0,arrow); 
                                               settingmode();                       
                                          }

#endif
