#ifndef TED_GULOSO_H
#define TED_GULOSO_H

#include <vector>
#include <string>

struct GulosoNode {
    int label;
    std::vector<GulosoNode*> children;
    GulosoNode(int l);
};

extern int current_recursion_depth;
extern int max_recursion_depth;

int greedy_ted(GulosoNode* t1, GulosoNode* t2);
GulosoNode* make_random_tree(int root_label, int num_nodes, int min_children = 0, int max_children = 5);
GulosoNode* parse_tree(const std::string& s, int& pos);
GulosoNode* parse_tree(const std::string& s);
void reset_metrics();
void run_and_report(const std::string& title, GulosoNode* t1, GulosoNode* t2);

#endif // TED_GULOSO_H
