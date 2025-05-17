# Aufgabe 5

## Ausgabe des Programms
LB2 git:(hfi2024/patrick-mueller) ✗ ./script-aufgabe-5 
Speicheradressanalyse:
---------------------
Stack-Variable: 0x7ffffc8035b8
Heap-Variable: 0x6191dbd962a0
Statische Variable: 0x6191da3ff010

Adressdifferenzen (in Bytes):
Stack - Heap: 33458343039768
Stack - Statisch: 33458369873320
Heap - Statisch: 26833552

Wachstumsrichtungen:
Stack wächst nach oben (höhere Adressen)

## Analyse des Programmausgangs und der Speicherverwaltung

### 1. Beschreibung der Ausgabe und Aussage zur Speicherorganisation

Das Programm gibt die Speicheradressen dreier Variablentypen aus:

- **Stack-Variable:** Adresse `0x7ffffc8035b8`
- **Heap-Variable:** Adresse `0x6191dbd962a0`
- **Statische Variable:** Adresse `0x6191da3ff010`

Die großen Adressdifferenzen zwischen Stack, Heap und statischen Variablen zeigen, dass diese im Speicher klar getrennt angeordnet sind.

Die Ausgabe: `Stack wächst nach oben (höhere Adressen)` zeigt, dass der Stack auf deinem Betriebssystem (vermutlich Linux x86_64) vom niedrigeren Speicherbereich zu höheren Adressen wächst.

Die deutlich unterschiedlichen Adressbereiche bestätigen die typische Segmentierung im Speicher eines Prozesses:

- Der Stack hat einen eigenen Bereich,
- der Heap einen separaten Bereich,
- und der statische Speicherbereich ist wieder ein anderer Abschnitt.

---

### 2. Warum liegen Variablen in verschiedenen Speicherbereichen?

Die verschiedenen Variablentypen sind in verschiedenen Speichersegmenten angeordnet, weil sie unterschiedliche Lebensdauern und Verwendungszwecke haben:

- **Statische Variablen** werden im statischen Datensegment (Data/BSS) abgelegt. Sie existieren während der gesamten Laufzeit des Programms und haben feste Adressen.
- **Heap-Variablen** werden dynamisch mit `malloc` alloziert. Der Heap ist ein flexibler Speicherbereich, der während der Laufzeit wächst oder schrumpft.
- **Stack-Variablen** werden für lokale Variablen und Funktionsaufrufe benutzt. Der Stack wächst oder schrumpft dynamisch mit dem Aufruf von Funktionen.

Die getrennte Organisation unterstützt die Sicherheit, Effizienz und Verwaltung des Speichers durch das Betriebssystem und die Laufzeitumgebung.

---

### 3. Auswirkungen des absichtlich erzeugten Speicherlecks und Umgang des Betriebssystems

Das Programm erzeugt absichtlich Speicherlecks, indem es mehrfach Speicher mit `malloc` reserviert, diesen aber nicht freigibt.

#### Auswirkungen:

- **Speicherverbrauch steigt:** Der belegte Speicher wird nicht zurückgegeben, auch wenn die Anwendung die Speicherbereiche nicht mehr nutzt.
- **Leistungseinbußen:** Langfristige Lecks können zu Speicherknappheit führen und das System verlangsamen.
- **Instabilität:** Im schlimmsten Fall kann das Programm abstürzen oder das System instabil werden.

#### Umgang des Betriebssystems:

- Das Betriebssystem verwaltet Speicher auf Prozessebene. Speicher, der einem Prozess zugeordnet ist, wird bei dessen Beendigung vollständig freigegeben.
- Es erkennt aber keine internen Speicherlecks innerhalb eines laufenden Prozesses.
- Für die Erkennung von Speicherlecks sind Werkzeuge wie **Valgrind** oder **AddressSanitizer** nötig.
- Gute Programmierpraktiken erfordern, dass jeder dynamisch reservierte Speicher auch wieder freigegeben wird (`free`).

---

## Zusammenfassung

Die Ausgabe des Programms bestätigt die typische Speicherorganisation mit klar getrennten Bereichen für Stack, Heap und statischen Speicher. Die Beobachtung, dass der Stack nach oben wächst, zeigt eine systemabhängige Besonderheit. Das absichtlich erzeugte Speicherleck verdeutlicht typische Probleme bei falscher Speicherverwaltung, die ein Betriebssystem nur eingeschränkt kompensieren kann.


