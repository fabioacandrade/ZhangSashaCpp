#include <iostream>
#include <vector>
#include <string>
#include "Tree.h"

void run_test(const std::string &desc, const std::string &s1, const std::string &s2, int esperado)
{
    Tree t1(s1), t2(s2);
    int dist = Tree::ZhangShasha(t1, t2);
    std::cout << desc << "\n";
    std::cout << "  Arvore 1: " << s1 << "\n";
    std::cout << "  Arvore 2: " << s2 << "\n";
    std::cout << "  Esperado: " << esperado << "; Obtido: " << dist << "\n\n";
}

int main()
{
    std::cout << "Este executável não possui testes. Use comparacao.cpp para comparar os algoritmos." << std::endl;
    return 0;
}
