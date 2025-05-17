#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    // Berechnen der Differenz zwischen den Adressen und Ausgabe
    unsigned long stack_heap_diff = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long stack_static_diff = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long heap_static_diff = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdressdifferenzen:\n");
    printf("Stack - Heap: %lu Bytes\n", labs(stack_heap_diff));
    printf("Stack - Static: %lu Bytes\n", labs(stack_static_diff));
    printf("Heap - Static: %lu Bytes\n", labs(heap_static_diff));

    printf("\nWachstumsrichtungen:\n");
    // Deklarieren von zwei lokalen Variablen und Vergleichen ihrer Adressen
    int local_var1;
    int local_var2;

    printf("Stack-Wachstumsrichtung: ");
    if (&local_var1 > &local_var2) {
        printf("abwärts (von höheren zu niedrigeren Adressen)\n");
    } else {
        printf("aufwärts (von niedrigeren zu höheren Adressen)\n");
    }

    printf("Heap-Wachstumsrichtung: typischerweise aufwärts\n");
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
    printf("Erzeuge absichtlich Speicherlecks...\n");
    for (int i = 0; i < 5; i++) {
        // Erzeugen eines Speicherlecks durch Zuweisung ohne Freigabe
        int* leak = (int*)malloc(1024 * sizeof(int));
        if (leak != NULL) {
            printf("Speicherleck #%d erzeugt: %p\n", i+1, (void*)leak);
            // Kein free(leak) - absichtliches Speicherleck
        }
    }

    // Speicher freigeben
    free(heap_variable);
    return 0;
}
