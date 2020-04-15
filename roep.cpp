#include"roep.h"
#include <nRF24L01.h>
#include <RF24.h>  
#include"line.h"   

RF24 radio(53, 31); // CE, CSN 
const byte addresses[][6] = {"00001", "00002"};

void rf_init(){
  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void  send_data()
{
    radio.stopListening();
    const char msg[30]="so nga tu ";
    radio.write(&msg, sizeof(msg));
   
    radio.write(&dem,sizeof(dem));  
}
