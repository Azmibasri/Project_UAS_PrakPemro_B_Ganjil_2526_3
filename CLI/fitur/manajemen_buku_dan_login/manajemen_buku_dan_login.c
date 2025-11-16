#include "manajemen_buku_dan_login.h"
#include "manajemen_file_data_Pencarian.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Fungsi pembantu untuk simulasi input (di C, ini biasanya fgets/scanf)
void INPUT_STRING(char* dest, int max_len) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Hapus newline jika ada
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(dest, buffer, max_len - 1);
        dest[max_len - 1] = '\0';
    }
}

// Helper untuk membuat objek Buku baru
Buku CREATE_BUKU(const char* id, const char* judul, const char* penulis, const char* kategori, const char* status, int jumlah) {
    Buku bukuBaru;
    strncpy(bukuBaru.ID_Buku, id, MAX_ID_LEN);
    strncpy(bukuBaru.Judul, judul, MAX_STRING_LEN);
    strncpy(bukuBaru.Penulis, penulis, MAX_STRING_LEN);
    strncpy(bukuBaru.Kategori, kategori, MAX_STRING_LEN);
    strncpy(bukuBaru.Status, status, MAX_ID_LEN);
    bukuBaru.JumlahDipinjam = jumlah;
    return bukuBaru;
}

// Helper baru untuk membuat objek Anggota baru
Anggota CREATE_ANGGOTA(const char* id, const char* nama) {
    Anggota anggotaBaru;
    strncpy(anggotaBaru.ID_Anggota, id, MAX_ID_LEN);
    strncpy(anggotaBaru.Nama, nama, MAX_STRING_LEN);
    return anggotaBaru;
}

bool TAMPILKAN_LOGIN() {
    char username[MAX_STRING_LEN];
    char password[MAX_STRING_LEN];

    printf("Username: ");
    INPUT_STRING(username, MAX_STRING_LEN);
    printf("Password: ");
    INPUT_STRING(password, MAX_STRING_LEN);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return true;
    } else {
        return false;
    }
}

void TAMBAH_BUKU_BARU() {
    char id[MAX_ID_LEN];
    char judul[MAX_STRING_LEN];
    char penulis[MAX_STRING_LEN];
    char kategori[MAX_STRING_LEN];

    printf("Masukkan ID Buku baru: ");
    INPUT_STRING(id, MAX_ID_LEN);

    // Cek dulu apakah ID sudah ada
    if (CARI_BUKU_BY_ID(id) != NULL) {
        printf("ID Buku sudah ada!\n");
        return;
    }

    printf("Masukkan Judul: ");
    INPUT_STRING(judul, MAX_STRING_LEN);
    printf("Masukkan Penulis: ");
    INPUT_STRING(penulis, MAX_STRING_LEN);
    printf("Masukkan Kategori: ");
    INPUT_STRING(kategori, MAX_STRING_LEN);
    
    // Buat objek buku baru
    Buku bukuBaru = CREATE_BUKU(id, judul, penulis, kategori, "Tersedia", 0);
    
    // Tambahkan ke list global
    if (globalListBuku.count < MAX_LIST_SIZE) {
        globalListBuku.data[globalListBuku.count++] = bukuBaru;
    } else {
        printf("Error: List Buku penuh.\n");
        return;
    }
    
    // Simpan perubahan ke file .txt
    SIMPAN_LIST_BUKU();
    printf("Buku baru berhasil ditambahkan.\n");
}

void EDIT_INFO_BUKU() {
    char id[MAX_ID_LEN];
    char judulBaru[MAX_STRING_LEN];
    char penulisBaru[MAX_STRING_LEN];
    char kategoriBaru[MAX_STRING_LEN];

    printf("Masukkan ID Buku yang akan diedit: ");
    INPUT_STRING(id, MAX_ID_LEN);
    Buku* buku = CARI_BUKU_BY_ID(id); // Dapatkan pointer ke bukunya
    
    if (buku != NULL) {
        printf("Masukkan Judul baru (lama: %s): ", buku->Judul);
        INPUT_STRING(judulBaru, MAX_STRING_LEN);
        printf("Masukkan Penulis baru (lama: %s): ", buku->Penulis);
        INPUT_STRING(penulisBaru, MAX_STRING_LEN);
        printf("Masukkan Kategori baru (lama: %s): ", buku->Kategori);
        INPUT_STRING(kategoriBaru, MAX_STRING_LEN);
        
        // Update data
        strcpy(buku->Judul, judulBaru);
        strcpy(buku->Penulis, penulisBaru);
        strcpy(buku->Kategori, kategoriBaru);
        
        SIMPAN_LIST_BUKU();
        printf("Data buku berhasil diperbarui.\n");
    } else {
        printf("Buku dengan ID %s tidak ditemukan.\n", id);
    }
}

void HAPUS_BUKU() {
    char id[MAX_ID_LEN];
    printf("Masukkan ID Buku yang akan dihapus: ");
    INPUT_STRING(id, MAX_ID_LEN);

    int index = -1;
    for (int i = 0; i < globalListBuku.count; i++) {
        if (strcmp(globalListBuku.data[i].ID_Buku, id) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        if (strcmp(globalListBuku.data[index].Status, "Dipinjam") == 0) {
            printf("Buku sedang dipinjam dan tidak bisa dihapus!\n");
            return;
        }

        // Geser elemen untuk menghapus (implementasi sederhana untuk array)
        for (int i = index; i < globalListBuku.count - 1; i++) {
            globalListBuku.data[i] = globalListBuku.data[i + 1];
        }
        globalListBuku.count--;

        SIMPAN_LIST_BUKU();
        printf("Buku berhasil dihapus.\n");
    } else {
        printf("Buku tidak ditemukan.\n");
    }
}

// --- IMPLEMENTASI FUNGSI MANAJEMEN ANGGOTA ---

void TAMBAH_ANGGOTA_BARU() {
    char id[MAX_ID_LEN];
    char nama[MAX_STRING_LEN];

    printf("\nMasukkan ID Anggota baru: ");
    INPUT_STRING(id, MAX_ID_LEN);

    // Cek dulu apakah ID sudah ada
    if (CARI_ANGGOTA_BY_ID(id) != NULL) {
        printf("ID Anggota sudah ada!\n");
        return;
    }

    printf("Masukkan Nama Anggota: ");
    INPUT_STRING(nama, MAX_STRING_LEN);
    
    // Buat objek anggota baru
    Anggota anggotaBaru = CREATE_ANGGOTA(id, nama);
    
    // Tambahkan ke list global
    if (globalListAnggota.count < MAX_LIST_SIZE) {
        globalListAnggota.data[globalListAnggota.count++] = anggotaBaru;
    } else {
        printf("Error: List Anggota penuh.\n");
        return;
    }
    
    // Simpan perubahan ke file .txt
    SIMPAN_LIST_ANGGOTA();
    printf("Anggota baru berhasil ditambahkan.\n");
}

void EDIT_INFO_ANGGOTA() {
    char id[MAX_ID_LEN];
    char namaBaru[MAX_STRING_LEN];

    printf("\nMasukkan ID Anggota yang akan diedit: ");
    INPUT_STRING(id, MAX_ID_LEN);
    Anggota* anggota = CARI_ANGGOTA_BY_ID(id); // Dapatkan pointer ke anggotanya
    
    if (anggota != NULL) {
        printf("Masukkan Nama baru (lama: %s): ", anggota->Nama);
        INPUT_STRING(namaBaru, MAX_STRING_LEN);
        
        // Update data
        strcpy(anggota->Nama, namaBaru);
        
        SIMPAN_LIST_ANGGOTA();
        printf("Data anggota berhasil diperbarui.\n");
    } else {
        printf("Anggota dengan ID %s tidak ditemukan.\n", id);
    }
}

void HAPUS_ANGGOTA() {
    char id[MAX_ID_LEN];
    printf("\nMasukkan ID Anggota yang akan dihapus: ");
    INPUT_STRING(id, MAX_ID_LEN);

    int index = -1;
    for (int i = 0; i < globalListAnggota.count; i++) {
        if (strcmp(globalListAnggota.data[i].ID_Anggota, id) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
      
        bool sedangMeminjam = false;
        for (int i = 0; i < globalListTransaksi.count; i++) {
            if (strcmp(globalListTransaksi.data[i].ID_Anggota, id) == 0 && 
                strcmp(globalListTransaksi.data[i].StatusTransaksi, "Dipinjam") == 0) {
                sedangMeminjam = true;
                break;
            }
        }
        
        if (sedangMeminjam) {
            printf("Anggota masih memiliki buku yang sedang dipinjam dan tidak bisa dihapus!\n");
            return;
        }


        for (int i = index; i < globalListAnggota.count - 1; i++) {
            globalListAnggota.data[i] = globalListAnggota.data[i + 1];
        }
        globalListAnggota.count--;

        SIMPAN_LIST_ANGGOTA();
        printf("Anggota berhasil dihapus.\n");
    } else {
        printf("Anggota tidak ditemukan.\n");
    }
}