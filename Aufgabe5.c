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
    printf("differenz Stack - Heap: %ld Bytes\n", (unsigned long)stack_var - (unsigned long)heap_var);
    printf("differenz Stack - Static: %ld Bytes\n", (unsigned long)stack_var - (unsigned long)static_var);
    printf("differenz Heap - Static: %ld Bytes\n", (unsigned long)heap_var - (unsigned long)static_var);

    printf("\nWachstumsrichtungen:\n");

    // TODO: Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    // um die Wachstumsrichtung des Stacks zu bestimmen
    int local1 = 1;
    int local2 = 2;
    printf("Adresse von local1: %p\n", (void*)&local1);
    printf("Adresse von local2: %p\n", (void*)&local2);
    if (&local2 > &local1) {
        printf("Stack wächst nach oben (aufsteigend)\n");
    } else {
        printf("Stack wächst nach unten (absteigend)\n");
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
        // TODO: Erzeugen Sie absichtlich ein Speicherleck
        // Hinweis: Weisen Sie Speicher zu, ohne ihn freizugeben
        int* leak = (int*)malloc(sizeof(int));
        *leak = i;
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}


output:
Speicheradressanalyse:
---------------------
Stack-Variable: 0x7ffe7051cc60
Heap-Variable: 0x5d0fc21d72a0
Statische Variable: 0x5d0fc1e2f010
differenz Stack - Heap: 38408520227264 Bytes
differenz Stack - Static: 38408524061776 Bytes
differenz Heap - Static: 3834512 Bytes

Wachstumsrichtungen:
Adresse von local1: 0x7ffe7051cc40
Adresse von local2: 0x7ffe7051cc44
Stack wächst nach oben (aufsteigend)



Beschreibung: 
-Die relativen Positionen von Stack, Heap und statischem Speicher
-Die Wachstumsrichtung des Stacks
-Demonstration von Speicherlecks
-Typischerweise werden Sie sehen:
-Stack und Heap wachsen aufeinander zu
-Statische Variablen liegen in einem anderen Speicherbereich
-Die Stack-Wachstumsrichtung ist meist abwärts (höhere zu niedrigere Adressen)
