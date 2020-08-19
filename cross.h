// cross.h

#include <iostream>

struct Cross {
    int x = 0;
    int y = 0;
    int size = 0;

    friend std::ostream& operator<<(std::ostream& os, const Cross& cross);
};

std::ostream& operator<<(std::ostream& os, const Cross& cross) {
    os << "x: " << cross.x << "\ny: " << cross.y << "\nsize: " << cross.size;
    return os;
}