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

    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nWachstumsrichtungen:\n");

    // TODO: Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    // um die Wachstumsrichtung des Stacks zu bestimmen
    int local1 = 1;
    int local2 = 2;

    if (&local2 > &local1) {
        printf("Stack wächst nach unten\n");
    } else {
        printf("Stack wächst nach oben\n");
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
        int* leak = (int*)malloc(99);
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}
