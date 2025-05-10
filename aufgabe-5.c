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

    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap: %lu Bytes\n", diff_stack_heap);
    printf("Stack - Statisch: %lu Bytes\n", diff_stack_static);
    printf("Heap - Statisch: %lu Bytes\n", diff_heap_static);

    printf("\nWachstumsrichtungen:\n");

    // Zwei lokale Variablen deklarieren
    int local_var1 = 1;
    int local_var2 = 2;

    printf("Adresse local_var1: %p\n", (void*)&local_var1);
    printf("Adresse local_var2: %p\n", (void*)&local_var2);

    if (&local_var2 < &local_var1) {
        printf("Stack wächst nach unten (zu kleineren Adressen)\n");
    } else {
        printf("Stack wächst nach oben (zu größeren Adressen)\n");
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
        void* leak = malloc(1024);  // 1 KB Speicher wird zugewiesen, aber nie freigegeben
        (void)leak; // Suppress unused variable warning
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
