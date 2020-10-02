#include <iostream>
#include <bits/stdc++.h>
#include "tree.h"

#define VALUE_RANGE 100
#define POINTS_AMOUNT 1000

Tree* BuildTree(Tree *t) {

    // generate random points
    bool points[VALUE_RANGE * VALUE_RANGE] = { false };
    std::fill(points, points + (POINTS_AMOUNT * sizeof(bool)), true);
    std::random_shuffle(points, points + (VALUE_RANGE * VALUE_RANGE));

    // build tree root from first point
    int index = -1;
    while (!points[++index]);
    t = new Tree { .point = { .x = index % VALUE_RANGE, .y = index / VALUE_RANGE }, .left = nullptr, .right = nullptr };

    // insert all points
    while (++index < VALUE_RANGE * VALUE_RANGE) {
        if (points[index]) {
            t = AVL::insert(t, { .x = index % VALUE_RANGE, .y = index / VALUE_RANGE });
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

int main() {
    
    srand(time(0));

    // build random tree
    Tree *pRoot = nullptr;
    pRoot = BuildTree(pRoot);

    // find nearest right point
    Point ans = NearestRightPoint(pRoot, 25);
    std::cout << ans;

    return 1;
}