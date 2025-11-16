#ifndef MANAJEMEN_FILE_DATA_PENCARIAN_H
#define MANAJEMEN_FILE_DATA_PENCARIAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 


typedef time_t DATE;


#define MAX_STRING_LEN 100
#define MAX_ID_LEN 10

typedef struct {
    char ID_Buku[MAX_ID_LEN];
    char Judul[MAX_STRING_LEN];
    char Penulis[MAX_STRING_LEN];
    char Kategori[MAX_STRING_LEN];
    char Status[MAX_ID_LEN]; 
    int JumlahDipinjam;
} Buku;

typedef struct {
    char ID_Anggota[MAX_ID_LEN];
    char Nama[MAX_STRING_LEN];
} Anggota;

typedef struct {
    char ID_Transaksi[MAX_ID_LEN];
    char ID_Buku[MAX_ID_LEN];
    char ID_Anggota[MAX_ID_LEN];
    DATE TanggalPinjam;
    DATE TanggalJatuhTempo;
    DATE TanggalKembali; 
    char StatusTransaksi[MAX_ID_LEN]; 
    int Denda;
} Transaksi;


#define MAX_LIST_SIZE 1000

typedef struct {
    Buku data[MAX_LIST_SIZE];
    int count;
} ListBuku;

typedef struct {
    Anggota data[MAX_LIST_SIZE];
    int count;
} ListAnggota;

typedef struct {
    Transaksi data[MAX_LIST_SIZE];
    int count;
} ListTransaksi;



extern ListBuku globalListBuku;
extern ListAnggota globalListAnggota;
extern ListTransaksi globalListTransaksi;


void LOAD_DATA_DARI_FILE();
void SAVE_SEMUA_DATA_KE_FILE();
void SIMPAN_LIST_BUKU();
void SIMPAN_LIST_ANGGOTA();
void SIMPAN_LIST_TRANSAKSI();


Buku* CARI_BUKU_BY_ID(const char* id); 
Anggota* CARI_ANGGOTA_BY_ID(const char* id);
Transaksi* CARI_TRANSAKSI_BY_ID(const char* id);
Transaksi* CARI_TRANSAKSI_AKTIF_BY_BUKU_ID(const char* id);
void CARI_BUKU_BY_JUDUL(const char* judul);
void CARI_BUKU_BY_PENULIS(const char* penulis);
void CARI_BUKU_BY_KATEGORI(const char* kategori);

#endif 