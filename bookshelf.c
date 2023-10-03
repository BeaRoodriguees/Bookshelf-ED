#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.c"

#define QNT 6

// Depois ver o como fazer com várias estantes

typedef struct shelf {
    int key;
    int actualWidth;
    book *book;
    struct shelf *next;
} Shelf;

typedef struct bookshelf {
    Shelf *table[QNT];
} bs;

bs *create_bs(){
    bs *newBs = malloc(sizeof(bs));
    for(int i = 0; i < QNT; i++)
        newBs->table[i] = NULL;
    return newBs;
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

book *get(bs *bs, int key){
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

void printTable(bs *bs) {
    for (int i = 0; i < QNT; i++) {
        printf("Self %d: ", i+1);
        Shelf *curr = bs->table[i];
        while (curr != NULL) {
            printf("(%d, %s) ", curr->key, curr->book->title);
            curr = curr->next;
        }
        printf("\n");
    }
}

void inputBooks(bs *books){
    FILE *readInput = fopen("input.txt", "r");

    if (readInput == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int shelf = -1;
    char *line = malloc(sizeof(char)*1000);
    char tokens[] = "/\\,;"; //tokens para separar as informações do livro

/*      
 // get the bookcases
    while(fgets(line, sizeof(line), fp))
    {
        if(line[0] == '/')
        {
            Stack * st = NULL;
            char *token = strtok(line, ",/\\");
            while (token != NULL) {
                push_str(&st, token);
                j++;
                token = strtok(NULL, ",/\\");
            }
            i++;
            j = 0;
            pushs(&sts, st);
        }
        else if(line[0] == '_')
        {
            push_bk(lib, sts);
            sts = NULL;
            i = 0; j = 0;
        }
        else return 2;
    }
*/

    while (shelf++ < QNT)
    {
        fscanf(readInput, "%[^\n]", line);
        fgetc(readInput); // Para ler o \n

        char *portion = strtok(line, tokens);
        char title[100], autor[100], publisher[100];
        int ano, isbn, i = 1, j = 0;
        double width;
       
        while (portion != NULL) {
            switch (i)
            {
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
                    j++;
                break;
            }
            
            portion = strtok(NULL, tokens);
        }
       
        // Para o último livro da estante
        if(i == 6){
            book *newBook = create_book(title, autor, publisher, ano, isbn, width);
            put(books, j* QNT + shelf, newBook);
        }

    }

    fclose(readInput);
}

int main(){
    bs *bs = create_bs(); // Cria uma estante

    // ler o arquivo e colocar na estante
    inputBooks(bs);
    printTable(bs);

    return 0;
}