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

    // Datei-Infos abrufen
    if (stat(filename, &file_info) != 0) {
        perror("stat");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");
    printf("Dateigrösse: %ld Bytes\n", file_info.st_size);
    printf("Inode-Nummer: %ld\n", file_info.st_ino);
    printf("Anzahl der Hardlinks: %ld\n", file_info.st_nlink);
    printf("Zugriffsrechte (oktal): %o\n", file_info.st_mode & 0777);

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

    // Datei öffnen und Text anhängen
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Fehler beim Öffnen der Datei zum Anhängen");
        return 1;
    }

    // Weiteren Text hinzufügen
    fprintf(file, "Zusätzlicher Inhalt zur Demonstration der Änderung.\n");
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
    }

    // Metadaten des Hardlinks anzeigen
    printf("Metadaten des Hardlinks:\n");
    print_file_metadata(hardlink_name);

    // Dateien löschen
    remove(filename);
    remove(hardlink_name);

    return 0;
}

