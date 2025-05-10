#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // TODO: Berechnen Sie die Differenz zwischen den Adressen und geben Sie sie aus
    // Hinweis: Verwenden Sie Typecasting zu (unsigned long) für die Adressberechnung
    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap:       %ld Bytes\n", (long)((unsigned long)stack_var - (unsigned long)heap_var));
    printf("Stack - Static:     %ld Bytes\n", (long)((unsigned long)stack_var - (unsigned long)static_var));
    printf("Heap - Static:      %ld Bytes\n", (long)((unsigned long)heap_var - (unsigned long)static_var));

    printf("\nWachstumsrichtungen:\n");

    // Zwei lokale Stack-Variablen deklarieren
    int local1 = 1;
    int local2 = 2;

    printf("Adresse von local1: %p\n", (void*)&local1);
    printf("Adresse von local2: %p\n", (void*)&local2);

    if (&local2 > &local1)
        printf("Stack wächst nach oben (aufsteigende Adressen)\n");
    else
        printf("Stack wächst nach unten (absteigende Adressen)\n");

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
        int* leak = (int*)malloc(100); // Speicher wird nie freigegeben
        (void)leak; // Suppress "unused variable" warning
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}