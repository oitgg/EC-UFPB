#ifndef FILEIO_H
#define FILEIO_H

int fileWrite(char name[], unsigned char *data, unsigned int size);
unsigned char *fileRead(char name[], unsigned int *size); // retorna os dados e escreve o tamanho

#endif 