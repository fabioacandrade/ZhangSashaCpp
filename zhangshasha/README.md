# Algoritmo de Zhang-Shasha em C++

Implementação do algoritmo de Zhang-Shasha para calcular a distância de edição entre árvores ordenadas em C++.

> **Atenção:** Os testes foram removidos deste diretório. Use o programa `comparacao.cpp` na raiz do projeto para comparar os algoritmos.

## Estrutura do Diretório
- `Node.cpp`, `Node.h` — Nó da árvore
- `Tree.cpp`, `Tree.h` — Algoritmo principal
- `main.cpp` — (sem testes)

## Compilação (apenas para uso como biblioteca)

```
g++ -c Node.cpp Tree.cpp -std=c++11
```

Inclua os objetos ao compilar o comparador.

## Referência

Zhang, K., & Shasha, D. (1989). Simple fast algorithms for the editing distance between trees and related problems. SIAM journal on computing, 18(6), 1245-1262.