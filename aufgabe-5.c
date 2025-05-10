#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // TODO: Berechnen Sie die Differenz zwischen den Adressen und geben Sie sie aus
    // Hinweis: Verwenden Sie Typecasting zu (unsigned long) für die Adressberechnung
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("Differenz Stack - Heap:   %ld\n", diff_stack_heap);
    printf("Differenz Stack - Static: %ld\n", diff_stack_static);
    printf("Differenz Heap - Static:  %ld\n", diff_heap_static);

    printf("\nWachstumsrichtungen:\n");

    // TODO: Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    // um die Wachstumsrichtung des Stacks zu bestimmen
    int local1 = 1;
    int local2 = 2;
    printf("Adresse von local1: %p\n", (void*)&local1);
    printf("Adresse von local2: %p\n", (void*)&local2);

    if (&local2 < &local1) {
        printf("Der Stack wächst nach unten (zu kleineren Adressen).\n");
    } else {
        printf("Der Stack wächst nach oben (zu größeren Adressen).\n");
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
        // TODO: Erzeugen Sie absichtlich ein Speicherleck
        // Hinweis: Weisen Sie Speicher zu, ohne ihn freizugeben
        int* leak = (int*)malloc(sizeof(int));
        *leak = i;
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}