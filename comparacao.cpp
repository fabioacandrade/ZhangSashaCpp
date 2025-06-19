#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <functional>
#include <random>
#include <algorithm>
#include "zhangshasha/Tree.h"
#include "guloso/ted_guloso.h"

using namespace std;
using namespace chrono;

// Função para contar vértices em uma árvore Zhang-Shasha
int count_vertices(Tree &t) {
    t.traverse();
    return t.labels.size();
}

// Função para contar vértices em uma árvore gulosa
int count_vertices_guloso(GulosoNode* n) {
    if (!n) return 0;
    int total = 1;
    for (auto c : n->children) total += count_vertices_guloso(c);
    return total;
}

// Função adaptadora para Zhang-Shasha
int run_zhangshasha(const string &s1, const string &s2, int &v1, int &v2, int &dist, long long &ms) {
    Tree t1(s1), t2(s2);
    v1 = count_vertices(t1);
    v2 = count_vertices(t2);
    auto start = high_resolution_clock::now();
    dist = Tree::ZhangShasha(t1, t2);
    auto end = high_resolution_clock::now();
    ms = duration_cast<milliseconds>(end - start).count();
    return dist;
}

// Função para converter string de rótulos para int (apenas dígitos)
std::string convert_labels_to_int(const std::string& s) {
    std::string out;
    int label = 1;
    for (char c : s) {
        if (isalpha(c)) {
            out += std::to_string(label++);
        } else {
            out += c;
        }
    }
    return out;
}

// Função adaptadora para Guloso
int run_guloso(const string &s1, const string &s2, int &v1, int &v2, int &dist, double &micros) {
    std::string s1int = convert_labels_to_int(s1);
    std::string s2int = convert_labels_to_int(s2);
    GulosoNode* t1 = parse_tree(s1int);
    GulosoNode* t2 = parse_tree(s2int);
    v1 = count_vertices_guloso(t1);
    v2 = count_vertices_guloso(t2);
    auto start = high_resolution_clock::now();
    dist = greedy_ted(t1, t2);
    auto end = high_resolution_clock::now();
    micros = std::chrono::duration<double, std::micro>(end - start).count();
    return dist;
}

// Função para gerar árvore balanceada com rótulos customizáveis e label inicial
std::string gerar_arvore_custom(int n, int max_children, std::function<std::string(int)> rotulo_fn, int label_start = 1) {
    std::function<std::string(int&, int)> rec = [&](int& label, int n) -> std::string {
        if (n <= 0) return "";
        std::string root = rotulo_fn(label++);
        if (n == 1) return root;
        int filhos = std::min(max_children, n - 1);
        int restantes = n - 1;
        std::vector<int> filhos_sizes(filhos, restantes / filhos);
        for (int i = 0; i < restantes % filhos; ++i) filhos_sizes[i]++;
        std::string s = root + "(";
        for (int i = 0; i < filhos; ++i) {
            s += rec(label, filhos_sizes[i]);
            if (i < filhos - 1) s += " ";
        }
        s += ")";
        return s;
    };
    int label = label_start;
    return rec(label, n);
}

// Função para gerar árvore balanceada a partir de uma lista de rótulos
std::string gerar_arvore_com_rotulos(const std::vector<std::string>& rotulos, int max_children) {
    std::function<std::string(int, int)> rec = [&](int start, int n) -> std::string {
        if (n <= 0) return "";
        std::string root = rotulos[start];
        if (n == 1) return root;
        int filhos = std::min(max_children, n - 1);
        int restantes = n - 1;
        std::vector<int> filhos_sizes(filhos, restantes / filhos);
        for (int i = 0; i < restantes % filhos; ++i) filhos_sizes[i]++;
        std::string s = root + "(";
        int idx = start + 1;
        for (int i = 0; i < filhos; ++i) {
            s += rec(idx, filhos_sizes[i]);
            idx += filhos_sizes[i];
            if (i < filhos - 1) s += " ";
        }
        s += ")";
        return s;
    };
    return rec(0, rotulos.size());
}

// Realiza pequenas mutações em um vetor de rótulos: swap, remoção, adição
void mutar_rotulos(std::vector<std::string>& rotulos, std::mt19937& g) {
    std::uniform_int_distribution<> dist(0, rotulos.size() - 1);
    // Swap de dois rótulos
    if (rotulos.size() > 2) {
        int i = dist(g), j = dist(g);
        if (i != j) std::swap(rotulos[i], rotulos[j]);
    }
    // Remoção de um rótulo (com 30% de chance)
    if (rotulos.size() > 3 && (g() % 10 < 3)) {
        int idx = dist(g);
        rotulos.erase(rotulos.begin() + idx);
    }
    // Adição de um novo rótulo (com 30% de chance)
    if (g() % 10 < 3) {
        int idx = dist(g);
        rotulos.insert(rotulos.begin() + idx, "z" + std::to_string(g() % 10000));
    }
}

// Move subárvore (bloco de rótulos) para outra posição
void mover_subarvore(std::vector<std::string>& rotulos, std::mt19937& g) {
    if (rotulos.size() < 4) return;
    std::uniform_int_distribution<> dist(0, rotulos.size() - 2);
    int start = dist(g);
    int len = 1 + g() % std::min(10, (int)rotulos.size() - start); // tamanho do bloco
    int end = std::min((int)rotulos.size(), start + len);
    std::vector<std::string> bloco(rotulos.begin() + start, rotulos.begin() + end);
    rotulos.erase(rotulos.begin() + start, rotulos.begin() + end);
    int insert_at = g() % (rotulos.size() + 1);
    rotulos.insert(rotulos.begin() + insert_at, bloco.begin(), bloco.end());
}

void comparar_interativo() {
    std::cout << "\nComparacao interativa Zhang-Shasha x Guloso" << std::endl;
    std::cout << "Digite 0 para sair a qualquer momento.\n";
    std::random_device rd;
    std::mt19937 g(rd());
    while (true) {
        int n1, n2, maxc1, maxc2;
        std::cout << "\nNumero de vertices da arvore 1: ";
        std::cin >> n1;
        if (n1 <= 0) break;
        std::cout << "Numero maximo de filhos da arvore 1: ";
        std::cin >> maxc1;
        if (maxc1 <= 0) break;
        std::cout << "Numero de vertices da arvore 2: ";
        std::cin >> n2;
        if (n2 <= 0) break;
        std::cout << "Numero maximo de filhos da arvore 2: ";
        std::cin >> maxc2;
        if (maxc2 <= 0) break;

        // Gera rótulos base compartilhados
        int n_shared = std::min(n1, n2);
        std::vector<std::string> rotulos_shared;
        for (int i = 1; i <= n_shared; ++i) rotulos_shared.push_back("a" + std::to_string(i));
        // Rótulos exclusivos de cada árvore
        std::vector<std::string> rotulos1 = rotulos_shared;
        std::vector<std::string> rotulos2 = rotulos_shared;
        for (int i = n_shared + 1; i <= n1; ++i) rotulos1.push_back("x" + std::to_string(i));
        for (int i = n_shared + 1; i <= n2; ++i) rotulos2.push_back("y" + std::to_string(i));
        // Embaralha levemente os rótulos compartilhados da árvore 2
        std::random_device rd2;
        std::mt19937 g2(rd2());
        for (int i = 0; i < n_shared / 10 + 1; ++i) {
            int a = g2() % n_shared;
            int b = g2() % n_shared;
            if (a != b) std::swap(rotulos2[a], rotulos2[b]);
        }
        // Move subárvores inteiras algumas vezes
        for (int i = 0; i < std::max(1, n_shared / 20); ++i) {
            mover_subarvore(rotulos2, g2);
        }
        // Gera as strings das árvores
        std::string arv1_letras = gerar_arvore_com_rotulos(rotulos1, maxc1);
        std::string arv2_letras = gerar_arvore_com_rotulos(rotulos2, maxc2);
        // Para Guloso, converte para números
        auto rotulo_num = [](const std::string& s) {
            std::string out;
            for (char c : s) if (isdigit(c)) out += c;
            return out.empty() ? "1" : out;
        };
        std::vector<std::string> rotulos1_num, rotulos2_num;
        for (auto& s : rotulos1) rotulos1_num.push_back(rotulo_num(s));
        for (auto& s : rotulos2) rotulos2_num.push_back(rotulo_num(s));
        std::string arv1_num = gerar_arvore_com_rotulos(rotulos1_num, maxc1);
        std::string arv2_num = gerar_arvore_com_rotulos(rotulos2_num, maxc2);

        int v1, v2, dist;
        double micros;
        std::cout << "\n| Algoritmo     | Vertices1 | Vertices2 | Distancia | Tempo (us)  |" << std::endl;
        std::cout <<   "|---------------|-----------|-----------|-----------|-------------|" << std::endl;
        // Zhang-Shasha
        {
            long long ms_ll;
            run_zhangshasha(arv1_letras, arv2_letras, v1, v2, dist, ms_ll);
            std::cout << "| Zhang-Shasha  | " << std::setw(9) << v1 << " | " << std::setw(9) << v2 << " | " << std::setw(9) << dist << " | " << std::setw(11) << ms_ll * 1000 << " |" << std::endl;
        }
        // Guloso
        {
            run_guloso(arv1_num, arv2_num, v1, v2, dist, micros);
            std::cout << "| Guloso        | " << std::setw(9) << v1 << " | " << std::setw(9) << v2 << " | " << std::setw(9) << dist << " | " << std::setw(11) << std::fixed << std::setprecision(2) << micros << " |" << std::endl;
        }
    }
    std::cout << "\nEncerrando comparacao interativa.\n";
}

int main() {
    comparar_interativo();
    return 0;
}
