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

int GerarNumeroAleatorio() {
    int numeroAleatorio = rand() % 6;

    return numeroAleatorio;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int largura = 10, altura = 10;
    int** array = GerarArrayBiDimensional(largura, altura);
    int x, y;

    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
            int i;
            for (i = 0; i < 3; i++) {
                int numero_x = GerarNumeroAleatorio();
                int numero_y = GerarNumeroAleatorio();

                printf("\n o numero x é: %d \n", numero_x);
                if ((DescobrirSePontoValido(numero_x, numero_y, x, y) == 0) || (DescobrirSePontoValido(numero_x + 1, numero_y, x, y) == 0) || (DescobrirSePontoValido(numero_x + 2, numero_y, x, y) == 0)) {
                    array[x][y] = 3;
                }
            }
        }
    }
    
    imprimirArrayBiDimensional(array, largura, altura);
    
    for (x = 0; x < largura; x++) {
        free(array[x]);
    }


    free(array);

    GerarNumeroAleatorio();
  return 0;   
}