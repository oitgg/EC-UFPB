#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hashtable_dic // Entrada da Tabela
{
    struct hashtable_dic *next; //Próxima entrada na sequência
    char *name; //Nome Definido
    char *defn; // Texto de Substituição
};

#define HASHSIZE 150
static struct hashtable_dic *hashp[HASHSIZE]; //Ponteiro da Tabela

// Hash: Formular um valor hash para a string s
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval; //31 é número primo
    return hashval % HASHSIZE;
}

// procurar: Procura por 's' em hashp
struct hashtable_dic *procurar(char *s)
{
    struct hashtable_dic *np;
    for (np = hashp[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; // Encontrado
    return NULL; // Não encontrado
}

char *strdup(char *);
/* inserirstr: Insere 'put' (name, defn) na hashp */
struct hashtable_dic *inserirstr(char *name, char *defn)
{
    struct hashtable_dic *np;
    unsigned hashval;
    if ((np = procurar(name)) == NULL)
    { //Não encontrado
        np = (struct hashtable_dic *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashp[hashval];
        hashp[hashval] = np;
    }
    else // Já existe
        free((void *) np->defn); // Libera o defn anterior
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}

char *strdup(char *s) //Faz uma duplicata de s
{
    char *p;
    p = (char *) malloc(strlen(s)+1); // +1 para ’\0’
    if (p != NULL)
       strcpy(p, s);
    return p;
}


int main()
{
    printf("Hello world!\n");
    return 0;
}