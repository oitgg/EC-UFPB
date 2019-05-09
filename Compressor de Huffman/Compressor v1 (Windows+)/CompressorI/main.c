#include <stdio.h>
#include "huffman.h"
#include <string.h>
#include "fileio.h"

int main(int argc, char *argv[]){
    //return main_test(argc,argv)

    if(argc < 3){ // o arquivo deve estar nos argumentos
        printf("Instrucoes de  uso: <arquivo de entrada> [opcional -d] <arquivo de saida>\n\t -d\tO arquivo de entrada vai ser descomprimido para um arquivo de saida.");
        return 0;
    }
    char *inputFile = argv[1];
    char *outputFile;

    char decompress = 0;
    if(!strcmp(argv[2],"-d")){
        decompress = 1;
        if(argc < 4){
            printf("<arquivo de saida> faltando\n");
            return 0;
        }
        outputFile = argv[3];
    }
    else{
        outputFile = argv[2];
    }

    Huffman h;

    Huffman_init(&h);

    if(decompress){

        printf("Descomprimindo: %s\n", inputFile);

        unsigned int size; // tamanho do arquivo a ser calculado
        unsigned char *data; // novos dados depois da compressão

        Huffman_file_decompress(&h,inputFile);
        data = h.uc_data[0];
        size = h.uc_sizes[0];

        // outras manipulações de dados podem ser feitas aqui (?)

        printf("Salvando o arquivo descomprimido.\n");
        fileWrite(outputFile,data,size);
        printf("Arquivo descomprimido para: %s\n",outputFile);
    }
    else
    {
        unsigned int size; // tamanho do arquivo a ser calculado
        unsigned char *data; // dados lidos do arquivo

        data = fileRead(inputFile,&size); // lÊ o arquivo e armazena os dados

        printf("Comprimindo: %s\n", inputFile);
        Huffman_add_data_block(&h,data,size);

        Huffman_apply(&h);

        Huffman_compress_data_to_file(&h,outputFile);
        printf("Arquivo comprimido para: %s\n",outputFile);
    }
    Huffman_free(&h);
    return 0;
} 