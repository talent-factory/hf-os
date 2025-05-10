#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    unsigned long diff = (unsigned long)stack_var - (unsigned long)heap_var;
    printf("Diff Stack-Heap-Variable: %p\n", (void*)diff);

    diff = (unsigned long)stack_var - (unsigned long)static_var;
    printf("Diff Stack-Static-Variable: %p\n", (void*)diff);

    diff = (unsigned long)heap_var - (unsigned long)static_var;
    printf("Diff Static-Heap-Variable: %p\n", (void*)diff);

    // TODO: Berechnen Sie die Differenz zwischen den Adressen und geben Sie sie aus
    // Hinweis: Verwenden Sie Typecasting zu (unsigned long) für die Adressberechnung

    printf("\nWachstumsrichtungen:\n");

    int localOne;
    int localTwo;

    printf("%p\n", &localOne);
    printf("%p\n", &localTwo);

    // TODO: Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    // um die Wachstumsrichtung des Stacks zu bestimmen

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
        heap_variable = (int*)malloc(sizeof(int));
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}