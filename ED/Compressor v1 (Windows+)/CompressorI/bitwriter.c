#include "bitwriter.h"

int BitWriter_init(BitWriter *writer, char *filename) {
    writer->buffer = 0;
    writer->bit_number = 0;

    writer->file = fopen(filename, "wb");

    return (int) writer->file;
}

int BitWriter_write_bit(BitWriter *writer, unsigned char bit) {
    // Prepara o bit para que ele seja setado com um sinal (1)
    bit &= 1;
    // Shifta o buffer em uma posição
    writer->buffer <<= 1;
    // Seta o valor na posição apropriada
    writer->buffer |= bit;

    writer->bit_number++;
    // Em caso do buffer full, flusha (se livra/descarrega) tudo do arquivo
    if(writer->bit_number == 8) {
        return BitWriter_flush(writer);
    }

    return 0;
}

int BitWriter_write_bits(BitWriter *writer, unsigned char bitstream, int count) {
    int i;
    int retval = 0;
    for(i = 0; i < count; i++) {
        // Pega o bit mais a esquerda e vai levando ele pra direita até o final
        unsigned char bit = (bitstream & (1 << (count - i - 1)))?1:0;
        retval |= BitWriter_write_bit(writer, bit);
    }
    return retval;
}

int BitWriter_flush(BitWriter *writer) {
    // Se não tiver conteúdo, não tem nada pra escrever
    if(writer->bit_number == 0) {
        return 0;
    }

    writer->buffer <<= 8 - writer->bit_number;

    int retval = fwrite(&(writer->buffer), sizeof(char), 1, writer->file);
    writer->buffer = 0;
    writer->bit_number = 0;

    return !retval;
}

int BitWriter_close(BitWriter *writer) {
    int flush = BitWriter_flush(writer);
    int close = fclose(writer->file);
    return flush || close;
} 