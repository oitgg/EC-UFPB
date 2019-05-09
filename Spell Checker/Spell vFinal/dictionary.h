//Funcionalidade do dicion�rio

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// tamanho m�ximo para uma palavra
// == pneumoultramicroscopicossilicovulcanoconi�tico
#define LENGTH 46

/**
 * Retorna true caso a palavra esteja no dicion�rio, false caso contr�rio.
 */
bool check(const char* word);

/**
 * Carrega o dicion�rio na mem�ria. Retorna true caso carregue com sucesso, false caso contr�rio.
 */
bool load(const char* dictionary);

/**
 * Retorna o n�mero de palavras no dicion�rio caso carregado, retorna 0 caso n�o tiver sido carregado ainda.
 */
unsigned int size(void);

/**
 * Descarrega o dicion�rio da mem�ria. Retorna true caso descarregue com sucesso, false caso contr�rio.
 */
bool unload(void);

/**
 * Mapeia uma string para um n�mero correspondente � localiza��o na hash table.
 */

#endif // DICTIONARY_H
