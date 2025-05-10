#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Berechnung der Adressdifferenzen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("Differenz zwischen Stack und Heap: %lu\n", diff_stack_heap);
    printf("Differenz zwischen Stack und statischer Variable: %lu\n", diff_stack_static);
    printf("Differenz zwischen Heap und statischer Variable: %lu\n", diff_heap_static);

    printf("\nWachstumsrichtungen:\n");

    // Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    // um die Wachstumsrichtung des Stacks zu bestimmen
    int var1 = 0;
    int var2 = 1;

    // Ausgabe der Adressen der beiden Variablen
    printf("Adresse von var1: %p\n", (void*)&var1);
    printf("Adresse von var2: %p\n", (void*)&var2);

    // Bestimmung der Stack-Wachstumsrichtung
    if ((unsigned long)&var1 < (unsigned long)&var2) {
        printf("Der Stack wächst in Richtung niedrigerer Adressen.\n");
    } else {
        printf("Der Stack wächst in Richtung höherer Adressen.\n");
    }

    printf("\n");
}

int main() {
    // Statische Variable
    static int static_variable = 100;

    // Stack-Variable
    int stack_variable = 200;

    // Heap-Variable
    int* heap_variable = (int*)malloc(sizeof(int));
    if (heap_variable == NULL) {
        printf("Fehler bei der Speicherzuweisung\n");
        return 1;
    }
    *heap_variable = 300;

    // Speicherlayout analysieren
    analyze_memory_layout(&stack_variable, heap_variable, &static_variable);

    // Speicherleck demonstrieren
    for (int i = 0; i < 5; i++) {
        // Absichtlich ein Speicherleck erzeugen
        // Hinweis: Weisen Sie Speicher zu, ohne ihn freizugeben
        int* leak_var = (int*)malloc(sizeof(int));
        // Der zugewiesene Speicher wird nicht freigegeben, was zu einem Speicherleck führt
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}

