#include <stdio.h>
#include <string.h>
#include "fitur_transaksi_Denda.h"
#include "manajemen_file_data_Pencarian.h" //perlu untuk cari buku/anggota & simpan
#include <time.h>

//pengaturan bisa ditaruh disini
int globalDurasiPinjam = 7;
int globalDendaPerHari = 1000;

void PROSES_PEMINJAMAN_BUKU() {
    char idAnggota[10];

    printf("Masukkan ID Anggota: ");
    scanf("%s", idAnggota);

    struct Anggota *anggota = CARI_ANGGOTA_BY_ID(idAnggota);
        if (anggota == NULL)
        {
            printf("Anggota tidak ditemukan");
            return;
        }
        
    

    char idBuku[10];

    printf("Masukkan ID Buku: ");
    scanf("%s", idBuku);

    struct Buku *buku = CARI_BUKU_BY_ID(idBuku);
        if (buku == NULL)
        {
            printf("Buku tidak ditemukan.");
            return;
        }
        
    

    if (strcmp(buku->status, "Dipinjam") == 0)
    {
        printf("Buku sedang dipinjam.");
        return;
    }
    
    // --Semua validasi okee---
    time_t now = time(NULL);
    struct tm *tglPinjam = localtime(&now);
    
    struct tm tglJatuhTempo = *tglPinjam;
    tglJatuhTempo.tm_mday += globalDurasiPinjam;
    mktime(&tglJatuhTempo);

    char idTransaksi[10];
    sprintf(idTransaksi, "TRX%03d", rand() % 1000);

    //Buat transaksi baru
    struct Transaksi trxBaru;
    strcpy(trxBaru.idTransaksi, idTransaksi);
    strcpy(trxBaru.idBuku, idBuku);
    strcpy(trxBaru.idAnggota, idAnggota);
    strcpy(trxBaru.statusTransaksi, "Dipinjam");
    trxBaru.denda = 0;

    //update status buku dan jumlah dipinjam
    strcpy(buku->status, "Dipinjam");
    buku->jumlahDipinjam = buku->jumlahDipinjam + 1;

    //simpan perubahan ke file
    SIMPAN_LIST_TRANSAKSI();
    SIMPAN_LIST_BUKU();

    printf("Peminjaman berhasil.\n");
}

int HITUNG_DENDA(time_t tglKembali, time_t tglJatuhTempo) {
    double selisihDetik = difftime(tglKembali, tglJatuhTempo);
    int selisihHari = (int)(selisihDetik / 86400); // konversi ke hari

    if (selisihHari > 0) {
        return selisihHari * globalDendaPerHari;
    } else {
        return 0;
    }
}

void PROSES_PENGEMBALIAN_BUKU() {
    char id[10];
    printf("Masukkan ID Transaksi (atau ID Buku yang dikembalikan): ");
    scanf("%s", id);

    struct Transaksi *trx = CARI_TRANSAKSI_AKTIF_BY_BUKU_ID(id);
    if (trx != NULL) {
        // Ambil tanggal sekarang
        time_t now = time(NULL);
        time_t tglKembali = now;

        // Hitung denda
        int denda = HITUNG_DENDA(tglKembali, mktime(&trx->tglJatuhTempo));

        // Update transaksi
        trx->tglKembali = tglKembali;
        strcpy(trx->statusTransaksi, "Selesai");
        trx->denda = denda;

        // Update status buku
        struct Buku *buku = CARI_BUKU_BY_ID(trx->idBuku);
        if (buku != NULL) {
            strcpy(buku->status, "Tersedia");
        }

        // Simpan perubahan
        SIMPAN_LIST_TRANSAKSI();
        SIMPAN_LIST_BUKU();

        printf("Pengembalian berhasil.\n");
        printf("Denda: Rp %d\n", denda);
    } else {
        printf("Transaksi peminjaman aktif untuk buku itu tidak ditemukan.\n");
    }
}
