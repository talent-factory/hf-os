#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("----------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

    unsigned long diff1 = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff2 = (unsigned long)stack_var - (unsigned long)static_var;

    printf("Adressunterschied Stack <-> Heap: %lu\n", diff1);
    printf("Adressunterschied Stack <-> Static: %lu\n", diff2);

    printf("\nWachstumsrichtungen:\n");

    int local1 = 1;
    int local2 = 2;

    if ((unsigned long)&local2 < (unsigned long)&local1) {
        printf("Der Stack wächst nach unten.\n");
    } else {
        printf("Der Stack wächst nach oben.\n");
    }

    printf("\n");
}

int main() {
    static int static_variable = 100;
    int stack_variable = 200;
    int* heap_variable = (int*)malloc(sizeof(int));
    if (heap_variable == NULL) {
        printf("Fehler bei der Speicherzuweisung\n");
        return 1;
    }
    *heap_variable = 300;

    analyze_memory_layout(&stack_variable, heap_variable, &static_variable);

    for (int i = 0; i < 5; i++) {
        malloc(1024);  // Speicherleck
    }

    return 0;
}
