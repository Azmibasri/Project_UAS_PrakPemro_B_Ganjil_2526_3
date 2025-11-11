#include <stdio.h>
#include <string.h>
#include <time.h>

// Data anggota, buku, dan transaksi
struct Anggota {
    char id[10];
    char nama[50];
};

struct Buku {
    char id[10];
    char judul[50];
    char status[20]; // status buku: tersedia / dipinjam
};

struct Transaksi {
    char idTransaksi[10];
    char idBuku[10];
    char idAnggota[10];
    char status[20]; // status transaksi: dipinjam / selesai
    int denda;
};

// Data contoh (sementara) buat ngetes program
struct Anggota dataAnggota = {"A001", "Althaffia"};
struct Buku dataBuku = {"B001", "Pemrograman C", "Tersedia"};

// Fungsi buat ngitung denda
int HITUNG_DENDA(int selisihHari) {
    int dendaPerHari = 1000; // misalnya 1000 per hari
    if (selisihHari > 0)
        return selisihHari * dendaPerHari;
    else
        return 0;
}

// Proses saat anggota mau minjam buku
void PROSES_PEMINJAMAN_BUKU() {
    char idAnggota[10], idBuku[10];

    printf("\n=== PEMINJAMAN BUKU ===\n");
    printf("Masukkan ID Anggota: ");
    scanf("%s", idAnggota);

    // Cek apakah ID anggota sesuai
    if (strcmp(idAnggota, dataAnggota.id) != 0) {
        printf("Anggota tidak ditemukan.\n");
        return;
    }

    printf("Masukkan ID Buku: ");
    scanf("%s", idBuku);

    // Cek apakah ID buku sesuai
    if (strcmp(idBuku, dataBuku.id) != 0) {
        printf("Buku tidak ditemukan.\n");
        return;
    }

    // Cek kalau bukunya sudah dipinjam
    if (strcmp(dataBuku.status, "Dipinjam") == 0) {
        printf("Buku sedang dipinjam.\n");
        return;
    }

    // Kalau semua ok, berarti bisa dipinjam
    strcpy(dataBuku.status, "Dipinjam");
    printf("Peminjaman berhasil. Buku '%s' sekarang sedang dipinjam oleh %s.\n",
           dataBuku.judul, dataAnggota.nama);
}

// Proses saat anggota mengembalikan buku
void PROSES_PENGEMBALIAN_BUKU() {
    int selisihHari;
    printf("\n=== PENGEMBALIAN BUKU ===\n");

    // Cek dulu apakah ada buku yang sedang dipinjam
    if (strcmp(dataBuku.status, "Tersedia") == 0) {
        printf("Tidak ada buku yang sedang dipinjam.\n");
        return;
    }

    printf("Masukkan jumlah hari keterlambatan: ");
    scanf("%d", &selisihHari);

    int denda = HITUNG_DENDA(selisihHari);
    strcpy(dataBuku.status, "Tersedia");

    printf("Pengembalian berhasil.\n");
    printf("Denda: Rp %d\n", denda);
}

// Program utama
int main() {
    int pilihan;

    do {
        printf("\n=== MENU TRANSAKSI DAN DENDA ===\n");
        printf("1. Peminjaman Buku\n");
        printf("2. Pengembalian Buku\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                PROSES_PEMINJAMAN_BUKU();
                break;
            case 2:
                PROSES_PENGEMBALIAN_BUKU();
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak ada.\n");
        }
    } while (pilihan != 3);

    return 0;
}
