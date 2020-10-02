// tree.h

struct Point {
    int x;
    int y;
};

struct Tree {
    Point point;
    Tree *left;
    Tree *right;
};

class AVL {

    static Tree *rr_rotation(Tree *t) {
        Tree *right = t->right;
        t->right = right->left;
        right->left = t;

        return right;
    }

    static Tree *ll_rotation(Tree *t) {
        Tree *left = t->left;
        t->left = left->right;
        left->right = t;

        return left;
    }

    static Tree *lr_rotation(Tree *t) {
        Tree *left = t->left;
        t->left = rr_rotation(left);

        return ll_rotation(t);
    }

    static Tree *rl_rotation(Tree *t) {
        Tree *right = t->right;
        t->right = ll_rotation(right);

        return rr_rotation(t);
    }

    static int balanceFactor(Tree *t) {
        return height(t->left) - height(t->right);
    }

    static int height(Tree *t) {
        return t ? std::max(height(t->left), height(t->right)) + 1 : 0;
    }

    static Tree *balance(Tree *t) {
        int rootBalanceFactor = balanceFactor(t);

        if (rootBalanceFactor > 1) {
            if (balanceFactor(t->left) > 0) {
                t = ll_rotation(t);
            } else {
                t = lr_rotation(t);
            }
        } else if (rootBalanceFactor < -1) {
            if (balanceFactor(t->right) > 0) {
                t = rl_rotation(t);
            } else {
                t = rr_rotation(t);
            }
        }

        return t;
    }

    public:

    static Tree *insert(Tree *t, const Point p) {
        if (!t) {
            t = new Tree { .point = p, .left = nullptr, .right = nullptr };
        } else {
            if (t->point.x > p.x) {
                t->left = insert(t->left, p);
            } else {
                t->right = insert(t->right, p);
            }

            t = balance(t);
        }

        return t;
    }
};