#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable:    %p\n", (void*)stack_var);
    printf("Heap-Variable:     %p\n", (void*)heap_var);
    printf("Statische Variable:%p\n", (void*)static_var);

    // Adressdifferenz berechnen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;

    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap:      %lu Bytes\n", diff_stack_heap);
    printf("Stack - Static:    %lu Bytes\n", diff_stack_static);

    // Wachstumsrichtung des Stacks analysieren
    printf("\nWachstumsrichtungen:\n");

    int local1 = 1;
    int local2 = 2;

    if ((unsigned long)&local2 < (unsigned long)&local1) {
        printf("Stack wächst nach unten (absteigende Adressen)\n");
    } else {
        printf("Stack wächst nach oben (aufsteigende Adressen)\n");
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

    // Speicherleck demonstrieren
    for (int i = 0; i < 5; i++) {
        void* leak = malloc(1024); // 1 KB Speicherleck pro Iteration
        (void)leak; // suppress unused variable warning
    }

    free(heap_variable);

    return 0;
}