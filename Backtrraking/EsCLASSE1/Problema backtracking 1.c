#include <stdio.h>

#define N 4 // Dimensione del labirinto

void stampa_soluzione(int soluzione[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", soluzione[i][j]);
        }
        printf("\n");
    }
}

int is_valid_move(int labirinto[N][N], int x, int y, int soluzione[N][N]) {
    return (x >= 0 && y >= 0 && x < N && y < N && labirinto[x][y] == 1 && soluzione[x][y] == 0);
}

int risolvi_labirinto(int labirinto[N][N], int x, int y, int soluzione[N][N]) {
    if (x == N-1 && y == N-1) {
        soluzione[x][y] = 1;
        return 1;
    }

    if (is_valid_move(labirinto, x, y, soluzione)) {
        soluzione[x][y] = 1;

        if (risolvi_labirinto(labirinto, x+1, y, soluzione) || risolvi_labirinto(labirinto, x, y+1, soluzione)) {
            return 1;
        }

        soluzione[x][y] = 0;
    }

    return 0;
}

int main() {
    int labirinto[N][N] = {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };

    int soluzione[N][N] = {0};

    if (risolvi_labirinto(labirinto, 0, 0, soluzione)) {
        stampa_soluzione(soluzione);
    } else {
        printf("Non esiste un percorso valido nel labirinto.\n");
    }

    return 0;
}
