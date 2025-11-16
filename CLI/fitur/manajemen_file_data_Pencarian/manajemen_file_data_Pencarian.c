#include "manajemen_file_data_Pencarian.h"
#include <ctype.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define FILE_BUKU "buku.data"
#define FILE_ANGGOTA "anggota.data"
#define FILE_TRANSAKSI "transaksi.data"

// --- DEFINISI GLOBAL DATA LISTS ---
ListBuku globalListBuku = { .count = 0 };
ListAnggota globalListAnggota = { .count = 0 };
ListTransaksi globalListTransaksi = { .count = 0 };

// --- DEFINISI FUNGSI I/O FILE (Diperbarui) ---

void LOAD_DATA_DARI_FILE() {
    FILE *fileBuku = fopen(FILE_BUKU, "rb");
    
    // 1. Muat Data Buku
    if (fileBuku != NULL) {
        // Baca jumlah data (count)
        fread(&globalListBuku.count, sizeof(int), 1, fileBuku);
        
        // Baca seluruh array data
        if (globalListBuku.count > 0) {
            fread(globalListBuku.data, sizeof(Buku), globalListBuku.count, fileBuku);
        }
        fclose(fileBuku);
    } else {
        printf("[File] File buku.data tidak ditemukan. Membuat daftar baru.\n");
        // Jika file tidak ada, count tetap 0
    }

    // 2. Muat Data Anggota (Stub I/O biner)
    FILE *fileAnggota = fopen(FILE_ANGGOTA, "rb");
    if (fileAnggota != NULL) {
        fread(&globalListAnggota.count, sizeof(int), 1, fileAnggota);
        if (globalListAnggota.count > 0) {
            fread(globalListAnggota.data, sizeof(Anggota), globalListAnggota.count, fileAnggota);
        }
        fclose(fileAnggota);
    }

    // 3. Muat Data Transaksi (Stub I/O biner)
    FILE *fileTransaksi = fopen(FILE_TRANSAKSI, "rb");
    if (fileTransaksi != NULL) {
        fread(&globalListTransaksi.count, sizeof(int), 1, fileTransaksi);
        if (globalListTransaksi.count > 0) {
            fread(globalListTransaksi.data, sizeof(Transaksi), globalListTransaksi.count, fileTransaksi);
        }
        fclose(fileTransaksi);
    }

    // Contoh dummy data (dihapus karena sudah ada I/O file)
    
    printf("Data berhasil dimuat.\n");
}

void SIMPAN_LIST_BUKU() {
    FILE *fileBuku = fopen(FILE_BUKU, "wb"); // Mode Write Binary
    if (fileBuku != NULL) {
        // 1. Tulis jumlah data (count)
        fwrite(&globalListBuku.count, sizeof(int), 1, fileBuku);
        
        // 2. Tulis seluruh array data
        if (globalListBuku.count > 0) {
            fwrite(globalListBuku.data, sizeof(Buku), globalListBuku.count, fileBuku);
        }
        fclose(fileBuku);
        printf("[File] Data Buku berhasil disimpan ke %s.\n", FILE_BUKU);
    } else {
        perror("[File Error] Gagal membuka file buku.data untuk menulis.");
    }
}

void SIMPAN_LIST_ANGGOTA() {
    FILE *fileAnggota = fopen(FILE_ANGGOTA, "wb");
    if (fileAnggota != NULL) {
        fwrite(&globalListAnggota.count, sizeof(int), 1, fileAnggota);
        if (globalListAnggota.count > 0) {
            fwrite(globalListAnggota.data, sizeof(Anggota), globalListAnggota.count, fileAnggota);
        }
        fclose(fileAnggota);
        printf("[File] Data Anggota berhasil disimpan ke %s.\n", FILE_ANGGOTA);
    } else {
        perror("[File Error] Gagal membuka file anggota.data untuk menulis.");
    }
}

void SIMPAN_LIST_TRANSAKSI() {
    FILE *fileTransaksi = fopen(FILE_TRANSAKSI, "wb");
    if (fileTransaksi != NULL) {
        fwrite(&globalListTransaksi.count, sizeof(int), 1, fileTransaksi);
        if (globalListTransaksi.count > 0) {
            fwrite(globalListTransaksi.data, sizeof(Transaksi), globalListTransaksi.count, fileTransaksi);
        }
        fclose(fileTransaksi);
        printf("[File] Data Transaksi berhasil disimpan ke %s.\n", FILE_TRANSAKSI);
    } else {
        perror("[File Error] Gagal membuka file transaksi.data untuk menulis.");
    }
}

void SAVE_SEMUA_DATA_KE_FILE() {
    SIMPAN_LIST_BUKU();
    SIMPAN_LIST_ANGGOTA();
    SIMPAN_LIST_TRANSAKSI();
}

// --- DEFINISI FUNGSI PENCARIAN (Tidak Berubah) ---

Buku* CARI_BUKU_BY_ID(const char* id) {
    for (int i = 0; i < globalListBuku.count; i++) {
        if (strcmp(globalListBuku.data[i].ID_Buku, id) == 0) {
            return &globalListBuku.data[i]; 
        }
    }
    return NULL;
}

Anggota* CARI_ANGGOTA_BY_ID(const char* id) {
    for (int i = 0; i < globalListAnggota.count; i++) {
        if (strcmp(globalListAnggota.data[i].ID_Anggota, id) == 0) {
            return &globalListAnggota.data[i];
        }
    }
    return NULL;
}

Transaksi* CARI_TRANSAKSI_BY_ID(const char* id) {
    for (int i = 0; i < globalListTransaksi.count; i++) {
        if (strcmp(globalListTransaksi.data[i].ID_Transaksi, id) == 0) {
            return &globalListTransaksi.data[i];
        }
    }
    return NULL;
}

Transaksi* CARI_TRANSAKSI_AKTIF_BY_BUKU_ID(const char* id) {
    for (int i = 0; i < globalListTransaksi.count; i++) {
        if (strcmp(globalListTransaksi.data[i].ID_Buku, id) == 0 && 
            strcmp(globalListTransaksi.data[i].StatusTransaksi, "Dipinjam") == 0) {
            return &globalListTransaksi.data[i];
        }
    }
    Transaksi* trx = CARI_TRANSAKSI_BY_ID(id);
    if (trx != NULL && strcmp(trx->StatusTransaksi, "Dipinjam") == 0) {
        return trx;
    }

    return NULL;
}

int str_contains_insensitive(const char* haystack, const char* needle) {
    if (!*needle) return 1;

    char h_lower[MAX_STRING_LEN];
    char n_lower[MAX_STRING_LEN];

    size_t len_h = strlen(haystack);
    size_t len_n = strlen(needle);

    if (len_h >= MAX_STRING_LEN || len_n >= MAX_STRING_LEN) {
        return 0;
    }

    for (size_t i = 0; i <= len_h; i++) {
        h_lower[i] = tolower((unsigned char)haystack[i]);
    }
    for (size_t i = 0; i <= len_n; i++) {
        n_lower[i] = tolower((unsigned char)needle[i]);
    }
    
    if (strstr(h_lower, n_lower) != NULL) {
        return 1;
    }
    return 0;
}

void CARI_BUKU_BY_JUDUL(const char* judul) {
    printf("--- Hasil Pencarian (Judul: '%s') ---\n", judul);
    int ditemukan = 0;
    for (int i = 0; i < globalListBuku.count; i++) {
        if (str_contains_insensitive(globalListBuku.data[i].Judul, judul)) {
            printf("ID: %s, Judul: %s, Penulis: %s, Status: %s\n", 
                   globalListBuku.data[i].ID_Buku, 
                   globalListBuku.data[i].Judul, 
                   globalListBuku.data[i].Penulis, 
                   globalListBuku.data[i].Status);
            ditemukan = 1;
        }
    }
    if (!ditemukan) {
        printf("Buku tidak ditemukan berdasarkan Judul.\n");
    }
}

void CARI_BUKU_BY_PENULIS(const char* penulis) {
    printf("--- Hasil Pencarian (Penulis: '%s') ---\n", penulis);
    int ditemukan = 0;
    for (int i = 0; i < globalListBuku.count; i++) {
        if (str_contains_insensitive(globalListBuku.data[i].Penulis, penulis)) {
            printf("ID: %s, Judul: %s, Penulis: %s, Status: %s\n", 
                   globalListBuku.data[i].ID_Buku, 
                   globalListBuku.data[i].Judul, 
                   globalListBuku.data[i].Penulis, 
                   globalListBuku.data[i].Status);
            ditemukan = 1;
        }
    }
    if (!ditemukan) {
        printf("Buku tidak ditemukan berdasarkan Penulis.\n");
    }
}

void CARI_BUKU_BY_KATEGORI(const char* kategori) {
    printf("--- Hasil Pencarian (Kategori: '%s') ---\n", kategori);
    int ditemukan = 0;
    for (int i = 0; i < globalListBuku.count; i++) {
        if (str_contains_insensitive(globalListBuku.data[i].Kategori, kategori)) {
            printf("ID: %s, Judul: %s, Penulis: %s, Status: %s\n", 
                   globalListBuku.data[i].ID_Buku, 
                   globalListBuku.data[i].Judul, 
                   globalListBuku.data[i].Penulis, 
                   globalListBuku.data[i].Status);
            ditemukan = 1;
        }
    }
    if (!ditemukan) {
        printf("Buku tidak ditemukan berdasarkan Kategori.\n");
    }
}