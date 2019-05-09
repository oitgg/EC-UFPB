#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Número de listas encadeadas na hash table.
#define HASH_SIZE 27409

// Cada elemento da lista encadeada é um nó. Os nós contêm uma palavra e um ponteiro para o próximo nó.

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;


// A hash table é um array de listas encadeadas (nós).
node* hashtable[HASH_SIZE];

unsigned int hash_function(const char* word);

// Traça o númro de palavras em um dicionário.
int number_of_words = 0;

int filevalue;

/**
 * Retorna true se a palavra está no dicionário, e false caso contrário.
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

    // Usa a função hash para achar o bucket correto para inserir a palavra.
    int bucket = hash_function(lower_word);

    // Seta o cursor para o primeiro nó no bucket.
    node* cursor = hashtable[bucket];

    // Até que o final da lista encadeada seja alcançado (cursor == NULL),
    // compara cada palavra armazenada em cada nó com lower_word. Se elas são
    // as mesmas, então a palavra está no dicionário e não está digitada errada.
    // Caso contrário, a palavra está digitada errada.
    while (cursor != NULL)
    {
        if (strcmp(lower_word, cursor->word) == 0)
        {
            // Se a palavra minúscula é igual a outra dentro do bucket,
            // é um match, e retorna true.
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}


/**
 * Carrega o dicionário na memória. Retorna true se carregar com sucesso, caso contrário, retorna false.
 */
bool load(const char* dictionary)
{
    // Inicializa cada valor na hash table como NULL.
    for(int i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    // Abre o arquivo de texto do dicionário.
    FILE* the_dictionary;
    the_dictionary = fopen("dictionary.txt", "r");

    // Checa se o dicionário foi aberto corretamente.
    if (the_dictionary == NULL)
    {
        printf("Falha ao carregar o dicionário");
        return false;
    }

    char buffer[LENGTH+1];
    // Cria um loop dentro do arquivo até que o final dele seja alcançado.
    // Salva cada palavra em um buffer.
    while (fscanf(the_dictionary, "%s", buffer) > 0)
    {
        // Aloca memória para um novo nó.
        node* new_node = malloc(sizeof(node));
        // Seta o próximo ponteiro do nó para NULL.
        new_node->next = NULL;
        // Seta a palavra do nó para o valor armazenado no buffer.
        strcpy(new_node->word, buffer);
        // Lança a palavra na função hash para setar o bucket na hash table.
        int bucket = hash_function(new_node->word);
        // Se é o primeiro nó sendo adicionado no buffer, substitui
        // o valor NULL pelo novo nó.
        if (hashtable[bucket] == NULL)
        {
            hashtable[bucket] = new_node;
        }
        // Caso contrário, seta o novo ponteiro do nó para o primeiro nó da lista encadeada.
        // Então seta o novo nó para ser o primeiro nó da lista encadeada.
        else
        {
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
        // Traça o número de palavras no dicionário.
        number_of_words++;
    }
    // Fecha o arquivo de texto do dicionário.
    fclose(the_dictionary);
    // Se tudo correr bem, retorna true.
    return true;
}


/**
 * Retorna o número de palavras no dicionário se ele for carregado, caso contrário 0 se ainda não tiver sido carregado.
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


// Mapeia uma palavra para um valor inteiro para inserí-la na hash table.
// Soma o valor de cada caractere na palavra, e então econtra o
// resto (divisor) depois de dividí-lo pelo HASH_SIZE predefinido.


unsigned int hash_function(const char* word)
{
    unsigned long h;
    unsigned const char *us;

    us = (unsigned const char *) word;

    h = 0;

    while(*us != '\0')
    {
        h = (h * 151 + *us) % HASH_SIZE; // h vai assumir o valor no loop * 151 (base) + a soma do ASCII dividido por um número de buckets(numero primo)
        us++;
    }

    return h;
}


/**
 * Descarrega o dicionário da memória. Retorna true se descarregar com sucesso, false caso contrário.
 */
bool unload(void)
{
    // Itera todas as listas encadeadas na hash table. Seta o cursor
    // para apontar para a localização de cada uma na memória.
    for (int i = 0; i < HASH_SIZE;i++)
    {
        node* cursor = hashtable[i];

        while (cursor != NULL)
        {
            // Seta um ponteiro temporário para apontar para a posição do cursor na memória.
            // Move o cursor para o próximo nó para não o perder de vista antes de liberar a
            // memória temporarária do nó atual.
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
