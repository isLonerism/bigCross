#include <iostream>
#include <time.h>
#include "node.h"

#define CHANCE_SNAKE 0.5
#define CHANCE_NULL 0.01
#define CHANCE_LOOP_START 0.015
#define CHANCE_LOOP_END 0.02
#define VALUE_RANGE 100

#define chance(chance) !(rand() % (int)(1 / chance))
#define getValue() (rand() % VALUE_RANGE)

// Method 1
Node generateList() {

    // Init list head
    Node head = { .value = getValue(), .next = nullptr };
    Node *currentNode = &head;

    // Fills list until luck runs out
    auto fill = [](Node** currentNode, float terminationChance) {
        while (!chance(terminationChance)) {
            Node *nextNode = new Node { .value = getValue(), .next = nullptr };
            (*currentNode)->next = nextNode;
            (*currentNode) = (*currentNode)->next;
        }
    };

    // Snake
    if (chance(CHANCE_SNAKE)) {
        fill(&currentNode, CHANCE_NULL);
    }

    // Snail
    else {
        fill(&currentNode, CHANCE_LOOP_START);
        Node *loopStart = currentNode;

        fill(&currentNode, CHANCE_LOOP_END);
        currentNode->next = loopStart;
    }
    
    return head;
}

int main() {
    srand(time(0));

    Node node = generateList();
    while (node.next) {
        std::cout << node.value << " ";
        node = *node.next;
    }
    std::cout << node.value << " ";

    return 0;
}