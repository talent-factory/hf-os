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
    unsigned long stack_addr = (unsigned long)stack_var;
    unsigned long heap_addr = (unsigned long)heap_var;
    unsigned long static_addr = (unsigned long)static_var;

    printf("\nAdressdifferenzen:\n");
    printf("Heap - Stack: %lu Bytes\n", (heap_addr > stack_addr) ? (heap_addr - stack_addr) : (stack_addr - heap_addr));
    printf("Stack - Static: %lu Bytes\n", (stack_addr > static_addr) ? (stack_addr - static_addr) : (static_addr - stack_addr));
    printf("Heap - Static: %lu Bytes\n", (heap_addr > static_addr) ? (heap_addr - static_addr) : (static_addr - heap_addr));

    printf("\nWachstumsrichtungen:\n");

    // Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    // um die Wachstumsrichtung des Stacks zu bestimmen
    int local_var1;
    int local_var2;
    printf("Adresse lokale Variable 1 (Stack): %p\n", (void*)&local_var1);
    printf("Adresse lokale Variable 2 (Stack): %p\n", (void*)&local_var2);
    if (&local_var2 < &local_var1) {
        printf("Der Stack wächst nach unten (zu niedrigeren Adressen).\n");
    } else {
        printf("Der Stack wächst nach oben (zu höheren Adressen).\n");
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
    printf("Demonstration eines Speicherlecks:\n");
    for (int i = 0; i < 5; i++) {
        // Erzeugen Sie absichtlich ein Speicherleck
        int* leaked_memory = (int*)malloc(sizeof(int));
        if (leaked_memory == NULL) {
            printf("Fehler bei der Speicherzuweisung im Speicherleck-Beispiel\n");
            return 1;
        }
        *leaked_memory = i * 10;
        printf("Nicht freigegebener Speicher an Adresse: %p, Inhalt: %d\n", (void*)leaked_memory, *leaked_memory);
        // Hinweis: free(leaked_memory); würde das Speicherleck verhindern
    }
    printf("Speicherleck erzeugt (Speicher wurde zugewiesen, aber nicht freigegeben).\n");

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
