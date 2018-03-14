#include "bitreader.h"

int BitReader_init(BitReader *reader, char *filename){
    reader->buffer = 0;
    reader->isAtLastByte = 0;
    reader->bit_number = 8; // força o primeiro load do buffer
    reader->file = fopen(filename,"rb");
    if(reader->file == NULL){
        printf("Arquivo nao encontrado: %s\n",filename);
        exit(1);
    }

    // lê o ultimo byte
    fseek(reader->file,-1,SEEK_END);
    reader->lastBytePosition = ftell(reader->file);
    fread(&(reader->lastByteInfo),sizeof(unsigned char),1,reader->file);
    fseek(reader->file, 0, SEEK_SET);

    //printf("Info do ultimo byte: %d\n", reader->lastByteInfo);
    //printf("Posicao di ultimo byte: %d\n", reader->lastBytePosition);

    return (int) reader->file;
}

int BitReader_read_bit(BitReader *reader, unsigned char *bit){
    if(reader->bit_number == 8){
        reader->bit_number = 0;
        fread(&(reader->buffer),sizeof(unsigned char),1,reader->file);
        if(ftell(reader->file) == reader->lastBytePosition){
            //printf("alcancou o ultimo byte--------------\n");
            reader->isAtLastByte = 1;
        }
    }
    if(reader->isAtLastByte == 1 && reader->bit_number == (int)reader->lastByteInfo){
        return 0;
    }
    unsigned char tmp = reader->buffer;

    tmp >>= 7 - reader->bit_number;
    reader->bit_number++;
    *bit = tmp&1;

    return 1;
}

int BitReader_close(BitReader *reader){
    fclose(reader->file);
} 