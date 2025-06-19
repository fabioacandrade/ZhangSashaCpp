# Algoritmo de Zhang-Shasha em C++

Este diretório contém a implementação do algoritmo de Zhang-Shasha para calcular a distância de edição entre árvores ordenadas.

## Arquivos
- `Node.cpp`, `Node.h`: Estrutura de nó da árvore.
- `Tree.cpp`, `Tree.h`: Implementação do algoritmo de distância de edição.

## Uso
Este módulo é utilizado como parte do comparador principal (`comparacao.cpp`). Não há mais um arquivo `main.cpp` de testes nesta pasta.

Para compilar como biblioteca:
```
g++ -c Node.cpp Tree.cpp -std=c++11
```
Inclua os objetos ao compilar o comparador.

## Referência
Zhang, K., & Shasha, D. (1989). Simple fast algorithms for the editing distance between trees and related problems. SIAM journal on computing, 18(6), 1245-1262.