#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Adress-Differenzen berechnen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdress-Differenzen:\n");
    printf("Stack - Heap: %lu\n", diff_stack_heap);
    printf("Stack - Statisch: %lu\n", diff_stack_static);
    printf("Heap - Statisch: %lu\n", diff_heap_static);

    printf("\nWachstumsrichtungen:\n");
    int local_var1;
    int local_var2;
    if (&local_var2 > &local_var1) {
        printf("Der Stack wächst nach oben (zu höheren Adressen).\n");
    } else {
        printf("Der Stack wächst nach unten (zu niedrigeren Adressen).\n");
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

    // Speicherleck erzeugen
    for (int i = 0; i < 5; i++) {
        int* leak = (int*)malloc(sizeof(int));
        *leak = i; // nur Beispiel, Wert ist egal
        // Kein free(), absichtliches Speicherleck
    }

    free(heap_variable);
    return 0;
}
