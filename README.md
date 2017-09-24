#### Compilação dos arquivos tx.cpp e rx.cpp  e node.cpp:
Entre na pasta do projeto e execute make na linha de comando do terminal com o seguinte parâmetro.

> - Transmissor (tx.cpp)
	$ make tx
	O arquivo executável criado entra num loop enviando mensagens pela serial num intervalo de tempo determinado em intervalo_timer.
	No arquivo tx.cpp é preciso definir a Serial
	Serial rf("/dev/ttyUSB0", B9600);

> - Receptor (rx.cpp)
	$ make rx
	O arquivo executável criado entra num loop recebendo mensagens que chegam pela serial.
	No arquivo rx.cpp é preciso definir a Serial
	Serial rf("/dev/ttyUSB1", B9600);

> - Node tx e Rx (node.cpp)
	$ make node
	O arquivo executável criado monitora a serial e o teclado com um timeout que apresenta uma mensagem ao usuário.
	No arquivo node.cpp é preciso definir a Serial


#### Coisas para fazer:

> - Garantia de entrega: Stop and Wait(ARQ)
    Coloca cabeçalho: Tipo quadro, nº sequência, Id app, e passa para Enquadramento.

> - Timeout - Máquina de estados recepção bytes
> - Timeout - Máquina de estados
> - MAC - ALOHA
> - Implementar para arduino
> - Terminar Documentação PDF


##### Discussão


##### Ultimas alterações
* 13/09/2017 - Classe Enquadramento:
-			Alterado CRC
-			Modificado parâmetro buffer para unsigned char*			 
-			Testado Projeto com Enquadramento e CRC (OK)
			
* 24/09/2017 -   Arquivo de teste de comunicação e timeout
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
