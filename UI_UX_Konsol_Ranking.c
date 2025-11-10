#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUKU 100
#define MAX_ANGGOTA 50
#define MAX_PINJAM 200

// Struktur Data
typedef struct {
    int id;
    char judul[50];
    char penulis[30];
    char kategori[20];
    char status[10]; // "Tersedia" / "Dipinjam"
    int jumlahDipinjam;
} Buku;

typedef struct {
    int id;
    char nama[50];
} Anggota;

typedef struct {
    int idBuku;
    int idAnggota;
    char tglPinjam[20];
    char tglKembali[20];
} Transaksi;

// Global list
Buku daftarBuku[MAX_BUKU];
int totalBuku = 0;

// ----- PROSEDUR UTAMA -----
void tampilkanSemuaBuku();
void tampilkanRankingBuku();
void tampilkanMenuManajemenBuku();
void tampilkanMenuTransaksi();
void tampilkanMenuUtama();
void tambahBukuDummy(); // Isi data dummy

// ----- IMPLEMENTASI -----
void tambahBukuDummy() {
    totalBuku = 5;
    daftarBuku[0] = (Buku){1, "Harry Potter", "J.K. Rowling", "Fiksi", "Tersedia", 15};
    daftarBuku[1] = (Buku){2, "Naruto", "Masashi Kishimoto", "Komik", "Tersedia", 12};
    daftarBuku[2] = (Buku){3, "Laskar Pelangi", "Andrea Hirata", "Fiksi", "Dipinjam", 10};
    daftarBuku[3] = (Buku){4, "Eclipse", "Stephenie Meyer", "Fiksi", "Tersedia", 8};
    daftarBuku[4] = (Buku){5, "Matahari", "Tere Liye", "Fiksi", "Dipinjam", 7};
}

void tampilkanSemuaBuku() {
    printf("\n--- DAFTAR BUKU ---\n");
    printf("ID\tJudul\t\t\tPenulis\t\tStatus\t\tJumlah Dipinjam\n");
    printf("--------------------------------------------------------------\n");
    for(int i = 0; i < totalBuku; i++) {
        printf("%d\t%-20s\t%-15s\t%-10s\t%d\n", daftarBuku[i].id, daftarBuku[i].judul,
               daftarBuku[i].penulis, daftarBuku[i].status, daftarBuku[i].jumlahDipinjam);
    }
    printf("\n");
}

int compareBuku(const void *a, const void *b) {
    Buku *b1 = (Buku *)a;
    Buku *b2 = (Buku *)b;
    return b2->jumlahDipinjam - b1->jumlahDipinjam; // Descending
}

void tampilkanRankingBuku() {
    printf("\n--- RANKING BUKU TERPOPULER ---\n");
    // Buat copy array sementara
    Buku temp[MAX_BUKU];
    memcpy(temp, daftarBuku, sizeof(Buku)*totalBuku);

    // Urutkan berdasarkan jumlahDipinjam
    qsort(temp, totalBuku, sizeof(Buku), compareBuku);

    printf("Rank\tJudul\t\t\tJumlah Dipinjam\n");
    printf("-----------------------------------------\n");
    int limit = totalBuku < 5 ? totalBuku : 5;
    for(int i = 0; i < limit; i++) {
        printf("%d\t%-20s\t%d\n", i+1, temp[i].judul, temp[i].jumlahDipinjam);
    }
    printf("\n");
}

void tampilkanMenuManajemenBuku() {
    int pilihan;
    printf("\n--- MENU MANAJEMEN BUKU ---\n");
    printf("1. Tambah Buku Baru\n");
    printf("2. Edit Buku (Placeholder)\n");
    printf("3. Hapus Buku (Placeholder)\n");
    printf("4. Lihat Semua Buku\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    switch(pilihan) {
        case 1:
            printf("Fitur Tambah Buku Baru (Placeholder)\n");
            break;
        case 2:
            printf("Fitur Edit Buku (Placeholder)\n");
            break;
        case 3:
            printf("Fitur Hapus Buku (Placeholder)\n");
            break;
        case 4:
            tampilkanSemuaBuku();
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid!\n");
    }
    tampilkanMenuManajemenBuku();
}

void tampilkanMenuTransaksi() {
    int pilihan;
    printf("\n--- MENU TRANSAKSI ---\n");
    printf("1. Peminjaman Buku (Placeholder)\n");
    printf("2. Pengembalian Buku (Placeholder)\n");
    printf("0. Kembali ke Menu Utama\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    switch(pilihan) {
        case 1:
            printf("Fitur Peminjaman Buku (Placeholder)\n");
            break;
        case 2:
            printf("Fitur Pengembalian Buku (Placeholder)\n");
            break;
        case 0:
            return;
        default:
            printf("Pilihan tidak valid!\n");
    }
    tampilkanMenuTransaksi();
}

void tampilkanMenuUtama() {
    int pilihan;
    do {
        printf("\n=== MENU UTAMA PERPUSTAKAAN MINI ===\n");
        printf("1. Manajemen Buku\n");
        printf("2. Manajemen Anggota (Placeholder)\n");
        printf("3. Transaksi (Pinjam/Kembali)\n");
        printf("4. Cari Buku (Placeholder)\n");
        printf("5. Ranking Buku Terpopuler\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                tampilkanMenuManajemenBuku();
                break;
            case 2:
                printf("Fitur Manajemen Anggota (Placeholder)\n");
                break;
            case 3:
                tampilkanMenuTransaksi();
                break;
            case 4:
                printf("Fitur Cari Buku (Placeholder)\n");
                break;
            case 5:
                tampilkanRankingBuku();
                break;
            case 0:
                printf("Terima kasih! Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while(pilihan != 0);
}

// ----- MAIN -----
int main() {
    tambahBukuDummy(); // Isi data dummy untuk testing
    tampilkanMenuUtama();
    return 0;
}
