Aufgabe 6:
Output:
__________________________________________________
➜  LB2 git:(hfi2024a/jetmir-memeti) ✗ ./Aufgabe6                

Metadaten vor der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Dateigröße: 96 Bytes
Inode-Nummer: 546206
Anzahl Hardlinks: 1
Zugriffsrechte: 664 (oktal)
Letzter Zugriff: 2025-05-17 12:42:34
Letzte Änderung: 2025-05-17 12:42:34

Metadaten nach der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Dateigröße: 128 Bytes
Inode-Nummer: 546206
Anzahl Hardlinks: 1
Zugriffsrechte: 664 (oktal)
Letzter Zugriff: 2025-05-17 12:42:34
Letzte Änderung: 2025-05-17 12:42:34

Hardlink erstellt: testdatei_hardlink.txt
Metadaten des Hardlinks:
Metadaten für Datei: testdatei_hardlink.txt
------------------------
Dateigröße: 128 Bytes
Inode-Nummer: 546206
Anzahl Hardlinks: 2
Zugriffsrechte: 664 (oktal)
Letzter Zugriff: 2025-05-17 12:42:34
Letzte Änderung: 2025-05-17 12:42:34

➜  LB2 git:(hfi2024a/jetmir-memeti) ✗ 
_________________________________________________

Welche Änderungen an den Metadaten beobachten Sie nach dem Anhängen von Text?

Ich habe nach dem Anhängen gesehen, dass sich die Dateigrösse von 96 auf 128 Bytes erhöht hat.
Die Inode-Nummer und Zugriffsrechte blieben gleich.
Der Zeitstempel für Zugriff und Änderung blieb ebenfalls gleich, wahrscheinlich weil alles sehr schnell hintereinander ablief.


Erklären Sie den Unterschied zwischen der Inode-Nummer und dem Dateinamen. Was bedeutet es, wenn zwei Dateien die gleiche Inode-Nummer haben?

Der Dateiname ist nur ein Verweis in einem Verzeichnis.
Die Inode-Nummer zeigt auf den tatsächlichen Inhalt der Datei.
Beide Dateien (testdatei.txt und testdatei_hardlink.txt) haben dieselbe Inode-Nummer – das bedeutet, sie teilen sich denselben Inhalt.
Wenn ich eine ändere, ändert sich automatisch auch die andere.


Wie würde sich das Verhalten ändern, wenn Sie statt eines Hardlinks einen symbolischen Link (Symlink) erstellen würden?

Ein Symlink zeigt nur auf den Pfad der Originaldatei.
Er hat einen eigenen Inode und eigene Metadaten.
Wenn ich die Originaldatei lösche, funktioniert der Symlink nicht mehr.
Ein Hardlink hingegen bleibt voll funktionsfähig, solange mindestens einer der Links vorhanden ist.

