#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>



using namespace std;

volatile int bytes_processed = 0;	//Guarda os bytes processados por cada thread.
volatile int lock = 0;				//Lock para a variavel bytes_processed.
volatile int requests_quantity;		//Guarda a quantidade de requisições.
string path;						//Guarda o nome do arquivo requisitado.

volatile int *arrive;				//Ponteiros que apontarão para um array e serão usados na barreira.
volatile int *proceed;

void Processing(int thread_num, string process_name, bool status);

void Unlock() {						//Função que destrava a trava de forma atômica.
	__sync_synchronize();
	lock = 0;
}

/* Função que consulta a pasta reqs contando quantas requisições existem. */
void RequestsCounter() {			
	bool control = true;			//Será true enquanto houver requisições.
	int counter = 1;
	string path_reqs;				//Guarda o diretório de cada requisição.

	while (control) {		//Laço que conta a quantidade de requisições.
		path_reqs = "./reqs/" + path_reqs + "req" + to_string(counter) + ".req";
		ifstream req (path_reqs);

		if (req.is_open()) {		//Se a requisição existe, é aberta e contador incrementado.
			++counter;
			req.close();
			path_reqs = "";

		} else {					//Se a requisição não existe, fim do laço.
			control = false;
			--counter;

		} 
	}
	requests_quantity = counter;
	cout << endl;
	cout << "Processando " << requests_quantity << " requisicoes..." << endl;
	arrive = new int[requests_quantity]();			//Arrays das barreiras criados e apontados por ponteiros.
	proceed = new int[requests_quantity]();

}

/* Função que obtêm as requisições, verifica se são válidas e chama a função Processing().*/
void GetRequest(string req_name, int thread_num) {			

	while(__sync_lock_test_and_set(&lock,1));			// Protocolo de entrada da trava.
 
	string path_req = "./reqs/" + req_name + ".req";	// Diretório da requisição.
	bool checking = false;
	bool status = false;				// Caso a requisição seja inválida seu estado é falso, caso seja correta é true.
	string line;						// String que armazena linha por linha do arquivo requisitado e do .req.
	ifstream req (path_req);			// Abre o arquivo .req.

	if (req.is_open()) {				
		getline(req,line);				// Recebe o conteúdo do arquivo .req.

		if (line.find("GET") == string::npos) {		// Verifica se o comando GET foi encontrado.
			cout << "[THREAD " << thread_num << "] Erro: Comando invalido!" << endl;
			
			size_t pos = line.find(" ");
			path = line.substr(pos+1);		// Path armazena o nome do arquivo que está sendo requisitado. Ex: image.png 

			cout << "[THREAD " << thread_num << "] " << path << endl;
			checking = true;

			req.close();

			if (checking) {
				string process_name = req_name + ".req";
				Processing(thread_num, process_name, status);		//Chama a função Processing() passando o número da thread,
																	// o nome da requisição e status igual a true.
				Unlock();											// Protocolo de saída da trava.
			}

		} else {			//Caso o comando GET não for encontrado...
			status = true;
			size_t pos = line.find(" ");
			path = line.substr(pos+1);

			cout << "[THREAD " << thread_num << "] " << path << endl;
			checking = true;

			req.close();

			if (checking) {
				string process_name = req_name + ".req";
				Processing(thread_num, process_name, status);	//Status é false.

				Unlock();			// Protocolo de saída da trava.
			}
		}
		__sync_fetch_and_add(&arrive[thread_num-1],1); 		// Após o processamento e criação do arquivo de saída,
															// ocorre a primeira sincronização.	

		while(proceed[thread_num-1]==0);  					// Laço é encerrado quando a thread monitor setar todo o array proceed para um.

		proceed[thread_num-1] = 0;							// Protocolo de saída da barreira.

	} else {
		cout << "[THREAD " << thread_num << "] Erro ao abrir arquivo." << endl;
		req.close();
		
	  }
}

/* Função que faz o processo das requisições e geração dos arquivos de resposta. */
void Processing (int thread_num, string process_name, bool status) {

    if (status) {			// Verifica se a requisição for válida.
	    cout << "[THREAD " << thread_num << "] Processando " << process_name << endl;
	    string dir = "./files/";
	    dir = dir + path;		// Guarda o caminho do arquivo do arquivo da pasta files.

	    string path_answ = "./answ/";		
	    string aux;
	    size_t pos = path.find(".");
	    aux = path.substr(0,pos);
	    path_answ = path_answ + aux + ".answ";		// Caminho completo do arquivo de saída (resposta).

	    ifstream file_req(dir);			// Abre arquivo requisitado.
	    string line;					// Armazena linha por linha do conteúdo.

	    if (file_req.is_open()) {

	    	ofstream answ(path_answ);	// Arquivo de resposta criado.
	    	
	    	if (answ.is_open()) {
				while (getline(file_req,line)) {		// Laço que percorre o arquivo requisitado por completo, linha por linha.
		    		answ << line << "\n";				// Arquivo de resposta vai recebendo linha por linha. 

		    		bytes_processed += line.size();		// Tamanho em bytes da linha é guardado.
		    		
		    	}
		    	answ.close();							// Ambos arquivos fechados.
		    	file_req.close();

		    } else {			// No caso de erro ao criar arquivo de saída.
		    	cout << "[THREAD " << thread_num << "] Erro: Resposta não foi criada!" << endl;	

		    }
	    	
	    } else {			// No caso de erro ao abrir arquivo da pasta files.
	    	cout << "[THREAD " << thread_num << "] Erro: Arquivo requisitado não encontrado!" << endl;
	    	ofstream answ(path_answ);
	    	
	    	if (answ.is_open()) {		// Criando arquivo de resposta para o caso de arquivo solicitado não existente.
	    		answ << "Arquivo requisitado não encontrado!";
	    	}

	    }

	 } else {		// Para o caso de status falso, ou seja, comando presente no arquivo de requisição inválido.
	 	cout << "[THREAD " << thread_num << "] Processando " << process_name << endl;
	    string dir = "./files/";
	    dir = dir + path;
	    
	    string path_answ = "./answ/";
	    string aux;
	    size_t pos = path.find(".");
	    aux = path.substr(0,pos);
	    
	    path_answ = path_answ + aux + ".answ";
	    

	    ifstream file_req(dir);
	    string line = "Bad command!";

	    if (file_req.is_open()) {

	    	ofstream answ(path_answ);
	    	
	    	if (answ.is_open()) {		// Arquivo de resposta criado para o caso de comando diferente de GET.
	    		answ << line;

	    	} else {
		    	cout << "[THREAD " << thread_num << "] Erro: Resposta não foi criada!" << endl;
	 		}
	
		} else 
	    	cout << "[THREAD " << thread_num << "] Erro: Arquivo requisitado não encontrado!" << endl;
	}
}

/* Thread que gerencia a sincronização das barreiras. */
void Monitor(int num_threads) {

	for (int i=0; i<num_threads; i++) {		// Laço que se encerra ao fim da primeira sincronização. 
		while(arrive[i]==0);
		arrive[i] = 0;
	}
	
	for (int i=0; i<num_threads; i++) {		// Laço que se seta valores do array proceed para um.
		__sync_fetch_and_add(&proceed[i],1);
	}
}


/* Função principal. */
int main () {

	RequestsCounter();		// Conta quantas requisições existem na pasta reqs.

	for (int i = 0; i < requests_quantity; i++) {		// Seta os valores dos arrays da barreira para zero.
		arrive[i] = 0;
		proceed[i] = 0;
	}

	thread reqs[requests_quantity];						// Array de threads.

	thread mon (Monitor,requests_quantity);				// Criação da thread monitor.
	
	for (int i = 0; i< requests_quantity; i++) {		// Criação de uma thread para cada requisição.
		reqs[i] = thread (GetRequest, "req" + to_string(i+1), i+1);
	}

	mon.join();											// Término das threads.
	
	for (int i = 0; i< requests_quantity; i++) {
		reqs[i].join();
	}

	cout << "Respostas criadas com sucesso. Total de bytes processados: " << bytes_processed << " bytes" << endl;

	return 0;
}