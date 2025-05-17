Aufgabe 4:
 1. 
12300_10
 die virtuelle Adresse durch 4096 (Seitengrösse) -> ergibt die virtuelle Seitennummer
 12300 ÷ 4096 = 3 → virtuelle Seite 3
 
 OFFSET:
 Rest der Division (= % 4096) → das ist der Offset innerhalb der Seite
 12300 % 4096 = 12 → Offset = 12 Bytes
 
 2. 
 
16384₁₀:
16384 / 4096 = 4 -> virtuelle Seite 4

OFFSET:
16384 % 4096 = 0

 
Pagetable:
Virtuelle Seite 4 → physische Seite 4

4 × 4096 + 0 = 16384

gültig -> Kein Page Fault


3. 
32800₁₀

32800 / 4096 = 8  virtuelle Seite 8

OFFSET:
32800 % 4096 = 32

Pagetable:
Virtuelle Adresse 32800 liegt auf Seite 8.
Diese Seite ist laut Page Table nicht im physischen Speicher geladen (Eintrag = X).
Der Zugriff führt daher zu einem Page Fault, bei dem das Betriebssystem die Seite ggf. nachlädt.


