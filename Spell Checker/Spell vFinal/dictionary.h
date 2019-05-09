//Funcionalidade do dicionário

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// tamanho máximo para uma palavra
// == pneumoultramicroscopicossilicovulcanoconiótico
#define LENGTH 46

/**
 * Retorna true caso a palavra esteja no dicionário, false caso contrário.
 */
bool check(const char* word);

/**
 * Carrega o dicionário na memória. Retorna true caso carregue com sucesso, false caso contrário.
 */
bool load(const char* dictionary);

/**
 * Retorna o número de palavras no dicionário caso carregado, retorna 0 caso não tiver sido carregado ainda.
 */
unsigned int size(void);

/**
 * Descarrega o dicionário da memória. Retorna true caso descarregue com sucesso, false caso contrário.
 */
bool unload(void);

/**
 * Mapeia uma string para um número correspondente à localização na hash table.
 */

#endif // DICTIONARY_H
