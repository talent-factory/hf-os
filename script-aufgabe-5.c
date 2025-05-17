#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Adressdifferenzen berechnen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdressdifferenzen (in Bytes):\n");
    printf("Stack - Heap: %ld\n", diff_stack_heap);
    printf("Stack - Statisch: %ld\n", diff_stack_static);
    printf("Heap - Statisch: %ld\n", diff_heap_static);

    printf("\nWachstumsrichtungen:\n");

    // Zwei lokale Variablen deklarieren und deren Adressen vergleichen
    int local1;
    int local2;
    if (&local2 > &local1) {
        printf("Stack wächst nach oben (höhere Adressen)\n");
    } else {
        printf("Stack wächst nach unten (niedrigere Adressen)\n");
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
        // Absichtlich Speicherlecks erzeugen
        malloc(sizeof(int));
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}

