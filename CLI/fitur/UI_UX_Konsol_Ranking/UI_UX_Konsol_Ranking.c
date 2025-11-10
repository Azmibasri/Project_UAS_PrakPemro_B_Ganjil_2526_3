#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI_UX_Konsol_Ranking.h"

// ===================================================
// Variabel global
// ===================================================
Buku daftarBuku[100];
int totalBuku = 0;

// ===================================================
// Fungsi untuk menambah data dummy (contoh awal)
// ===================================================
void tambahBukuDummy() {
    totalBuku = 5;
    daftarBuku[0] = (Buku){1, "Harry Potter", "J.K. Rowling", "Fiksi", "Tersedia", 15};
    daftarBuku[1] = (Buku){2, "Naruto", "Masashi Kishimoto", "Komik", "Tersedia", 12};
    daftarBuku[2] = (Buku){3, "Laskar Pelangi", "Andrea Hirata", "Fiksi", "Dipinjam", 10};
    daftarBuku[3] = (Buku){4, "Eclipse", "Stephenie Meyer", "Fiksi", "Tersedia", 8};
    daftarBuku[4] = (Buku){5, "Matahari", "Tere Liye", "Fiksi", "Dipinjam", 7};
}

// ===================================================
// Fungsi tampilkan semua buku
// ===================================================
void tampilkanSemuaBuku() {
    printf("\n==============================================\n");
    printf("             DAFTAR SEMUA BUKU\n");
    printf("==============================================\n");

    for (int i = 0; i < totalBuku; i++) {
        printf("ID: %d\n", daftarBuku[i].id);
        printf("Judul: %s\n", daftarBuku[i].judul);
        printf("Penulis: %s\n", daftarBuku[i].penulis);
        printf("Kategori: %s\n", daftarBuku[i].kategori);
        printf("Status: %s\n", daftarBuku[i].status);
        printf("Jumlah Dipinjam: %d\n", daftarBuku[i].jumlahDipinjam);
        printf("----------------------------------------------\n");
    }
}

// ===================================================
// Fungsi untuk menampilkan buku dengan ranking peminjaman tertinggi
// ===================================================
void tampilkanRankingBuku() {
    if (totalBuku == 0) {
        printf("Belum ada data buku!\n");
        return;
    }

    // Sorting berdasarkan jumlah dipinjam (descending)
    Buku temp;
    for (int i = 0; i < totalBuku - 1; i++) {
        for (int j = i + 1; j < totalBuku; j++) {
            if (daftarBuku[j].jumlahDipinjam > daftarBuku[i].jumlahDipinjam) {
                temp = daftarBuku[i];
                daftarBuku[i] = daftarBuku[j];
                daftarBuku[j] = temp;
            }
        }
    }

    printf("\n==============================================\n");
    printf("         RANKING BUKU TERLARIS\n");
    printf("==============================================\n");

    for (int i = 0; i < totalBuku; i++) {
        printf("%d. %s (%d kali dipinjam)\n", i + 1, daftarBuku[i].judul, daftarBuku[i].jumlahDipinjam);
    }
}

// ===================================================
// Fungsi untuk manajemen buku (contoh sederhana)
// ===================================================
void tampilkanMenuManajemenBuku() {
    int pilihan;
    do {
        printf("\n==============================================\n");
        printf("           MENU MANAJEMEN BUKU\n");
        printf("==============================================\n");
        printf("1. Tampilkan Semua Buku\n");
        printf("2. Ranking Buku Terlaris\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanSemuaBuku();
                break;
            case 2:
                tampilkanRankingBuku();
                break;
            case 3:
                printf("Kembali ke Menu Utama...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 3);
}

// ===================================================
// Fungsi transaksi (contoh placeholder)
// ===================================================
void tampilkanMenuTransaksi() {
    printf("\n--- Fitur Transaksi (Belum diimplementasikan) ---\n");
}

// ===================================================
// Menu utama
// ===================================================
void tampilkanMenuUtama() {
    int pilihan;
    do {
        printf("\n==============================================\n");
        printf("         SISTEM RANKING PERPUSTAKAAN\n");
        printf("==============================================\n");
        printf("1. Manajemen Buku\n");
        printf("2. Transaksi\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanMenuManajemenBuku();
                break;
            case 2:
                tampilkanMenuTransaksi();
                break;
            case 3:
                printf("Terima kasih telah menggunakan sistem ini!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 3);
}

// ===================================================
// Fungsi main
// ===================================================
int main() {
    tambahBukuDummy();
    tampilkanMenuUtama();
    return 0;
}
