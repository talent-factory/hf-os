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

    /* --- Metadaten ermitteln ------------------------------------------- */
    if (stat(filename, &file_info) != 0) {
        perror("stat");
        return;
    }

    printf("Metadaten fuer Datei: %s\n", filename);
    printf("------------------------\n");

    /* --- Metadaten ausgeben -------------------------------------------- */
    printf("Dateigroesse (Bytes): %lld\n",        (long long)file_info.st_size);
    printf("Inode‑Nummer:         %llu\n",        (unsigned long long)file_info.st_ino);
    printf("Hardlinks:            %lu\n",         (unsigned long)file_info.st_nlink);
    printf("Zugriffsrechte(oct):  %o\n",          file_info.st_mode & 07777);

    char time_str[30];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S",
             localtime(&file_info.st_atime));
    printf("Letzter Zugriff:      %s\n", time_str);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S",
             localtime(&file_info.st_mtime));
    printf("Letzte Aenderung:     %s\n\n", time_str);
}

int main() {
    const char* filename = "testdatei.txt";
    const char* content  = "Dies ist ein Test fuer Dateioperationen.\n"
                           "Wir untersuchen, wie Dateisysteme Metadaten verwalten.\n";

    /* Datei anlegen und Basisinhalt schreiben --------------------------- */
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Fehler beim Oeffnen der Datei");
        return 1;
    }
    fprintf(file, "%s", content);
    fclose(file);

    /* Metadaten VOR Aenderung ------------------------------------------- */
    puts("Metadaten vor der Aenderung:");
    print_file_metadata(filename);

    /* Datei zum Anhängen oeffnen ---------------------------------------- */
    file = fopen(filename, "a");
    if (!file) {
        perror("Fehler beim Oeffnen der Datei zum Anhaengen");
        return 1;
    }

    /* --- Zusaetzlichen Text anhaengen ---------------------------------- */
    fprintf(file, "Dies ist eine zusaetzliche Zeile, um die Datei zu vergroessern.\n");
    fclose(file);

    /* Metadaten NACH Aenderung ------------------------------------------ */
    puts("Metadaten nach der Aenderung:");
    print_file_metadata(filename);

    /* Hardlink anlegen --------------------------------------------------- */
    const char* hardlink_name = "testdatei_hardlink.txt";
    if (link(filename, hardlink_name) != 0) {
        perror("Fehler beim Erstellen des Hardlinks");
        return 1;
    }
    printf("Hardlink erstellt: %s\n\n", hardlink_name);

    /* Metadaten des Hardlinks ------------------------------------------- */
    puts("Metadaten des Hardlinks:");
    print_file_metadata(hardlink_name);

    /* Aufraeumen --------------------------------------------------------- */
    remove(filename);
    remove(hardlink_name);
    return 0;
}
