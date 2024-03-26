#include <stdio.h>
#include "tarsau.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        print_usage();
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-b") == 0) {
        if (argc < 6) {
            print_usage();
            return EXIT_FAILURE;
        }

        long total_size = 0;
        for (int i = 2; i < argc - 2; ++i) {
            struct stat file_stat;
            if (stat(argv[i], &file_stat) == -1) {
                perror("Dosya istatistikleri alınamadı");
                return EXIT_FAILURE;
            }
            total_size += file_stat.st_size;
        }

        if (total_size > MAX_SIZE_PERMITTED) {
            fprintf(stderr, "Toplam dosya boyutu 200 MByte'dan fazla!\n");
            return EXIT_FAILURE;
        }

        merge_files(argc - 2, argv + 2, argv[argc - 1]);
        printf("Dosyalar birleştirildi.\n");
    } else if (strcmp(argv[1], "-a") == 0) {
        if (argc < 3 || argc > 4) {
            print_usage();
            return EXIT_FAILURE;
        }

        const char *archive_file = argv[2];
        create_archive(argc - 2, argv + 2, archive_file);
        printf("Arşiv oluşturuldu.\n");
    } else {
        print_usage();
        return EXIT_FAILURE;
    }

	while (1) {
        getchar(); // Sonsuz döngüde bir tuşa basılmasını bekler
    }
	
    return EXIT_SUCCESS;
}
