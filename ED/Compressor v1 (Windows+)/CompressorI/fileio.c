#include <stdio.h.>
#include <stdlib.h.>
#include "fileio.h"

int fileWrite(char name[], unsigned char *data, unsigned int size)
{
    FILE *f = fopen(name,"wb");
    fwrite(data,sizeof(unsigned char),size,f);
    fclose(f);
}


unsigned char *fileRead(char name[], unsigned int *size){
    FILE *f = fopen(name, "rb");
    if(f == NULL){
        printf("Arquivo não encontrado: %s\n",name);
        exit(1);
    }

    fseek(f,0L,SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char)*(*size));
    if(data == NULL){
        printf("Erro de memoria: %s\n",name);
        exit(1);
    }

    unsigned int readed = fread(data,1,*size,f);
    if(readed != *size){
        printf("Erro na leitura: %s\n",name);
        exit(1);
    }
    fclose(f);
    return data;
} 