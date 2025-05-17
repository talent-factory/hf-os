#include <stdio.h>
#include <stdlib.h>

int main() {
    // TODO: Stack-Wachstumsrichtung bestimmen
    int a;
    int b;
    if (&b < &a) {
        printf("Stack wächst nach unten\n");
    } else {
        printf("Stack wächst nach oben\n");
    }

    // TODO: Heap-Adressbereich untersuchen
    void* addr1 = malloc(1);
    void* addr2 = malloc(1);

    unsigned long diff = (unsigned long)addr1 - (unsigned long)addr2;
    printf("Adressdifferenz im Heap: %ld\n", diff);

    // TODO: Speicherleck erzeugen
    void* leak = malloc(100);  // absichtlich kein free()

    // Aufräumen (nicht für leak, da wir ein Speicherleck demonstrieren)
    free(addr1);
    free(addr2);

    return 0;
}
