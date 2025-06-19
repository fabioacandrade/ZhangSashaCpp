// main.cpp para o algoritmo guloso
#include "ted_guloso.h"
#include <iostream>
#include <vector>
#include <string>

// Função adaptadora para interface igual à do main
int ted_guloso(const std::string& s1, const std::string& s2) {
    GulosoNode* t1 = parse_tree(s1);
    GulosoNode* t2 = parse_tree(s2);
    return greedy_ted(t1, t2);
}

void run_test(const std::string &desc, const std::string &s1, const std::string &s2)
{
    int dist = ted_guloso(s1, s2);
    std::cout << desc << "\n";
    std::cout << "  Arvore 1: " << s1 << "\n";
    std::cout << "  Arvore 2: " << s2 << "\n";
    std::cout << "  Distancia (guloso): " << dist << "\n\n";
}

int main()
{
    std::cout << "==== Exemplos para o algoritmo guloso ====" << std::endl;
    run_test("Exemplo 1", "1(2(4 5) 3)", "1(3 2(4 5))");
    run_test("Exemplo 2", "1(2(4 5) 3(6 7(8)))", "1(2(4 5) 3(6 7(9)))");
    run_test("Exemplo 3", "1", "2(3)");
    return 0;
}
