#include <iostream>
#include <vector>
#include <string>

class Node {
public:
    std::string label;  // rótulo do nó
    int index;         // índice em pré-ordem
    std::vector<Node*> children;
    Node* leftmost;    // usado pela função recursiva O(n) leftmost()

    Node() : index(0), leftmost(nullptr) {
    }

    Node(std::string label) : label(label), index(0), leftmost(nullptr) {
    }
};
