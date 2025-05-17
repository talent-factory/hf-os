# Lösungen Aufgabe 2

## Unterschied zwischen interner und externer Speicherfragmentierung

### Interne Fragmentierung
Interne Fragmentierung tritt auf, wenn ein Speicherblock zugewiesen wird, welcher nicht vollständig genutzt wird. Der nicht genutzte Teil ist verschwendet.

#### Beispiel
Ein Prozess benötigt 5 KB speicher. Das Betriebssystem weist nur Speicherblöcke mit 8 KB-Grösse zu. Die übrigen 3 KB können vom OS nichtmehr verwendet werden und bleiben ungenutzt.

### Externe Fragmentierung
Externe Fragmentierung tritt auf, wenn genug freier Speicher vorhanden ist, dieser aber in viele kleine, nicht zusammenhängende Blöcke aufgeteilt ist. Dadurch steht kein genug grosser Block zur Verfügung.

#### Beispiel
Ein OS hat 4 freie Blöcke: 5 KB, 10 KB, 15 KB, 20 KB. Ein Prozess benötigt einen 25 KB grossen Block. Obwohl über 25 KB Speicher vorhanden ist, kann der Prozess nicht zugewiesen werden.

### Unterschiede

**Interne Fragmentierung** entsteht, wenn einem Prozess ein größerer Speicherblock zugewiesen wird, als tatsächlich benötigt wird – ungenutzter Speicher innerhalb des Blocks geht verloren. **Externe Fragmentierung** dagegen tritt auf, wenn durch viele kleine, nicht zusammenhängende freie Bereiche zwischen belegten Blöcken kein ausreichend großer zusammenhängender Speicher verfügbar ist. Der Hauptunterschied liegt also darin, wo der Speicher verschwendet wird: intern innerhalb, extern zwischen den Speicherblöcken.

## 2 Strategien zur Reduzierung oder Vermeidung von Speicherfragmentierung

### Strategie 1: Paging
Der Speicher wird in gleich grosse Seiten (Pages) aufgeteilt. Der logische Speicher eines Prozesses kann so in beliebiger Reihenfolge in den physischen Speicher geladen werden.

#### Vorteile
- Vermeidet **externe Fragmentierung** vollständig
- Effiziente Speicherausnutzung durch flexible Verteilung

#### Nachteile
- Kann **interne Fragmentierung** erzeugen, wenn ein Prozess eine Page nicht vollständig nutzt
- Zusätzlicher Verwaltungsaufwand durch Page-tables
- Langsamerer Zugriff auf Speicher, da über Page-Tables

### Strategie 2: Speicherkompatierung (Compaction)
Das Betriebssystem verschiebt Prozesse im Speicher, um verstreuten freien Speicher zu einem großen zusammenhängenden Block zu vereinigen.

#### Vorteile
- Reduziert **externe Fragmentierung**, indem der freie Speicher konsolidiert wird

#### Nachteile
- keinen einfluss auf **interne Fragmentierung**
- Hoher Rechenaufwand, da Prozesse verschoben werden müssen
- Leistungseinbussen bei ausgelasteten Systemen
- Nur umsetzbar wenn Prozesse dynamisch verschiebbar sind

### Kurzes Fazit
Moderne Betriebssysteme verwenden meist virtuelle Speicherverwaltung mit Techniken wie Paging oder Segmentierung, um Fragmentierung weitgehend zu vermeiden. Speicherkompaktierung ist in reinen realen Speicherverwaltungssystemen (ohne Paging) manchmal notwendig, aber in der Praxis wegen des Overheads selten.
