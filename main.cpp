#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm> 
#include "cross.h"

#define MATRIX2_SIZE 50

void printMatrix(bool **M, int m) {
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < m; x++) {
            std::cout << M[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

Cross BigCross1(bool **M, int m) {
    Cross bigCross;

    for (int y = 0; y < m; y++) {
        for (int x = 0; x < m; x++) {
            if (M[y][x]) {
                bool cross = true;
                for (int size = 1;
                     y - size >= 0 && y + size < m && x - size >= 0 && x + size < m && cross;
                     size++) {
                    if (M[y - size][x] &&
                        M[y + size][x] &&
                        M[y][x - size] &&
                        M[y][x + size]) {
                            if (size > bigCross.size) {
                                bigCross.x = x;
                                bigCross.y = y;
                                bigCross.size = size;
                            }
                        }
                    else {
                        cross = false;
                    }
                }
            }
        }
    }

    return bigCross;
}

Cross BigCross2(bool **M, int m) {
    Cross bigCross;

    struct Length {
        int left = 0;
        int right = 0;
        int top = 0;
        int bottom = 0;
    };

    Length **M2 = new Length *[m];
    for (int i = 0; i < m; i++) {
        M2[i] = new Length[m];
    }

    for (int y = 0; y < m; y++) {

        for (int x = 0; x < m; x++) {

            // left length from top left direction
            M2[y][x].left = M[y][x] && x - 1 >= 0 ? M2[y][x - 1].left + 1 : M[y][x];

            // top length from top left direction
            M2[y][x].top = M[y][x] && y - 1 >= 0 ? M2[y - 1][x].top + 1 : M[y][x];

            // right length from bottom right direction
            M2[m - y - 1][m - x - 1].right = M[m - y - 1][m - x - 1] && x != 0 ? M2[m - y - 1][m - x].right + 1 : M[m - y - 1][m - x - 1];

            // bottom length from bottom right direction
            M2[m - y - 1][m - x - 1].bottom = M[m - y - 1][m - x - 1] && y != 0 ? M2[m - y][m - x - 1].bottom + 1 : M[m - y - 1][m - x - 1];

        }
    }

    // find the biggest cross within the new matrix
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < m; x++) {
            int size = std::min({ M2[y][x].left, M2[y][x].right, M2[y][x].top, M2[y][x].bottom }) - 1;
            if (size > bigCross.size) {
                bigCross.x = x;
                bigCross.y = y;
                bigCross.size = size;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        delete[] M2[i];
    }
    delete[] M2;

    return bigCross;
}

int main() {
    srand(time(0));

    bool **matrix1 = new bool *[15] { 
        new bool[15] { 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
        new bool[15] { 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1 },
        new bool[15] { 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 },
        new bool[15] { 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0 },
        new bool[15] { 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
        new bool[15] { 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
        new bool[15] { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
        new bool[15] { 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0 },
        new bool[15] { 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0 },
        new bool[15] { 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0 },
        new bool[15] { 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
        new bool[15] { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0 },
        new bool[15] { 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1 },
        new bool[15] { 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
        new bool[15] { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1 },
        };

    bool **matrix2 = new bool *[MATRIX2_SIZE];
    for (int i = 0; i < MATRIX2_SIZE; i++) {
        matrix2[i] = new bool[MATRIX2_SIZE];
        for (int j = 0; j < MATRIX2_SIZE; j++) {
            matrix2[i][j] = rand() % 2;
        }
    }

    // Matrix 1

    std::cout << "Matrix 1 (15 x 15)" << std::endl;
    printMatrix(matrix1, 15);

    std::cout << std::endl << "BigCross1" << std::endl;
    std::cout << BigCross1(matrix1, 15) << std::endl;

    std::cout << std::endl << "BigCross2" << std::endl;
    std::cout << BigCross2(matrix1, 15) << std::endl << std::endl;

    // Matrix 2

    std::cout << "Matrix 2 (" << MATRIX2_SIZE << " x " << MATRIX2_SIZE << ")" << std::endl;
    printMatrix(matrix2, MATRIX2_SIZE);

    std::cout << std::endl << "BigCross1" << std::endl;
    std::cout << BigCross1(matrix2, MATRIX2_SIZE) << std::endl;

    std::cout << std::endl << "BigCross2" << std::endl;
    std::cout << BigCross2(matrix2, MATRIX2_SIZE) << std::endl;

    // -----

    for (int i = 0; i < 15; i++) {
        delete[] matrix1[i];
    }
    delete[] matrix1;

    for (int i = 0; i < MATRIX2_SIZE; i++) {
        delete[] matrix2[i];
    }
    delete[] matrix2;
}