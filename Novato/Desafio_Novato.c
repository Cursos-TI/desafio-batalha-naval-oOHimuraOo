#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

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

int main() {
    setlocale(LC_ALL, "Portuguese");
    int largura = 10, altura = 10;
    int** array = GerarArrayBiDimensional(largura, altura);
    int x, y;

    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
            if ((x == 7 && y == 3) || (x == 8 && y == 4) || (x == 9 && y == 5)) {
                array[x][y] = 3;
            }
            if ((x == 4 && y == 6) || (x == 5 && y == 6) || (x == 6 && y == 6)) {
                array[x][y] = 3;
            }
            if ((x == 2 && y == 4) || (x == 2 && y == 5) || (x == 2 && y == 6)) {
                array[x][y] = 3;
            }
        }
    }
    
    imprimirArrayBiDimensional(array, largura, altura);
    
    for (x = 0; x < largura; x++) {
        free(array[x]);
    }


    free(array);
}