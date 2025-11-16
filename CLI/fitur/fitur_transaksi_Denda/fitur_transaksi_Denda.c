#include "fitur_transaksi_Denda.h"
#include "../manajemen_file_data_Pencarian/manajemen_file_data_Pencarian.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


int globalDurasiPinjam = 7;  
int globalDendaPerHari = 1000;


extern void INPUT_STRING(char* dest, int max_len);


DATE GET_CURRENT_DATE() {
    return time(NULL); 
}


DATE GET_JATUH_TEMPO(DATE tglPinjam, int durasi) {
    return tglPinjam + (durasi * 86400); 
}


char* GENERATE_UNIQUE_ID(char* buffer) {
    static int counter = 1;
    sprintf(buffer, "TRX%03d", counter++);
    return buffer;
}


Transaksi CREATE_TRANSAKSI(const char* id, const char* idBuku, const char* idAnggota, DATE tglPinjam, DATE tglJatuhTempo, DATE tglKembali, const char* status, int denda) {
    Transaksi trxBaru;
    strncpy(trxBaru.ID_Transaksi, id, MAX_ID_LEN);
    strncpy(trxBaru.ID_Buku, idBuku, MAX_ID_LEN);
    strncpy(trxBaru.ID_Anggota, idAnggota, MAX_ID_LEN);
    trxBaru.TanggalPinjam = tglPinjam;
    trxBaru.TanggalJatuhTempo = tglJatuhTempo;
    trxBaru.TanggalKembali = tglKembali;
    strncpy(trxBaru.StatusTransaksi, status, MAX_ID_LEN);
    trxBaru.Denda = denda;
    return trxBaru;
}

void PROSES_PEMINJAMAN_BUKU() {
    char idAnggota[MAX_ID_LEN];
    char idBuku[MAX_ID_LEN];

    printf("Masukkan ID Anggota: ");
    INPUT_STRING(idAnggota, MAX_ID_LEN);
    Anggota* anggota = CARI_ANGGOTA_BY_ID(idAnggota);
    if (anggota == NULL) {
        printf("Anggota tidak ditemukan.\n");
        return;
    }

    printf("Masukkan ID Buku: ");
    INPUT_STRING(idBuku, MAX_ID_LEN);
    Buku* buku = CARI_BUKU_BY_ID(idBuku);
    if (buku == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }
    
    if (strcmp(buku->Status, "Dipinjam") == 0) {
        printf("Buku sedang dipinjam.\n");
        return;
    }

    DATE tglPinjam = GET_CURRENT_DATE();
    DATE tglJatuhTempo = GET_JATUH_TEMPO(tglPinjam, globalDurasiPinjam);
    char idTransaksi[MAX_ID_LEN];
    GENERATE_UNIQUE_ID(idTransaksi);


    Transaksi trxBaru = CREATE_TRANSAKSI(idTransaksi, idBuku, idAnggota, tglPinjam, tglJatuhTempo, (DATE)0, "Dipinjam", 0);
    

    if (globalListTransaksi.count < MAX_LIST_SIZE) {
        globalListTransaksi.data[globalListTransaksi.count++] = trxBaru;
    } else {
        printf("Error: List Transaksi penuh.\n");
        return;
    }
    

    strcpy(buku->Status, "Dipinjam");
    buku->JumlahDipinjam += 1;
    

    SIMPAN_LIST_TRANSAKSI();
    SIMPAN_LIST_BUKU();
    
    printf("Peminjaman berhasil. Jatuh Tempo: %s", ctime(&tglJatuhTempo));
}

int HITUNG_DENDA(DATE tglKembali, DATE tglJatuhTempo) {
    double selisihDetik = difftime(tglKembali, tglJatuhTempo);

    int selisihHari = (int)(selisihDetik / 86400.0);
    
    if (selisihHari > 0) {
        return selisihHari * globalDendaPerHari;
    } else {
        return 0;
    }
}

void PROSES_PENGEMBALIAN_BUKU() {
    char id[MAX_ID_LEN];
    printf("Masukkan ID Transaksi (atau ID Buku yang dikembalikan): ");
    INPUT_STRING(id, MAX_ID_LEN);
    
   
    Transaksi* trx = CARI_TRANSAKSI_AKTIF_BY_BUKU_ID(id);
    
    if (trx != NULL) {
        DATE tglKembali = GET_CURRENT_DATE();
        int denda = HITUNG_DENDA(tglKembali, trx->TanggalJatuhTempo);
        

        trx->TanggalKembali = tglKembali;
        strcpy(trx->StatusTransaksi, "Selesai");
        trx->Denda = denda;
        

        Buku* buku = CARI_BUKU_BY_ID(trx->ID_Buku);
        if (buku != NULL) {
             strcpy(buku->Status, "Tersedia");
        }
        

        SIMPAN_LIST_TRANSAKSI();
        SIMPAN_LIST_BUKU();
        
        printf("Pengembalian berhasil.\n");
        printf("Denda: Rp %d\n", denda);
    } else {
        printf("Transaksi peminjaman aktif untuk buku itu tidak ditemukan.\n");
    }
}