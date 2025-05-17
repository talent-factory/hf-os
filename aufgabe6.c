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

    // TODO: Rufen Sie stat() auf, um Informationen über die Datei zu erhalten
    // Hinweis: Überprüfen Sie den Rückgabewert auf Fehler
    if (stat(filename, &file_info) != 0) {
        perror("stat");
        return;
    }

    // TODO: Geben Sie die folgenden Metadaten aus:
    // - Dateigrösse in Bytes
    // - Inode-Nummer
    // - Anzahl der Hardlinks
    // - Zugriffsrechte (in Oktalform)
    // - Letzter Zugriff (als formatiertes Datum)
    // - Letzte Änderung (als formatiertes Datum)
    char access_time[30];
    char mod_time[30];

    strftime(access_time, sizeof(access_time), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_atime));
    strftime(mod_time, sizeof(mod_time), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_mtime));
    
    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");
    printf("Dateigrösse in bytes: %ld\n", file_info.st_size);
    printf("Inode-Num: %ld\n", file_info.st_ino);
    printf("Anzahl Hardlinks: %ld\n", file_info.st_nlink);
    printf("Zugriffsrechte (oktal): %o\n", file_info.st_mode & 0777);
    printf("Letzter Zugriff: %s\n", access_time);
    printf("Letzte Änderung: %s\n", mod_time);
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

    // TODO: Fügen Sie weiteren Text zur Datei hinzu
    // Hinweis: Verwenden Sie fprintf()
    fprintf(file, "%s", content);

    fclose(file);

    // Metadaten nach der Änderung anzeigen
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);

    // Hardlink erstellen
    const char* hardlink_name = "testdatei_hardlink.txt";

    // TODO: Erstellen Sie einen Hardlink zur Originaldatei
    // Hinweis: Verwenden Sie die link()-Funktion
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
