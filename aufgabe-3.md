# Lösungen Aufgabe 3

## Erklärung der Befehle
| **Befehl**                                     | **Erklärung**                                                                 |
|------------------------------------------------|--------------------------------------------------------------------------------|
| `mkdir -p test/subdir && cd test`             | Erstellt Verzeichnisstruktur und wechselt nach `test`.                        |
| `echo "Inhalt-$(date +%s)" > original.txt`     | Schreibt aktuellen Zeitstempel in Datei `original.txt`.                       |
| `ln -s original.txt symlink.txt`              | Erstellt symbolischen Link auf `original.txt`.                                |
| `ln original.txt hardlink.txt`                | Erstellt Hardlink mit identischem Inode wie `original.txt`.                   |
| `chmod 640 original.txt`                      | Setzt Rechte: Besitzer rw-, Gruppe r--, andere ---.                           |
| `touch -d "2 days ago" original.txt`          | Ändert Zeitstempel von `original.txt` auf vor 2 Tagen.                        |
| `ls -la`                                      | Listet alle Dateien mit Details wie Rechte, Größe, Zeit, Links und Inode.    |

## Ausgabe des Befehls `ls -la`
➜  test git:(hfi2024/patrick-mueller) ✗ ls -la
insgesamt 20
rwxrwxr-x 3 vmadmin vmadmin 4096 Mai 17 11:33 .
drwxr-xr-x 4 vmadmin vmadmin 4096 Mai 17 11:33 ..
-rw-r----- 2 vmadmin vmadmin   18 Mai 15 11:34 hardlink.txt
-rw-r----- 2 vmadmin vmadmin   18 Mai 15 11:34 original.txt
drwxrwxr-x 2 vmadmin vmadmin 4096 Mai 17 11:33 subdir
lrwxrwxrwx 1 vmadmin vmadmin   12 Mai 17 11:33 symlink.txt -> original.txt

## Analyse der Ausgabe

### Erklärung der Spalten
| **Spalte**              | **Bedeutung**                                                                           |
| ----------------------- | --------------------------------------------------------------------------------------- |
| `drwxr-xr-x`            | Dateityp (`d` = Verzeichnis, `-` = reguläre Datei) + Zugriffsrechte (User/Group/Others) |
| `4`                     | Anzahl der Hardlinks (bei Verzeichnissen inkl. `.` und Unterverzeichnissen)             |
| `vmadmin`               | Besitzer (User), dem die Datei/Verzeichnis gehört                                       |
| `vmadmin`               | Gruppe, der die Datei zugeordnet ist                                                    |
| `4096`, etc.    | Dateigröße in Byte                                                                      |
| `Mai 17 11:33`          | Zeitstempel der letzten Änderung (`mtime`)                                              |
| `.`, `..`, `hardlink.txt`… | Dateiname oder Verzeichnisname                                                          |

### Unterschiede zwischen den drei Dateien
| **Datei**      | **Berechtigungen** | **Inode (implizit)**  | **Zeitstempel** | **Besonderheiten**                                  |
| -------------- | ------------------ | --------------------- | --------------- | --------------------------------------------------- |
| `original.txt` | `-rw-r-----`       | *gleich wie hardlink* | Mai 15 11:34    | Reguläre Datei, enthält den tatsächlichen Inhalt    |
| `hardlink.txt` | `-rw-r-----`       | *gleich wie original* | Mai 15 11:34    | Hardlink auf dieselbe Inode wie `original.txt`      |
| `symlink.txt`  | `lrwxrwxrwx`       | *eigene Inode*        | Mai 17 11:33    | Symbolischer Link, verweist auf Pfad `original.txt` |

### Warum haben bestimmte Dateien die gleiche Inode-Nummer und andere nicht?

#### Gleiche Inode-Nummer bei `original.txt` `hardlink.txt`
- Beide Dateien zeigen auf den selben physikalischen Speicherplatz
- Wird eine Datei verändert, wirkt sich dies auf die andere Datei aus
- In der zweiten Spalte der Ausgabe "ls -la" sieht man, dass zwei Dateinamen dieselbe Inode referenzierne

#### Unterschiedliche Inode bei `symlink.txt`
- Ein Symlink ist eine eigene Datei, welche lediglich den Pfad der gelinkten Datei (original.txt) als Inhalt speichert
- Besitzt deshalb
    - eigene Inode
	- eigene Metadaten (z. B. Zeitstempel),
	- andere Dateiberechtigungen (`lrwxrwxrwx` → Lesen von Pfad, nicht Inhalt).
- Verschiebt oder löscht man die gelinkte Datei, wird der Symlink "broken" da der Inhalt nicht mehr lesbar ist

## Analyse der letzten Befehle
### 1. `echo "Neuer Inhalt" > original.txt`

- **Ausgabe:** Keine sichtbare Ausgabe.
- **Erklärung:**  
  Überschreibt den Inhalt von `original.txt` mit „Neuer Inhalt“.  
  Die Datei behält ihre ursprüngliche Inode, da die Datei nicht ersetzt, sondern nur ihr Inhalt geändert wird.  
  Da `hardlink.txt` ein Hardlink auf dieselbe Inode ist, zeigt auch diese Datei den neuen Inhalt.

---

### 2. `cat symlink.txt hardlink.txt`

- **Ausgabe:** Neuer Inhalt Neuer Inhalt
- **Erklärung:**  
- `symlink.txt` ist ein symbolischer Link, der auf `original.txt` zeigt und deshalb den neuen Inhalt ausgibt.  
- `hardlink.txt` ist ein Hardlink und zeigt direkt auf dieselbe Inode, also ebenfalls den neuen Inhalt.

---

### 3. `mv original.txt ../original.txt`

- **Ausgabe:** Keine sichtbare Ausgabe.
- **Erklärung:**  
- Die Datei `original.txt` wird in das übergeordnete Verzeichnis verschoben.  
- Die Inode der Datei bleibt erhalten, da die Datei nicht verändert, sondern nur der Pfad geändert wird.  
- `hardlink.txt` verweist weiterhin auf dieselbe Inode und bleibt gültig.  
- `symlink.txt` verweist auf den ursprünglichen Pfad `original.txt` im aktuellen Verzeichnis, der jetzt nicht mehr existiert. Somit wird der Symlink „broken“.

---

### 4. `cat symlink.txt hardlink.txt 2>&1`

- **Ausgabe:** cat: symlink.txt: No such file or directory Neuer Inhalt
- **Erklärung:**  
- Beim Versuch, `symlink.txt` zu lesen, schlägt `cat` fehl, da der Symlink auf einen nicht mehr existierenden Pfad zeigt.  
- `hardlink.txt` funktioniert weiterhin, da er direkt auf die gültige Inode zeigt.

---

## Zusammenfassung: Verhalten von Hard- und Symbolischen Links

| Aspekt                   | Symbolischer Link (`symlink.txt`)                    | Hardlink (`hardlink.txt`)                           |
|--------------------------|-----------------------------------------------------|----------------------------------------------------|
| Verweist auf             | Pfadname                                            | Inode                                              |
| Inode                    | Eigene Inode                                        | Dieselbe Inode wie die Originaldatei               |
| Verhalten nach `mv`      | Link wird ungültig (broken), da Pfad nicht mehr existiert | Link bleibt gültig, da Inode erhalten bleibt       |
| Auswirkung von Inhaltänderungen | Zeigt neuen Inhalt, solange Pfad gültig bleibt      | Zeigt immer neuen Inhalt (Inode-basiert)           |
| Fehlerquelle             | Pfadänderungen brechen den Link                     | Keine, solange die Inode noch existiert            |

---

Diese Analyse verdeutlicht die fundamentalen Unterschiede zwischen symbolischen und harten Links bezüglich Pfadbindung und Inode-Verwaltung.

## Bonus-Frage: Verhalten bei Dateien auf unterschiedlichen Dateisystemen

- **Hardlinks** können **nicht** über Dateisystemgrenzen hinweg erstellt werden.  
  Das bedeutet:  
  Wenn `original.txt` und die Links auf unterschiedlichen Partitionen oder Dateisystemen liegen,  
  ist es nicht möglich, einen Hardlink auf `original.txt` auf einem anderen Dateisystem anzulegen.  
  Ein Versuch schlägt mit einem Fehler fehl (z.B. „Invalid cross-device link“).

- **Symbolische Links (Symlinks)** hingegen **funktionieren auch über Dateisystemgrenzen hinweg**,  
  da sie nur den Pfad als Text speichern und nicht direkt auf eine Inode zeigen.  
  Somit können Symlinks problemlos auf Dateien in anderen Partitionen oder Dateisystemen zeigen.

### Zusammenfassung:

| Aspekt          | Gleiche Partition / Dateisystem         | Unterschiedliche Partition / Dateisystem           |
|-----------------|----------------------------------------|----------------------------------------------------|
| Hardlink        | Möglich                               | Nicht möglich (Fehler beim Erstellen)              |
| Symbolischer Link | Möglich                               | Möglich                                            |

---

**Fazit:**  
Wenn Dateien über verschiedene Dateisysteme verteilt sind, sind symbolische Links die einzige Möglichkeit, verlässliche Verweise zwischen ihnen zu erstellen.
