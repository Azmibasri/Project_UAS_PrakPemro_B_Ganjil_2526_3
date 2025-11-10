#ifndef UI_UX_KONSOL_RANKING_H
#define UI_UX_KONSOL_RANKING_H

// Struktur data untuk menyimpan info buku
typedef struct {
    int id;
    char judul[50];
    char penulis[30];
    char kategori[20];
    char status[10];
    int jumlahDipinjam;
} Buku;

// Variabel global (dideklarasikan di .c)
extern Buku daftarBuku[100];
extern int totalBuku;

// Deklarasi semua fungsi yang akan diimplementasikan di .c
void tampilkanMenuUtama();
void tampilkanMenuManajemenBuku();
void tampilkanMenuTransaksi();
void tampilkanSemuaBuku();
void tampilkanRankingBuku();
void tambahBukuDummy();

#endif
