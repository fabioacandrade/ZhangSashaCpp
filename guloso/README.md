# Algoritmo Guloso para Distância entre Árvores

Este diretório contém a implementação do algoritmo guloso para calcular a distância de edição entre árvores ordenadas.

## Arquivos
- `ted_guloso.cpp`, `ted_guloso.h`: Implementação do algoritmo guloso e funções auxiliares.

## Uso
Este módulo é utilizado como parte do comparador principal (`comparacao.cpp`). Não há mais um arquivo `main.cpp` de testes nesta pasta.

Para compilar como biblioteca:
```
g++ -c ted_guloso.cpp -std=c++11
```
Inclua o objeto ao compilar o comparador.

## Observação
O algoritmo guloso é uma aproximação e pode não encontrar sempre a menor distância possível, mas é eficiente para grandes árvores.
