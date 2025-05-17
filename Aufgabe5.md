Ausgabe;
Speicheradressanalyse:
---------------------
Stack-Variable: 0x7fffe77eff58
Heap-Variable: 0x5c60027b72a0
Statische Variable: 0x5c6001717010

Adressabstände:
Stack - Heap:       39169648987320 Bytes
Stack - Statisch:   39169666420552 Bytes

Wachstumsrichtungen:
Adresse von local_a: 0x7fffe77eff20
Adresse von local_b: 0x7fffe77eff24
Stack wächst nach oben (aufsteigende Adressen)


1. Was sagt die Ausgabe über die Organisation des Speichers im Betriebssystem aus?

Ich sehe, dass Stack-, Heap- und statische Variablen in völlig unterschiedlichen Speicherbereichen liegen.
Die Adressen sind weit auseinander – das ist typisch für ein virtuelles Speichermodell, wie es moderne Betriebssysteme verwenden.
Jeder Bereich wird separat verwaltet, was die Sicherheit und Stabilität erhöht.


2. Warum liegen die Adressen der verschiedenen Variablentypen (Stack, Heap, statisch) in unterschiedlichen Speicherbereichen?

Die Stack-Variable liegt oben im Speicher, weil lokale Variablen dort gespeichert werden.
Die Heap-Variable wird mit malloc zur Laufzeit im mittleren Bereich zugewiesen.
Die statische Variable wird beim Programmstart im Data-Segment angelegt.
Diese Trennung macht es einfacher, Fehler zu vermeiden und Speicher gezielt zu verwalten.



3. Welche Richtung hat der Stack in deinem System?

Ich habe gemessen, dass local_b eine höhere Adresse hat als local_a.
Das bedeutet: Der Stack wächst nach oben – was eher ungewöhnlich ist, da er auf vielen Systemen nach unten wächst.
Es zeigt aber, dass das plattformabhängig ist.



4. 
Ein Speicherleck entsteht, wenn ich mit malloc Speicher anfordere, ihn aber nicht mit free zurückgebe.
Dann bleibt der Speicher reserviert, obwohl ich ihn nicht mehr brauche.
Wenn das oft passiert, z. B. in Schleifen, kann der Speicher irgendwann knapp werden.
Das Betriebssystem erkennt solche Lecks nicht von selbst.

