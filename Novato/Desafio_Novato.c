#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

//função responsavel por limpar o console. Ela possui um funcionamento levemente diferente a depender se ela foi compilada em windows ou não.
void limpar_console() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

//função responsavel por pausar o programa. Ela possui um funcionamento levemente diferente a depender se ela foi compilada em Windows ou não.
void pausar_programa() {
#if defined(_WIN32) || defined(_WIN64)
    printf("\n");
    system("pause");
    printf("\n");
#else 
    printf("\nPressione ENTER para continuar...\n");
    getchar();
#endif
}

int** GerarArrayBiDimensional(int largura, int altura) {
    int x, y;
    int** array = (int**) malloc(largura*sizeof(int*));
    for (x = 0; x < largura; x++) {
        array[x] = (int*) malloc(altura * sizeof(int));
        for (y = 0; y < altura; y++) {
            array[x][y] = 0;
        }
    }

    return array;
}

void imprimirArrayBiDimensional(int** array, int largura, int altura) {
    int x, y;
    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
            printf("%d ", array[x][y]);
        }
        printf("\n");
    }
}

int DescobrirSePontoValido(int limitador_x, int limitador_y, int ponto_x, int ponto_y) {
    if (limitador_x == ponto_x && limitador_y == ponto_y) {
        return 0;
    }
    return 1;
}

int GerarNumeroAleatorio(int limite) {
    int numeroAleatorio = rand() % limite;

    return numeroAleatorio;
}

int VerificarOverlap(int** array, int largura, int altura, int numero_x, int numero_y, int direcao) {
    int i;
    for (i = 0; i < 3; i++) {
        if (direcao == 0 ) {
            if (numero_x + i < largura && array[numero_x + i][numero_y] != 0) {
                return 1;
            }
        } else if (direcao == 1) {
            if (numero_y + i < altura && array[numero_x][numero_y + i] != 0) {
                return 1;
            }
        } else if (direcao == 2) {
            if (numero_x + i < largura && numero_y + i < altura && array[numero_x + i][numero_y + i] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void PreencherArray(int** array, int largura, int altura) {
    int x, y, i, direcao = 0;

    for (i = 0; i < 3; i++) {
        int numero_x, numero_y;
        int overlap;

        do {
            numero_x = GerarNumeroAleatorio(largura);
            numero_y = GerarNumeroAleatorio(altura);
            overlap = VerificarOverlap(array, largura, altura, numero_x, numero_y, direcao);
        } while (overlap == 1);
        
        if (direcao == 0) {
            array[numero_x][numero_y] = 3;
            array[numero_x + 1][numero_y] = 3;
            array[numero_x + 2][numero_y] = 3;
        } else if (direcao == 1) {
            array[numero_x][numero_y] = 3;
            array[numero_x][numero_y + 1] = 3;
            array[numero_x][numero_y + 2] = 3;
        } else if (direcao == 2) {
            array[numero_x][numero_y] = 3;
            array[numero_x + 1][numero_y + 1] = 3;
            array[numero_x + 2][numero_y + 2] = 3;
        }
        direcao++;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int largura = 10, altura = 10;
    int** array = GerarArrayBiDimensional(largura, altura);
    int x;
    
    PreencherArray(array, largura, altura);
    
    imprimirArrayBiDimensional(array, largura, altura);
    
    for (x = 0; x < largura; x++) {
        free(array[x]);
    }


    free(array);

  return 0;   
}