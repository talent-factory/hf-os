#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    unsigned long diff1 = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff2 = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff3 = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap: %lu Bytes\n", diff1);
    printf("Stack - Static: %lu Bytes\n", diff2);
    printf("Heap - Static: %lu Bytes\n", diff3);

    printf("\nWachstumsrichtungen:\n");
    int a = 1;
    int b = 2;
    if (&a > &b)
        printf("Stack wächst nach unten.\n");
    else
        printf("Stack wächst nach oben.\n");

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
        int* leak = (int*)malloc(1024); // 1 KB pro Iteration wird nicht freigegeben
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
