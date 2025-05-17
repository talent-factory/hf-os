Aufgabe 3: 
Ausgabe
_____________________________________________________________
➜  test git:(hfi2024a/jetmir-memeti) ✗ ls -la
insgesamt 20
drwxrwxr-x 3 vmadmin vmadmin 4096 Mai 17 11:19 .
drwxr-xr-x 4 vmadmin vmadmin 4096 Mai 17 11:19 ..
-rw-r----- 2 vmadmin vmadmin   18 Mai 15 11:19 hardlink.txt
-rw-r----- 2 vmadmin vmadmin   18 Mai 15 11:19 original.txt
drwxrwxr-x 2 vmadmin vmadmin 4096 Mai 17 11:19 subdir
lrwxrwxrwx 1 vmadmin vmadmin   12 Mai 17 11:19 symlink.txt -> original.txt
➜  test git:(hfi2024a/jetmir-memeti) ✗ 
_____________________________________________________________

mkdir -p:
erstellt rekursiv die Verzeichnisse test und subdir, falls sie noch nicht existieren. Wechselt dann anschliessend in das verzeichnis text.  

echo "Inhalt-$(date +%s)" > original.txt:
Schreibt den String "Inhalt-sekundentimestamp in die Datei original.txt. Das > überschreibt die Datei davor. wenn >> fügt es sie hinzu. Leitet sie in stdout Datei.

ln -s original.txt symlink.txt
Erzeugt einen symbolischen Link und verweisst auf den Pfad Original mit dem Namen Symlink.txt -> Inode: verweist auf neuen Inode mit Pfadinfo.

ln original.txt hardlink.txt
Erstellt einen hartcodeten Link. Beide Namen verweisen direkt auf denselben Speicherbereich. -> Hardlink: gleicher Inode, andere Name. Diese Datei existiert, solange mindestens ein hardlink aktiv ist.

chmod 640 original.txt
Legt Berechtigugnen fest. 
Besitzer lesen schreiben. 
Gruppe: Lesen
Alle anderen: nichts, nada.

ls -la:
Gibt die Ausgabe wie oben ausgegeben. 

Spalte	Bedeutung
- / d / l -> Dateityp: - = reguläre Datei, d = Verzeichnis, l = Symlink
rw-r ->	Berechtigungen: Besitzer rw, Gruppe r, andere -
2 ->	Link-Count: Anzahl harter Verweise (Hardlinks) auf denselben Inode
vmadmin	Besitzer uid
vmadmin	Gruppe gid
18 ->	Dateigrösse in Bytes (nur bei regulären Dateien)
Mai 15 11:19->letzter Modifikationszeitpunkt (mtime)
original.txt-> Dateiname
-> original.txt	(bei Symlink) Pfad-Ziel des Links

echo "Neuer Inhalt" > original.txt 
überschreibt die Datei. Der Operator > öffnet original.txt zum Schreiben, truncate-and-write: alte Daten werden gelöscht, neuer Inhalt hineingeschrieben.


cat symlink.txt hardlink.txt
Gibt den Inhalt der Datei zwei Mal aus. beide zeigen auf denselben Inode / Inhalt

mv original.txt ../original.txt
Verschiebt die Datei in den übergeordneten Ordner

test git:(hfi2024a/jetmir-memeti) ✗ cat symlink.txt hardlink.txt 2>&1
cat: symlink.txt: Datei oder Verzeichnis nicht gefunden
Neuer Inhalt

Hardlink bleibt im test-Verzeichnis → Datei existiert weiter
Symlink ist nun kaputt, da original.txt im selben Verzeichnis nicht mehr existiert
hardlink.txt: zeigt weiterhin den Inhalt korrekt an

Mögliche Fehler:
- Das Dateisystem kann den vom Symlink referenzierten Pfad nicht auflösen.  führt zu einem Fehler im Systemaufruf open()
- Es könnten Berechtigungen fehlen, wenn man sie falsch vergibt. 
-Der Hardlink-Systemaufruf (link()) verwendet direkt die Inode-ID – die ist nur innerhalb eines Dateisystems eindeutig und gültig.


Bonus Frage: 
Auf unterschiedlichen Dateisystemen funktionieren symbolische Links problemlos, da sie nur Pfade speichern. Harte Links hingegen sind nicht erlaubt, weil sie auf denselben Inode verweisen müssten – dieser ist nur innerhalb eines Dateisystems eindeutig. Ein mv über Dateisystemgrenzen bewirkt intern eine Dateikopie mit anschliessendem Löschen, wodurch sich der Inode der Datei ändert.


 




