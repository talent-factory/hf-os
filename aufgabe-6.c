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

    // stat() liefert alle Metadaten zu einer Datei
    if (stat(filename, &file_info) != 0) {
        perror("Fehler beim Abrufen der Metadaten");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");

    // Dateigröße
    printf("Größe: %lld Bytes\n", (long long)file_info.st_size);

    // Inode-Nummer
    printf("Inode: %ld\n", (long)file_info.st_ino);

    // Anzahl der Hardlinks
    printf("Hardlinks: %ld\n", (long)file_info.st_nlink);

    // Zugriffsrechte in Oktalform
    printf("Berechtigungen (Oktal): %o\n", file_info.st_mode & 0777);

    // Zeitformatierung
    char time_str[30];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_atime));
    printf("Letzter Zugriff: %s\n", time_str);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_mtime));
    printf("Letzte Änderung: %s\n", time_str);

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

    // Zusätzlicher Inhalt → bewirkt Änderung am Inhalt und Metadaten
    fprintf(file, "Dieser Text wurde später hinzugefügt.\n");
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
