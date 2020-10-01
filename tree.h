// tree.h

struct Point {
    int x;
    int y;
};

struct Tree {
    Point point;
    Tree *left;
    Tree *right;

    void insert(const Point p) {
        if (this->point.x > p.x) {
            if (this->left) {
                this->left->insert(p);
            } else {
                Tree *newLeft = new Tree { .point = p };
                this->left = newLeft;
            }
        }

        else {
            if (this->right) {
                this->right->insert(p);
            } else {
                Tree *newRight = new Tree { .point = p };
                this->right = newRight;
            }
        }
    }
};