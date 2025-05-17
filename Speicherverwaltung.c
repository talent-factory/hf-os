#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);
    
    // Berechnen der Differenz zwischen den Adressen
    printf("\nAdressdifferenzen:\n");
    printf("Stack zu Heap: %lu Bytes\n", 
           (unsigned long)stack_var > (unsigned long)heap_var ? 
           (unsigned long)stack_var - (unsigned long)heap_var : 
           (unsigned long)heap_var - (unsigned long)stack_var);
    
    printf("Stack zu Statisch: %lu Bytes\n", 
           (unsigned long)stack_var > (unsigned long)static_var ? 
           (unsigned long)stack_var - (unsigned long)static_var : 
           (unsigned long)static_var - (unsigned long)stack_var);
    
    printf("Heap zu Statisch: %lu Bytes\n", 
           (unsigned long)heap_var > (unsigned long)static_var ? 
           (unsigned long)heap_var - (unsigned long)static_var : 
           (unsigned long)static_var - (unsigned long)heap_var);

    printf("\nWachstumsrichtungen:\n");
    // Zwei lokale Variablen für die Analyse der Stack-Wachstumsrichtung
    int local_var1 = 10;
    int local_var2 = 20;
    
    printf("Stack-Wachstumsrichtung: ");
    if (&local_var1 > &local_var2) {
        printf("nach unten (von höheren zu niedrigeren Adressen)\n");
    } else {
        printf("nach oben (von niedrigeren zu höheren Adressen)\n");
    }
    
    printf("Heap-Wachstumsrichtung: typischerweise nach oben (von niedrigeren zu höheren Adressen)\n");
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
    printf("Demonstriere Speicherleck durch wiederholte Allokation ohne Freigabe:\n");
    for (int i = 0; i < 5; i++) {
        // Erzeugen eines Speicherlecks durch Speicherzuweisung ohne Freigabe
        int* leak = (int*)malloc(1024 * sizeof(int)); // 4KB Speicherzuweisung
        if (leak != NULL) {
            printf("Speicherleck #%d: %p (%lu Bytes)\n", i+1, (void*)leak, 1024 * sizeof(int));
            // Wir geben den Speicher absichtlich nicht frei (free(leak)) um ein Speicherleck zu erzeugen
        }
    }
    
    // Speicher freigeben
    free(heap_variable);
    return 0;
}
