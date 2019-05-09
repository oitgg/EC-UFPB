#include <sys/types.h>
typedef struct self {
    // Para cada ponto
    int is_node;
    struct self *parent;

    // Árvore customizada
    int weight;
    int index;

    // Folha
    int character;

    // Nó
    struct self *left;
    struct self *right;

} Tree;

// Retorna uma nova struct como folha
Tree* new_leaf(int);

// Retorna uma nova struct como nó
Tree* new_node(Tree*, Tree*);

// Troca dois pontos na árvore
// Não checa se os pontos estão relacionados
void swap_in_tree(Tree*, Tree*);
