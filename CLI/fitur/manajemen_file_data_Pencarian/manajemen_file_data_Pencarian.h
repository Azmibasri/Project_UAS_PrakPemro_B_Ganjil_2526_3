#ifndef MANAJEMEN_FILE_DATA_PENCARIAN_H
#define MANAJEMEN_FILE_DATA_PENCARIAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUKU 100
#define MAX_ANGGOTA 100
#define MAX_TRANSAKSI 200

typedef struct {
    char ID_Buku[20];
    char Judul[100];
    char Penulis[100];
    char Kategori[50];
    char Status[20];
    int JumlahDipinjam;
} Buku;

typedef struct {
    char ID_Anggota[20];
    char Nama[100];
} Anggota;

typedef struct {
    char ID_Transaksi[20];
    char ID_Buku[20];
    char ID_Anggota[20];
    char TanggalPinjam[20];
    char TanggalJatuhTempo[20];
    char TanggalKembali[20];
    char StatusTransaksi[20];
    int Denda;
} Transaksi;

extern Buku globalListBuku[MAX_BUKU];
extern int jumlahBuku;

extern Anggota globalListAnggota[MAX_ANGGOTA];
extern int jumlahAnggota;

extern Transaksi globalListTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

void LOAD_DATA_DARI_FILE();
void SAVE_SEMUA_DATA_KE_FILE();
void SIMPAN_LIST_BUKU();
void SIMPAN_LIST_ANGGOTA();
void SIMPAN_LIST_TRANSAKSI();

Buku* CARI_BUKU_BY_ID(const char* id);
Anggota* CARI_ANGGOTA_BY_ID(const char* id);
Transaksi* CARI_TRANSAKSI_BY_ID(const char* id);

void CARI_BUKU_BY_JUDUL(const char* judul);
void CARI_BUKU_BY_PENULIS(const char* penulis);
void CARI_BUKU_BY_KATEGORI(const char* kategori);

#endif
