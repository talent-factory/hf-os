#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Berechnen Sie die Differenz zwischen den Adressen und geben Sie sie aus
    unsigned long stack_heap_diff = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long stack_static_diff = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long heap_static_diff = (unsigned long)heap_var - (unsigned long)static_var;
    
    printf("\nAdressdifferenzen:\n");
    printf("Stack zu Heap: %lu Bytes\n", stack_heap_diff);
    printf("Stack zu Statisch: %lu Bytes\n", stack_static_diff);
    printf("Heap zu Statisch: %lu Bytes\n", heap_static_diff);

    printf("\nWachstumsrichtungen:\n");

    // Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen
    int stack_var1 = 10;
    int stack_var2 = 20;
    
    printf("Stack-Variable 1: %p\n", (void*)&stack_var1);
    printf("Stack-Variable 2: %p\n", (void*)&stack_var2);
    
    if (&stack_var1 > &stack_var2) {
        printf("Der Stack wächst nach unten (von hohen zu niedrigen Adressen)\n");
    } else {
        printf("Der Stack wächst nach oben (von niedrigen zu hohen Adressen)\n");
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
    printf("Erzeuge absichtlich Speicherlecks:\n");
    for (int i = 0; i < 5; i++) {
        // Erzeugen Sie absichtlich ein Speicherleck
        int* leak = (int*)malloc(1024 * sizeof(int));  // 4KB Speicher zuweisen
        if (leak != NULL) {
            *leak = i;  // Etwas in den Speicher schreiben
            printf("Speicherleck %d erzeugt an Adresse: %p\n", i, (void*)leak);
            // Kein free(leak) - absichtliches Speicherleck
        }
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
