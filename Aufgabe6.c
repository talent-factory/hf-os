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

    // Rufen Sie stat() auf, um Informationen über die Datei zu erhalten
    if (stat(filename, &file_info) == -1) {
        perror("Fehler beim Abrufen der Dateiinformationen");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");

    // Geben Sie die folgenden Metadaten aus:
    printf("Dateigrösse: %lld Bytes\n", (long long)file_info.st_size);
    printf("Inode-Nummer: %lu\n", (unsigned long)file_info.st_ino);
    printf("Anzahl der Hardlinks: %lu\n", (unsigned long)file_info.st_nlink);
    printf("Zugriffsrechte (Oktal): %o\n", file_info.st_mode & 0777);

    // Letzter Zugriff (als formatiertes Datum)
    char access_time_str[100];
    strftime(access_time_str, sizeof(access_time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_atime));
    printf("Letzter Zugriff: %s\n", access_time_str);

    // Letzte Änderung (als formatiertes Datum)
    char modification_time_str[100];
    strftime(modification_time_str, sizeof(modification_time_str), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_mtime));
    printf("Letzte Änderung: %s\n", modification_time_str);

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

    // Fügen Sie weiteren Text zur Datei hinzu
    fprintf(file, "Zusätzlicher Inhalt wurde angehängt.\n");

    fclose(file);

    // Metadaten nach der Änderung anzeigen
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);

    // Hardlink erstellen
    const char* hardlink_name = "testdatei_hardlink.txt";

    // Erstellen Sie einen Hardlink zur Originaldatei
    if (link(filename, hardlink_name) == -1) {
        perror("Fehler beim Erstellen des Hardlinks");
        return 1;
    }

    printf("Hardlink erstellt: %s\n", hardlink_name);

    // Metadaten des Hardlinks anzeigen
    printf("Metadaten des Hardlinks:\n");
    print_file_metadata(hardlink_name);

    // Dateien löschen
    if (remove(filename) == -1) {
        perror("Fehler beim Löschen der Originaldatei");
        return 1;
    }
    if (remove(hardlink_name) == -1) {
        perror("Fehler beim Löschen des Hardlinks");
        return 1;
    }

    return 0;
}
