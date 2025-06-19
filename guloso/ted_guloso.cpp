#include "ted_guloso.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <random>
#include <sstream>
using namespace std;
using namespace chrono;

GulosoNode::GulosoNode(int l) : label(l) {}

int current_recursion_depth = 0;
int max_recursion_depth = 0;

int greedy_ted(GulosoNode* t1, GulosoNode* t2) {
    current_recursion_depth++;
    max_recursion_depth = max(max_recursion_depth, current_recursion_depth);

    if (!t1 && !t2) {
        current_recursion_depth--;
        return 0;
    }
    if (!t1) {
        int cost = 1;
        for (auto c : t2->children) cost += greedy_ted(nullptr, c);
        current_recursion_depth--;
        return cost;
    }
    if (!t2) {
        int cost = 1;
        for (auto c : t1->children) cost += greedy_ted(c, nullptr);
        current_recursion_depth--;
        return cost;
    }

    int cost = 0;
    if (t1->label != t2->label) {
        cost = 1;
    }

    int m = t1->children.size();
    int n = t2->children.size();
    int min_children = min(m, n);
    int total = cost;

    for (int i = 0; i < min_children; ++i) {
        total += greedy_ted(t1->children[i], t2->children[i]);
    }
    for (int i = min_children; i < m; ++i) {
        total += greedy_ted(t1->children[i], nullptr);
    }
    for (int i = min_children; i < n; ++i) {
        total += greedy_ted(nullptr, t2->children[i]);
    }

    current_recursion_depth--;
    return total;
}

GulosoNode* make_random_tree(int root_label, int num_nodes, int min_children, int max_children) {
    GulosoNode* root = new GulosoNode(root_label);
    vector<GulosoNode*> nodes = {root};
    int current_label = root_label + 1;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> child_dist(min_children, max_children);

    size_t index = 0;
    while (current_label < root_label + num_nodes) {
        if (index >= nodes.size()) break;
        GulosoNode* current = nodes[index++];
        int remaining = (root_label + num_nodes) - current_label;
        int num_children = min(child_dist(gen), remaining);
        for (int i = 0; i < num_children; ++i) {
            GulosoNode* child = new GulosoNode(current_label++);
            current->children.push_back(child);
            nodes.push_back(child);
        }
    }

    return root;
}

GulosoNode* parse_tree(const string& s, int& pos) {
    if (pos >= s.length())
        return nullptr;

    while (pos < s.length() && isspace(s[pos]))
        pos++;

    string label_str = "";
    while (pos < s.length() && !isspace(s[pos]) && s[pos] != '(' && s[pos] != ')') {
        label_str += s[pos];
        pos++;
    }
    if (label_str.empty())
        return nullptr;

    int label = stoi(label_str);
    GulosoNode* node = new GulosoNode(label);

    while (pos < s.length() && isspace(s[pos]))
        pos++;

    if (pos < s.length() && s[pos] == '(') {
        pos++;
        while (pos < s.length() && s[pos] != ')') {
            GulosoNode* child = parse_tree(s, pos);
            if (child != nullptr) {
                node->children.push_back(child);
            }
            while (pos < s.length() && isspace(s[pos]))
                pos++;
        }
        if (pos < s.length() && s[pos] == ')')
            pos++;
    }

    return node;
}

GulosoNode* parse_tree(const string& s) {
    int pos = 0;
    return parse_tree(s, pos);
}

void reset_metrics() {
    current_recursion_depth = 0;
    max_recursion_depth = 0;
}

void run_and_report(const string& title, GulosoNode* t1, GulosoNode* t2) {
    cout << "\n===== " << title << " =====\n";
    reset_metrics();

    auto start = high_resolution_clock::now();
    int cost = greedy_ted(t1, t2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Resultado TED: " << cost << endl;
    cout << "Tempo de execucao: " << duration.count() << " ms\n";
    cout << "Profundidade maxima da recursao (proxy para espaco): " << max_recursion_depth << endl;
}