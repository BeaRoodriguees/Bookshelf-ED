# Livaria
Projeto para um sistema de alocação de livros.

## Estruturas
```c
typedef struct book{
    char *title;
    char *author;
    char *publisher;
    int edition;
    int IBMS;
} Books;

typedef struct bookshelf{
    Books book;
    int qnt_borrowed;
    int qnt_local;
}
```

## Funções
### 1 - Compra de Livro
- Pesquisar se o livro é novo ou já tem uma cópia na Livraria;
    - Caso já tenha: Pesquisar na lista e adicionar a quantidade de livros comprado.
    - Caso seja seja novo: Cadastrar o livro.

### 2 - Desfazer do Livro
- Remover o livro da lista.

### 3 - Emprestar Livro
- Pesquisar:
    - Caso tenha: checar a quantidade no local
        - Caso tenha apenas 1: não empresta.
        - Caso tenha mais: emprestar.
    - Caso não tenha: "Infelizmente não temos o livro procurado."
  
# ORGANIZAR A ESTANTE
"Roberta está reorganizando suas estantes de livros. Ela pega os livros das prateleiras mais altas para as mais baixas, das estantes mais à esquerda para as estantes mais à direita. Assumindo que todos os livros têm a mesma profundidade. O formato da entrada dos livros considera que os caracteres '/' e '\', indicam respectivamente quando uma prateleira inicia e quando ela termina. Considere que cada estante com 90cm tem no máximo 6 prateleiras. Imprima apenas uma string exibindo a sequência das prateleiras e estantes após o rearranjo."


1. A Estante - HashTable
/ As Crônicas de Roberta, Roberta Lopes, IC, 2023, 31244, 2.21; As Aventuras de Willy e Paes, Monitores de P1, IC, 2020, 31212, 4.72; Chuva de Bençãos: A Alegria de Calculo 2, Diego Chicuta, 2023, 546495, 3.55 \
/ Desconectado, Wifi, UFAL, 2012, 121112, 2.101; Já Pode Almoçar?, Alunos IC, 2023, 1257, 2.41 \
/ Socorro Deus!, Beatriz Rodrigues, 2023, 6132845, 6.1 \
/\
/\
/\
