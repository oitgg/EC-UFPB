#include <stdio.h>
#include "huffman.h"
#include "fileio.h"

int main_test(int argc, char *argv[]){
    //tests1();
    //tests2();
    tests3();
    return 0;
}

void tests3(){

    Huffman h;

    Huffman_init(&h);

    int size;
    unsigned char *data = fileRead("rio.bmp",&size);

    Huffman_add_data_block(&h,data,size);
    Huffman_apply(&h);
    Huffman_compress_data_to_file(&h,"rio.bmp.hff");

    Huffman_free(&h);

    Huffman_init(&h);
    Huffman_file_decompress(&h,"rio.bmp.hff");

    fileWrite("Decompressed rio.bmp",h.uc_data[0],h.uc_sizes[0]);

}

void tests2(){

    Huffman h;

    Huffman_init(&h);

    int size;
    unsigned char *data = fileRead("LICENSE",&size);

    Huffman_add_data_block(&h,data,size);
    Huffman_apply(&h);
    Huffman_compress_data_to_file(&h,"LICENSE.hff");

    Huffman_free(&h);

    Huffman_init(&h);
    Huffman_file_decompress(&h,"LICENSE.hff");

    fileWrite("Decompressed LICENSE.txt",h.uc_data[0],h.uc_sizes[0]);

}

void tests1(){

    Huffman h;

    Huffman_init(&h);

    unsigned char vet[5] = {'b','b','b','b','b'};
    unsigned char vet2[3] = {'B','N','G'};
    printf("blocks = %d\n",h.uc_blocks);

    Huffman_add_data_block(&h,vet,5);
    Huffman_add_data_block(&h,vet2,3);

    printf("blocks = %d\n",h.uc_blocks);

    int i,j;
    for(i=0;i<h.uc_blocks;i++){
        for(j=0;j<h.uc_sizes[i];j++){
            printf("%c",(int)h.uc_data[i][j]);
        }
        printf("\n");
    }

    Huffman_count_frequencies(&h);

    printf("h.bytes_count = %d\n",h.bytes_count);

    Huffman_build_tree(&h);

    printf("h.htree->frequency %d\nh.htree->l->frequency %d\nh.htree->r->frequency %d\n", h.htree->frequency,h.htree->l->frequency,h.htree->r->frequency);

    Huffman_generate_codes(&h);

//    int j;
    for(i=0;i<256;i++){
        if(h.frequencies[i]>0){
            printf("Byte: %c -> ",i);
            for(j=0; h.codes[i][j] != 2;j++){
                printf("%d",h.codes[i][j]);
            }
            printf("\n");
        }
    }

    Huffman_compress_data_to_file(&h,"test.txt");

    Huffman_free(&h);

    Huffman_init(&h);

    printf("\n\n\n Reading...\n\n");
    Huffman_file_decompress(&h,"test.txt");

    printf("blocks = %d\n",h.uc_blocks);
    for(i=0;i<h.uc_blocks;i++){
        for(j=0;j<h.uc_sizes[i];j++){
            printf("%c",(int)h.uc_data[i][j]);
        }
        printf("\n");
    }
}