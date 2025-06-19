#include "Node.h"

Node::Node() : index(0), leftmost(nullptr) {}

Node::Node(std::string label) : label(label), index(0), leftmost(nullptr) {}
