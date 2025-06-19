#include <iostream>
#include <vector>
#include <string>

class Node
{
public:
    // Rotulo
    std::string label;

    // Índice postorder
    int index;

    // Filhos deste nó
    std::vector<Node *> children;

    // Ponteiro para o nó folha mais à esquerda da subárvore enraizada neste nó
    Node *leftmost;

    Node() : index(0), leftmost(nullptr)
    {
    }

    Node(std::string label) : label(label), index(0), leftmost(nullptr)
    {
    }
};
