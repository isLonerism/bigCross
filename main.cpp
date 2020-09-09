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
        for (Node::iterator it = (*currentNode); !chance(terminationChance); it++) {
            Node *nextNode = new Node { .value = getValue(), .next = nullptr };
            (*it).next = nextNode;
            (*currentNode) = &(*it);
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

// Method 2
Node* snakeOrSnail(Node *head) {

    Node::iterator slowPointer = head;
    Node::iterator fastPointer = ++slowPointer;

    do {
        if (fastPointer == nullptr || ++fastPointer == nullptr) {
            return nullptr;
        }
    } while (slowPointer++ != fastPointer++);

    (slowPointer = head)++;
    while (++slowPointer != ++fastPointer);

    return &(*slowPointer);
}

// Method 3
void printList(Node *head) {

    Node *loopStart = snakeOrSnail(head);
    Node::iterator it = head;
    int atStart = 0, listLength = 0, loopLength = 0;

    // Print node values
    std::cout << it;
    do {
        if (&(*++it) == loopStart && loopStart != nullptr) {
            std::cout << (++atStart == 1 ? " [ " + std::to_string((*it).value) : " ] ");
        } else {
            std::cout << " -> " << it;
        }
        
        listLength++;
        loopLength += (atStart == 1);
    } while (it != nullptr && atStart < 2);

    // Print metadata
    std::cout << "\n\n" << (loopStart ? "Snail" : "Snake") << " length: " << listLength << std::endl;
    std::cout << (loopLength ? "Loop length: " + std::to_string(loopLength) + "\n" : "");

}

int main() {
    srand(time(0));

    Node node = generateList();
    printList(&node);
}