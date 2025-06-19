# Projeto de Comparação de Algoritmos de Distância de Edição entre Árvores

Este projeto implementa e compara dois algoritmos para calcular a distância de edição entre árvores ordenadas:
- **Zhang-Shasha** (algoritmo clássico)
- **Guloso** (aproximação)

## Como compilar e executar

Compile todos os arquivos necessários:

```
g++ -o comparacao comparacao.cpp zhangshasha/Tree.cpp zhangshasha/Node.cpp guloso/ted_guloso.cpp -std=c++11
```

Execute o comparador interativo:

```
./comparacao.exe
```

## Como usar

O programa irá pedir:
- Número de vértices da árvore 1
- Número máximo de filhos da árvore 1
- Número de vértices da árvore 2
- Número máximo de filhos da árvore 2

Ele irá gerar árvores aleatórias com rótulos compartilhados e diferenças estruturais, e mostrar a distância de edição calculada pelos dois algoritmos.

## Pastas
- `zhangshasha/` — implementação do algoritmo de Zhang-Shasha
- `guloso/` — implementação do algoritmo guloso

> **Atenção:** Os arquivos `main.cpp` das pastas `zhangshasha` e `guloso` não executam mais testes. Use apenas o `comparacao.cpp` para comparar os algoritmos.
