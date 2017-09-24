/* 
  Arquivo: rx.cpp
  Author:  fmuller
  Data:    Setembro 2017
*/

#include "Enquadramento.h"
#include "Serial.h"
 
using namespace std; 

// ls -lh /dev/ttyU*

Serial rf("/dev/ttyUSB1", B9600);
Enquadramento radio(rf, 8, 256);

unsigned char buffer[256];
int n = 0;

int main() {
	 
	// Bloqueante !!!!!
	// Aguarda o recebimento de uma mensagem 	
	while(1){
		n = radio.recebe(buffer);
		
		//debug
		printf ("\nBuffer  recebido  Hex  (com CRC):");
		for(int h = 0; h<n; h++){
			printf(" %x", buffer[h]);
		}	
		//printf ("\nMensagem recebida char (sem CRC): ");
		//cout.write((char*) buffer, n-2);		 
		
		n = 0;
	}	

	return 0;
}

