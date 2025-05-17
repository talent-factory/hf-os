#include <stdio.h>
#include <stdlib.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) { 
    printf("Speicheradressanalyse:\\n"); 
    printf("---------------------\\n"); 
    printf("Stack-Variable:     %p\\n", (void*)stack_var); 
    printf("Heap-Variable:      %p\\n", (void*)heap_var); 
    printf("Statische Variable: %p\\n", (void*)static_var); 

    unsigned long diff1 = (unsigned long)heap_var - (unsigned long)stack_var; 
    unsigned long diff2 = (unsigned long)static_var - (unsigned long)heap_var; 

    printf("\\nAdressdifferenzen:\\n"); 
    printf("Heap - Stack:       %lu Bytes\\n", diff1); 
    printf("Static - Heap:      %lu Bytes\\n", diff2); 

    printf("\\nWachstumsrichtungen:\\n"); 
    int local1 = 1; 
    int local2 = 2; 

    printf("Adresse local1:     %p\\n", (void*)&local1); 
    printf("Adresse local2:     %p\\n", (void*)&local2); 
    if (&local2 < &local1) { 
        printf("→ Stack wächst nach unten\\n"); 
    } else { 
        printf("→ Stack wächst nach oben\\n"); 
    } 
} 

int main() { 
    static int static_variable = 100; 
    int stack_variable = 200; 
    int* heap_variable = (int*)malloc(sizeof(int)); 
    if (heap_variable == NULL) { 
        printf("Fehler bei der Speicherzuweisung\\n"); 
        return 1; 
    } 
    *heap_variable = 300; 

    analyze_memory_layout(&stack_variable, heap_variable, &static_variable); 

    // Speicherleck erzeugen 
    for (int i = 0; i < 5; i++) { 
        void* leak = malloc(100); // absichtlich nicht freigegeben 
        (void)leak; // keine Warnung vom Compiler 
    } 

    free(heap_variable); 
    return 0; 
}
