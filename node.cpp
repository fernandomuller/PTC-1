/* 
  Arquivo: node.cpp
  Author:  fmuller
  Data:    Setembro 2017
  
  Arquivo de teste de comunicação e timeout
  O programa monitora a serial e o teclado:
  
  * Se algo for recebido na serial, 
    é lido e apresentado na tela.
  * Se algo for digitado no teclado, essa
    mensagem é enviada pelo rádio.
  * Se ocorrer um timeout, uma 
    mensagem é apresentada ao usuário 
   
   OBS: Nada a ver com ARQ
   
   Para compilar:
   $ g++ node.cpp Enquadramento.cpp Serial.cpp -onode -std=c++11
   
*/

#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h> 

#include "Enquadramento.h"
#include "Serial.h"
 
using namespace std; 

// ls -lh /dev/ttyU*

Serial rf("/dev/ttyUSB0", B9600);
Enquadramento enq(rf, 8, 256);

enum TipoEvento {payload, quadro, timeout};
 
struct Evento {
    TipoEvento tipo;
    unsigned char * ptr;
    int bytes; 
    // construtor sem parâmetros: cria um Evento Timeout
    Evento() { tipo = timeout;} 
    // construtor com parâmetros: cria um evento Payload ou Quadro
    Evento(TipoEvento t, unsigned char * p, int len) : tipo(t), ptr(p), bytes(len) {}
}; 
  // executa a MEF, passando como parâmetro um evento
void handle(Evento & e);
void protoInit();

unsigned char buffer[1024];
int intervalo_timer = 7;
timeval timer = {intervalo_timer,0};

Evento e = Evento(payload, &buffer[0], 0);
int n = 0;

int main() {
	
	protoInit();
   
}
void protoInit(){
	cout << "\nInicializando...\n";
	// cria um conjunto de descritores
	fd_set r;
   
	int fd_serial = rf.get(); 
	// faz com que fd opere em modo não-bloqueante
	int op_serial = fcntl(fd_serial, F_GETFL);
	fcntl(fd_serial, F_SETFL, op_serial | O_NONBLOCK);
   
	int fd_teclado = 0;// o descritor de arquivo da entrada padrão
	int op_teclado = fcntl(fd_teclado, F_GETFL);
	fcntl(fd_teclado, F_SETFL, op_teclado | O_NONBLOCK);  	
 	
 	while(1){
 			
		FD_ZERO(&r);
 		FD_SET(fd_teclado, &r);
   		FD_SET(fd_serial, &r);   			   			

		cout << "Aguardando dados da Serial(RX) ou Teclado(TX)... ";
		cout.flush();
		 
		n = select(fd_serial+1, &r, NULL, NULL, &timer);

		// testa se algo foi digitado no teclado
        if (FD_ISSET(fd_teclado, &r)) {
        	e.tipo = payload;
        	e.bytes = read(fd_teclado, buffer, 1024);
        	
            cout << "\nVocê digitou: ";
			cout.write((char*)buffer, e.bytes); cout << endl;
			 
        	handle(e);          	  
        }

        // testa se existem bytes na serial
        if (FD_ISSET(fd_serial, &r)) {  
        	e.tipo = quadro;     
        	 
        	handle(e);        				
        }
        
        if (n <= 0) { 
    		e.tipo = timeout;
        	handle(e);
   		}                       
		//timer = {5,0};
 	}
}
void handle(Evento & e){
//TipoEvento {Payload, Quadro, Timeout};
//int estado; estado atual da MEF
int rx_bytes;
 
  switch ( e.tipo )
  {	//-------------------------------------------------------
     case payload :		 	
			cout << "Enviando Mensagem!!! ";
            enq.envia((unsigned char*) e.ptr, e.bytes);	
            timer = {intervalo_timer,0};// Reinicia o timer	
     break;
 	//--------------------------------------------------------
     case quadro :
			 rx_bytes = enq.recebe((unsigned char*) &buffer[0]);
			 printf ("\nBuffer  recebido  Hex  (com CRC):");
			 for(int h = 0; h<rx_bytes; h++){
					printf(" %x",  buffer[h]);
			 }printf(" \n");
     break;
 	//---------------------------------------------------------
     case timeout :
			cout << "\n\nTIMEOUT!!!!	Digite algo!  " << endl;
			timer = {intervalo_timer,0};
     break;     
 	//---------------------------------------------------------
     default :
       printf ("Evento invalido!\n");

  }

}
