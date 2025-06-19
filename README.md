# Algoritmo de Zhang-Shasha em C++

Implementação do algoritmo de Zhang-Shasha para calcular a distância de edição entre árvores ordenadas em C++.

## Descrição

O algoritmo de Zhang-Shasha calcula a menor quantidade de operações necessárias para transformar uma árvore ordenada em outra, usando três operações básicas:
- **Inserção** de um nó (custo: 1)
- **Remoção** de um nó (custo: 1)
- **Substituição** de um rótulo (custo: 1)

A implementação segue fielmente o artigo original, utilizando pós-ordem para indexação dos nós e cálculo dos vetores auxiliares (`l`, `keyroots`, `labels`).

## Estrutura do Projeto

```
├── Node.cpp      # Classe que representa um nó da árvore
├── Tree.cpp      # Classe principal com o algoritmo Zhang-Shasha
├── main.cpp      # Programa principal com exemplos de teste
└── README.md     # Este arquivo
```

## Como Compilar e Executar

### Windows (PowerShell ou CMD)

```
g++ -o zhang_shasha main.cpp Tree.cpp Node.cpp -std=c++11
./zhang_shasha.exe
```

## Formato de Entrada

As árvores são representadas em notação pré-ordem usando parênteses e podem conter espaços:
- `f(d(a c(b)) e)` - árvore com raiz 'f', filhos 'd' e 'e', onde 'd' tem filhos 'a' e 'c', e 'c' tem filho 'b'
- `d` - árvore com apenas um nó 'd'

## Exemplos de Teste

O programa inclui exemplos de teste no arquivo `main.cpp`, como:

```
==== Exemplos Simples do Artigo ====
Exemplo 1 (artigo)
  Arvore 1: f(d(a c(b)) e)
  Arvore 2: f(c(d(a b)) e)
  Esperado: 2; Obtido: 2

Exemplo 2
  Arvore 1: a(b(c d) e(f g(i)))
  Arvore 2: a(b(c d) e(f g(h)))
  Esperado: 1; Obtido: 1

Exemplo 3
  Arvore 1: d
  Arvore 2: g(h)
  Esperado: 2; Obtido: 2
```

## Saída Esperada

O programa imprime para cada teste:
```
Descricao do teste
  Arvore 1: ...
  Arvore 2: ...
  Esperado: X; Obtido: Y
```

## Complexidade

- **Tempo**: O(|T1| × |T2| × min(profundidade(T1), folhas(T1)) × min(profundidade(T2), folhas(T2)))
- **Espaço**: O(|T1| × |T2|)

Onde |T1| e |T2| são os números de nós nas árvores T1 e T2.

## Referência

Zhang, K., & Shasha, D. (1989). Simple fast algorithms for the editing distance between trees and related problems. SIAM journal on computing, 18(6), 1245-1262.