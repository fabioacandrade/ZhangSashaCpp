#include <iostream>
#include <vector>
#include <string>
#include "Tree.cpp"

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
    std::cout << "==== Exemplos Simples do Artigo ====" << std::endl;
    run_test("Exemplo 1 (artigo)", "f(d(a c(b)) e)", "f(c(d(a b)) e)", 2);
    run_test("Exemplo 2", "a(b(c d) e(f g(i)))", "a(b(c d) e(f g(h)))", 1);
    run_test("Exemplo 3", "d", "g(h)", 2);

    std::cout << "==== Insercao, Remocao e Substituicao ====" << std::endl;
    run_test("Adicao de no", "a(b(c d))", "a(b(c d) e)", 1);
    run_test("Remocao e adicao", "a(b(c d) e)", "a(b(d) e(f))", 2);
    run_test("Substituicao de raiz", "a(b(c d) e)", "x(b(c d) e)", 1);
    run_test("Substituicao de folha", "a(b(c(d)))", "a(b(c(e)))", 1);

    std::cout << "==== Exemplos Mais Complexos ====" << std::endl;
    run_test("Complexo 1", "a(b(c d(e f)) g(h))", "a(b(d c(f e)) g(h))", 4);
    run_test("Complexo 2", "a(b(c(d e(f))))", "a(b(c(f d(e))))", 3);

    return 0;
}
