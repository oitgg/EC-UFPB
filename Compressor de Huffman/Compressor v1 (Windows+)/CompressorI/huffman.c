#include "huffman.h"

#define MAX_ALLOCATION 100000

void Huffman_iniciar(Huffman *h){
    int i;
    for(i=0;i<256;i++){
        h->frequencias[i] = 0;
        h->codes[i] = NULL;
    }
    h->bytes_count = 0;
    h->uc_data = NULL;
    h->uc_sizes = NULL;
    h->uc_blocks = 0;
}


void Huffman_add_data_block(Huffman *h, unsigned char *data,unsigned int size){
    h->uc_blocks += 1;
    h->uc_data = (unsigned char **)realloc(h->uc_data, sizeof(unsigned char *)*h->uc_blocks);
    h->uc_sizes = (unsigned int *)realloc(h->uc_sizes, sizeof(unsigned int)*h->uc_blocks);
    h->uc_data[h->uc_blocks-1] = data;
    h->uc_sizes[h->uc_blocks-1] = size;
}

void Huffman_contador_frequencias(Huffman *h){
    int i,j;
    for(i=0;i<h->uc_blocks;i++){
        for(j=0;j<h->uc_sizes[i];j++){
            h->frequencias[h->uc_data[i][j]]++;
        }
    }
    for(i=0;i<256;i++){
        if(h->frequencias[i] > 0){
            h->bytes_count++;
        }
    }
}

void sortNodes(Node **nodes, int size){ // implementação de Insertion Sort
    int i,j;
    Node *aux;
    Node *greatest;
    int greatestPos;
    for(i=0;i<size;i++){
        greatest = nodes[i];
        greatestPos = i;
        for(j=i+1;j<size;j++){
            if(nodes[j]->frequencia > greatest->frequencia){
                greatest = nodes[j];
                greatestPos = j;
            }
        }
        aux = nodes[i];
        nodes[i] = nodes[greatestPos];
        nodes[greatestPos] = aux;
    }
}

void construir_arvore_huffman(Huffman *h){

    Node **array = (Node **) malloc(sizeof(Node *)*h->bytes_count);

    int i,count=0;
    for(i=0;i<256;i++){
        if(h->frequencias[i] > 0){
            array[count] = Tree_newNode(i,h->frequencias[i],TRUE);
            count++;
        }
    }

    sortNodes(array,h->bytes_count);
//descomentar aqui pra ver os bytes e suas frequencias
/*
    for(i=0;i<h->bytes_count;i++){
        printf("char %d  freq %u\n",array[i]->byte,array[i]->frequencia);
    }
    printf("\n");
//*/

    Node * newnode;

    while(count > 1){
        newnode = Tree_newNode(0,array[count-1]->frequencia + array[count-2]->frequencia, FALSE);
        Tree_insertNodeLeft(newnode,array[count-1]);
        Tree_insertNodeRight(newnode,array[count-2]);
        array[count-1] = NULL;
        array[count-2] = newnode;
        count--;

        sortNodes(array,count);

    }

    h->htree = array[0];

    free(array);
}

// DFS (depht-first-search) para achar os códigos de Huffman
void depthCodes(Node *root, char tcode[], int last, unsigned char **codes){
    if(root->l != NULL){
        tcode[last] = 0;
        depthCodes(root->l,tcode,last+1,codes);
    }
    if(root->r != NULL){
        tcode[last] = 1;
        depthCodes(root->r,tcode,last+1,codes);
    }
    if(root->isLeaf == TRUE){
        int i;
        for(i=0;i<last;i++){
            codes[root->byte][i] = tcode[i];
        }
        codes[root->byte][last] = 2;
    }
}

void gerador_codigo_huffman(Huffman *h){

    int i;
    for(i=0;i<256;i++){
        if(h->frequencias[i] > 0)
            h->codes[i] = (unsigned char *)malloc(sizeof(unsigned char)*MAX_CODE_LENGTH);
    }
    char tcode[MAX_CODE_LENGTH];
    depthCodes(h->htree,tcode,0,h->codes);

}

void Huffman_apply(Huffman *h){
    contador_frequencias_huffman(h);
    construir_arvore_huffman(h);
    gerador_codigo_huffman(h);
}

void comprimir_dados_para_arquivo(Huffman *h, char filename[]){
    unsigned int i,j;

    BitWriter writer;
    BitWriter_init(&writer,filename); // escreve os dados dos bits no arquivo comprimido

    // começa a escrita do header da compressão de Huffman

    fwrite(&h->bytes_count,sizeof(int),1,writer.file); // Escreve o número de bytes que um código
    //printf("h->bytes_count = %d\n",h->bytes_count);
    unsigned char *code;

    int c;
    for(c=0;c<256;c++){
        if(h->frequencias[c]>0){
            unsigned char c2 = (unsigned char)c;
            fwrite(&(c2),sizeof(unsigned char),1,writer.file); // escreve o byte
            fwrite(&(h->frequencias[c]),sizeof(unsigned int),1,writer.file); // escreve a sua frequência
            //printf("writing: %c, freq: %d\n",c,h->frequencias[c]);
        }
    }

    //int count = 0;
    int b;
    for(b=0;b<h->uc_blocks;b++){
        for(i=0;i<h->uc_sizes[b];i++){
            code = h->codes[h->uc_data[b][i]]; // cada código é traduzido aqui

            for(j=0; code[j] != 2;j++){
                BitWriter_write_bit(&writer,code[j]); // escreve cada bit do código
            }
        }
    }
    // O último byte pode ter zeros na direita, então um novo byte é escrito no final só pra dizer quantos buts são validos no último byte dos dados comprimidos.
    char lastByte = (char)writer.bit_number;
    BitWriter_flush(&writer);
    BitWriter_write_bits(&writer,lastByte,8);

    BitWriter_close(&writer);
}

void Huffman_free(Huffman *h){
    int c,b;
    for(c=0;c<256;c++){
        if(h->codes[c] != NULL){
            free(h->codes[c]);
        }
    }
    Tree_free(h->htree);

    for(b=0;b<h->uc_blocks;b++){
        free(h->uc_data[b]);
    }
    free(h->uc_data);
    return;
}

void descomprimir_arquivo_huffman(Huffman *h, char filename[]){
    BitReader reader;
    BitReader_init(&reader,filename);

    // Leitura do Header
    unsigned char byte;

    FILE *f = reader.file;

    fread(&h->bytes_count,(sizeof(int)),1,f);

    int i;
    for(i=0;i<h->bytes_count;i++){
        fread(&(byte),sizeof(unsigned char),1,f); // lê o byte
        fread(&(h->frequencias[byte]),sizeof(unsigned int),1,f); // lê sua frequencia

        //printf("byte = %c    freq = %d\n",byte,h->frequencias[byte]);
    }

    // Reconstrói a árvore de Huffman com os dados lidos a partir do Header
    construir_arvore_huffman(h);
    Node *iterator = h->htree; // nó para procurar os códigos na árvore

    unsigned int maxSize = MAX_ALLOCATION;
    unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char)*maxSize);
    unsigned int pos = 0;

    unsigned char read;
    while(BitReader_read_bit(&reader,&read)){
        if(read == 0){
            iterator = iterator->l;
        }else{
            iterator = iterator->r;
        }
        if(iterator->isLeaf == TRUE){
            //printf("%c",iterator->byte);

            // armazena os dados
            data[pos] = iterator->byte;
            pos++;
            if(pos == maxSize){ // se checar na capacidade máxima, realoca
                maxSize += MAX_ALLOCATION;
                data = (unsigned char *)realloc(data,maxSize*sizeof(unsigned char));
            }

            iterator = h->htree;
        }
    }
    unsigned int size = pos;

    BitReader_close(&reader);

    Huffman_add_data_block(h,data,size);

    return ;
} 