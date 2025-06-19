#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include "Node.cpp"

class Tree {
public:
    Node* root;
    // função l() que retorna o filho mais à esquerda
    std::vector<int> l;
    // lista de keyroots, ou seja, nós com filho esquerdo e a raiz da árvore
    std::vector<int> keyroots;
    // lista dos rótulos dos nós usada para comparação de nós
    std::vector<std::string> labels;

    static std::vector<std::vector<int>> TD;

    // Parser simples para notação de árvore como "f(d(a c(b)) e)"
    Tree(std::string s) {
        root = new Node();
        int pos = 0;
        root = parseTree(s, pos);
    }

private:
    Node* parseTree(const std::string& s, int& pos) {
        if (pos >= s.length()) return nullptr;
          Node* node = new Node();
        
        // Pula espaços em branco
        while (pos < s.length() && s[pos] == ' ') pos++;
        
        // Lê o rótulo
        std::string label = "";
        while (pos < s.length() && s[pos] != '(' && s[pos] != ')' && s[pos] != ' ') {
            label += s[pos];
            pos++;
        }
        node->label = label;
        
        // Pula espaços em branco
        while (pos < s.length() && s[pos] == ' ') pos++;
        
        // Verifica se há filhos
        if (pos < s.length() && s[pos] == '(') {
            pos++; // Pula '('
            
            while (pos < s.length() && s[pos] != ')') {
                while (pos < s.length() && s[pos] == ' ') pos++; // Pula espaços em branco
                if (pos < s.length() && s[pos] != ')') {
                    Node* child = parseTree(s, pos);
                    if (child != nullptr) {
                        node->children.push_back(child);
                    }
                }
            }
            
            if (pos < s.length() && s[pos] == ')') {
                pos++; // Pula ')'
            }
        }
        
        return node;
    }

public:    void traverse() {
        // monta uma lista ordenada dos rótulos dos nós da árvore
        labels.clear();
        traverse(root, labels);
    }

private:
    std::vector<std::string>& traverse(Node* node, std::vector<std::string>& labels) {
        for (int i = 0; i < node->children.size(); i++) {
            labels = traverse(node->children[i], labels);
        }
        labels.push_back(node->label);
        return labels;
    }

public:    void index() {
        // indexa cada nó na árvore de acordo com o método de travessia
        index(root, 0);
    }

private:
    int index(Node* node, int index) {
        for (int i = 0; i < node->children.size(); i++) {
            index = this->index(node->children[i], index);
        }
        index++;
        node->index = index;
        return index;
    }

public:    void l_func() {
        // monta uma função que retorna l()
        leftmost();
        l.clear();
        l = l_helper(root, std::vector<int>());
    }

private:
    std::vector<int> l_helper(Node* node, std::vector<int> l_vec) {
        for (int i = 0; i < node->children.size(); i++) {
            l_vec = l_helper(node->children[i], l_vec);
        }
        l_vec.push_back(node->leftmost->index);
        return l_vec;
    }

    void leftmost() {
        leftmost(root);
    }

    void leftmost(Node* node) {
        if (node == nullptr)
            return;
        for (int i = 0; i < node->children.size(); i++) {
            leftmost(node->children[i]);
        }
        if (node->children.size() == 0) {
            node->leftmost = node;
        } else {
            node->leftmost = node->children[0]->leftmost;
        }
    }

public:    void keyroots_func() {
        // calcula os keyroots
        keyroots.clear();
        for (int i = 0; i < l.size(); i++) {
            int flag = 0;
            for (int j = i + 1; j < l.size(); j++) {
                if (l[j] == l[i]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                this->keyroots.push_back(i + 1);
            }
        }
    }

    static int ZhangShasha(Tree& tree1, Tree& tree2) {
        tree1.index();
        tree1.l_func();
        tree1.keyroots_func();
        tree1.traverse();
        tree2.index();
        tree2.l_func();
        tree2.keyroots_func();
        tree2.traverse();

        std::vector<int>& l1 = tree1.l;
        std::vector<int>& keyroots1 = tree1.keyroots;
        std::vector<int>& l2 = tree2.l;
        std::vector<int>& keyroots2 = tree2.keyroots;        // complexidade espacial do algoritmo
        TD = std::vector<std::vector<int>>(l1.size() + 1, std::vector<int>(l2.size() + 1, 0));

        // resolve subproblemas
        for (int i1 = 1; i1 < keyroots1.size() + 1; i1++) {
            for (int j1 = 1; j1 < keyroots2.size() + 1; j1++) {
                int i = keyroots1[i1 - 1];
                int j = keyroots2[j1 - 1];
                TD[i][j] = treedist(l1, l2, i, j, tree1, tree2);
            }
        }

        return TD[l1.size()][l2.size()];
    }

private:
    static int treedist(std::vector<int>& l1, std::vector<int>& l2, int i, int j, Tree& tree1, Tree& tree2) {
        std::vector<std::vector<int>> forestdist(i + 1, std::vector<int>(j + 1, 0));        // custos das três operações atômicas
        int Delete = 1;
        int Insert = 1;
        int Relabel = 1;

        forestdist[0][0] = 0;
        for (int i1 = l1[i - 1]; i1 <= i; i1++) {
            forestdist[i1][0] = forestdist[i1 - 1][0] + Delete;
        }
        for (int j1 = l2[j - 1]; j1 <= j; j1++) {
            forestdist[0][j1] = forestdist[0][j1 - 1] + Insert;
        }
        for (int i1 = l1[i - 1]; i1 <= i; i1++) {
            for (int j1 = l2[j - 1]; j1 <= j; j1++) {
                int i_temp = (l1[i - 1] > i1 - 1) ? 0 : i1 - 1;
                int j_temp = (l2[j - 1] > j1 - 1) ? 0 : j1 - 1;
                if ((l1[i1 - 1] == l1[i - 1]) && (l2[j1 - 1] == l2[j - 1])) {

                    int Cost = (tree1.labels[i1 - 1] == tree2.labels[j1 - 1]) ? 0 : Relabel;
                    forestdist[i1][j1] = std::min(
                            std::min(forestdist[i_temp][j1] + Delete, forestdist[i1][j_temp] + Insert),
                            forestdist[i_temp][j_temp] + Cost);
                    TD[i1][j1] = forestdist[i1][j1];
                } else {
                    int i1_temp = l1[i1 - 1] - 1;
                    int j1_temp = l2[j1 - 1] - 1;

                    int i_temp2 = (l1[i - 1] > i1_temp) ? 0 : i1_temp;
                    int j_temp2 = (l2[j - 1] > j1_temp) ? 0 : j1_temp;

                    forestdist[i1][j1] = std::min(
                            std::min(forestdist[i_temp][j1] + Delete, forestdist[i1][j_temp] + Insert),
                            forestdist[i_temp2][j_temp2] + TD[i1][j1]);
                }
            }
        }
        return forestdist[i][j];
    }
};

std::vector<std::vector<int>> Tree::TD;
