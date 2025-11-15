#include <stdio.h>
#include <stdlib.h>

/*
 * Batalha Naval - Desafios Novato / Aventureiro / Mestre
 * Projeto educacional em C que demonstra o uso de vetores e matrizes
 * para representar um tabuleiro 10x10, posicionar navios (horizontais,
 * verticais e diagonais) e sobrepor áreas de efeito de habilidades
 * (cone, cruz e octaedro) usando matrizes de habilidade.
 *
 * Observações:
 * - Valores no tabuleiro:
 *      0 -> água
 *      3 -> navio
 *      5 -> área afetada por habilidade (se não houver navio)
 * - As coordenadas e orientações dos navios/habilidades são
 *   definidas diretamente no código para simplificar.
 * - As matrizes de habilidade são construídas dinamicamente usando
 *   loops aninhados e condicionais.
 *
 * Autor: projeto acadêmico (comentários leves para facilitar leitura)
 */

#define BOARD_SIZE 10
#define SHIP_SIZE 3

/* Protótipos */
void init_board(int board[BOARD_SIZE][BOARD_SIZE]);
void print_board(int board[BOARD_SIZE][BOARD_SIZE]);
int can_place_horizontal(int board[BOARD_SIZE][BOARD_SIZE], int row, int col_start);
int can_place_vertical(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col);
int can_place_diagonal(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col_start, int dr, int dc);
void place_horizontal(int board[BOARD_SIZE][BOARD_SIZE], int row, int col_start);
void place_vertical(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col);
void place_diagonal(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col_start, int dr, int dc);

/* Habilidades */
void build_cone(int size, int cone[size][size]);
void build_cross(int size, int cross[size][size]);
void build_octahedron(int size, int oct[size][size]);
void overlay_skill(int board[BOARD_SIZE][BOARD_SIZE], int skill_size, int skill[][skill_size], int origin_row, int origin_col);

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    int tabuleiro5[5][5] = {0};
    for (int c = 1; c <= 3; c++) tabuleiro5[1][c] = 3;    // navio horizontal
    for (int l = 2; l <= 4; l++) tabuleiro5[l][3] = 3;    // navio vertical

    printf("=== Tabuleiro 5x5 - Nível Novato ===
");
    for (int i = 0; i < 5; i++) { for (int j = 0; j < 5; j++) printf("%d ", tabuleiro5[i][j]); printf("
"); }

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    int tabuleiro10[10][10] = {0};
    for (int c = 2; c <= 6; c++) tabuleiro10[2][c] = 3;      // horizontal
    for (int l = 4; l <= 8; l++) tabuleiro10[l][5] = 3;      // vertical
    for (int d = 0; d < 5; d++) tabuleiro10[1 + d][1 + d] = 3;  // diagonal principal
    for (int d = 0; d < 4; d++) tabuleiro10[8 - d][2 + d] = 3;  // diagonal invertida

    printf("
=== Tabuleiro 10x10 - Nível Aventureiro ===
");
    for (int i = 0; i < 10; i++) { for (int j = 0; j < 10; j++) printf("%d ", tabuleiro10[i][j]); printf("
"); }

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    printf("
=== Habilidade: Cone ===
");
    int cone[3][5] = {0};
    for (int j = 2; j <= 2; j++) cone[0][j] = 1;
    for (int j = 1; j <= 3; j++) cone[1][j] = 1;
    for (int j = 0; j <= 4; j++) cone[2][j] = 1;
    for (int i = 0; i < 3; i++) { for (int j = 0; j < 5; j++) printf("%d ", cone[i][j]); printf("
"); }

    printf("
=== Habilidade: Cruz ===
");
    int cruz[3][5] = {0};
    for (int j = 0; j < 5; j++) cruz[1][j] = 1;
    cruz[0][2] = cruz[2][2] = 1;
    for (int i = 0; i < 3; i++) { for (int j = 0; j < 5; j++) printf("%d ", cruz[i][j]); printf("
"); }

    printf("
=== Habilidade: Octaedro ===
");
    int oct[3][5] = {0};
    oct[0][2] = oct[1][1] = oct[1][2] = oct[1][3] = oct[2][2] = 1;
    for (int i = 0; i < 3; i++) { for (int j = 0; j < 5; j++) printf("%d ", oct[i][j]); printf("
"); }

    return 0;
}
}

/* Inicializa o tabuleiro com 0s (agua) */
void init_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

/* Imprime o tabuleiro no console de forma organizada */
void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("   ");
    for (int c = 0; c < BOARD_SIZE; c++) printf("%d ", c);
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%d ", board[i][j]);
            if (j < BOARD_SIZE - 1) printf(" ");
        }
        printf("\n");
    }
}

/* Verifica se um navio horizontal de tamanho SHIP_SIZE cabe e não sobrepoe outros navios */
int can_place_horizontal(int board[BOARD_SIZE][BOARD_SIZE], int row, int col_start) {
    if (row < 0 || row >= BOARD_SIZE) return 0;
    if (col_start < 0 || col_start + SHIP_SIZE - 1 >= BOARD_SIZE) return 0;
    for (int k = 0; k < SHIP_SIZE; k++) {
        if (board[row][col_start + k] != 0) return 0; // ja ocupado
    }
    return 1;
}

/* Verifica se um navio vertical cabe e não sobrepoe */
int can_place_vertical(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col) {
    if (col < 0 || col >= BOARD_SIZE) return 0;
    if (row_start < 0 || row_start + SHIP_SIZE - 1 >= BOARD_SIZE) return 0;
    for (int k = 0; k < SHIP_SIZE; k++) {
        if (board[row_start + k][col] != 0) return 0;
    }
    return 1;
}

/* Verifica se um navio diagonal cabe e não sobrepoe.
 * dr, dc definem a direcao por passo (ex: dr=1,dc=1 para desc dir)
 */
int can_place_diagonal(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col_start, int dr, int dc) {
    int r = row_start;
    int c = col_start;
    for (int k = 0; k < SHIP_SIZE; k++) {
        if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE) return 0;
        if (board[r][c] != 0) return 0;
        r += dr; c += dc;
    }
    return 1;
}

/* Coloca um navio horizontal no tabuleiro (assume validacao previa) */
void place_horizontal(int board[BOARD_SIZE][BOARD_SIZE], int row, int col_start) {
    for (int k = 0; k < SHIP_SIZE; k++) board[row][col_start + k] = 3;
}

/* Coloca um navio vertical no tabuleiro (assume validacao previa) */
void place_vertical(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col) {
    for (int k = 0; k < SHIP_SIZE; k++) board[row_start + k][col] = 3;
}

/* Coloca um navio diagonal no tabuleiro (assume validacao previa)
 * dr, dc definem a direcao por passo
 */
void place_diagonal(int board[BOARD_SIZE][BOARD_SIZE], int row_start, int col_start, int dr, int dc) {
    int r = row_start;
    int c = col_start;
    for (int k = 0; k < SHIP_SIZE; k++) {
        board[r][c] = 3;
        r += dr; c += dc;
    }
}

/* Constroi uma matriz em forma de cone apontando para baixo.
 * Para size impar (ex: 5), usamos centro = size/2. O topo do cone
 * fica na linha 0 e se expandem nas linhas abaixo.
 */
void build_cone(int size, int cone[size][size]) {
    int center = size / 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Condicional: posicao afetada se abs(j - center) <= i
            if (abs(j - center) <= i) cone[i][j] = 1; else cone[i][j] = 0;
        }
    }
}

/* Constroi uma matriz em forma de cruz com o ponto de origem no centro */
void build_cross(int size, int cross[size][size]) {
    int center = size / 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == center || j == center) cross[i][j] = 1; else cross[i][j] = 0;
        }
    }
}

/* Constroi uma matriz que representa a vista frontal de um octaedro (um losango/diamante)
 * Utilizamos a condicao abs(i-center) + abs(j-center) <= center
 */
void build_octahedron(int size, int oct[size][size]) {
    int center = size / 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (abs(i - center) + abs(j - center) <= center) oct[i][j] = 1; else oct[i][j] = 0;
        }
    }
}

/* Sobrepoe a matriz de habilidade (skill) ao tabuleiro, centrando-a em origin_row/origin_col.
 * Regra de escrita: se a posicao do tabuleiro estiver vazia (0), substitui por 5.
 * Se ja houver um navio (3), mantemos 3 para evidenciar o navio (prioridade visual ao navio).
 */
void overlay_skill(int board[BOARD_SIZE][BOARD_SIZE], int skill_size, int skill[][skill_size], int origin_row, int origin_col) {
    int center = skill_size / 2; // deslocamento do centro da skill

    for (int i = 0; i < skill_size; i++) {
        for (int j = 0; j < skill_size; j++) {
            if (skill[i][j] == 1) {
                int board_r = origin_row + (i - center);
                int board_c = origin_col + (j - center);
                if (board_r >= 0 && board_r < BOARD_SIZE && board_c >= 0 && board_c < BOARD_SIZE) {
                    if (board[board_r][board_c] == 0) {
                        board[board_r][board_c] = 5; // marca area afetada
                    }
                    // se houver navio (3), mantemos 3 (para nao "apagar" navio)
                }
            }
        }
    }
}
