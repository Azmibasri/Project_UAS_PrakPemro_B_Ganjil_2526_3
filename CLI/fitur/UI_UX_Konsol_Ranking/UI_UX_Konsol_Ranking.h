#ifndef UI_UX_KONSOL_RANKING_H
#define UI_UX_KONSOL_RANKING_H

// Struktur data buku
typedef struct {
    int ID_Buku;
    char Judul[50];
    char Penulis[30];
    char Kategori[20];
    char Status[10]; // "Tersedia" / "Dipinjam"
    int JumlahDipinjam;
} Buku;

// Variabel global
extern Buku globalListBuku[100];
extern int totalBuku;

// Deklarasi fungsi UI/UX
void TAMPILKAN_MENU_UTAMA();
void TAMPILKAN_MENU_MANAJEMEN_BUKU();
void TAMPILKAN_MENU_MANAJEMEN_ANGGOTA();
void TAMPILKAN_MENU_TRANSAKSI();
void TAMPILKAN_SEMUA_BUKU();
void TAMPILKAN_SEMUA_ANGGOTA();
void TAMPILKAN_RIWAYAT_PEMINJAMAN_ANGGOTA();
void TAMPILKAN_RANKING_BUKU();
void ATUR_PENGATURAN_SISTEM();
void TAMBAH_BUKU_DUMMY();

#endif

