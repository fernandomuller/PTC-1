
tx: tx.o Enquadramento.o Serial.o 	
	g++ -g -o tx tx.o Enquadramento.o Serial.o 
	-rm -f *.o *~
	
tx.o: tx.cpp
	@echo Executando makefile TX
	g++ -g -c tx.cpp -std=c++11

rx: rx.o Enquadramento.o Serial.o 
	g++ -g -o rx rx.o Enquadramento.o Serial.o 
	-rm -f *.o *~
	
rx.o: rx.cpp
	@echo Executando makefile RX
	g++ -g -c rx.cpp -std=c++11
		
Serial.o: Serial.cpp Serial.h
	g++ -g -c Serial.cpp -std=c++11
	
Enquadramento.o: Enquadramento.cpp Enquadramento.h
	g++ -g -c Enquadramento.cpp -std=c++11
	
clean:
	-rm -f *.o *~
	
node: node.o Enquadramento.o Serial.o 	
	g++ -g -o node node.o Enquadramento.o Serial.o 
	-rm -f *.o *~
	
node.o: node.cpp
	@echo Executando makefile node (Tx e Rx)
	g++ -g -c node.cpp -std=c++11
