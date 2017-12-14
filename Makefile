		
Serial.o: Serial.cpp Serial.h
	g++ -g -c Serial.cpp -std=c++11
	
Enquadramento.o: Enquadramento.cpp Enquadramento.h
	g++ -g -c Enquadramento.cpp -std=c++11
	
ARQ.o: ARQ.cpp ARQ.h
	g++ -g -c ARQ.cpp -std=c++11
	
clean:
	-rm -f *.o *~
	
node: proto.o Enquadramento.o Serial.o 	
	g++ -g -o proto proto.o Enquadramento.o Serial.o ARQ.o
	-rm -f *.o *~
	
node.o: node.cpp
	@echo Executando makefile proto.cpp Tx e Rx
	g++ -g -c proto.cpp -std=c++11
