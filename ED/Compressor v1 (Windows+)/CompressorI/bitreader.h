#ifndef BITREADER_H
#define BITREADER_H

#include <stdlib.h>
#include <stdio.h>

/**
    Esse bitreader deve ser usado para ler os dados comprimidos.
    O ultimo byte dos dados deve ter zeros na direita que não são significantes.
    Então o leitor vai ler o ultimo byte do arquivo para indicar quantos bits tem no ultimo byte dos dados.
*/

typedef struct BitReader {

    // Byte lido do arquivo
    unsigned char buffer;
    // Número do próximo bit a ser lido no buffer
    int bit_number;
    // Ponteiro para o arquivo, para o leitor
    FILE *file;

    unsigned int lastBytePosition; // armazena a posição do último byte
    char lastByteInfo; // ultimo byte

    char isAtLastByte; // checa se o que está lendo é o último byte

} BitReader;


/**
    Inicializa o BitReader, todos os arquivos do bitreader são abertos no modo "rb" (apenas leitura e truncado pra zero)
 */
int BitReader_init(BitReader *reader, char *filename);

/**
    Lê o bit do arquivo, retorna 1 se sucesso ou 0 se chegar no fim do arquivo
 */
int BitReader_read_bit(BitReader *reader, unsigned char *bit);

/**
    Fecha o leitor
 */
int BitReader_close(BitReader *reader);

#endif 