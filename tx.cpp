/* 
  Arquivo: tx.cpp
  Author:  fmuller
  Data:    Setembro 2017
*/
 
#include "Enquadramento.h"
#include "Serial.h"
 
using namespace std; 

// ls -lh /dev/ttyU*

Serial rf("/dev/ttyUSB1", B9600);
Enquadramento radio(rf, 8, 256);

time_t timer;

// ~  0x7E
// }  0x7D

string msg = "um teste}~kk~ fim teste!!!\r\n";
int msg_len = msg.size();

int main() {

	timer = time(NULL);	
	int intervalo_timer = 5;// 5 segundos	
	
	// Entra num loop e envia a mensagem msg
	// num intervalo de tempo determinado em intervalo_timer
	
	while(1){
		if((time(NULL) - timer) >= intervalo_timer){		
			radio.envia((unsigned char*) &msg[0], msg_len);						
			timer += intervalo_timer;
		}
	}    
	
	return 0;
}
