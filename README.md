# Algoritmo de Zhang-Shasha em C++

Implementação do algoritmo de Zhang-Shasha para calcular a distância de edição entre árvores em C++.

## Descrição

O algoritmo de Zhang-Shasha é um método eficiente para calcular a distância mínima de edição entre duas árvores ordenadas. A distância é calculada usando três operações básicas:
- **Inserção** de um nó (custo: 1)
- **Remoção** de um nó (custo: 1) 
- **Substituição** de um rótulo (custo: 1)

## Estrutura do Projeto

```
├── Node.cpp      # Classe que representa um nó da árvore
├── Tree.cpp      # Classe principal com o algoritmo Zhang-Shasha
├── main.cpp      # Programa principal com exemplos de teste
├── compile.bat   # Script de compilação para Windows
└── README.md     # Este arquivo
```

## Como Compilar e Executar

### Opção 1: Usando o script (recomendado)
```bash
# No PowerShell ou CMD
.\compile.bat
```

### Opção 2: Compilação manual
```bash
g++ -o zhang_shasha main.cpp Tree.cpp Node.cpp -std=c++11
.\zhang_shasha.exe
```

## Formato de Entrada

As árvores são representadas em notação pré-ordem usando parênteses:
- `f(d(a c(b)) e)` - árvore com raiz 'f', filhos 'd' e 'e', onde 'd' tem filhos 'a' e 'c', e 'c' tem filho 'b'
- `d` - árvore com apenas um nó 'd'

## Exemplos de Teste

O programa inclui três casos de teste:

1. **Teste 1**: `f(d(a c(b)) e)` vs `f(c(d(a b)) e)`
   - Distância esperada: 2

2. **Teste 2**: `a(b(c d) e(f g(i)))` vs `a(b(c d) e(f g(h)))`
   - Distância esperada: 1

3. **Teste 3**: `d` vs `g(h)`
   - Distância esperada: 2

## Saída Esperada

```
Esperado 2; obtido 2
Esperado 1; obtido 1
Esperado 2; obtido 2
```

## Complexidade

- **Tempo**: O(|T1| × |T2| × min(profundidade(T1), folhas(T1)) × min(profundidade(T2), folhas(T2)))
- **Espaço**: O(|T1| × |T2|)

Onde |T1| e |T2| são os números de nós nas árvores T1 e T2.

## Referência

Zhang, K., & Shasha, D. (1989). Simple fast algorithms for the editing distance between trees and related problems. SIAM journal on computing, 18(6), 1245