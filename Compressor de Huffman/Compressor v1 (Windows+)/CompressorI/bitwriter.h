#include <stdlib.h>
#include <stdio.h>

#ifndef BITWRITER
#define BITWRITER

typedef struct BitWriter {

    // Os bits são escritos no arquivo
    unsigned char buffer;
    // Número de bits que estão sendo escritos no buffer
    int bit_number;
    // Ponteiro do arquivo para escrita
    FILE *file;

} BitWriter;

/**
    Inicializa o bitwriter, todos os arquivos do bitwriter são abertos no modo "wb" (trunca pra zero e prepara o arquivo pra ser escrito)
 */
int BitWriter_init(BitWriter *writer, char *filename);

/**
    Escreve um bit no bitwriter, se o buffer do bitwriter está cheio, 
    ele vai ser descarregado no arquivo
 */
int BitWriter_write_bit(BitWriter *writer, unsigned char bit);

/**
    Escreve uma corrente (stream) de bits no arquivo.
    @param conta o número de bits para extrair do bitstream
*/
int BitWriter_write_bits(BitWriter *writer, unsigned char bitstream, int count);

/**
    Força a escrita de todo o conteúdo do buffer para um arquivo
 */
int BitWriter_flush(BitWriter *writer);

/**
    Descarrega o buffer e fecha o escritor
 */
int BitWriter_close(BitWriter *writer);

#endif 