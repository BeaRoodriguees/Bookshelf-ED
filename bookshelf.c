#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG if(1)
#define QNT 6
#define MAX_WIDTH 90
#define MAX_LEN 100

typedef struct jeej {
    char title[MAX_LEN];
    char autor[MAX_LEN];
    char publisher[MAX_LEN];
    int edition;
    int isbn;
    double width; // Em cm
} book;

typedef struct shelf {
    int key;
    book *book;
    struct shelf *next;
} Shelf;

typedef struct bookshelf {
    Shelf *table[QNT];
    double actualWidth[QNT];
} bs;

typedef struct library{
    bs *bookshelfs;
    struct library *next;
} lib;

bs *create_bs(){
    bs *newBs = malloc(sizeof(bs));
    for(int i = 0; i < QNT; i++){
        newBs->table[i] = NULL;
        newBs->actualWidth[i] = 0;
    }
    return newBs;
}

book *create_book (char *title, char *autor, char *publisher, int edition, int isbn, double width){
    book *new_book = malloc(sizeof(book));
    
    strcpy(new_book->title, title);
    strcpy(new_book->autor, autor);
    strcpy(new_book->publisher, publisher);
    new_book->edition = edition;
    new_book->isbn = isbn;
    new_book->width = width;

    return new_book;
}

void put(bs *bs, int key, book *book){
    int h = key % QNT;
    
    Shelf *newShelf = malloc(sizeof(Shelf));
    newShelf->key = key;
    newShelf->book = book;
    newShelf->next = NULL;
    
    if (bs->table[h] == NULL) {
        bs->table[h] = newShelf;
    } else {
        Shelf *curr = bs->table[h];
        while (curr->next != NULL && curr->key != key) {
            curr = curr->next;
        }
        if (curr->key == key) {
            curr->book = book;
        } else {
            curr->next = newShelf;
        }
    }
}

book *getBook(bs *bs, int key){
    int h = key % QNT;
    Shelf *curr = bs->table[h];
    while (curr != NULL) {
        if (curr->key == key)
            return curr->book;
        curr = curr->next;
    }
    return NULL;
}

void freeTable(bs *bs, int key){
    int h = key % QNT;
    Shelf *curr = bs->table[h];
    Shelf *prev = NULL;
    while (curr != NULL && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != NULL) {
        if (prev == NULL) {
            bs->table[h] = curr->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }
}

lib *addShelf(lib *library, bs *bookshelf){
    lib *newLib = malloc(sizeof(lib));
    newLib->bookshelfs = bookshelf;
    newLib->next = library;
    return newLib;
}

lib *inputBooks(lib *library){ 
    FILE *readInput = fopen("data/library.txt", "r");

    if (readInput == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return library;
    }

    while(feof(readInput) == 0){
        bs *books = create_bs();

        int shelf = -1;
        char *line = malloc(sizeof(char)*1000);
        char tokens[] = "/\\,;"; //tokens para separar as informações do livro
        
        while (shelf++ < QNT)
        {
            fscanf(readInput, "%[^\n]", line);
            fgetc(readInput); // Para ler o \n

            char *portion = strtok(line, tokens);
            char title[100], autor[100], publisher[100];
            int ano, isbn, i = 1, j = 0;
            double width;
        
            while (portion != NULL) {
                switch (i) {
                    case 1:
                        strcpy(title, portion);
                        i++;
                        break;
                    case 2:
                        strcpy(autor, portion);
                        i++;
                        break;
                    case 3:
                        strcpy(publisher, portion);
                        i++;
                        break;
                    case 4:
                        ano = atoi(portion);
                        i++;
                        break;
                    case 5:
                        isbn = atoi(portion);
                        i++;
                        break;
                    case 6:
                        width = atof(portion);
                        i++;
                    case 7:
                        i = 1;
                        book *newBook = create_book(title, autor, publisher, ano, isbn, width);
                        put(books, j * QNT + shelf, newBook);
                        books->actualWidth[shelf] += width;
                        j++;
                    break;
                }
                
                portion = strtok(NULL, tokens);
            }
        
            // Para o último livro da estante
            if(i == 6){
                book *newBook = create_book(title, autor, publisher, ano, isbn, width);
                put(books, j* QNT + shelf, newBook);
                books->actualWidth[shelf] += width;
            }
        }

        library = addShelf(library, books);
    }  

    fclose(readInput);
    return library;
}

void printBook(bs *bs, int key){
    book *book = getBook(bs, key);
    if (book != NULL) {
        printf("Title: %s\n", book->title);
        printf("Autor: %s\n", book->autor);
        printf("Publisher: %s\n", book->publisher);
        printf("Edition: %d\n", book->edition);
        printf("ISBN: %d\n", book->isbn);
        printf("Width: %.2lf\n", book->width);
    } else {
        printf("Book not found.\n");
    }
}

void printShelf(bs *bs) {
    for (int i = 0; i < QNT; i++) {
        printf("Shelf %d - %.2lf cm: ", i+1, bs->actualWidth[i]);
        Shelf *curr = bs->table[i];
        while (curr != NULL) {
            printf("(%d, %s, %.3lf) ", curr->key, curr->book->title, curr->book->width);;
            curr = curr->next;
        }
        printf("\n");
    }
    printf("\n");
}

// Simular tirar os livros da estante para reorganizar --  Tirando os livros da estante e colocando-os lista encadeada
Shelf *putBox (bs *original){
    Shelf *all = NULL;

    for (int i = 0; i < QNT; i++) {
        Shelf *curr = original->table[i];
        while (curr != NULL) {
            Shelf *temp = curr;
            curr = curr->next;
            temp->next = all;
            all = temp;
        }
        original->table[i] = NULL;
    }
    
    return all; 
}

// Ordenação Alfabética e por Largura
bs *sortAlphaWidth(bs *original){
    bs *sorted = create_bs();
    Shelf *all = putBox(original); // Tira todos os livros da estante
    
    // Ordenar Lista Encadeada -- Selection Sort  
    Shelf *curr = all;
    int j = 0;
    while(curr != NULL){
        Shelf *min = curr;
        Shelf *aux = curr->next;

        while(aux != NULL){
            if(min->book->title[0] > aux->book->title[0])
                min = aux;
            else if (min->book->title[0] == aux->book->title[0] && min->book->width > aux->book->width)
                min = aux;
            aux = aux->next;
        }

        if(min != curr){
            book *temp = curr->book;
            curr->book = min->book;
            min->book = temp;
        }

        curr = curr->next;
    }
    
    // Colocar os livros na estante
    for (int shelf = 0; shelf < QNT; shelf++){
        j = 0;
        while(all != NULL && sorted->actualWidth[shelf] + all->book->width < MAX_WIDTH){  // Verifica se ainda há livro e se não ocupou toda a estante
            sorted->actualWidth[shelf] += all->book->width;
            put(sorted, j * QNT + shelf, all->book);
            j++;
            all = all->next;
        }
    } 

    return sorted;
}

int main(){
    lib *library = NULL; // Cria uma biblioteca
    bs *bs = create_bs(); // Cria uma estante

    printf("Estante Original:\n");
    library = inputBooks(library);

    lib *aux = library;
    while(aux != NULL){
        printShelf(aux->bookshelfs);
        aux = aux->next;
    }

    aux = library;
    printf("Estante Ordenada Alfabeticamente:\n");
    while (aux != NULL) {
        bs = sortAlphaWidth(aux->bookshelfs);
        printShelf(bs);
        aux = aux->next;
    }

    return 0;
}