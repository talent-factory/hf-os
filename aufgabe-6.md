# Aufgabe 6

## Ausgabe
➜  LB2 git:(hfi2024/patrick-mueller) ✗ ./script-aufgabe-6 
Metadaten vor der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Dateigröße: 96 Bytes
Inode-Nummer: 546346
Anzahl der Hardlinks: 1
Zugriffsrechte (okt.): 664
Letzter Zugriff: 2025-05-17 12:09:58
Letzte Änderung: 2025-05-17 12:09:58

Metadaten nach der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Dateigröße: 143 Bytes
Inode-Nummer: 546346
Anzahl der Hardlinks: 1
Zugriffsrechte (okt.): 664
Letzter Zugriff: 2025-05-17 12:09:58
Letzte Änderung: 2025-05-17 12:09:58

Hardlink erstellt: testdatei_hardlink.txt
Metadaten des Hardlinks:
Metadaten für Datei: testdatei_hardlink.txt
------------------------
Dateigröße: 143 Bytes
Inode-Nummer: 546346
Anzahl der Hardlinks: 2
Zugriffsrechte (okt.): 664
Letzter Zugriff: 2025-05-17 12:09:58
Letzte Änderung: 2025-05-17 12:09:58

## Aufgaben nach der Ausführung

### 1. Beschreibung der Ausgabe und Änderungen der Metadaten nach dem Anhängen von Text

- **Dateigröße**: Die Dateigröße hat sich von 96 Bytes auf 143 Bytes erhöht, was zeigt, dass zusätzlicher Text erfolgreich an die Datei angehängt wurde.
- **Inode-Nummer**: Diese bleibt unverändert (546346), da die Datei dieselbe physische Datei im Dateisystem ist.
- **Anzahl der Hardlinks**: Vor dem Erstellen des Hardlinks ist die Anzahl 1, danach 2, da jetzt zwei Verweise (Dateinamen) auf dieselbe Datei zeigen.
- **Zugriffsrechte (Oktal)**: Bleiben gleich bei 664.
- **Letzter Zugriff und letzte Änderung**: Die Zeitstempel sind gleich geblieben (12:09:58). Normalerweise würde die letzte Änderung (`st_mtime`) sich beim Anhängen ändern, hier scheint die Ausgabe eventuell vor dem tatsächlichen Zeitupdate erfolgt zu sein oder die Zeitanzeige hat eine geringe Auflösung. In einer realen Umgebung würde sich der `st_mtime` nach dem Schreiben ändern.

### 2. Unterschied zwischen Inode-Nummer und Dateiname

- **Inode-Nummer** ist eine eindeutige Kennung im Dateisystem, die auf die physische Datei verweist und ihre Metadaten (Größe, Rechte, Zeitstempel, Speicherorte der Datenblöcke) enthält.
- **Dateiname** ist ein symbolischer Verweis (ein "Link") im Verzeichnis, der auf einen Inode zeigt.
- Wenn zwei Dateien dieselbe **Inode-Nummer** haben, handelt es sich um Hardlinks — also verschiedene Dateinamen, die auf dieselbe Datei im Dateisystem zeigen und dieselben Daten und Metadaten teilen.
- Werden Änderungen an der Datei über einen Hardlink gemacht, spiegeln sich diese über alle Hardlinks wider, da nur eine Datei existiert.

### 3. Unterschiede zwischen Hardlink und symbolischem Link (Symlink)

| Eigenschaft                 | Hardlink                                  | Symbolischer Link (Symlink)                    |
|----------------------------|-------------------------------------------|-----------------------------------------------|
| Verweist auf               | Direkt auf den Inode der Datei             | Auf den Pfad (Namen) der Originaldatei        |
| Inode-Nummer des Links     | Identisch mit der Originaldatei             | Eigene Inode, da es eine separate Datei ist   |
| Anzahl der Hardlinks       | Erhöht sich um 1 bei jedem Hardlink         | Anzahl der Hardlinks der Originaldatei bleibt gleich |
| Verhalten beim Löschen der Originaldatei | Datei bleibt erhalten, da Hardlink weiterhin existiert | Symlink wird „broken“ (zeigt auf nicht vorhandene Datei) |
| Löschung eines Links       | Entfernt nur den Link, Datei bleibt bei weiteren Hardlinks erhalten | Entfernt nur den Symlink, Originaldatei bleibt erhalten |

**Zusammenfassung:**  
Ein Hardlink ist ein weiterer Name für dieselbe Datei im Dateisystem. Ein Symlink ist eine separate Datei, die auf einen Pfad verweist. Wenn die Originaldatei gelöscht wird, bleibt ein Hardlink die Datei erhalten, ein Symlink ist danach ungültig.
