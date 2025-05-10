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
    unsigned long stack_heap_diff = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long stack_static_diff = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long heap_static_diff = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap: %ld\n", stack_heap_diff);
    printf("Stack - Statisch: %ld\n", stack_static_diff);
    printf("Heap - Statisch: %ld\n", heap_static_diff);

    printf("\nWachstumsrichtungen:\n");

    int local1 = 1;
    int local2 = 2;

    if (&local2 > &local1)
        printf("Stack waechst nach oben (steigende Adressen)\n");
    else
        printf("Stack waechst nach unten (fallende Adressen)\n");

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
        *leak = i; // Verwendung zur Verhinderung von Optimierung
        // Hinweis: kein free(leak)
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
