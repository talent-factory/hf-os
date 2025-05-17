#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_memory_layout(int* stack_var, int* heap_var, int* static_var) {
    printf("Speicheradressanalyse:\n");
    printf("---------------------\n");
    printf("Stack-Variable: %p\n", (void*)stack_var);
    printf("Heap-Variable: %p\n", (void*)heap_var);
    printf("Statische Variable: %p\n", (void*)static_var);

 
    // Differenzen berechnen
    unsigned long diff_stack_heap = (unsigned long)stack_var - (unsigned long)heap_var;
    unsigned long diff_stack_static = (unsigned long)stack_var - (unsigned long)static_var;
    unsigned long diff_heap_static = (unsigned long)heap_var - (unsigned long)static_var;

    printf("\nAdressunterschiede:\n");
    printf("Stack - Heap:       %lu Bytes\n", diff_stack_heap);
    printf("Stack - Static:     %lu Bytes\n", diff_stack_static);
    printf("Heap - Static:      %lu Bytes\n", diff_heap_static);




    printf("\nWachstumsrichtungen:\n");

    // TODO: Deklarieren Sie zwei lokale Variablen und vergleichen Sie ihre Adressen,
    int local1 = 1;
    int local2 = 2;

    if (&local2 > &local1) {
        printf("Stack wächst nach oben (höhere Adressen)\n");
    } else {
        printf("Stack wächst nach unten (niedrigere Adressen)\n");
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
        int* leak = (int*)malloc(1024); // 1 KB
        // Kein free() → Speicherleck
        (void)leak; // Verhindert Compiler-Warnung
    }

    // Speicher freigeben
    free(heap_variable);

    return 0;
}




/*
1.Beschreiben Sie die Ausgabe des Programms. Was sagt sie über die Organisation des Speichers in Ihrem Betriebssystem aus?

Antwort:
Der Speicher ist in Bereiche aufgeteilt: Der Stack liegt oben, der Heap in der Mitte und die statischen Variablen unten. So kann das Betriebssystem Ordnung halten und Fehler vermeiden.

2. Erklären Sie, warum die Adressen der verschiedenen Variablentypen (Stack, Heap, statisch) in unterschiedlichen Speicherbereichen liegen.

Antwort:
Weil sie unterschiedlich genutzt werden: Statische Variablen gelten das ganze Programm über, Stack-Variablen nur kurz, und Heap-Variablen werden bei Bedarf erstellt.

Stack: Wird für lokale Variablen genutzt, wird vom Compiler automatisch verwaltet.
Heap: Dynamischer Speicher, wird mit malloc() reserviert und muss manuell freigegeben werden.
Statische Variable: Wird beim Programmstart angelegt und bleibt bis zum Ende bestehen.

3. Welche Auswirkungen hat das absichtlich erzeugte Speicherleck? Wie könnte ein Betriebssystem mit solchen Situationen umgehen?

Antwort:
Ein Speicherleck bedeutet, dass Speicher belegt bleibt, obwohl er nicht mehr gebraucht wird. Das Betriebssystem gibt diesen Speicher erst frei, wenn das Programm beendet wird.
Virtueller Speicher und Speicherschutzmechanismen verhindern, dass ein Prozess anderen Speicher beeinflusst.

ALs hilfemittel wurde KI benutzt.

*/
