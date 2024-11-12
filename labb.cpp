#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef struct Polinom {
    int koeficijent;
    int eksponent;
    struct Polinom* next;
} Polinom;

// Funkcija za dodavanje člana polinoma na kraj liste
void dodajClan(Polinom** head, int koeficijent, int eksponent) {
    Polinom* noviClan = (Polinom*)malloc(sizeof(Polinom));
    if (!noviClan) {
        printf("Greska u alociranju memorije!\n");
        return;
    }
    noviClan->koeficijent = koeficijent;
    noviClan->eksponent = eksponent;
    noviClan->next = NULL;

    if (*head == NULL) {
        *head = noviClan;
    }
    else {
        Polinom* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = noviClan;
    }
}

// Funkcija za citanje polinoma iz datoteke
void ucitajPolinom(Polinom** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Greska prilikom otvaranja datoteke!\n");
        return;
    }

    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, file) != NULL) {
        int koeficijent, eksponent, numBytes;
        while (strlen(buffer) > 0) {
            int status = sscanf(buffer, "%d %d %n", &koeficijent, &eksponent, &numBytes);
            if (status != 2) break;  // Ako nije procitao oba parametra, prekidamo
            dodajClan(head, koeficijent, eksponent);
            buffer += numBytes;
        }
    }
    fclose(file);
}

// Funkcija za zbrajanje polinoma
Polinom* zbrojiPolinome(Polinom* p1, Polinom* p2) {
    Polinom* rezultat = NULL;
    Polinom* temp1 = p1;
    Polinom* temp2 = p2;

    // Zbrajamo polinome p1 i p2
    while (temp1 != NULL) {
        dodajClan(&rezultat, temp1->koeficijent, temp1->eksponent);
        temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        dodajClan(&rezultat, temp2->koeficijent, temp2->eksponent);
        temp2 = temp2->next;
    }

    return rezultat;
}

// Funkcija za ispis polinoma
void ispisiPolinom(Polinom* head) {
    Polinom* temp = head;
    while (temp != NULL) {
        printf("%dx^%d ", temp->koeficijent, temp->eksponent);
        temp = temp->next;
    }
    printf("\n");
}

// Oslobodi memoriju povezane liste
void oslobodiPolinom(Polinom* head) {
    Polinom* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Polinom* polinom1 = NULL;
    Polinom* polinom2 = NULL;

    // Učitavanje polinoma iz datoteke
    ucitajPolinom(&polinom1, "polinom1.txt");
    ucitajPolinom(&polinom2, "polinom2.txt");

    printf("Polinom 1: ");
    ispisiPolinom(polinom1);

    printf("Polinom 2: ");
    ispisiPolinom(polinom2);

    // Zbrajanje polinoma
    Polinom* rezultat = zbrojiPolinome(polinom1, polinom2);

    printf("Rezultat zbrajanja: ");
    ispisiPolinom(rezultat);

    // Oslobađanje memorije
    oslobodiPolinom(polinom1);
    oslobodiPolinom(polinom2);
    oslobodiPolinom(rezultat);

    return 0;
}
