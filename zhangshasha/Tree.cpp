#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>
#include "Tree.h"
#include "Node.h"

// Construtor: recebe uma string na notação e monta a árvore
// Exemplo de notação: "f(d(a c(b)) e)"
Tree::Tree(std::string s)
{
    int pos = 0;
    root = parseTree(s, pos);
}

// Função pra construir a árvore
Node *Tree::parseTree(const std::string &s, int &pos)
{
    if (pos >= s.length())
        return nullptr;
    Node *node = new Node();

    // Pula espaços em branco iniciais
    while (pos < s.length() && s[pos] == ' ')
        pos++;

    // Lê o rótulo do nó
    std::string label = "";
    while (pos < s.length() && s[pos] != '(' && s[pos] != ')' && s[pos] != ' ')
    {
        label += s[pos];
        pos++;
    }
    node->label = label;

    // Pula espaços em branco após o rótulo
    while (pos < s.length() && s[pos] == ' ')
        pos++;

    // Verifica se há filhos
    if (pos < s.length() && s[pos] == '(')
    {
        pos++; // Pula '('
        while (pos < s.length() && s[pos] != ')')
        {
            while (pos < s.length() && s[pos] == ' ')
                pos++; // Pula espaços em branco
            if (pos < s.length() && s[pos] != ')')
            {
                Node *child = parseTree(s, pos);
                if (child != nullptr)
                {
                    node->children.push_back(child);
                }
            }
        }
        if (pos < s.length() && s[pos] == ')')
        {
            pos++; // Pula ')'
        }
    }
    return node;
}

// Preenche o vetor de rótulos dos nós em pós-ordem
void Tree::traverse()
{
    labels.clear();
    traverse_postorder(root, labels);
}

// Função auxiliar para travessia pós-ordem
std::vector<std::string> &Tree::traverse_postorder(Node *node, std::vector<std::string> &labels)
{
    if (!node)
        return labels;
    for (int i = 0; i < node->children.size(); i++) // percorre os filhos
    {
        labels = traverse_postorder(node->children[i], labels);
    }
    labels.push_back(node->label); // adiciona o rótulo
    return labels;
}

// Indexa cada nó da árvore em pós-ordem (atribui o campo index de cada nó)
void Tree::index()
{
    int idx = 0;
    index_postorder(root, idx);
}

// Função auxiliar para indexação pós-ordem
int Tree::index_postorder(Node *node, int &idx)
{
    if (!node)
        return idx;
    for (int i = 0; i < node->children.size(); i++)
    {
        index_postorder(node->children[i], idx);
    }
    node->index = ++idx;
    return idx;
}

// Preenche o vetor l (folha mais à esquerda) em pós-ordem
void Tree::l_func()
{
    leftmost();
    l.clear();
    l_postorder(root, l);
}

// Percorre a árvore em pós-ordem e adiciona ao vetor l_vec o índice do nó folha mais à esquerda de cada subárvore.
// Deve ser chamada após leftmost() para garantir que os ponteiros leftmost estejam corretos.
void Tree::l_postorder(Node *node, std::vector<int> &l_vec)
{
    if (!node)
        return;
    for (int i = 0; i < node->children.size(); i++)
    {
        l_postorder(node->children[i], l_vec);
    }
    l_vec.push_back(node->leftmost->index);
}

// Inicializa o cálculo dos ponteiros leftmost para todos os nós da árvore.
void Tree::leftmost()
{
    leftmost_postorder(root);
}

// Função recursiva que define o ponteiro leftmost de cada nó.
// Se o nó for folha, leftmost aponta para ele mesmo; caso contrário, aponta para o leftmost do primeiro filho.
void Tree::leftmost_postorder(Node *node)
{
    if (!node)
        return;
    for (int i = 0; i < node->children.size(); i++)
    {
        leftmost_postorder(node->children[i]);
    }
    if (node->children.size() == 0)
    {
        node->leftmost = node;
    }
    else
    {
        node->leftmost = node->children[0]->leftmost;
    }
}

// Preenche o vetor keyroots:
void Tree::keyroots_func()
{
    keyroots.clear();
    for (int i = 0; i < l.size(); i++)
    {
        bool found = false;
        for (int j = i + 1; j < l.size(); j++)
        {
            if (l[j] == l[i])
            {
                found = true; // se encontrar um índice posterior com o mesmo valor de l[i], não é um keyroot
                break;
            }
        }
        if (!found)
        {
            keyroots.push_back(i + 1); // +1 é necessario porque esta indexando os índices de 1 a n
        }
    }
}

int Tree::ZhangShasha(Tree &tree1, Tree &tree2)
{
    tree1.index(); // indexa postorder
    tree1.l_func(); // calcula leftmost de cada nó
    tree1.keyroots_func(); // calcula keyroots
    tree1.traverse(); // percorre a árvore para preencher o vetor labels
    tree2.index();
    tree2.l_func();
    tree2.keyroots_func();
    tree2.traverse();

    std::vector<int> &l1 = tree1.l;
    std::vector<int> &keyroots1 = tree1.keyroots;
    std::vector<int> &l2 = tree2.l;
    std::vector<int> &keyroots2 = tree2.keyroots;
    TD = std::vector<std::vector<int>>(l1.size() + 1, std::vector<int>(l2.size() + 1, 0)); // Somamos 1 para incluir o caso base (vazio)

    // Resolve subproblemas para todos os pares de keyroots
    for (int i1 = 1; i1 < keyroots1.size() + 1; i1++)
    {
        for (int j1 = 1; j1 < keyroots2.size() + 1; j1++)
        {
            int i = keyroots1[i1 - 1]; // keyroots1 e keyroots2 são indexados de 1 a n, então subtraímos 1 para acessar o vetor l
            int j = keyroots2[j1 - 1];
            TD[i][j] = treedist(l1, l2, i, j, tree1, tree2);
        }
    }
    return TD[l1.size()][l2.size()];
}

// Função que calcula a distância entre subárvores usando programação dinâmica
int Tree::treedist(std::vector<int> &l1, std::vector<int> &l2, int i, int j, Tree &tree1, Tree &tree2)
{
    int Delete = 1;  // custo de remoção
    int Insert = 1;  // custo de inserção
    int Relabel = 1; // custo de substituição

    std::vector<std::vector<int>> forestdist(i + 1, std::vector<int>(j + 1, 0));

    int i_start = l1[i - 1];
    int j_start = l2[j - 1];

    // Inicializa primeira linha e coluna
    forestdist[i_start - 1][j_start - 1] = 0;

    for (int i1 = i_start; i1 <= i; i1++)
        forestdist[i1][j_start - 1] = forestdist[i1 - 1][j_start - 1] + Delete; // Custo de transformar uma floresta com i1 nós em uma floresta vazia

    for (int j1 = j_start; j1 <= j; j1++)
        forestdist[i_start - 1][j1] = forestdist[i_start - 1][j1 - 1] + Insert; // Custo de transformar uma floresta vazia em uma floresta com j1 nós

    // Preenche matriz
    for (int i1 = i_start; i1 <= i; i1++)
    {
        for (int j1 = j_start; j1 <= j; j1++)
        {
            if (l1[i1 - 1] == i_start && l2[j1 - 1] == j_start) // Verifica se estamos na raiz
            {
                int cost = (tree1.labels[i1 - 1] == tree2.labels[j1 - 1]) ? 0 : Relabel; // Ve se os rótulos são iguais

                forestdist[i1][j1] = std::min({
                    forestdist[i1 - 1][j1] + Delete,  // Custo de remover o nó i1 da floresta de T1 (remoção)
                    forestdist[i1][j1 - 1] + Insert,  // Custo de inserir o nó j1 na floresta de T2 (inserção)
                    forestdist[i1 - 1][j1 - 1] + cost // Custo de substituir o nó i1 de T1 pelo nó j1 de T2 (substituição)
                });

                // Atualiza TD para subárvore completa
                TD[i1][j1] = forestdist[i1][j1];
            }
            else
            {
                forestdist[i1][j1] = std::min({
                    forestdist[i1 - 1][j1] + Delete,  // Custo de remover o nó i1 da floresta de T1 (remoção)
                    forestdist[i1][j1 - 1] + Insert,  // Custo de inserir o nó j1 na floresta de T2 (inserção)
                    forestdist[l1[i1 - 1] - 1][l2[j1 - 1] - 1] + TD[i1][j1] // Custo de transformar as subflorestas menores e somar o custo das subárvores enraizadas em i1 e j1
                });
            }
        }
    }

    return forestdist[i][j];
}

// Definição da variável estática apenas aqui
std::vector<std::vector<int>> Tree::TD = {};