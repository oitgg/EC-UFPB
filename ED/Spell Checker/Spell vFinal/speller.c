#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"
#undef calculate
#undef getrusage

// dictionary default
#define DICTIONARY "/home/tgg/Desktop/ED/Spell1/Spell1/dictionary.txt"

double calculate(const struct rusage* b, const struct rusage* a);


int main()
{
    FILE *wrong;
    wrong = fopen("wrong.txt", "w");

   // struct para o temporizador
    struct rusage before, after;

    // benchmark
    double ti_load = 0.0, ti_check = 0.0, ti_unload = 0.0;

    // determina o dicionário utilizado
    char* dictionary = DICTIONARY;

    // carrega o dicionário
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // aborta caso o dicionário não seja carregado
    if (!loaded)
    {
        printf("Nao foi possivel abrir %s.\n", dictionary);
        return 1;
    }

    // calcula o tempo para carregar o dicinário
    ti_load = calculate(&before, &after)*1000;

    // tenta abrir o arquivo de texto
    FILE* fp = fopen("texto.txt", "r");
    if (fp == NULL)
    {
        printf("Nao foi possivel abrir %s.\n", fp);
        unload();
        return 1;
    }

    // prepara para reportar as palavras incorretas
    printf("PALAVRAS INCORRETAS\n\n");

    // prepara para checar as palavras
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];
    int coluna = 0;
    int linha = 1;

    // checa cada palavra no texto
    while (!feof(fp))
    {

        char c = fgetc(fp);
        coluna++;
        // permite apenas caracteres alfabéticos e apóstrofos
        if (isalpha(c) || (c == '\-') || (c == '\'') || (c == '-'))
        {

            // indexa os caracteres à palavra
            word[index] = c;
            index++;


            // ignora strings alfabéticas longas demais para serem palavras (maior palavra = pneumoultramicroscopicossilicovulcanoconiótico)
            if (index > LENGTH)
            {  index++;

                // consome o resto da string alfabética
                while ((c = fgetc(fp)) != EOF && isalpha(c));

                // prepara para uma nova palavra
                index = 0;
            }
        }


        // uma palavra inteira foi encontrada
        else if (index > 0)
        {
            // termina a palavra atual
            word[index] = '\0';

            // atualiza o contador
            words++;

            // checa a palavra
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // tempo de comparação
            ti_check += calculate(&before, &after)*1000;

            // printa a palavra caso esteja incorreta
            if (misspelled)
            {
                printf("'%s' na linha %d e coluna: %d\n", word, linha, coluna - index);
                fprintf(wrong, "'%s' na linha %d e coluna: %d\n", word, linha, coluna - index);
                misspellings++;
            }

            // prepara para uma nova palavra
            index = 0;
        }
        //char c = fgetc(fp);
        if (c == '\n')
        {
                  coluna = 0;
                  linha ++;
        }
    }

    // checa se houve algum erro
    if (ferror(fp))
    {
        fclose(fp);
        printf("Erro lendo %s.\n", fp);
        unload();
        return 1;
    }

    emptypos();
    numcollisions();
    savelog();

    // fecha o texto
    fclose(fp);

    // determina o tamanho do dicionário
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // descarrega o dicionário
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // aborta caso o dicionário não for descarregado
    if (!unloaded)
    {
        printf("Nao pode descarregar %s.\n", dictionary);
        return 1;
    }

    // calcula o tempo para descarregar o dicionário
    ti_unload = calculate(&before, &after)*1000;

    // reporta os benchmarks
    printf("\n\nPALAVRAS INCORRETAS:     %d\n", misspellings);
    printf("PALAVRAS NO DICIONARIO:  %d\n", n);
    printf("PALAVRAS NO TEXTO:        %d\n", words);
    printf("TEMPO PARA CARREGAR O DICIONARIO EM MEMORIA:         %.2f ms\n", ti_load);
    printf("TEMPO DE COMPARACAO TEXTO-DICIONARIO:        %.2f ms\n", ti_check);
    printf("TEMPO PARA DESCARREGAR O DICIONARIO DA MEMORIA:       %.2f ms\n", ti_unload);
    printf("TEMPO TOTAL:        %.2f ms\n\n", ti_load + ti_check + ti_unload);
        FILE *stats;
        stats = fopen("estatisticas.txt", "w");
            fprintf(stats, "\nPALAVRAS INCORRETAS: %d\n", misspellings);
            fprintf(stats, "PALAVRAS NO DICIONARIO: %d\n", n);
            fprintf(stats, "PALAVRAS NO TEXTO: %d\n", words);
            fprintf(stats, "TEMPO PARA CARREGAR O DICIONARIO EM MEMORIA: %.2f ms\n", ti_load);
            fprintf(stats, "TEMPO DE COMPARACAO TEXTO-DICIONARIO: %.2f ms\n", ti_check);
            fprintf(stats, "TEMPO PARA DESCARREGAR O DICIONARIO DA MEMORIA: %.2f ms\n", ti_unload);
            fprintf(stats, "TEMPO TOTAL: %.2f ms\n\n", ti_load + ti_check + ti_unload);
        fclose(stats);
        fclose(wrong);



    return 0;
}

/**
 * Retorna o número de segundos entre b e a.
 */
double calculate(const struct rusage* b, const struct rusage* a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                 (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                 (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
