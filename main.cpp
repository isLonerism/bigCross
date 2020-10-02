#include <iostream>
#include <bits/stdc++.h>
#include "tree.h"

#define VALUE_RANGE 100
#define POINTS_AMOUNT 1000

Tree BuildTree() {

    // generate random points
    bool points[VALUE_RANGE * VALUE_RANGE] = { false };
    std::fill(points, points + (POINTS_AMOUNT * sizeof(bool)), true);
    std::random_shuffle(points, points + (VALUE_RANGE * VALUE_RANGE));

    // build tree root from first point
    int index = -1;
    while (!points[++index]);
    Tree root = { .point = { .x = index % VALUE_RANGE, .y = index / VALUE_RANGE } };
    Tree *pRoot = &root;

    // insert all points
    while (++index < VALUE_RANGE * VALUE_RANGE) {
        if (points[index]) {
            pRoot = AVL::insert(pRoot, { .x = index % VALUE_RANGE, .y = index / VALUE_RANGE });
        }
    }

    return root;
}

int main() {
    
    srand(time(0));

    Tree root = BuildTree();
    Tree *p = &root;

    while (p) {
        std::cout << "(" << p->point.x << ", " << p->point.y << ") ";
        p = p->right;
    }

    return 1;
}