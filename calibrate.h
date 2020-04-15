   #ifndef calibrate_h
   #define calibrate_h
   #include "data.h"
   #include "EEPROMAnything.h"

  struct Tempdata
                {
                  int white[8];
                  int black[8];
                 
                }tempData;
                
  void speaker()
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

  void calibrate_White(int sensor)
  {    
       int pin;
               
          if((sensor==1)||(sensor==2))           
                  { 
                    
                      digitalWrite(45,LOW); 
                      digitalWrite(49,LOW);
                      digitalWrite(43,HIGH);    
                      digitalWrite(47,HIGH); 
                  } 
                    
           if((sensor==3)||(sensor==4))           
                  {   
                      digitalWrite(43,LOW); 
                      digitalWrite(47,LOW);
                      digitalWrite(45,HIGH);    
                      digitalWrite(49,HIGH); 
                  }   



      
       
      Serial.println("Start calibrating White");
     
      for (int i=0 ; i <8 ; i++)
      {   
             tempData.white[i]=0;   //ban dau gan=0
        
          for (int j = 0; j <600; j++)
          {
                    
               if((sensor==1)||(sensor==3))           
                   pin=i;
               if((sensor==2)||(sensor==4))           
                   pin=i+8;
                  
            
             int reading = analogRead(pin);
              
              if(j>=300)  //bat dau sau 300ms
                    { 
                           if (tempData.white[i] < reading)     //lay white lon nhat                          
                           tempData.white[i] = reading;                          
                    }
        
              delay(1);
          }

          
          switch (sensor)
          
          { case 1: DuLieu.whiteline_1[i]= tempData.white[i];break;
            case 2: DuLieu.whiteline_2[i]= tempData.white[i];break;
            case 3: DuLieu.whiteline_3[i]= tempData.white[i];break;
            case 4: DuLieu.whiteline_4[i]= tempData.white[i];break;      
          }
       }
       
         EEPROM_writeAnything(0, DuLieu);
        Serial.println("Calibrate White completely");

  }   

    void calibrate_Black(int sensor)
    {       int pin;
            speaker();
             if((sensor==1)||(sensor==2))           
                  { 
                    
                      digitalWrite(45,LOW); 
                      digitalWrite(49,LOW);
                      digitalWrite(43,HIGH);    
                      digitalWrite(47,HIGH); 
                  } 
                    
           if((sensor==3)||(sensor==4))           
                  {   
                      digitalWrite(43,LOW); 
                      digitalWrite(47,LOW);
                      digitalWrite(45,HIGH);    
                      digitalWrite(49,HIGH); 
                  }   
     Serial.println("Start calibrating Black");
    
      for (int i=0; i < 8; i++)
        {    
              for (int j = 0; j < 600; j++)
              { 

                   if((sensor==1)||(sensor==3))           
                   pin=i;
                   if((sensor==2)||(sensor==4))           
                   pin=i+8;                 
                                
                   int reading = analogRead(pin);
                    
                    if(j>=300)       //bat dau doc
                        {  
                            if(j==300)
                            tempData.black[i] = reading;  //the firstime
                         
                            if (reading < tempData.black[i] )   //lay black be nhat
                            tempData.black[i] = reading;                      
                        }
                
                delay(1);
              }
          
           switch (sensor)
          { 
            case 1: DuLieu.blackline_1[i]= tempData.black[i];break;
            case 2: DuLieu.blackline_2[i]= tempData.black[i];break;
            case 3: DuLieu.blackline_3[i]= tempData.black[i];break;
            case 4: DuLieu.blackline_4[i]= tempData.black[i];break;       
          }
              
      }
      EEPROM_writeAnything(0, DuLieu);
      Serial.println("Calibrate Black completely");
   
   }

int blackline_1[]={196,181,279,248,283,280,225,139};
int blackline_2[]={240,235,265,348,308,271,265,228};
int blackline_3[]={251,318,403,373,407,418,354,369};
int blackline_4[]={259,265,303,290,256,347,277,285};

int whiteline_1[]={55,50,81,72,89,81,58,35};
int whiteline_2[]={74,74,80,127,103,89,86,74};
int whiteline_3[]={57,89,150,109,126,158,158,125};
int whiteline_4[]={90,90,106,92,80,108,83,93};
   

//---------------------------------------------------------------------Các hàm calib Line----------------------------------------------------------------//
void clear_flag()
        {
           DuLieu.cali_flag=0;
           EEPROM_writeAnything(0, DuLieu);
        }

void calibrate()
        { 
          speaker();
        
          if(DuLieu.cali_flag==0)              
              { 
//           for(int i=0;i<8;i++)
//           {
//            DuLieu.blackline_1[i]=blackline_1[i];
//            DuLieu.blackline_2[i]=blackline_2[i];
//            DuLieu.blackline_3[i]=blackline_3[i];
//            DuLieu.blackline_4[i]=blackline_4[i];
//          
//            DuLieu.whiteline_1[i]=whiteline_1[i];
//            DuLieu.whiteline_2[i]=whiteline_2[i];
//            DuLieu.whiteline_3[i]=whiteline_3[i];
//            DuLieu.whiteline_4[i]=whiteline_4[i];
//
//
//
//            
//           }









                
//              calibrate_White(1);
//               calibrate_White(2);
//                calibrate_White(3);
//                calibrate_White(4);
             // calibrate_Black(4);
               //calibrate_Black(4);
              // calibrate_Black(3);
              //calibrate_Black(4);
                
                DuLieu.cali_flag=1;
                EEPROM_writeAnything(0, DuLieu);              
              }
        }



void test(int pin1,int pin2)
      {
          digitalWrite(pin1,HIGH);
          digitalWrite(pin2,HIGH);
         
           for(int i=0;i<8;i++)
            { 
              Serial.print("sensor: ");
              Serial.print(i);
              Serial.print(" ");
              Serial.print("  value= ");
              Serial.println(analogRead(i));
           if(analogRead(i)<10)
               {
               digitalWrite(42,HIGH);
               delay(20);
               digitalWrite(42,0);
               }
            }
            Serial.println("***");
               for(int i=8;i<16;i++)
            { 
              Serial.print("sensor: ");
              Serial.print(i);
              Serial.print(" ");
              Serial.print("  value= ");
              Serial.println(analogRead(i));
                 if(analogRead(i)<10)
               {
               digitalWrite(42,HIGH);
               delay(20);
               digitalWrite(42,0);
               }
                
           }
        Serial.println("***");
      
        
      }




#endif
