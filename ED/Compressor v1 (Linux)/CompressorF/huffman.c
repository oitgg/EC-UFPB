#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "tree.h"
#include "io.h"
#include <sys/types.h>


// Guarda uma folha desconhecida
static Tree* unknow;

// Guarda o fim do arquivo (virtual)
static Tree* my_eof;

// Gurda raíz pra árvore de Huffman
static Tree* root;

// Guarda todos ponteiros para a árvore de Huffman orenados por Gallager
static Tree* gallager[515] = {0}; // 515 é o número máximo de ponteiros na árvore de Huffman

// Guarda o tamanho dos arrays de Gallager
static int gallager_size;

// Guarda todas as folhas ASCII
static Tree* ascii[256] = {NULL};

// Guarda o caminho para um ponto
static int path[257] = {0};

// Guarda o tamanho do caminho do array
static int path_size;

// Função update, não faz nada
void nothing() 
{
        }
static void(*update)() = &nothing;

/* Inicialização de Destrução */

// Inicializa as variáveis
static void init_variables() {
    /* Árvore */
    unknow = new_leaf('?');
    my_eof = new_leaf('0');

    // Cria raíz
    root = new_node(my_eof, unknow);

    // Atualiza o pai da folha
    unknow->parent = root;
    my_eof->parent = root;

    // Seta o peso
    my_eof->weight = 1;
    root->weight = 1;

    /* Gallager */
    // Array básico
    gallager[0] = root;
    gallager[1] = my_eof;
    gallager[2] = unknow;
    root->index = 0;
    my_eof->index = 1;
    unknow->index = 2;
    // Tamanho básico
    gallager_size = 3;

    /* Array ASCII */
    path_size = 0;

    // Tudo é inicializado
}

// Inicializa tudo
static void init() {
    int error;

    // Abre os arquivos
    error = create_reader();
    if (error != 0) {
        fprintf(stderr, "%s: %s\n", get_input(), strerror(errno));
        exit(1);
    }

    error = create_writer();
    if (error != 0) {
        fprintf(stderr, "%s: %s\n", get_output(), strerror(errno));
        exit(2);
    }

    // Arvore de Huffman
    init_variables();
}

// Fecha os arquivos
static void destroy() {
    // Fecha os arquivos
    delete_reader();
    delete_writer();
}

/* Funções da Árvore */

//// Caminho

// Acha todos os caminhos com direção (esquerda 0, direita 1) para retornar o ponteiro
// root point -> root
static void path_from(Tree* point) {
    Tree* current = point;
    path_size = 0;

    // Volta subindo pra cada nó
    while (current != NULL) {
        Tree* parent = current->parent;

        // Termina se a raíz for alcançada
        if (parent == NULL) {
            break;
        }

        // Adiciona direção para retornar o filho
        if (parent->left == current) {
            // Filho da esquerda
            path[path_size] = 0;
        } else {
            // Filho da direita
            path[path_size] = 1;
        }

        // Próximo passo
        ++path_size;
        current = parent;
    }
}

// Lê a direção do input até chegar na folha
static Tree* goto_leaf() {
	Tree* current = root;

	// Para cada nó, vai pra baixo
	while (current->is_node == 1) {

		int dir = read_bit();

		if (dir == 0) {
			// Esquerda
			current = current->left;
		} else {
			// Direita
			current = current->right;
		}

	}

	// Retorna a folha
	return current;
}

// Escreve o caminho reverso no output
// root -> point
static void write_path_inverse() {
    // Índice
    int i;

    // Escreve cada direção como um bit
    for (i = path_size - 1 ; i >= 0 ; --i) {
        if (path[i] == 0) {
            // Direção esquerda
            write_bit(0);
        } else {
            // Direção direita
            write_bit(1);
        }
    }
}

//// Array
static void swap_in_gallager(Tree* recto, Tree* verso) {
    // Índice da árvore
    int i = recto->index;
    int j = verso->index;

    // Inversão básica
    Tree* temp = gallager[i];  // temp = recto
    gallager[i] = gallager[j]; // recto = verso
    gallager[j] = temp;        // verso = temp

    // Atualiza o índice
    recto->index = j;
    verso->index = i;
}

// Checa se a folha associada com c já está na árvore
static int already_added(int c) {
    if (ascii[c] == NULL) {
        return 0; // Não presente
    } else {
        return 1; // Presente
    }
}

// Retorna o ponto máximo em Gallager com algum peso
static Tree* higher_point_with_same_weight(Tree* point) {
    int index = point->index;

    Tree* previous = gallager[index];

    // Volta enquanto tem o mesmo peso e não é a raiz
    while (index > 0 && previous->weight == point->weight) {
        index -= 1;
        if (index == 0 || gallager[index]->weight != point->weight) {
            return previous;
        }
        previous = gallager[index];
    }

    // Retorna o ponto com o mesmo peso
    //printf("\np %d %d\n", point->weight, previous->weight);
    return previous;
}

//// Árvore

// Cria um pai em cima do null com uma nova folha
static void add_char(int c) {
    // Nova folha
    Tree* leaf = new_leaf(c);

    // Novo nó, apontando para null e uma nova folga
    Tree* node = new_node(leaf, unknow);

    // Atualiza os pais
    if (unknow->parent->left == unknow) {
        unknow->parent->left = node;
    } else {
        unknow->parent->right = node;
    }
    node->parent = unknow->parent;
    leaf->parent = node;
    unknow->parent = node;

    // Pontos mais pesados
    leaf->weight = 1;
    node->weight = 1;

    // Atualiza gallager
    gallager[unknow->index] = node;
    node->index = unknow->index;
    gallager[unknow->index + 1] = leaf;
    leaf->index = unknow->index + 1;
    gallager[unknow->index + 2] = unknow;
    unknow->index += 2;
    gallager_size += 2;

    // Adiciona para ASCII
    ascii[c] = leaf;
}

// "Engorda" um ponto
static void increment(Tree* point) {

    // Procura para um ponto mais alto com a mesma altura
    Tree* higher = higher_point_with_same_weight(point);

    // Troca de ponto
    if (higher != root) {
        swap_in_tree(point, higher);
        swap_in_gallager(point, higher);
    }

    // "Engorda o ponto"
    point->weight += 1;
}

// "Engorda" uma folha e todos os seus pais
static void increment_from(Tree* leaf) {
    Tree* current = leaf;

    // "Engorda cada ponto"
    while (current != NULL) {
        increment(current);

        // "Engorda os pais"
        current = current->parent;
    }

    // Raíz alcançada
}

void compress() {

    init();

    // Um byte em [0,255]
    int byte;

    (*update)(); // Primeiro update
    // Lê o byte
    byte = read_byte();

    // Comprime cada byte
    while (byte != EOF) {

        if (already_added(byte) == 1) {

            // Escreve o caminho para a folha
            Tree* leaf = ascii[byte];
            path_from(leaf);
            write_path_inverse();

            // Atualiza a árvore
            increment_from(leaf);

        } else {
            // Novo char

            // Escreve o caminho para '?'
            path_from(unknow);
            write_path_inverse();

            // Escreve o char
            write_byte(byte);

            // Adiciona o char para a árvore
            add_char(byte);

            // Atualiza a árvore
            // O peso do novo pai de '?' é determinado
            // Incrementa a partir do avô
            increment_from(unknow->parent->parent);
        }

        (*update)(); // Update

        // Lê o próximo byte
        byte = read_byte();
    }

    // Fim do arquivo alcançado
    path_from(my_eof);
    write_path_inverse();

    // Compressão completa
    destroy();
}

void uncompress() {

	init();

	// Ponteiro para a folha
	Tree* leaf;

    (*update)(); // Update

	// Pega a primeira folha
	leaf = goto_leaf();

	// Faz algo enquanto o fim do arquivo (virtual) é alcançado
	while (leaf != my_eof) {

        if (leaf == unknow) {
            // Novochar

            int byte = read_byte();
            write_byte(byte);

            // Aiciona char
            add_char(byte);

            // Update na árvore
            increment_from(unknow->parent->parent);
        } else {
            // Char já existe
            write_byte(leaf->character);

            // Update na árvore
            increment_from(leaf);
        }

        // Próxima folha
        leaf = goto_leaf();

        (*update)(); // Update
	}

	// Fim do arquivo (virtual) alcançado
	destroy();

	// Descompressão completa
}

void set_update(void(*new_update)()) {
    update = new_update;
}
