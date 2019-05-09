#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "huffman.h"

static int last = -1;
static int clock = 0;

// HELP
static void helper() {
    printf("\
Compressor de Huffman\n\
\n\
Uso: huffman [-h] [ [-s] <arquivo_de_saida> (-c|-u) <arquivo_de_entrada> ]\n\
  -c, --comprimir    Comprime um arquivo especifico\n\
  -d, --descomprimir  Descomprime um arquivo especifico\n\
  -s, --silenciar      Nao mostra a progressao e comparacao\n\
  -h, --help        Mostra essa mensagem\n\
");
}

// Seta o arquivo de entrada e de saída
static void match_files(int pos, char *argv[]) {
    set_output(argv[pos - 1]);
    set_input(argv[pos + 1]);
}

static void update() {
    int percent = ((float)get_input_current() / (float)get_input_size()) * 100;
    // Mostra a porcentagem apenas na mudança
    if (last != percent) {
        last = percent;
        clock = (clock + 1) % 8;

        char timer = '|';

        if (clock == 1 || clock == 5) {
            timer = '/';
        } else if (clock == 2 || clock == 6) {
            timer = '-';
        } else if (clock == 7 || clock == 3) {
            timer = '\\';
        }

        printf("\r%c %3d%% ", timer, percent);
        fflush(stdout);
    }
}

static void show_diff(int mode) {
    int percent = ((float)get_output_current() / (float)get_input_size()) * 100;
    printf("\n");
    if (mode == 'c') {
        printf("Compressao");
    } else if (mode == 'd') {
        printf("Dsecompressao");
    }
    printf(" taxa : 100%% -> %d%%\n", percent);
}

// Executa o método de Huffman baseado na CLI
int main(int argc, char *argv[]) {

    // Pelo menos 1 argumento
    if (argc > 1) {

        // Checa se as opções são validas
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            helper();

        } else {

            if (argc > 3) {

                // Onde encontrar a opção de comprimir/descomprimir
                int look_at = 2;

                // default
                int verbose = 1;
                set_update(&update);

                // Checa se
                if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--silenciar") == 0) {
                    set_update(&nothing);
                    verbose = 0; // Silencia
                    ++look_at; // Operador de shift ++1
                }

                if (strcmp(argv[look_at], "-c") == 0 || strcmp(argv[look_at], "--comprimir") == 0) {
                    // Compressão
                    match_files(look_at, argv);
                    compress();

                    // Mostra a taxa de compressao
                    if (verbose == 1) {
                        show_diff('c');
                    }

                } else if (strcmp(argv[look_at], "-d") == 0 || strcmp(argv[look_at], "--descomprimir") == 0) {
                    // Descomprime
                    match_files(look_at, argv);
                    uncompress();

                    // Mostra a taxa de descompressao
                    if (verbose == 1) {
                        show_diff('d');
                    }

                } else {
                    helper();
                }

            } else {
                helper();
            }

        }

    } else {
        helper();
    }

    return 0;
}
