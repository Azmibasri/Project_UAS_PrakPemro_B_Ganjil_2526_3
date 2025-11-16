#ifndef FITUR_TRANSAKSI_DENDA_H
#define FITUR_TRANSAKSI_DENDA_H

#include <time.h>  // perlu include untuk tipe time_t

// Deklarasi fungsi
void PROSES_PEMINJAMAN_BUKU();
void PROSES_PENGEMBALIAN_BUKU();
int HITUNG_DENDA(time_t tglKembali, time_t tglJatuhTempo);

#endif // FITUR_TRANSAKSI_DENDA_H
