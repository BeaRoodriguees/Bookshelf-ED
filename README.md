# Livaria
Projeto para um sistema de alocação de livros.

## Estruturas
```c
typedef struct book{
    char *title;
    char *author;
    char *publisher;
    int edition;
    int ISBN;
    double width;
} Books;
```

# ORGANIZAR A ESTANTE
"Roberta está reorganizando suas estantes de livros. Ela pega os livros das prateleiras mais altas para as mais baixas, das estantes mais à esquerda para as estantes mais à direita. Assume-se que todos os livros têm a mesma profundidade. O formato da entrada dos livros considera que os caracteres '/' e '\', indicam respectivamente quando uma prateleira inicia e quando ela termina. Considere que cada estante com 90 cm tem no máximo 6 prateleiras. Imprima apenas uma string exibindo a sequência das prateleiras e estantes após o rearranjo."


## A Estante
As barras marcam o inicio e o fim de uma prateleirae a estante é uma HashTable, onde cada prateleira é uma lista encadeada. Cada livro é separado do outro por um ponto e vírgula (;).

    / As Crônicas de Roberta, Roberta Lopes, IC, 2023, 31244, 2.21; As Aventuras de Willy e Paes, Monitores de P1, IC, 2020, 31212, 4.72; Chuva de Bençãos: A Alegria de Calculo 2, Diego Chicuta, 2023, 546495, 3.55 \
    / Desconectado, Wifi, UFAL, 2012, 121112, 2.101; Já Pode Almoçar?, Alunos IC, 2023, 1257, 2.41 \
    / Socorro Deus!, Beatriz Rodrigues, 2023, 6132845, 6.1 \
    /\
    /\
    /\

## Ordenação
Critérios: 
 - Autor: Por Ordem alfabética
 - Altura: Da maior para a menor
