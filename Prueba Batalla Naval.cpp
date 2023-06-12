#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 10
#define COLUMNAS 10

void imprimirTablero(char tablero[FILAS][COLUMNAS]) {
    printf("   ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%2d ", i);
        for (int j = 0; j < COLUMNAS; j++) {
            printf("|%c", tablero[i][j]);
        }
        printf("|\n");
    }
}

void imprimirGrafico(char tablero[FILAS][COLUMNAS]) {
    printf("\nGrafico de barcos:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == static_cast<char>(219)) {
                printf("|O");
            } else {
                printf("| ");
            }
        }
        printf("|\n");
    }
}

void imprimirTableroDisparos(char tablero[FILAS][COLUMNAS]) {
    printf("\nTablero de disparos:\n");
    printf("   ");
    for (int j = 0; j < COLUMNAS; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%2d ", i);
        for (int j = 0; j < COLUMNAS; j++) {
            printf("|%c", tablero[i][j]);
        }
        printf("|\n");
    }
}

void colocarBarcosUsuario(char tablero[FILAS][COLUMNAS]) {
    printf("Coloque sus barcos en el tablero.\n");

    int barcos[6][2] = {
        {2, 1}, {2, 1}, {2, 1},    // Barcos de 2x1
        {3, 1}, {3, 1},             // Barcos de 3x1
        {4, 1}                      // Barco de 4x1
    };

    for (int i = 0; i < 6; i++) {
        int fila, columna;
        int tamano = barcos[i][0];

        printf("Ingrese la fila inicial para el barco de tamano %dx1: ", tamano);
        scanf("%d", &fila);

        printf("Ingrese la columna inicial para el barco de tamano %dx1: ", tamano);
        scanf("%d", &columna);

        char orientacion;
        printf("Ingrese la orientacion (V para vertical, H para horizontal): ");
        scanf(" %c", &orientacion);

        if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
            printf("Coordenadas no válidas. Vuelva a intentarlo.\n");
            i--;
            continue;
        }

        int valido = 1;
        if (orientacion == 'V' || orientacion == 'v') {
            if (fila + tamano > FILAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila + j][columna] == static_cast<char>(219)) {
                        valido = 0;
                        break;
                    }
                }
            }
        } else if (orientacion == 'H' || orientacion == 'h') {
            if (columna + tamano > COLUMNAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila][columna + j] == static_cast<char>(254)) {
                        valido = 0;
                        break;
                    }
                }
            }
        } else {
            valido = 0;
        }

        if (!valido) {
            printf("Posición no válida. Vuelva a intentarlo.\n");
            i--;
            continue;
        }

        if (orientacion == 'V' || orientacion == 'v') {
            for (int j = 0; j < tamano; j++) {
                tablero[fila + j][columna] = static_cast<char>(219);
            }
        } else if (orientacion == 'H' || orientacion == 'h') {
            for (int j = 0; j < tamano; j++) {
                tablero[fila][columna + j] = static_cast<char>(254);
            }
        }

        imprimirGrafico(tablero);
    }
}

void colocarBarcosMaquina(char tablero[FILAS][COLUMNAS]) {
    int barcos[6][2] = {
        {2, 1}, {2, 1}, {2, 1},    // Barcos de 2x1
        {3, 1}, {3, 1},             // Barcos de 3x1
        {4, 1}                      // Barco de 4x1
    };

    srand(time(NULL));

    for (int i = 0; i < 6; i++) {
        int fila, columna;
        int tamano = barcos[i][0];

        fila = rand() % FILAS;
        columna = rand() % COLUMNAS;

        int orientacion = rand() % 2; // 0 para vertical, 1 para horizontal

        int valido = 1;
        if (orientacion == 0) {
            if (fila + tamano > FILAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila + j][columna] == static_cast<char>(219)) {
                        valido = 0;
                        break;
                    }
                }
            }
        } else if (orientacion == 1) {
            if (columna + tamano > COLUMNAS) {
                valido = 0;
            } else {
                for (int j = 0; j < tamano; j++) {
                    if (tablero[fila][columna + j] == static_cast<char>(219)) {
                        valido = 0;
                        break;
                    }
                }
            }
        }

        if (!valido) {
            i--;
            continue;
        }

        if (orientacion == 0) {
            for (int j = 0; j < tamano; j++) {
                tablero[fila + j][columna] = static_cast<char>(219);
            }
        } else if (orientacion == 1) {
            for (int j = 0; j < tamano; j++) {
                tablero[fila][columna + j] = static_cast<char>(219);
            }
        }
    }
}

int realizarDisparo(char tablero[FILAS][COLUMNAS], char tableroDisparos[FILAS][COLUMNAS], int fila, int columna) {
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        return 0; // Disparo fuera de los límites del tablero
    }

    if (tableroDisparos[fila][columna] != ' ') {
        return 0; // Ya se ha disparado en esta posición anteriormente
    }

    if (tablero[fila][columna] == static_cast<char>(219)) {
        tableroDisparos[fila][columna] = 'X'; // Disparo acertado
        return 1;
    } else {
        tableroDisparos[fila][columna] = 'O'; // Disparo fallido
        return -1;
    }
}

int main() {
    char tableroUsuario[FILAS][COLUMNAS];
    char tableroMaquina[FILAS][COLUMNAS];
    char tableroDisparosUsuario[FILAS][COLUMNAS];
    char tableroDisparosMaquina[FILAS][COLUMNAS];

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tableroUsuario[i][j] = ' ';
            tableroMaquina[i][j] = ' ';
            tableroDisparosUsuario[i][j] = ' ';
            tableroDisparosMaquina[i][j] = ' ';
        }
    }

    for (int i = 1; i < FILAS; i += 2) {
        for (int j = 0; j < COLUMNAS; j++) {
            tableroUsuario[i][j] = '-';
            tableroMaquina[i][j] = '-';
        }
    }

    colocarBarcosUsuario(tableroUsuario);
    colocarBarcosMaquina(tableroMaquina);

    printf("\nTablero del usuario:\n");
    imprimirTablero(tableroUsuario);

    printf("\nTablero de disparos del usuario:\n");
    imprimirTableroDisparos(tableroDisparosUsuario);

    // Comienza el juego
    int barcosUsuario = 6;
    int barcosMaquina = 6;
    int turno = 0; // 0 para el usuario, 1 para la máquina

    while (barcosUsuario > 0 && barcosMaquina > 0) {
        int fila, columna;

        if (turno == 0) {
            printf("\nTurno del usuario:\n");
            printf("Ingrese la fila para el disparo: ");
            scanf("%d", &fila);

            printf("Ingrese la columna para el disparo: ");
            scanf("%d", &columna);

            int resultado = realizarDisparo(tableroMaquina, tableroDisparosUsuario, fila, columna);
            if (resultado == 1) {
                printf("¡Has acertado un barco!\n");
                barcosMaquina--;
            } else if (resultado == -1) {
                printf("Has disparado al agua.\n");
            } else {
                printf("Disparo inválido. Vuelve a intentarlo.\n");
                continue;
            }

            printf("\nTablero de disparos del usuario:\n");
            imprimirTableroDisparos(tableroDisparosUsuario);
        } else {
            printf("\nTurno de la máquina:\n");
            fila = rand() % FILAS;
            columna = rand() % COLUMNAS;

            int resultado = realizarDisparo(tableroUsuario, tableroDisparosMaquina, fila, columna);
            if (resultado == 1) {
                printf("La máquina ha acertado un barco.\n");
                barcosUsuario--;
            } else if (resultado == -1) {
                printf("La máquina ha disparado al agua.\n");
            }

            printf("\nTablero de disparos de la máquina:\n");
            imprimirTableroDisparos(tableroDisparosMaquina);
        }

        turno = (turno + 1) % 2;
    }

    if (barcosUsuario == 0) {
        printf("¡Has ganado! Has hundido todos los barcos de la máquina.\n");
    } else {
        printf("¡Has perdido! La máquina ha hundido todos tus barcos.\n");
    }

    return 0;
}

