#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Differenzen berechnen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap: %lu\n", diff_stack_heap);
    printf("Stack - Statisch: %lu\n", diff_stack_static);

    printf("\nWachstumsrichtungen:\n");

    int local1;
    int local2;
    if (&local2 > &local1) {
        printf("Stack wächst nach oben\n");
    } else {
        printf("Stack wächst nach unten\n");
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

    for (int i = 0; i < 5; i++) {
        malloc(100); // Speicherleck – Speicher wird zugewiesen aber nie freigegeben
    }

    free(heap_variable);
    return 0;
}
