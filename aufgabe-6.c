#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

// Funktion zur Ausgabe der Metadaten
void print_file_metadata(const char* filename) {
    struct stat file_info;

    // TODO: Rufen Sie stat() auf, um Informationen über die Datei zu erhalten
    // Hinweis: Überprüfen Sie den Rückgabewert auf Fehler
    if (stat(filename, &file_info) == -1) {
        perror("Fehler beim Abrufen der Metadaten");
        return;
    }

    printf("Metadaten für Datei: %s\n", filename);
    printf("-----------------------\n");

    // TODO: Geben Sie die folgenden Metadaten aus:
    printf("Dateigröße: %lld Bytes\n", (long long)file_info.st_size);
    printf("Inode-Nummer: %llu\n", (unsigned long long)file_info.st_ino);
    printf("Anzahl der Hardlinks: %lu\n", (unsigned long)file_info.st_nlink);
    printf("Zugriffsrechte: %o (Oktalform)\n", file_info.st_mode & 0777);

    // Letzter Zugriff
    char access_time[20];
    strftime(access_time, sizeof(access_time), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_atime));
    printf("Letzter Zugriff: %s\n", access_time);

    // Letzte Änderung
    char modification_time[20];
    strftime(modification_time, sizeof(modification_time), "%Y-%m-%d %H:%M:%S", localtime(&file_info.st_mtime));
    printf("Letzte Änderung: %s\n", modification_time);

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
    fprintf(file, "Hier ist eine zusätzliche Zeile.\n");
    fclose(file);

    // Metadaten nach der Änderung anzeigen
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);

    // Hardlink erstellen
    const char* hardlink_name = "testdatei_hardlink.txt";

    // TODO: Erstellen Sie einen Hardlink zur Originaldatei
    // Hinweis: Verwenden Sie die link()-Funktion
    if (link(filename, hardlink_name) == -1) {
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

