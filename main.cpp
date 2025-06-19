#include <iostream>
#include "Tree.cpp"

int main() {
    // Árvores de exemplo (em pré-ordem).
    std::string tree1Str1 = "f(d(a c(b)) e)";
    std::string tree1Str2 = "f(c(d(a b)) e)";
    // Distância: 2 (exemplo principal usado no artigo de Zhang-Shasha)

    std::string tree1Str3 = "a(b(c d) e(f g(i)))";
    std::string tree1Str4 = "a(b(c d) e(f g(h)))";
    // Distância: 1

    std::string tree1Str5 = "d";
    std::string tree1Str6 = "g(h)";
    // Distância: 2

    Tree tree1(tree1Str1);
    Tree tree2(tree1Str2);

    Tree tree3(tree1Str3);
    Tree tree4(tree1Str4);

    Tree tree5(tree1Str5);
    Tree tree6(tree1Str6);

    int distance1 = Tree::ZhangShasha(tree1, tree2);
    std::cout << "Esperado 2; obtido " << distance1 << std::endl;

    int distance2 = Tree::ZhangShasha(tree3, tree4);
    std::cout << "Esperado 1; obtido " << distance2 << std::endl;

    int distance3 = Tree::ZhangShasha(tree5, tree6);
    std::cout << "Esperado 2; obtido " << distance3 << std::endl;

    // Novos casos
    std::string case1A = "a(b c)";
    std::string case1B = "a(c b)";
    // Distância esperada: 2 (troca de filhos)

    std::string case2A = "a(b(c d))";
    std::string case2B = "a(b(c d) e)";
    // Distância esperada: 1 (adição do nó 'e')

    std::string case3A = "a(b(c d) e)";
    std::string case3B = "x(b(c d) e)";
    // Distância esperada: 1 (substituição da raiz)

    std::string case4A = "a(b(d) c)";
    std::string case4B = "a(b c(d))";
    // Distância esperada: 2 (reorganização estrutural)

    std::string case5A = "a(b(c d) e)";
    std::string case5B = "a(b(d) e(f))";
    // Distância esperada: 2 (remoção e adição)

    std::string case6A = "a(b(c(d)))";
    std::string case6B = "a(b(c(e)))";
    // Distância esperada: 1 (substituição de folha)

    std::string case7A = "a(b(c d) e(f g))";
    std::string case7B = "a(b(d c) e(g f))";
    // Distância esperada: 4 (troca de ordem das folhas)

    std::string case8A = "a(b c(d e))";
    std::string case8B = "a(b(d e) c)";
    // Distância esperada: 2 (reorganização dos filhos)

    Tree t1(case1A), t2(case1B);
    Tree t3(case2A), t4(case2B);
    Tree t5(case3A), t6(case3B);
    Tree t7(case4A), t8(case4B);
    Tree t9(case5A), t10(case5B);
    Tree t11(case6A), t12(case6B);
    Tree t13(case7A), t14(case7B);
    Tree t15(case8A), t16(case8B);

    std::cout << "Esperado 2; obtido " << Tree::ZhangShasha(t1, t2) << std::endl;
    std::cout << "Esperado 1; obtido " << Tree::ZhangShasha(t3, t4) << std::endl;
    std::cout << "Esperado 1; obtido " << Tree::ZhangShasha(t5, t6) << std::endl;
    std::cout << "Esperado 2; obtido " << Tree::ZhangShasha(t7, t8) << std::endl;
    std::cout << "Esperado 2; obtido " << Tree::ZhangShasha(t9, t10) << std::endl;
    std::cout << "Esperado 1; obtido " << Tree::ZhangShasha(t11, t12) << std::endl;
    std::cout << "Esperado 4; obtido " << Tree::ZhangShasha(t13, t14) << std::endl;
    std::cout << "Esperado 2; obtido " << Tree::ZhangShasha(t15, t16) << std::endl;

    return 0;
}

