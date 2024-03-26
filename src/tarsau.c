#include "tarsau.h"

void print_usage() {
    printf("Kullanım: \n");
    printf("tarsau -b dosya1 dosya2 ... -o arsivdosyasi.sau\n");
    printf("tarsau -a arsivdosyasi.sau [hedef_dizin]\n");
}

void merge_files(int argc, char *argv[], const char *output_file) {
    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        perror("Çıkış dosyası oluşturulamadı");
        exit(EXIT_FAILURE);
    }

    for (int i = 2; i < argc - 2; ++i) {
        FILE *input = fopen(argv[i], "r");
        if (input == NULL) {
            perror("Giriş dosyası açılamadı");
            exit(EXIT_FAILURE);
        }

        int ch;
        while ((ch = fgetc(input)) != EOF) {
            fputc(ch, output);
        }

        fclose(input);
    }

    fclose(output);
}

void create_archive(int argc, char *argv[], const char *archive_file) {
    // Organizasyon bilgilerini oluştur
    FileRecord records[MAX_FILES];
    int num_files = 0;
    for (int i = 2; i < argc - 2; ++i) {
        struct stat file_stat;
        if (stat(argv[i], &file_stat) == -1) {
            perror("Dosya istatistikleri alınamadı");
            exit(EXIT_FAILURE);
        }

        if (!S_ISREG(file_stat.st_mode)) {
            fprintf(stderr, "%s dosya biçimi uyumsuz!\n", argv[i]);
            exit(EXIT_FAILURE);
        }

        strncpy(records[num_files].filename, argv[i], sizeof(records[num_files].filename));
        records[num_files].permissions = file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
        records[num_files].size = file_stat.st_size;

        num_files++;

        if (num_files > MAX_FILES) {
            fprintf(stderr, "Maksimum dosya sayısına ulaşıldı!\n");
            exit(EXIT_FAILURE);
        }
    }

    // Arşiv dosyasını oluştur
    FILE *archive = fopen(archive_file, "w");
    if (archive == NULL) {
        perror("Arşiv dosyası oluşturulamadı");
        exit(EXIT_FAILURE);
    }

    // Organizasyon bilgilerini yaz
    fprintf(archive, "%d", num_files);
    for (int i = 0; i < num_files; ++i) {
        fprintf(archive, "|%s,%o,%ld", records[i].filename, records[i].permissions, records[i].size);
    }
    fprintf(archive, "|");

    // Arşivlenen dosyaları yaz
    for (int i = 2; i < argc - 2; ++i) {
        FILE *input = fopen(argv[i], "r");
        if (input == NULL) {
            perror("Giriş dosyası açılamadı");
            exit(EXIT_FAILURE);
        }

        int ch;
        while ((ch = fgetc(input)) != EOF) {
            fputc(ch, archive);
        }

        fclose(input);
    }

    fclose(archive);
}
