#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Struktur data buku
typedef struct {
    int id;
    char judul[100];
    char penulis[100];
    int tahun;
} Buku;

// Menyimpan data buku ke file txt
void simpanBuku(const char *namaFile, Buku buku) {
    FILE *file = fopen(namaFile, "a"); // mode append
    if (file == NULL) {
        printf("Gagal membuka file %s!\n", namaFile);
        return;
    }
    fprintf(file, "%d|%s|%s|%d\n", buku.id, buku.judul, buku.penulis, buku.tahun);
    fclose(file);
    printf("Data buku berhasil disimpan!\n");
}

// Menampilkan semua data buku dari file
void tampilkanBuku(const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Belum ada data buku.\n");
        return;
    }

    Buku buku;
    char baris[200];

    printf("\n=== DAFTAR BUKU ===\n");
    while (fgets(baris, sizeof(baris), file)) {
        sscanf(baris, "%d|%[^|]|%[^|]|%d", &buku.id, buku.judul, buku.penulis, &buku.tahun);
        printf("ID: %d\nJudul: %s\nPenulis: %s\nTahun: %d\n\n",
               buku.id, buku.judul, buku.penulis, buku.tahun);
    }
    fclose(file);
}

// Mencari buku berdasarkan keyword (judul atau penulis)
void cariBuku(const char *namaFile, const char *keyword) {
    FILE *file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Belum ada data buku.\n");
        return;
    }

    Buku buku;
    char baris[200];
    int ditemukan = 0;

    printf("\n=== HASIL PENCARIAN '%s' ===\n", keyword);
    while (fgets(baris, sizeof(baris), file)) {
        sscanf(baris, "%d|%[^|]|%[^|]|%d", &buku.id, buku.judul, buku.penulis, &buku.tahun);

        if (strstr(buku.judul, keyword) || strstr(buku.penulis, keyword)) {
            printf("ID: %d\nJudul: %s\nPenulis: %s\nTahun: %d\n\n",
                   buku.id, buku.judul, buku.penulis, buku.tahun);
            ditemukan = 1;
        }
    }

    if (!ditemukan)
        printf("Tidak ada buku yang cocok dengan keyword '%s'.\n", keyword);

    fclose(file);
}

// Menu utama
int main() {
    Buku buku;
    int pilihan;
    char keyword[100];
    const char *namaFile = "data_buku.txt";

    do {
        printf("\n=== MENU MANAJEMEN FILE & PENCARIAN ===\n");
        printf("1. Tambah data buku\n");
        printf("2. Tampilkan semua buku\n");
        printf("3. Cari buku\n");
        printf("4. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        getchar(); // hapus newline

        switch (pilihan) {
            case 1:
                printf("Masukkan ID Buku   : ");
                scanf("%d", &buku.id);
                getchar();

                printf("Masukkan Judul     : ");
                fgets(buku.judul, sizeof(buku.judul), stdin);
                buku.judul[strcspn(buku.judul, "\n")] = 0;

                printf("Masukkan Penulis   : ");
                fgets(buku.penulis, sizeof(buku.penulis), stdin);
                buku.penulis[strcspn(buku.penulis, "\n")] = 0;

                printf("Masukkan Tahun Terbit: ");
                scanf("%d", &buku.tahun);

                simpanBuku(namaFile, buku);
                break;

            case 2:
                tampilkanBuku(namaFile);
                break;

            case 3:
                printf("Masukkan kata kunci (judul/penulis): ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = 0;
                cariBuku(namaFile, keyword);
                break;

            case 4:
                printf("Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);

    return 0;
}
