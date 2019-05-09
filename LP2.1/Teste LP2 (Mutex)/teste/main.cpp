/*
* PROJETO 1 - LINGUAGEM DE PROGRAMAÇÃO 2
*
* Alunos:
* Matheus Amorim
* Pedro Felipe Amorim
* Thiago Gonzaga Gomes
*
*/


/*Declaração das bibliotecas padrões de C, de entrada e saída e threads POSIX
* Definição do numero maximo de pessoas
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#define max_pessoas 15 // Número máximo de pessoas no parque


/* Variveis que serão usadas para teste de condições em estruturas de controle
* e armazenamento de informações para detalhar a execuçao do programa
*/
int carro_movimento=0; /* Vai definir quando o carro está se movimentando "1" e quando está parado "0"
                        * para evitar que pessoas entrem e saiam do carro com ele em movimento */
int capacity = 4; /* Define a capacidade maxima de pessoas que podem entrar no carro para cada passeio */
int arrived = 0; /* Variável para saber se o carro terminou o passeio "1" ou se ainda não terminou "0" */
int volta = 0; /* Contador que vai ser incrementado uma vez a cada passeio que o carro der */
int voltamax = 4; /* Número máximo de voltas que o carro dará até que o parque seja fechado */
int entrada_l = 0; /* Variável que vai definir se as pessoas podem "1" ou nao "0" entrar no carro */
int numero_pessoas = 0; /* Número de pessoas que vão entrar no carro (contador) */
int fecha_parque = 0; /* Variável que vai definir o fechamento do parque após o número de voltas máximas ser alcançado */
int vazio=0; /* Variável que vai indicar quando o carro ficar vazio para liberar a entrada de novas pessoas */
int tempo=0;

/* Iniciação do objeto MUTEX
* Que vai permitir a exclusão mútua das threads
* e que não haja alteração durante a execução concorrente das threads.
* Necesário para a implementação de sessões críticas
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_arrive = PTHREAD_MUTEX_INITIALIZER;



/* Implementação de threads que serão sincronizadas de acordo com alguma condição,
* para que possam interromper a execução se necessário ou quando satisfizerem alguma condição especificada.
*/
pthread_cond_t car = PTHREAD_COND_INITIALIZER;
pthread_cond_t pessoa = PTHREAD_COND_INITIALIZER;
pthread_cond_t arrive = PTHREAD_COND_INITIALIZER;
pthread_cond_t leave = PTHREAD_COND_INITIALIZER;




/* Função Responsável pela entrada de pessoas no carro
* o while (entrada l==0) vai impedir que a execução prossiga ate que a entrada de pessoas seja liberada novamente por outra
* thread, evitando a falta de controle do momento em que as pessoas entram e saem do veículo
*/
void entra_carro(void* pi){
    int entrei;
    entrei = 0;
    while (!entrei){
    while (entrada_l==0){};
	pthread_mutex_lock(&mutex);

	if (numero_pessoas < capacity)
	{
	printf("O passageiro %d vai entrar. %d passageiros no carro\n", *(int *)(pi),numero_pessoas+1);
	numero_pessoas++;
    	if (numero_pessoas == capacity) {
        	printf("O carro vai sair.\n");
        	entrada_l=0;
        	carro_movimento = 1;
    		}
    entrei=1;
    }
    pthread_mutex_unlock(&mutex);
    }
}



/* Espera pra começar o passeio
* o while vai manter a função parada ate que o outro passeio acabe "arrived=1"
*/
void wait_round() {
    	while(arrived == 0){}
                  }




/*Pessoas saindo do carro
* Vai controlar a saída de pessoas do carro, decrementando o contador de pessoas
*/
void sai_carro(void* pi){
    pthread_mutex_lock(&mutex);
    printf("O passageiro %d saiu. %d passageiros no carro. \n", *(int *)(pi),numero_pessoas-1);
    numero_pessoas--;
    pthread_mutex_unlock(&mutex);
}





/* Atraso responsável pelo passeio das pessoas pelo parque */
void walk_away(){
	Sleep(3);
}




/* Aguarda o carro encher pra começar o passeio
* O while (entrada_l == 1) vai manter a thread parada até que o carro fique cheio e a entrada de pessoas seja bloqueada
* "entrada_l = 0".
*/
void wait_full(){
    pthread_mutex_lock(&mutex);
    printf("Passageiros podem entrar\n");
    entrada_l=1;
    pthread_mutex_unlock(&mutex);
    //printf("Esperando para comecar o passeio\n");
    while (entrada_l == 1) {}
  }



/* Inicia o passeio de carro após ele encher */
void round(){

     pthread_mutex_lock(&mutex);
     printf("Carro esta saindo agora. %d passageiros no carro.\n", numero_pessoas);
     pthread_mutex_unlock(&mutex);

     Sleep(1);
     printf("Carro terminou o percurso\n");

     pthread_mutex_lock(&mutex_arrive);
     carro_movimento=0;
     arrived = 1;
     pthread_mutex_unlock(&mutex_arrive);
}




/* Aguarda o carro esvaziar
* o while nesse caso vai segurar a thread até que a função sai_carro termine de esvaziar o carro
*/
void wait_empty(){

    while(numero_pessoas > 0){}
    printf("Desembarque completo do carro!\n\n");
    pthread_mutex_lock(&mutex_arrive);
    arrived = 0;
    pthread_mutex_unlock(&mutex_arrive);
}




/* Função que vai definir o comportamento das pessoas no parque */
void *cidadao (void* pi)
{

  while(volta<=voltamax)
  {
    entra_carro(pi);
	wait_round();
	sai_carro(pi);
	walk_away();
	}
}


/* Função que define o comportamento do carro enquanto o numero de voltas maximas nao for atingido*/
void *func(){

  while(volta<=voltamax)
  {
    wait_full();
    round();
    wait_empty();
    volta++;
  }
  pthread_mutex_lock(&mutex);
  fecha_parque=1;
  printf("\n\nO parque foi fechado!\n\n");
  pthread_mutex_unlock(&mutex);
  return 0;

}

int main(){
  int erro;
  int i;
  int *cont;

  pthread_t tcont[max_pessoas];

  for (i = 0; i < max_pessoas; i++)
  {
    cont = (int *) malloc(sizeof(int));
    *cont = i;
    erro = pthread_create(&tcont[i], NULL, cidadao, (void *) (cont));

    if(erro)
    {
      printf("Erro na Thread %d\n", i);
      exit(1);
    }
  }

    func();
    return 0;
}
