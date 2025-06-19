#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
public:
    std::string label;
    int index;
    std::vector<Node *> children;
    Node *leftmost;

    Node();
    Node(std::string label);
};

#endif
