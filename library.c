#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define DEBUG if(1)

typedef struct book{
    char title[MAX_LEN];
    char autor[MAX_LEN];
    char publisher[MAX_LEN];
    int ano;
    int isbn;
    double width; // Em cm
} book;

typedef struct collection {
    book *elem;
    int qnt_local;
    int qnt_emp;
    struct collection *next;
} collection;

int isEmpty(collection *head) {
    return (head == NULL);
}

collection *create_collection(){
    return NULL;
}

book *create_book (char *title, char *autor, char *publisher, int ano, int isbn, double width){
    book *new_book = malloc(sizeof(book));
    
    strcpy(new_book->title, title);
    strcpy(new_book->autor, autor);
    strcpy(new_book->publisher, publisher);
    new_book->ano = ano;
    new_book->isbn = isbn;
    new_book->width = width;

    return new_book;
}

collection *addNew(collection *head, book *livro, int qnt_l) {
    collection *new_node = malloc(sizeof(collection));
    new_node->elem = livro;
    new_node->qnt_local = qnt_l;
    new_node->qnt_emp = 0;

    new_node->next = head;
    return new_node;
}

collection *addLoad(collection *head, book *livro, int qnt_l, int qnt_e) {
    collection *new_node = malloc(sizeof(collection));
    new_node->elem = livro;
    new_node->qnt_local = qnt_l;
    new_node->qnt_emp = qnt_e;

    new_node->next = head;
    return new_node;
}

collection *searchList(collection *head, int isbn) {
    while (!isEmpty(head)) {
        if (head->elem->isbn == isbn) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

collection *purchaseBooks(collection *head, book *newBook, int qnt) {
    collection *book = searchList(head, newBook->isbn);
    if (book != NULL) { // se o livro ja existe na lista
        book->qnt_local += qnt;
        return head; // retorna o ponteiro sem mexer na cabeça
    }
    else{
        book = addNew(head, newBook, qnt);
        return book; // retorna a nova cabeça para o novo livro
    }
}

collection *lendBooks(collection *head, int wantedIMBS) {
    collection *book = searchList(head, wantedIMBS);
    if (book != NULL) {
        if (book->qnt_local > 2) {
            book->qnt_local--;
            book->qnt_emp++;
            printf("Livro emprestado com sucesso.\n");
            return head; // retorna o ponteiro sem mexer na cabeça
        }
        else {
            printf("Livro esgotado.\n");
            return head;
        }
    }
    else{
        printf("Livro não encontrado.\n");
        return head;
    }
}

collection *removeCollection(collection *head, int wantedBook){
    collection *prev = NULL;
    collection *curr = head;

    while(curr != NULL && curr->elem->isbn != wantedBook){
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL){
        printf("Livro não encontrado\n");
        return head;
    } 

    if (prev == NULL) head = curr->next;
    else prev->next = curr->next;    
    
    free(curr);
    return head;
}

void print(collection *head)
{
    while (head != NULL)
    {
        printf("title: %s\nAutor: %s\nEditora: %s\n", head->elem->title, head->elem->autor, head->elem->publisher);
        printf("Ano: %d\nIMBS: %d\nQnt: %d\n", head->elem->ano, head->elem->isbn, head->qnt_local);
        
        head = head->next;
        printf("\n");
    }
}

/* 
int main() 
{
    collection *teste = create_collection();

    char title[MAX_LEN]; strcpy(title, "As Cronicas de Roberta");
    char autor[MAX_LEN]; strcpy(autor, "Roberta Lopes");
    char publisher[MAX_LEN]; strcpy(publisher, "IC");
    int ano = 2023;
    int isbn = 31244;

    book *livroTeste = create_book(title, autor, publisher, ano, isbn);

    DEBUG{ // Criação
        printf("Teste de criação de livro\n");
        print(teste);
        teste = addNew(teste, livroTeste, 10);
        print(teste);
    }

    title[MAX_LEN]; strcpy(title, "As Aventuras de Willy e Paes");
    autor[MAX_LEN]; strcpy(autor, "Monitores de P1");
    publisher[MAX_LEN]; strcpy(publisher, "IC");
    ano = 2023; 
    isbn = 31212;

    DEBUG{ // Compra
        printf("Teste de compra de livro\n");
        teste = purchaseBooks(teste, livroTeste, 7);
        livroTeste = create_book(title, autor, publisher, ano, isbn);
        teste = purchaseBooks(teste, livroTeste, 15);
        print(teste);
    }

    DEBUG{ // Emprestimo
        printf("Teste de emprestimo de livro\n");
        teste = lendBooks(teste, livroTeste->isbn);
        print(teste);
    }

    DEBUG{ // Remoção
        printf("Teste de remoção de livro\n");
        teste = removecollection(teste, livroTeste->isbn);
        print(teste);
    }

    return 0;
} */