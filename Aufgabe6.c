#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

void print_file_metadata(const char* filename) {
    struct stat file_info;

    // Stat-Informationen abrufen
    if (stat(filename, &file_info) != 0) {
        perror("Fehler beim Abrufen der Dateimetadaten");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");

    // Dateigröße
    printf("Größe: %ld Bytes\n", file_info.st_size);

    // Inode-Nummer
    printf("Inode: %lu\n", file_info.st_ino);

    // Anzahl Hardlinks
    printf("Hardlinks: %lu\n", file_info.st_nlink);

    // Zugriffsrechte (Oktal)
    printf("Berechtigungen: %o\n", file_info.st_mode & 0777);

    // Zeitstempel formatieren
    char time_buf[80];
    struct tm* timeinfo;

    // Letzter Zugriff
    timeinfo = localtime(&file_info.st_atime);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Letzter Zugriff: %s\n", time_buf);

    // Letzte Änderung
    timeinfo = localtime(&file_info.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Letzte Änderung: %s\n", time_buf);

    printf("\n");
}

int main() {
    const char* filename = "testdatei.txt";
    const char* content = "Dies ist ein Test für Dateioperationen.\n"
                         "Wir untersuchen, wie Dateisysteme Metadaten verwalten.\n";

    // Datei erstellen und schreiben
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return 1;
    }

    fprintf(file, "%s", content);
    fclose(file);

    // Metadaten vor der Änderung anzeigen
    printf("Metadaten vor der Änderung:\n");
    print_file_metadata(filename);

    // Datei öffnen und zusätzlichen Inhalt anhängen
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei zum Anhängen");
        return 1;
    }

    // Zusätzlichen Text anhängen
    fprintf(file, "Zusätzlicher Inhalt für Metadatenanalyse.\n");

    fclose(file);

    // Metadaten nach der Änderung anzeigen
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);

    // Hardlink erstellen
    const char* hardlink_name = "testdatei_hardlink.txt";
    if (link(filename, hardlink_name) != 0) {
        perror("Fehler beim Erstellen des Hardlinks");
        return 1;
    }

    printf("Hardlink erstellt: %s\n", hardlink_name);

    // Metadaten des Hardlinks anzeigen
    printf("Metadaten des Hardlinks:\n");
    print_file_metadata(hardlink_name);

    // Dateien löschen
    remove(filename);
    remove(hardlink_name);

    return 0;
}


Outout: 

Metadaten nach der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Größe: 140 Bytes
Inode: 546197
Hardlinks: 1
Berechtigungen: 664
Letzter Zugriff: 2025-05-10 12:15:15
Letzte Änderung: 2025-05-10 12:15:15

Hardlink erstellt: testdatei_hardlink.txt
Metadaten des Hardlinks:
Metadaten für Datei: testdatei_hardlink.txt
------------------------
Größe: 140 Bytes
Inode: 546197
Hardlinks: 2
Berechtigungen: 664
Letzter Zugriff: 2025-05-10 12:15:15
Letzte Änderung: 2025-05-10 12:15:15




Beschreibung: 

Beschreiben Sie die Ausgabe des Programms. Welche Änderungen an den Metadaten beobachten Sie nach dem Anhängen von Text?

*** 
Das Programm zeigt anschaulich, wie sich Dateimetadaten bei verschiedenen Operationen verändern. Zuerst wird die Datei "testdatei.txt" erstellt und mit Inhalt gefüllt. Zu diesem Zeitpunkt hat sie typischerweise eine bestimmte Anfangsgröße, etwa 100 Bytes, und genau einen Hardlink (den Originaldateinamen selbst).
Die gezeigte Ausgabe demonstriert drei wichtige Sachen
	* Originaldatei nach Erstellung
	* Nach Anhängen von Text
	* Nach Hardlink-Erstellung:
	Änderungen: 
	-- Erhöht sich um die Länge des angehängten Texts +40 Bytes
	-- Wird auf den Zeitpunkt des Anhängens aktualisiert
	-- Inode/Hardlinks nleiben unverändert

------------------------------------------------
Erklären Sie den Unterschied zwischen der Inode-Nummer und dem Dateinamen. Was bedeutet es, wenn zwei Dateien die gleiche Inode-Nummer haben?
***
Dateiname: 
 -- benutzerfreundliche Bezeichnung, verstehlich, un lesbar
 -- Ein Verzeichniseintrag, der auf eine Inode verweist.
 -- beliebig umbenannt, verschoben
Inode-Nummer
 -- Dateitype
 -- berechtigungen
 -- Grösse
 -- Zeitstempel

wenn zwei Dateien die gleiche Inode-Nummer haben, sind sie harklink zueinander verbunde wruden.

----------------------------------------------
Wie würde sich das Verhalten ändern, wenn Sie statt eines Hardlinks einen symbolischen Link (Symlink) erstellen würden? Beschreiben Sie die Unterschiede in Bezug auf Metadaten und Verhalten beim Löschen der Originaldatei.

In Hardlinke wrid die Inode wie es in Orginal steht aber in in Symbolischer Linke wird ihre einige Inode haben.
Dateigrösse wird auch in hrlinke wie Orginal aber in Symlink hat kein

