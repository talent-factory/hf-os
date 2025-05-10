#include <stdio.h>     // For printf()
#include <stdlib.h>    // For malloc() and free()
#include <stddef.h>    // For NULL
#include <string.h>    // For memset()

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("-----------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Adressunterschiede berechnen
    printf("\nAdressunterschiede:\n");
    printf("Stack -> Heap: %lu Bytes\n", (unsigned long)((void*)stack_var - (void*)heap_var));
    printf("Heap -> Static: %lu Bytes\n", (unsigned long)((void*)heap_var - (void*)static_var));
    printf("Static -> Stack: %lu Bytes\n", (unsigned long)((void*)static_var - (void*)stack_var));

    // Wachstumsrichtung des Stacks bestimmen
    printf("\nWachstumsrichtung des Stacks:\n");
    int local_var1 = 10;
    int local_var2 = 20;

    if ((void*)&local_var1 > (void*)&local_var2) {
        printf("Der Stack wächst nach unten.\n");
    } else {
        printf("Der Stack wächst nach oben.\n");
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
        malloc(sizeof(int)); // Speicherleck erzeugt, da kein free() erfolgt
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}

