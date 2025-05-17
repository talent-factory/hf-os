#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable:     %p\n", (void*)stack_var);
    printf("Heap-Variable:      %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Differenzen berechnen
    printf("\nAdressdifferenzen (in Bytes):\n");
    printf("Stack - Heap:       %ld\n", (unsigned long)stack_var - (unsigned long)heap_var);
    printf("Stack - Static:     %ld\n", (unsigned long)stack_var - (unsigned long)static_var);
    printf("Heap - Static:      %ld\n", (unsigned long)heap_var - (unsigned long)static_var);

    printf("\nWachstumsrichtungen:\n");

    // Stack-Wachstumsrichtung
    int local1 = 1;
    int local2 = 2;

    if (&local2 > &local1) {
        printf("Stack wächst nach oben (aufsteigende Adressen)\n");
    } else {
        printf("Stack wächst nach unten (absteigende Adressen)\n");
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
        int* leak = (int*)malloc(sizeof(int));
        *leak = i * 10;
        // Kein free(leak) → Speicherleck
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
