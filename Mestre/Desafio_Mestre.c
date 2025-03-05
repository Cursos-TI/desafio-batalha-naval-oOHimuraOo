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

//função responsavel por gerar e retornar um array bidimensional do tipo inteiro com todos os seus valores sendo 0 por padrão. 
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

//função responsavel por imprimir o um array bidimensional na tela.
void imprimirArrayBiDimensional(int** array, int largura, int altura) {
    int x, y;
    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
            printf("%d ", array[x][y]);
        }
        printf("\n");
    }
}

//função responsavel por gerar e retornar um numero inteiro aleatorio dentro de um limite. Esse limite precisa ser passado como parametro.
int GerarNumeroAleatorio(int limite) {
    int numeroAleatorio = rand() % limite;
    if (numeroAleatorio >= limite - 3) {
        numeroAleatorio -= 3;
    }

    return numeroAleatorio;
}

//Função responsavel por verificar se algum dos navios estão dando overlap um no outro. Caso esteja dando overlap a função retorna 1 caso contrario 0.
int VerificarOverlap(int** array, int largura, int altura, int numero_x, int numero_y, int direcao, int repenticao) {
    int i;
    for (i = 0; i < repenticao; i++) {
        if (direcao == 0 ) {
            if (numero_x + i < largura && array[numero_x + i][numero_y] != 0) {
                return 1;
            }
        } else if (direcao == 1) {
            if (numero_y + i < altura && array[numero_x][numero_y + i] != 0) {
                return 1;
            }
        } else if (direcao == 2 || direcao == 3) {
            if (numero_x + i < largura && numero_y + i < altura && array[numero_x + i][numero_y + i] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

//função responsavel por adicionar os navios em seus respectivos espaços. Ela precisa receber 4 parametros, o primeiro parametro precisa ser o array bidimensional a ser modificado. o segundo parametro a largura do array. o terceiro parametro a altura do array. o quarto parametro é a quantidade de vezes que essa verificação precisa ser rodada para ser valida.
void PreencherArray(int** array, int largura, int altura, int repeticao) {
    int x, y, i, direcao = 0;

    for (i = 0; i < repeticao; i++) {
        int numero_x, numero_y;
        int overlap;

        do {
            numero_x = GerarNumeroAleatorio(largura);
            numero_y = GerarNumeroAleatorio(altura);
            overlap = VerificarOverlap(array, largura, altura, numero_x, numero_y, direcao, repeticao);
        } while (overlap == 1);
        
        if (direcao == 0) {
            array[numero_x][numero_y] = 3;
            array[numero_x + 1][numero_y] = 3;
            array[numero_x + 2][numero_y] = 3;
        } else if (direcao == 1) {
            array[numero_x][numero_y] = 3;
            array[numero_x][numero_y + 1] = 3;
            array[numero_x][numero_y + 2] = 3;
        } else if (direcao == 2 || direcao == 3) {
            array[numero_x][numero_y] = 3;
            array[numero_x + 1][numero_y + 1] = 3;
            array[numero_x + 2][numero_y + 2] = 3;
        }
        direcao++;
        if (direcao >= 4) {
            direcao = 0;
        }
    }
}

//função responsavel por adicionar novos valores a um array bidimensional. Os valores inseridos são 1 e eles possuem uma formatação do tipo cone. A função precisa receber 3 parametros, o primeiro é o array bidimensional a ser modificado. O segundo a largura do array. O terceiro a altura do array.
void PreencherCone(int** cone, int largura, int altura) {
    int x, y;
    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
            if (x == 0 && y == 2 ){
                cone[x][y] = 1;
            } else if (y > 0 && y < 4 && x == 1) {
                cone[x][y] = 1;
            } else if (y >= 0 && y <= 4 && x == 2) {
                cone[x][y] = 1;
            } else {
                cone[x][y] = 0;
            }
        }
    }
}

//função responsavel por adicionar novos valores a um array bidimensional. Os valores inseridos são 1 e eles possuem uma formatação do tipo cruz. A função precisa receber 3 parametros, o primeiro é o array bidimensional a ser modificado. O segundo a largura do array. O terceiro a altura do array.
void PreencherCruz(int** cruz, int largura, int altura) {
    int x, y;
    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
            if ((y > 1 && y < 3 && x >= 0) || (y >= 0 && x == 2)) {
                cruz[x][y] = 1;
            } else {
                cruz[x][y] = 0;
            }
        }
    }
}

//função responsavel por adicionar novos valores a um array bidimensional. Os valores inseridos são 1 e eles possuem uma formatação do tipo losango. A função precisa receber 3 parametros, o primeiro é o array bidimensional a ser modificado. O segundo a largura do array. O terceiro a altura do array.
void PreencherOctaedro(int** Octaedro, int largura, int altura) {
    int x, y;
    for (x = 0; x < largura; x++) {
        for (y = 0; y < altura; y++) {
         if ((x == 1 && y == 2) || (y >= 1 && y <= 3 && x == 2) || (x == 3 && y == 2)) {
            Octaedro[x][y] = 1;
         } else {
            Octaedro[x][y] = 0;
         }
        }
    }
}

//função responsavel por aplicar os valores dentro dos arrays bidimensionais de habilidades no array do tabuleiro. Caso o espaço fosse agua o valor simplesmente torna-se 1, caso fosse barco ele torna-se 5.
void SobreporHabilidades(int** Array, int** Cone, int** Cruz, int** Octaedro,int largura,int altura,int habilidade_largura,int habilidade_altura){
    int x, y;

    for (x = 0; x < habilidade_largura; x++) {
        for (y = 0; y < habilidade_altura; y++) {
            if (Array[x][y] == 3) {
                Array[x][y] += Cone[x][y] + Cone[x][y];
            } else {
                Array[x][y] += Cone[x][y];
            }
        }
    }

    for (x = 0; x < habilidade_largura; x++) {
        for (y = 0; y < habilidade_altura; y++) {
            if (Array[5 + x][y] == 3) {
                Array[5 + x][y] += Cruz[x][y] + Cruz[x][y];
            } else {
                Array[5 + x][y] += Cruz[x][y];
            }
        }
    }

    for (x = 0; x < habilidade_largura; x++) {
        for (y = 0; y < habilidade_altura; y++) {
            if (Array[x][5 + y] == 3) {
                Array[x][5 + y] += Octaedro[x][y] + Octaedro[x][y];
            } else {
                Array[x][5 + y] += Octaedro[x][y];
            }
        }
    }
}


//função responsavel por limpar os slots de memoria utilizados durante o programa.
void LimparMemoria(int** array, int largura) {
    int x;
    for (x = 0; x < largura; x++) {
        free(array[x]);
    }
    
    free(array);
}

//função principal responsavel por organizar as funcionalidades das funções geradoras e verificadoras.
int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    int largura = 10, altura = 10, habilidade_Largura = 5, habilidade_Altura = 5;
    int** array = GerarArrayBiDimensional(largura, altura);
    int** cone = GerarArrayBiDimensional(habilidade_Largura, habilidade_Altura);
    int** cruz = GerarArrayBiDimensional(habilidade_Largura, habilidade_Altura);
    int** octaedro = GerarArrayBiDimensional(habilidade_Largura, habilidade_Altura);
    int x;

    printf("Essa é a representação da matriz da habilidade Cone: \n\n");
    PreencherCone(cone, habilidade_Largura, habilidade_Altura);
    imprimirArrayBiDimensional(cone, habilidade_Largura, habilidade_Altura);

    pausar_programa();
    limpar_console();

    printf("Essa é a representação da matriz da habilidade Cruz: \n\n");
    PreencherCruz(cruz, habilidade_Largura, habilidade_Altura);
    imprimirArrayBiDimensional(cruz, habilidade_Largura, habilidade_Altura);

    pausar_programa();
    limpar_console();

    printf("Essa é a representação da matriz da habilidade Octaedro: \n\n");
    PreencherOctaedro(octaedro, habilidade_Largura, habilidade_Altura);
    imprimirArrayBiDimensional(octaedro, habilidade_Largura, habilidade_Altura);

    pausar_programa();
    limpar_console();

    printf("Essa é a representação da matriz que representa o tabuleiro com os navios: \n\n");
    PreencherArray(array, largura, altura, 4);
    imprimirArrayBiDimensional(array, largura, altura);
    
    pausar_programa();
    limpar_console();

    printf("Essa é a representação da matriz do tabuleiro com a sobreposição das habilidades no tabuleiro: \n\n");
    SobreporHabilidades(array, cone, cruz, octaedro, largura, altura, habilidade_Largura, habilidade_Altura);
    imprimirArrayBiDimensional(array, largura, altura);

    LimparMemoria(array, largura);
    LimparMemoria(cone, habilidade_Largura);
    LimparMemoria(cruz, habilidade_Largura);
    LimparMemoria(octaedro, habilidade_Largura);

  return 0;   
}