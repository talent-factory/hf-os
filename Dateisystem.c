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
    if (stat(filename, &file_info) != 0) {
        perror("Fehler beim Abrufen der Datei-Metadaten");
        return;
    }
    
    printf("Metadaten für Datei: %s\n", filename);
    printf("------------------------\n");
    
    // Ausgabe der Metadaten
    printf("Dateigröße: %ld Bytes\n", file_info.st_size);
    printf("Inode-Nummer: %lu\n", (unsigned long)file_info.st_ino);
    printf("Anzahl der Hardlinks: %lu\n", (unsigned long)file_info.st_nlink);
    printf("Zugriffsrechte (oktal): %o\n", file_info.st_mode & 0777);
    
    // Formatierte Zeitausgabe
    char time_str[100];
    struct tm *access_time = localtime(&file_info.st_atime);
    strftime(time_str, sizeof(time_str), "%d.%m.%Y %H:%M:%S", access_time);
    printf("Letzter Zugriff: %s\n", time_str);
    
    struct tm *modify_time = localtime(&file_info.st_mtime);
    strftime(time_str, sizeof(time_str), "%d.%m.%Y %H:%M:%S", modify_time);
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
    
    // Fügen Sie weiteren Text zur Datei hinzu
    fprintf(file, "Dieser Text wurde nachträglich hinzugefügt.\n");
    fprintf(file, "Die Metadaten sollten sich nach dieser Änderung aktualisieren.\n");
    fclose(file);
    
    // Metadaten nach der Änderung anzeigen
    printf("Metadaten nach der Änderung:\n");
    print_file_metadata(filename);
    
    // Hardlink erstellen
    const char* hardlink_name = "testdatei_hardlink.txt";
    
    // Erstellen Sie einen Hardlink zur Originaldatei
    if (link(filename, hardlink_name) != 0) {
        perror("Fehler beim Erstellen des Hardlinks");
        remove(filename);
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
