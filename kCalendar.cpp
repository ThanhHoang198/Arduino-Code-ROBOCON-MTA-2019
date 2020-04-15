#include<Arduino.h>
#include "kCalendar.h"
#include"line.h"
#include"PID.h"
#include "roep.h"

extern int mode;

bool kCalendar_true_condition()
      {
        return true;
      }

bool kCalendar_stop_condition()
      {
        return false;
      }

void kCalendar::initialize()
      {
        m_lastCheckedJobId = -1;
      }


//---------------------------------------------------------------------------------HÀM XỬ LÝ LỊCH LÀM VIỆC--------------------------------------------------------------------------//
    int co_cheo=0;
unsigned long time_dimu;
 int k,b,c;
void kCalendar::update() 
{
  
   k=m_lastCheckedJobId+1;
   
  if (m_lastCheckedJobId== m_count-1)               //kiểm tra job đã hết chưa
      {
         m_lastCheckedJobId = -1;
  
      }
      
  if(  k< m_count)
    {
       kJob job = m_jobs[k];

            
             if(mode==1||mode==3||mode==4||mode==5)
                 {  
                     if(k==1)         //đi mù đoạn đầu
                            {
                                if(c==0)
                                      { 
                                        time_dimu =millis();
                                        c=1;
                                      }                                
                                   while(millis()-time_dimu<=500)
                                   di_mu();
                                   
                             }
                 }

                  if(mode==20||mode==6)
                 {  
                     if(k==7)         //đi mù đoạn đầu
                            {
                                if(c==0)
                                      { 
                                        time_dimu =millis();
                                        c=1;
                                      }                                
                                   while(millis()-time_dimu<=500)
                                   di_mu();
                             }
                 }

       
       if(job.intersec_count!=0)
         {   
              
          if(k==0)
          { 
            dem=count1;                
          }
          if(mode==6)
          {
           if(k==1)
           dem=count1;
           
          if(k==6)
            {
              back=1;
            dem=count2;
            }
            
          }
       
                if(dem<job.intersec_count)
                       {
                         flag=0;  // cờ để job.func sang chế độ PID
                         job.func();
                       }
              
                else{  
                            count1=3;             
                          while(b==0)          //dừng lần 1
                                {
                                 stopp();    
                                 delay(300);  
                                 
                                  b=1;
                                 }
                          
                                                 
                            flag=1;  //bật cờ chuyển qua giảm tốc dò
                           job.func();
                                    
                    
                            if(dung==1)  //quét led phát hiện điểm dừng
                                  {                                     
                                    ham_nguoc();
                                      
                                    back=0;
                                    //dừng lần 2                                   
                                    dem=0;      //reset dếm
                                    b=0;
                                    dung=0;     //reset cờ dừng
                                    flag=0;
                                    integral_1=0;
                                    integral_2=0;
                                    m_lastCheckedJobId++;   //nhảy sang job khác                                
                                  }
                       }

           }
        
       else
           {           
                      while(job.conditionStop()==false)
                      {
                         
                          job.func();       
                      }
                       if(ham==3)
                                      {   
                                        
                                         ham_cheo();
                                        delay(600);
                                        stopp();
                                         delay(200);
                                        }
                       dem=0;
                      stop_flag=0; 
                      back_flag=0;  
                      dao=0;
                      
                      m_lastCheckedJobId++;   
                      co_cheo=0;
                      dicheo=0;
            }
  }
  
      
     
      
}

//--------------------------------------------------------------------hàm tạo mới job--------------------------------------------------------------------------------------------------------//

void kCalendar::addJob(void (*func)(),int intersec)                                            
                        { 
                         
                          kJob job = {func,kCalendar_stop_condition,intersec};                     //nếu k có conditionstop thì mặc định condition ==false, chạy k dừng
                        
                          insertJob(job);                                                                 //tạo xong thì thêm job vào
                        }



void kCalendar::addJob(void (*func)(), bool (*conditionStop)())
                        {
                        
                           kJob job = {func,conditionStop,0};
                           insertJob(job);   
                          
                        }


void kCalendar::insertJob(kJob &job) 
                        {                                                                         //hàm thêm job
                          m_count++;
                          kJob *jobs = new kJob[m_count];
                          if (m_count > 1)
                            for (long long i = 0; i < m_count - 1; i++)
                              jobs[i] = m_jobs[i];
                          
                          jobs[m_count - 1] = job;
                          delete m_jobs;
                          m_jobs = jobs;
                        }
