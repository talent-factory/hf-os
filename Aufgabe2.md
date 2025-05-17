Aufgabe 2.

Unterschied zwischen interner und externer Speicherfragmentierung:
Interne Speicherfragmentierung

Interne Fragmentierung entsteht, wenn einem Prozess ein fester Speicherblock zugewiesen wird, er aber weniger braucht. Der nicht genutzte Teil ist blockiert, obwohl er physisch vorhanden wäre.

Beispiel aus der Praxis:
Ein Betriebssystem verwendet 4 KB grosse Seiten (z. B. beim Paging).
Ein Prozess benötigt 6 KB → es werden zwei Seiten zu je 4 KB allokiert = 8 KB.
Davon werden aber nur 6 KB genutzt → die restlichen 2 KB sind intern fragmentiert.

Externe Speicherfragmentierung
Externe Fragmentierung entsteht, wenn der Speicher dynamisch in unterschiedlich grosse Blöcke aufgeteilt wird, und durch Beenden oder Auslagern von Prozessen entstehen kleine freie Lücken (sog. „Löcher“) zwischen belegten Bereichen. Diese Lücken sind zwar frei, aber nicht gross genug für neue Prozesse, obwohl gesamt gesehen ausreichend Speicher vorhanden wäre

Strategie 1: Paging mit virtuellem Speicher
Speicher wird in gleich grosse Pages aufgeteilt (z. B. 4 KB)
Ein Prozess erhält Seiten nicht zusammenhängend, sondern beliebig im RAM verteilt.
Der Prozess „denkt“, er hätte zusammenhängenden Speicher – tatsächlich liegen die Seiten aber überall verstreut.

Vorteile:
+ Keine externe Fragmentierung weil physische Lage egal ist
+ Prozesse können grösser sein als der physische RAM (durch Swapping).
+ Effizient bei vielen Prozessen mit unterschiedlicher Grösse.

Nachteile::
+ Kann zu interner Fragmentierung führen, wenn Seiten nicht vollständig genutzt werden.
+ Zusätzlicher Verwaltungsaufwand (Page Tables, TLB, MMU-Hardware).

Strategie 2: Speicherverdichtung
Belegte Speicherblöcke werden im RAM physisch verschoben, um alle freien Lücken zu einem zusammenhängenden Bereich zu konsolidieren.
Dadurch kann ein grösserer Block tatsächlich allokiert werden.

Vorteile:
+ Beseitigt externe Fragmentierung vollständig
+ Erlaubt es grosse Prozesse auch bei fragmentirten Speicher zu starten

Nachteile: 
Sehr aufwendig in Rechenzeit ind I/O
Bei vielen Prozessen üssen sie pausiert werden
Muss vom OS sorgfältig geteuert werden.

