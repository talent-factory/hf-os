#include <stdio.h>
#include <stdlib.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable:     %p\n", (void*)stack_var);
    printf("Heap-Variable:      %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Adressdifferenzen berechnen
    printf("\nAdressdifferenzen:\n");
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("Stack - Heap:       %ld Bytes\n", diff_stack_heap);
    printf("Stack - Statisch:   %ld Bytes\n", diff_stack_static);
    printf("Heap - Statisch:    %ld Bytes\n", diff_heap_static);

    // Stack-Wachstumsrichtung
    printf("\nWachstumsrichtungen:\n");
    int a = 1;
    int b = 2;
    if (&b > &a)
        printf("Stack wächst nach oben (höhere Adressen)\n");
    else
        printf("Stack wächst nach unten (niedrigere Adressen)\n");

    printf("\n");
}

int main() {
    static int static_variable = 100; // Statische Variable
    int stack_variable = 200;         // Stack-Variable

    // Heap-Variable
    int* heap_variable = (int*)malloc(sizeof(int));
    if (heap_variable == NULL) {
        printf("Fehler bei der Speicherzuweisung\n");
        return 1;
    }
    *heap_variable = 300;

    // Speicherlayout analysieren
    analyze_memory_layout(&stack_variable, heap_variable, &static_variable);

    // Speicherleck erzeugen
    for (int i = 0; i < 5; i++) {
        int* leak = (int*)malloc(sizeof(int)); // kein free()
        *leak = i;
    }

    // Heap-Variable freigeben
    free(heap_variable);

    return 0;
}

