#include "line.h"
#include <Arduino.h>
#include "data.h"
#include "EEPROMAnything.h"
#include "PID.h"

 
int san;
 
  void speaker2()                 //hàm hú còi
                {
                 digitalWrite(42,HIGH); 
                 delay(500);
                 digitalWrite(42,LOW);      
                 delay(500);    
                 digitalWrite(42,HIGH);   
                 delay(500);
                 digitalWrite(42,LOW);      
                 delay(500); 
                 digitalWrite(42,HIGH);   
                 delay(500);
                 digitalWrite(42,LOW);      
                 delay(500);
                  
                }


line::line(int *white, int *black,int*sensorPins,int*sensorValues,int*normalizedValues)             //khai báo line
        {  
           EEPROM_readAnything(0,DuLieu);                                                       //Đọc dữ liệu từ Rom, k có thì DL=0; rất quan trọng
          
           for(int i=0;i<8;i++)
            { 
           
              this->white[i]=white[i];
              this->black[i]= black[i];
              this->sensorPins[i]=sensorPins[i];
              this->sensorValues[i]= sensorValues[i];
              this-> normalizedValues[i]=normalizedValues[i];
              }
        }



int line::readSensors()                     //hàm đọc cảm biến
       {
            for (int i = 0; i < 8; i++)                 
            {
              sensorValues[i] = analogRead(sensorPins[i]);
            }
       }



        int back_flag,stop_flag,co_lui,back;
        int start_passing,start_cheo;
        unsigned long timenow,start_lui,timecheo;
        
                
        int dem;
        int dung=0,dung_tam=0;
         int dicheo,dung_cheo1,demcheo=0;
        int count1,count2,tha2,next_time;
        

void line::normalizeSensors()                  //hàm xử lí dữ liệu cảm biến về dải chung
        {           
          for ( int i=0 ; i<8; i++)         
        
          {   
            normalizedValues[i] = map(sensorValues[i], white[i],black[i], 0, 1023);   //nội suy ra dải mới từ 0-1023
                
            normalizedValues[i]=constrain(normalizedValues[i],0,1023) ;           
          }
            

  //-------------------------------------------------------------------------------------XỬ LÝ ĐẾM NGÃ TƯ------------------------------------------------------------------------------------------------//                      
            
                                  if(linecheck==0)                                //chế độ đi đường
                                   {   
                                         if(direct==1||direct==-2)                 //nếu TIẾN, RẼ TRÁI
                                             {         if(sensorPins[7]<8)       // đọc error1                                                                  
                                                      {                                                        
                                                           if(start_passing==0)   //cờ qua vạch     
                                                             {  
                                                                  if(count1<2)
                                                                     {  if(san==green)
                                                                        {
                                                                           if(normalizedValues[7]>400)                                                                
                                                                            { 
                                                                              count1++;
                                                                              start_passing=1;
                                                                              digitalWrite(42,HIGH);
                                                                              delay(20);
                                                                              digitalWrite(42,0);
                                                                                               
                                                                             timenow=millis();  
                                                                             
                                                                             }
                                                                        }
                                                                        else
                                                                      
                                                                           if(normalizedValues[0]>400)                                                                
                                                                            { 
                                                                              count1++;
                                                                              start_passing=1;
                                                                              digitalWrite(42,HIGH);
                                                                              delay(20);
                                                                              digitalWrite(42,0);
                                                                                               
                                                                              timenow=millis();  
                                                                             
                                                                            }
                                                                     }
                                                                      if(count1>2)
                                                                           {
                                                                    
                                                            
                                                                                   if((normalizedValues[5]>400&&normalizedValues[2]>400))
                                                                                      {
                                                                                      
                                                                                         dem++;
                                                                                         digitalWrite(42,HIGH);
                                                                                         delay(20);
                                                                                         digitalWrite(42,0);
                                                                                         
                                                                                         start_passing=1;     //bật cờ để k vào đây trong lúc qua vạch
                                                                                         Serial.println(dem);
                                                                                          timenow=millis();     //lấy mốc thời gian
                                                                                                                                                                               
                                                                                         
                                                                                      }
                                                                           }
                                                               }
                                                               
                                                                if((millis()-timenow)>=100)    //nếu thời gian qua vạch đủ lớn, xóa cờ
                                                                    start_passing=0;                                                            
                                                        }                                                     
                                                }

                                          if(direct==-1||direct==2)         //nếu LÙI, RẼ PHẢI
                                            {
                                                     if(sensorPins[0]>7)     //đọc error2(line sau)                                                            
                                                       {    
                                                          
                                                           //----------------------CỜ PHÁT HIỆN ĐẾN CỘT LÚC LÙI-----------------------------//
                                                          if(back_flag==1)
                                                                   {  
                                                                      if (co_lui==0)
                                                                         {
                                                                          start_lui=millis();
                                                                          co_lui=1;
                                                                         }
                                                                 
                                                                    if((millis()-start_lui)>=next_time)   
                                                                        {  
                                                                         if(normalizedValues[6]>300&&normalizedValues[1]>300)
                                                                          {stop_flag=1;  
                                                                          
//                                                                     
                                                                           co_lui=0;}                                                                                                                    
                                                                        }
                                                                       
                                                                   }
                                                                   

                                                            //-------------------------------------------------------------------------------//

                                                        
                                                               if(start_passing==0)   //cờ qua vạch  
                                                               {   
                                                                if(back==1)
                                                                {
                                                                  if(count2<1)
                                                                     {
                                                                      
                                                                      if(san==red)
                                                                     { 
                                                                      if(normalizedValues[7]>400)                                                                
                                                                        { 
                                                                        count2++;
                                                                        digitalWrite(42,HIGH);
                                                                        delay(20);
                                                                        digitalWrite(42,0);                                                                                        
                                                                                                                                          
                                                                        }
                                                                     }
                                                                     else
                                                                     {
                                                                        if(normalizedValues[0]>400)                                                                
                                                                        { 
                                                                        count2++;
                                                                        digitalWrite(42,HIGH);
                                                                        delay(20);
                                                                        digitalWrite(42,0);                                                                                        
                                                                                                                                          
                                                                        }
                                                                        
                                                                     } 
                                                                        
                                                                    }
                                                                }

                                                       
                                                                             if((normalizedValues[5]>400&&normalizedValues[2]>400))
                                                                                  {    
                                                                                     dem++;
                                                                                     start_passing=1; 
                                                                                     digitalWrite(42,HIGH);
                                                                                     delay(20);
                                                                                     digitalWrite(42,0);
                                                                                     
                                                                                     //bật cờ để k vào đây trong lúc qua vạch
                                                                                     Serial.println(dem);
                                                                                     timenow=millis();     //lấy mốc thời gian                                                                       
                                                                                 }
                                                                           
                                                                 }
                                                                 
                                                              if((millis()-timenow)>=100)    //nếu thời gian qua vạch đủ lớn, xóa cờ
                                                                start_passing=0;  
                                                                                                                       
                                                      }
                                             }
                                   }
                                   
                                 
                                                                                                     
        }


float line::Error_calculating()
     {    
                   int max=normalizedValues[0];                 //tính toán mắt có giá trị cao nhất
                   int index_max=0;
                      
                  for(int i=1;i<8;i++)
                  {
                    if(max<normalizedValues[i])
                      
                      { max=normalizedValues[i]; 
                        index_max=i;
                      }  
                  }
                          
                   float sum1;                            //nhân giá trị với trọng số tương ứng
                           
                    switch (index_max)
                          {     case 0:  sum1=(-6.3)*max;break;
                                case 1:  sum1=(-4.3)*max;break;
                                case 2:  sum1=(-2.3)*max;break;
                                case 3:  sum1=max*(-1);break;
                                case 4:  sum1=max*(1);break;
                                case 5:  sum1=max*2.3;break;
                                case 6:  sum1=max*(4.3);break;
                                case 7:  sum1=max*(6.3);break;                                                            
                          }   
                          
 
                  int max2=0;                 //tìm giá trị max thứ 2
                  int index_max2;
                   for(int j=0;j<8;j++)
                  {
                       if((normalizedValues[j]>max2)&&(j!=index_max)&&(normalizedValues[j]<=max))                 
                      { 
                        max2=normalizedValues[j];
                        index_max2=j;
                      }
                  }

              
                  float sum2;                                  //nhân với trọng số tương ứng
                  
                  switch (index_max2)                    
                  {    
                        case 0:  sum2=max2*(-6.3);break;
                        case 1:  sum2=max2*(-4.3);break;
                        case 2:  sum2=max2*(-2.3);break;
                        case 3:  sum2=max2*(-1);break;
                        case 4:  sum2=max2*(1);break;
                        case 5:  sum2=max2*(2.3);break;
                        case 6:  sum2=max2*(4.3);break;
                        case 7:  sum2=max2*(6.3);break;
                  }    
                        //if(sensorPins[7]<8)  {
                        //
                        //            Serial.print(index_max);
                        //            Serial.print(" ");
                        //            
                        //            Serial.print(max);
                        //            Serial.print(" ");
                        //
                        //           
                        //            Serial.print(index_max2);
                        //            Serial.print(" ");
                        //
                        //            
                        //            Serial.println(max2);
                        //            Serial.println("****");
                        //}

               
            float error; 
            float x;
            float y;

  if((index_max-index_max2<=2)||(index_max2-index_max<=2))                    //tính toán sai lệch, yêu cầu 2 bóng phải gần nhau, trường hợp xấu nhất 2 bóng max1 max2 cách nhau 1 bóng
   
          { 
            x= sum1+sum2;           
            y= max+max2;
       
            error = x/y;
            error=constrain(error, -6.3, 6.3); 
          }
                       
                                                                    
  if(linecheck==1)                 //kiểm tra điểm dừng
             {    
                 // if(tha2==0)
                   {
                            if((direct=-2)||(direct==2))
                           
                             {  
                                               
                                      if(error<1&&error>-1&&normalizedValues[4]-normalizedValues[0]>=200)  //kiểm tra                                                                       
                                        dung=1;  
        
                             }
        
                        if(direct=-1)
                             {  if(sensorPins[7]<8)              
                                    {  if(error<6.5&&error>4&&normalizedValues[7]-normalizedValues[0]>=200)  //kiểm tra                                                                       
                                        dung=1;  
                                    }
                             }
        
                        if(direct=1)
                             { 
                               if(sensorPins[7]<8)              
                                    {  if(error<-1&&error>-2.5&&normalizedValues[1]-normalizedValues[7]>=200)  //kiểm tra                                                                       
                                        dung=1;  
                                    }
                             }
                   }
                     
//              if(tha2==1)
//              {  if(sensorPins[7]>8)
//                   {
//                       if(error<5.5&&error>4&&(normalizedValues[6]-normalizedValues[0]>=200))
//                       dung=1;
//                   }
//
//                 if(sensorPins[0]>7)
//                 {
//
//                       
//                      if(error>-5.5&&error<-4&&(normalizedValues[1]-normalizedValues[7]>=200))
//                     dung=1;
//                                                                         
//
//                  }
//
//                
//              }

              if(dao==1)
              {  if(san==green)
                 {
                     if(sensorPins[7]<8) 
                     {
                      if(normalizedValues[5]>60&&normalizedValues[4]>600&&normalizedValues[1]<100)
                         dung_tam=1;
                     }
                 }
                 else{
                        if(sensorPins[7]<8) 
                     {
                      if(normalizedValues[2]>60&&normalizedValues[3]>600&&normalizedValues[6]<100)
                         dung_tam=1;
                     }

                  
                 }
              }

                 
             if(dicheo==1)
             {  if(san==green)
                 {
                    if(sensorPins[0]>7) 
                    {  
                      if(normalizedValues[7]>600&&normalizedValues[6]>600&&normalizedValues[2]<100)  //kiểm tra                                                                       
                      dung_cheo1=1; 
                    }
                  }
                  else
                  {
                     if(sensorPins[0]>7) 
                    {  
                      if(normalizedValues[1]>600&&normalizedValues[0]>600&&normalizedValues[6]<100)  //kiểm tra                                                                       
                      dung_cheo1=1; 
                    }
                    
                  }
             }
              
                                             
             }
                //kiểm tra điểm dừng



        return error;
 
    }



void line:: sendvalue()
            {
                  for(int i=0;i<8;i++)
                    { 
                      Serial.print("sensor: ");
                      Serial.print(i+1);
                      Serial.print(" ");
                      Serial.print("  black= ");
                      Serial.print(black[i]);
                      Serial.print("  white= ");
                      Serial.println(white[i]);
                    }
                    Serial.println("***");
            }
