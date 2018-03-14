/**
*
*  Compressor
*
*  O arquivo comprimido tem os seguintes dados:
*  [Huffman Header] [Dados comprimidos] [ultimo byte]
*
*  O Huffman Header contém pares de chars e suas frequencias para reconstruir a árvore de Huffman.
*  [Numero de pares] {[char][frequencia] ... }
*
*  O ultimo byte é usado para descrever quantos bits no ultimo byte são válidos;
*
*/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#define MAX_CODE_LENGTH 50

#include "tree.h"
#include "bitwriter.h"
#include "bitreader.h"
#include <stdlib.h>


typedef struct{
    unsigned int frequencies[256];
    unsigned int bytes_count;  // conta o número de bytes para gerar o código, 256+

    unsigned char *codes[256]; // array de strings, cada string é um código binário do byte

    Node *htree;

    // uc : uncompressed (descomprimido)
    unsigned char **uc_data; // blocos de dados para descomprimir
    unsigned int uc_blocks;
    unsigned int *uc_sizes;

} Huffman;

/**
    Inicializa a construção da estrutura de dados
*/
void Huffman_init(Huffman *h);

/**
    Adiciona os blocos de dados na estrutura, todos os blocos vão ser comprimidos
*/
void Huffman_add_data_block(Huffman *h, unsigned char *data,unsigned int size);


/**
    Contra a frequência dos bytes nos blocos de dados
*/
void Huffman_count_frequencies(Huffman *h);

/**
    Constrói a árvore de Huffman usando a frequência dos bytes
*/
void Huffman_build_tree(Huffman *h);

/**
    Gera os códigos de Huffman para cada byte
*/
void Huffman_generate_codes(Huffman *h);

/**
    Aplica as ultimas 3 funções acima, o processo de compreção é inicializar -> adicionar os blocos de dados -> aplicar -> comprimir os dados pro arquivo
*/
void Huffman_apply(Huffman *h);

/**
    Vai comprimir todos os dados usando o código de Huffman gerado
*/
void Huffman_compress_data_to_file(Huffman *h, char filename[]);

/**
    Libera a memória usada pela árvore
*/
void Huffman_free(Huffman *h);

/**
    Descomprime o arquivo comprimido pelo algoritmo, vai realocando cada bloco de dada correspondente no arquivo de saída
*/
void Huffman_file_decompress(Huffman *h, char filename[]);


#endif 