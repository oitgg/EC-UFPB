#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// N�mero de listas encadeadas na hash table.
#define HASH_SIZE 27409

// Cada elemento da lista encadeada � um n�. Os n�s cont�m uma palavra e um ponteiro para o pr�ximo n�.

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;


// A hash table � um array de listas encadeadas (n�s).
node* hashtable[HASH_SIZE];

unsigned int hash_function(const char* word);

// Tra�a o n�mro de palavras em um dicion�rio.
int number_of_words = 0;

int filevalue;

/**
 * Retorna true se a palavra est� no dicion�rio, e false caso contr�rio.
 */

bool check(const char* word)
{
    int word_length = strlen(word);
    char lower_word[LENGTH+1];


    // Converte a palavra para lowercase para comparar de forma precisa com a hash table.
    for (int i = 0; i < word_length; i++)
    {
        lower_word[i] = word[i];
    }

       // Adiciona o caractere nulo no final do char do array.
    lower_word[word_length] = '\0';

    // Usa a fun��o hash para achar o bucket correto para inserir a palavra.
    int bucket = hash_function(lower_word);

    // Seta o cursor para o primeiro n� no bucket.
    node* cursor = hashtable[bucket];

    // At� que o final da lista encadeada seja alcan�ado (cursor == NULL),
    // compara cada palavra armazenada em cada n� com lower_word. Se elas s�o
    // as mesmas, ent�o a palavra est� no dicion�rio e n�o est� digitada errada.
    // Caso contr�rio, a palavra est� digitada errada.
    while (cursor != NULL)
    {
        if (strcmp(lower_word, cursor->word) == 0)
        {
            // Se a palavra min�scula � igual a outra dentro do bucket,
            // � um match, e retorna true.
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}


/**
 * Carrega o dicion�rio na mem�ria. Retorna true se carregar com sucesso, caso contr�rio, retorna false.
 */
bool load(const char* dictionary)
{
    // Inicializa cada valor na hash table como NULL.
    for(int i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    // Abre o arquivo de texto do dicion�rio.
    FILE* the_dictionary;
    the_dictionary = fopen("dictionary.txt", "r");

    // Checa se o dicion�rio foi aberto corretamente.
    if (the_dictionary == NULL)
    {
        printf("Falha ao carregar o dicion�rio");
        return false;
    }

    char buffer[LENGTH+1];
    // Cria um loop dentro do arquivo at� que o final dele seja alcan�ado.
    // Salva cada palavra em um buffer.
    while (fscanf(the_dictionary, "%s", buffer) > 0)
    {
        // Aloca mem�ria para um novo n�.
        node* new_node = malloc(sizeof(node));
        // Seta o pr�ximo ponteiro do n� para NULL.
        new_node->next = NULL;
        // Seta a palavra do n� para o valor armazenado no buffer.
        strcpy(new_node->word, buffer);
        // Lan�a a palavra na fun��o hash para setar o bucket na hash table.
        int bucket = hash_function(new_node->word);
        // Se � o primeiro n� sendo adicionado no buffer, substitui
        // o valor NULL pelo novo n�.
        if (hashtable[bucket] == NULL)
        {
            hashtable[bucket] = new_node;
        }
        // Caso contr�rio, seta o novo ponteiro do n� para o primeiro n� da lista encadeada.
        // Ent�o seta o novo n� para ser o primeiro n� da lista encadeada.
        else
        {
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
        // Tra�a o n�mero de palavras no dicion�rio.
        number_of_words++;
    }
    // Fecha o arquivo de texto do dicion�rio.
    fclose(the_dictionary);
    // Se tudo correr bem, retorna true.
    return true;
}


/**
 * Retorna o n�mero de palavras no dicion�rio se ele for carregado, caso contr�rio 0 se ainda n�o tiver sido carregado.
 */
unsigned int size(void)
{
    return number_of_words;
}


void emptypos(void)
{
    int cont = 0;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        node* cursor = hashtable[i];

        if (cursor == NULL)
        {
            cont++;
        }

    }

    printf("\nNUMERO DE BUCKETS VAZIOS: %d", cont);
}

void numcollisions(void)
{
    int i;
    int cont;

    for(i = 0; i < HASH_SIZE; i++)
    {
        cont = 0;
        node* aux = hashtable[i];

        if(aux != NULL)
        {
            while(aux->next != NULL)
            {
                cont++;
                aux = aux->next;
            }
        }

  //printf("\nO BUCKET %d TEM %d COLISOES", i, cont);

    }
}


void savelog()
{
    FILE *log;
    log = fopen("log.csv", "w");

    int i, cont;

    for(i = 0; i < HASH_SIZE; i++)
    {
        cont = 0;
        node* aux = hashtable[i];

        if(aux != NULL)
        {
            while(aux->next != NULL)
            {
                aux = aux->next;
                cont++;
            }
        }

       fprintf(log, "\nBUCKET; %d; COLISOES; %d;", i, cont);
    }

    fclose(log);

}


// Mapeia uma palavra para um valor inteiro para inser�-la na hash table.
// Soma o valor de cada caractere na palavra, e ent�o econtra o
// resto (divisor) depois de divid�-lo pelo HASH_SIZE predefinido.


unsigned int hash_function(const char* word)
{
    unsigned long h;
    unsigned const char *us;

    us = (unsigned const char *) word;

    h = 0;

    while(*us != '\0')
    {
        h = (h * 151 + *us) % HASH_SIZE; // h vai assumir o valor no loop * 151 (base) + a soma do ASCII dividido por um n�mero de buckets(numero primo)
        us++;
    }

    return h;
}


/**
 * Descarrega o dicion�rio da mem�ria. Retorna true se descarregar com sucesso, false caso contr�rio.
 */
bool unload(void)
{
    // Itera todas as listas encadeadas na hash table. Seta o cursor
    // para apontar para a localiza��o de cada uma na mem�ria.
    for (int i = 0; i < HASH_SIZE;i++)
    {
        node* cursor = hashtable[i];

        while (cursor != NULL)
        {
            // Seta um ponteiro tempor�rio para apontar para a posi��o do cursor na mem�ria.
            // Move o cursor para o pr�ximo n� para n�o o perder de vista antes de liberar a
            // mem�ria temporar�ria do n� atual.
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
