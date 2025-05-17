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

    // stat() aufrufen und Fehler überprüfen
    if (stat(filename, &file_info) != 0) {
        perror("stat");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");
    printf("Dateigrösse:         %ld Bytes\n", file_info.st_size);
    printf("Inode-Nummer:       %ld\n", file_info.st_ino);
    printf("Anzahl Hardlinks:   %ld\n", file_info.st_nlink);
    printf("Zugriffsrechte:     %o (oktal)\n", file_info.st_mode & 0777);

    char time_str[30];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_atime));
    printf("Letzter Zugriff:    %s\n", time_str);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_mtime));
    printf("Letzte Änderung:    %s\n", time_str);

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

    // Zusätzlicher Text
    fprintf(file, "Zusätzlicher Inhalt wird angehängt.\n");
    fclose(file);

    // Metadaten nach der Änderung anzeigen
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);

    // Hardlink erstellen
    const char* hardlink_name = "testdatei_hardlink.txt";
    if (link(filename, hardlink_name) != 0) {
        perror("Fehler beim Erstellen des Hardlinks");
    } else {
        printf("Hardlink erstellt: %s\n", hardlink_name);
        // Metadaten des Hardlinks anzeigen
        printf("Metadaten des Hardlinks:\n");
        print_file_metadata(hardlink_name);
    }

    // Dateien löschen
    remove(filename);
    remove(hardlink_name);

    return 0;
}

/*
Ausgabe:

➜  LB2 git:(hfi2024a/kavindu-JasinPathiranage) ✗ ./aufgabe6
Metadaten vor der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Dateigrösse:         96 Bytes
Inode-Nummer:       533399
Anzahl Hardlinks:   1
Zugriffsrechte:     664 (oktal)
Letzter Zugriff:    2025-05-17 12:22:29
Letzte Änderung:    2025-05-17 12:22:29

Metadaten nach der Änderung:
Metadaten für Datei: testdatei.txt
------------------------
Dateigrösse:         134 Bytes
Inode-Nummer:       533399
Anzahl Hardlinks:   1
Zugriffsrechte:     664 (oktal)
Letzter Zugriff:    2025-05-17 12:22:29
Letzte Änderung:    2025-05-17 12:22:29

Hardlink erstellt: testdatei_hardlink.txt
Metadaten des Hardlinks:
Metadaten für Datei: testdatei_hardlink.txt
------------------------
Dateigrösse:         134 Bytes
Inode-Nummer:       533399
Anzahl Hardlinks:   2
Zugriffsrechte:     664 (oktal)
Letzter Zugriff:    2025-05-17 12:22:29
Letzte Änderung:    2025-05-17 12:22:29


*/


/*
1. Beschreiben Sie die Ausgabe des Programms. Welche Änderungen an den Metadaten beobachten Sie nach dem Anhängen von Text?

Antwort:
Die Dateigrösse wird grösser, da mehr Inhalt hinzugefügt wurde. Ausserdem ändert sich das Änderungsdatum (mtime) der Datei, da der Inhalt verändert wurde.

2. Erklären Sie den Unterschied zwischen der Inode-Nummer und dem Dateinamen. Was bedeutet es, wenn zwei Dateien die gleiche Inode-Nummer haben?

Antwrot:
Die Inode-Nummer ist die eindeutige ID für den Speicherblock auf dem Dateisystem, wo die Metadaten und der Inhalt liegen.

Der Dateiname ist nur ein Verweis auf diese Inode.
→ Wenn zwei Dateien dieselbe Inode-Nummer haben, sind es harte Links, die denselben Inhalt teilen.

3. Wie würde sich das Verhalten ändern, wenn Sie statt eines Hardlinks einen symbolischen Link (Symlink) erstellen würden? Beschreiben Sie die Unterschiede in Bezug auf Metadaten und Verhalten beim Löschen der Originaldatei.

Antwort:
Ein Symlink verweist nur auf den Dateinamen, nicht direkt auf die Inode.

Wird die Originaldatei gelöscht, bleibt der Symlink bestehen, zeigt aber auf eine nicht existierende Datei ("broken link").

Die Metadaten des Symlinks (z. B. Größe) beziehen sich nur auf den Link selbst, nicht auf die Zieldatei.


Als Hilfemittel wurde KI benutzt.
*/

