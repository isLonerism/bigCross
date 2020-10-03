#include <iostream>
#include <bits/stdc++.h>
#include "tree.h"

#define MATRIX_X 200
#define MATRIX_Y 50
#define POINTS_AMOUNT 1000

Tree* BuildTree(Tree *t) {

    // generate random points
    bool points[MATRIX_X * MATRIX_Y] = { false };
    std::fill(points, points + (POINTS_AMOUNT * sizeof(bool)), true);
    std::random_shuffle(points, points + (MATRIX_X * MATRIX_Y));

    // build tree root from first point
    int index = -1;
    while (!points[++index]);
    t = new Tree { .point = { .x = index % MATRIX_X, .y = index / MATRIX_X }, .left = nullptr, .right = nullptr };

    // insert all points
    while (++index < MATRIX_X * MATRIX_Y) {
        if (points[index]) {
            t = AVL::insert(t, { .x = index % MATRIX_X, .y = index / MATRIX_X });
        }
    }

    return t;
}

Point NearestRightPoint(Tree *t, int x0) {
    Point nearest = { .x = 0, .y = 0 };
    Tree *p = t;

    while (p) {

        // if a new closest point is found
        if (p->point.x > x0 && (nearest.x == 0 || p->point.x < nearest.x)) {
            nearest = p->point;
        }

        // traverse AVL tree based on the current value
        if (p->point.x <= x0) {
            p = p->right;
        } else {
            p = p->left;
        }
    }

    return nearest;
}

void printMatrix(Tree *t, int x0) {
    Tree *p = t;
    bool matrix[MATRIX_Y][MATRIX_X] = { false };

    // fill matrix with points
    static void (*fill)(bool[MATRIX_Y][MATRIX_X], Tree*) = [](bool matrix[MATRIX_Y][MATRIX_X], Tree* t) {
        if (t) {
            matrix[t->point.y][t->point.x] = true;

            fill(matrix, t->right);
            fill(matrix, t->left);
        }
    };
    fill(matrix, p);

    // print matrix
    for (int i = 0; i < MATRIX_Y; i++) {
        for (int j = 0; j < MATRIX_X; j++) {
            std::cout << (j == x0 ? "|" : (matrix[i][j] ? "*" : " "));
        }
        std::cout << "\n";
    }
}

int main() {
    
    srand(time(0));
    int x0 = 45;

    // build random tree
    Tree *pRoot = nullptr;
    pRoot = BuildTree(pRoot);

    // display matrix
    printMatrix(pRoot, x0);

    // find nearest right point
    std::cout << NearestRightPoint(pRoot, x0);
}