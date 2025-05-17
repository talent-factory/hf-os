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

    if (stat(filename, &file_info) != 0) {
        perror("stat");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");
    printf("Grösse: %ld Bytes\n", file_info.st_size);
    printf("Inode: %lu\n", file_info.st_ino);
    printf("Anzahl Hardlinks: %lu\n", file_info.st_nlink);
    printf("Rechte (oktal): %o\n", file_info.st_mode & 0777);

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

    // Datei zum Schreiben öffnen (neu anlegen)
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Fehler beim Öffnen der Datei");
        return 1;
    }
    fprintf(file, "%s", content);
    fclose(file);

    printf("Metadaten vor der Änderung:\n");
    print_file_metadata(filename);

    // Datei zum Anhängen öffnen
    file = fopen(filename, "a");
    if (!file) {
        perror("Fehler beim Öffnen zum Anhängen");
        return 1;
    }
    // Zusätzlichen Text anhängen
    fprintf(file, "Dieser Text wird angehängt.\n");
    fclose(file);
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);

    const char* hardlink_name = "testdatei_hardlink.txt";

    // Hardlink erstellen
    if (link(filename, hardlink_name) != 0) {
        perror("Fehler beim Erstellen des Hardlinks");
    } else {
        printf("Hardlink erstellt: %s\n", hardlink_name);

        printf("Metadaten des Hardlinks:\n");
        print_file_metadata(hardlink_name);
    }

    // Dateien löschen
    remove(filename);
    remove(hardlink_name);

    return 0;
}
