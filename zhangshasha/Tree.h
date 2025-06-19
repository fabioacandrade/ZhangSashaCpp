#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include "Node.h"

class Tree {
public:
    Node *root;
    std::vector<int> l;
    std::vector<int> keyroots;
    std::vector<std::string> labels;
    static std::vector<std::vector<int>> TD;

    Tree(std::string s);
    void traverse();
    void index();
    void l_func();
    void keyroots_func();
    static int ZhangShasha(Tree &tree1, Tree &tree2);

private:
    Node *parseTree(const std::string &s, int &pos);
    std::vector<std::string> &traverse_postorder(Node *node, std::vector<std::string> &labels);
    int index_postorder(Node *node, int &idx);
    void l_postorder(Node *node, std::vector<int> &l_vec);
    void leftmost();
    void leftmost_postorder(Node *node);
    static int treedist(std::vector<int> &l1, std::vector<int> &l2, int i, int j, Tree &tree1, Tree &tree2);
};

#endif 
