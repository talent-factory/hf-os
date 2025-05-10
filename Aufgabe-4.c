#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable:   %p\n", (void*)stack_var);
    printf("Heap-Variable:    %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Berechnung der Adressdifferenzen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap:     %lu Bytes\n", diff_stack_heap);
    printf("Stack - Statisch: %lu Bytes\n", diff_stack_static);
    printf("Heap  - Statisch: %lu Bytes\n", diff_heap_static);

    // Stack-Wachstumsrichtung
    printf("\nWachstumsrichtungen:\n");

    int local1 = 1;
    int local2 = 2;

    if (&local2 < &local1) {
        printf("Stack wächst nach unten (höhere Adressen -> niedrigere Adressen)\n");
    } else {
        printf("Stack wächst nach oben (niedrigere Adressen -> höhere Adressen)\n");
    }

    printf("\n");
}

int main() {
    static int static_variable = 100;
    int stack_variable = 200;
    int* heap_variable = (int*)malloc(sizeof(int));
    if (heap_variable == NULL) {
        printf("Fehler bei der Speicherzuweisung\n");
        return 1;
    }
    *heap_variable = 300;

    analyze_memory_layout(&stack_variable, heap_variable, &static_variable);

    // Absichtliches Speicherleck erzeugen
    for (int i = 0; i < 5; i++) {
        int* leak = (int*)malloc(100);  // kein free()
        // Hinweis: leak wird überschrieben, kein Zugriff mehr möglich -> Leck
    }

    free(heap_variable);

    return 0;
}
