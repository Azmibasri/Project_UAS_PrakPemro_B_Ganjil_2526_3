#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI_UX_Konsol_Ranking.h"

// ===================================================
// Variabel global
// ===================================================
Buku globalListBuku[100];
int totalBuku = 0;

// ===================================================
// Fungsi tambahan untuk testing
// ===================================================
void TAMBAH_BUKU_DUMMY() {
    totalBuku = 5;
    globalListBuku[0] = (Buku){1, "Harry Potter", "J.K. Rowling", "Fiksi", "Tersedia", 15};
    globalListBuku[1] = (Buku){2, "Naruto", "Masashi Kishimoto", "Komik", "Tersedia", 12};
    globalListBuku[2] = (Buku){3, "Laskar Pelangi", "Andrea Hirata", "Fiksi", "Dipinjam", 10};
    globalListBuku[3] = (Buku){4, "Eclipse", "Stephenie Meyer", "Fiksi", "Tersedia", 8};
    globalListBuku[4] = (Buku){5, "Matahari", "Tere Liye", "Fiksi", "Dipinjam", 7};
}

// ===================================================
// Fungsi tampilkan semua buku
// ===================================================
void TAMPILKAN_SEMUA_BUKU() {
    printf("\n--- DAFTAR SEMUA BUKU ---\n");
    printf("ID\tJudul\t\t\tPenulis\t\tStatus\tJumlahDipinjam\n");
    printf("-----------------------------------------------------------\n");
    for(int i = 0; i < totalBuku; i++) {
        printf("%d\t%-20s\t%-15s\t%-10s\t%d\n", globalListBuku[i].ID_Buku, 
               globalListBuku[i].Judul, globalListBuku[i].Penulis, 
               globalListBuku[i].Status, globalListBuku[i].JumlahDipinjam);
    }
}

// ===================================================
// Fungsi ranking buku
// ===================================================
void TAMPILKAN_RANKING_BUKU() {
    Buku temp[100];
    memcpy(temp, globalListBuku, sizeof(Buku)*totalBuku);

    // Sort descending
    for(int i=0; i<totalBuku-1; i++){
        for(int j=i+1; j<totalBuku; j++){
            if(temp[j].JumlahDipinjam > temp[i].JumlahDipinjam){
                Buku t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    printf("\n--- RANKING BUKU TERPOPULER ---\n");
    for(int i=0; i<totalBuku && i<5; i++){
        printf("%d. %s (%d kali dipinjam)\n", i+1, temp[i].Judul, temp[i].JumlahDipinjam);
    }
}

// ===================================================
// Menu Manajemen Buku
// ===================================================
void TAMPILKAN_MENU_MANAJEMEN_BUKU() {
    int pilihan;
    do {
        printf("\n--- MENU MANAJEMEN BUKU ---\n");
        printf("1. Tambah Buku Baru (Placeholder)\n");
        printf("2. Edit Informasi Buku (Placeholder)\n");
        printf("3. Hapus Buku (Placeholder)\n");
        printf("4. Lihat Semua Daftar Buku\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan){
            case 1: printf("Fitur Tambah Buku (Placeholder)\n"); break;
            case 2: printf("Fitur Edit Buku (Placeholder)\n"); break;
            case 3: printf("Fitur Hapus Buku (Placeholder)\n"); break;
            case 4: TAMPILKAN_SEMUA_BUKU(); break;
            case 0: break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while(pilihan != 0);
}

// ===================================================
// Menu Transaksi (Placeholder)
// ===================================================
void TAMPILKAN_MENU_TRANSAKSI() {
    printf("Fitur Transaksi (Pinjam/Kembali) - Placeholder\n");
}

// ===================================================
// Menu utama
// ===================================================
void TAMPILKAN_MENU_UTAMA() {
    int pilihan;
    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Manajemen Buku\n");
        printf("2. Manajemen Anggota (Placeholder)\n");
        printf("3. Transaksi (Pinjam/Kembali)\n");
        printf("4. Cari Buku (Placeholder)\n");
        printf("5. Tampilkan Ranking Buku Terpopuler\n");
        printf("6. Lihat Riwayat Pinjam Anggota (Placeholder)\n");
        printf("7. Pengaturan Sistem (Placeholder)\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan){
            case 1: TAMPILKAN_MENU_MANAJEMEN_BUKU(); break;
            case 2: printf("Fitur Manajemen Anggota (Placeholder)\n"); break;
            case 3: TAMPILKAN_MENU_TRANSAKSI(); break;
            case 4: printf("Fitur Pencarian Buku (Placeholder)\n"); break;
            case 5: TAMPILKAN_RANKING_BUKU(); break;
            case 6: printf("Riwayat Pinjam Anggota (Placeholder)\n"); break;
            case 7: printf("Pengaturan Sistem (Denda/Durasi) - Placeholder\n"); break;
            case 0: printf("Keluar dari sistem.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while(pilihan != 0);
}

// ===================================================
// Fungsi main
// ===================================================
int main() {
    TAMBAH_BUKU_DUMMY();
    TAMPILKAN_MENU_UTAMA();
    return 0;
}


