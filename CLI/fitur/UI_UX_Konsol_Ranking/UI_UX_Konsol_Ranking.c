#include "UI_UX_Konsol_Ranking.h"
#include "manajemen_buku_dan_login.h"
#include "fitur_transaksi_Denda.h"
#include "manajemen_file_data_Pencarian.h"
#include <stdio.h>
#include <string.h>


int INPUT_INTEGER() {
    int val;

    if (scanf("%d", &val) != 1) {
        val = -1; 
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return val;
}


extern void INPUT_STRING(char* dest, int max_len);


int compareBuku(const void *a, const void *b) {
    Buku *bukuA = (Buku *)a;
    Buku *bukuB = (Buku *)b;
    return (bukuB->JumlahDipinjam - bukuA->JumlahDipinjam);
}

void TAMPILKAN_MENU_UTAMA() {
    int pilihan;
    while (1) {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Manajemen Buku\n");
        printf("2. Manajemen Anggota\n");
        printf("3. Transaksi (Pinjam/Kembali)\n");
        printf("4. Cari Buku\n");
        printf("5. Tampilkan Ranking Buku Terpopuler\n");
        printf("6. Lihat Riwayat Pinjam Anggota\n");
        printf("7. Pengaturan Sistem (Denda/Durasi)\n");
        printf("0. Simpan dan Keluar\n");
        printf("Pilih: ");
        pilihan = INPUT_INTEGER();

        switch (pilihan) {
            case 1: TAMPILKAN_MENU_MANAJEMEN_BUKU(); break;
            case 2: TAMPILKAN_MENU_MANAJEMEN_ANGGOTA(); break; // Diimplementasikan di bawah
            case 3: TAMPILKAN_MENU_TRANSAKSI(); break;
            case 4: {
                char query[MAX_STRING_LEN];
                printf("Cari berdasarkan Judul/Penulis/Kategori: ");
                INPUT_STRING(query, MAX_STRING_LEN);
                CARI_BUKU_BY_JUDUL(query);
                CARI_BUKU_BY_PENULIS(query);
                
                break;
            }
            case 5: TAMPILKAN_RANKING_BUKU(); break;
            case 6: TAMPILKAN_RIWAYAT_PEMINJAMAN_ANGGOTA(); break; 
            case 7: ATUR_PENGATURAN_SISTEM(); break;
            case 0:
                printf("Menyimpan semua data...\n");
                SAVE_SEMUA_DATA_KE_FILE();
                return;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
}

void TAMPILKAN_MENU_MANAJEMEN_BUKU() {
    int pilihan;
    printf("\n--- MANAJEMEN BUKU ---\n");
    printf("1. Tambah Buku Baru\n");
    printf("2. Edit Informasi Buku\n");
    printf("3. Hapus Buku\n");
    printf("4. Lihat Semua Daftar Buku\n");
    printf("Pilih: ");
    pilihan = INPUT_INTEGER();
    
    switch (pilihan) {
        case 1: TAMBAH_BUKU_BARU(); break;
        case 2: EDIT_INFO_BUKU(); break;
        case 3: HAPUS_BUKU(); break;
        case 4: TAMPILKAN_SEMUA_BUKU(); break;
        default: printf("Pilihan tidak valid.\n");
    }
}

void TAMPILKAN_MENU_MANAJEMEN_ANGGOTA() {
    int pilihan;
    printf("\n--- MANAJEMEN ANGGOTA ---\n");
    printf("1. Tambah Anggota Baru\n");
    printf("2. Edit Informasi Anggota\n");
    printf("3. Hapus Anggota\n");
    printf("4. Lihat Semua Daftar Anggota\n");
    printf("Pilih: ");
    pilihan = INPUT_INTEGER();
    
    switch (pilihan) {

        case 1: TAMBAH_ANGGOTA_BARU(); break; 
        case 2: EDIT_INFO_ANGGOTA(); break;
        case 3: HAPUS_ANGGOTA(); break;
        case 4: TAMPILKAN_SEMUA_ANGGOTA(); break; 
        default: printf("Pilihan tidak valid.\n");
    }
}

void TAMPILKAN_MENU_TRANSAKSI() {
    int pilihan;
    printf("\n--- MENU TRANSAKSI ---\n");
    printf("1. Proses Peminjaman Buku\n");
    printf("2. Proses Pengembalian Buku\n");
    printf("Pilih: ");
    pilihan = INPUT_INTEGER();
    
    switch (pilihan) {
        case 1: PROSES_PEMINJAMAN_BUKU(); break;
        case 2: PROSES_PENGEMBALIAN_BUKU(); break;
        default: printf("Pilihan tidak valid.\n");
    }
}

void TAMPILKAN_SEMUA_BUKU() {
    printf("\n--- DAFTAR SEMUA BUKU ---\n");
    printf("| ID     | Judul                         | Penulis                     | Status     |\n");
    printf("|--------|-------------------------------|-----------------------------|------------|\n");
    if (globalListBuku.count == 0) {
        printf("| Tidak ada data buku.                                                               |\n");
    }
    for (int i = 0; i < globalListBuku.count; i++) {
        Buku b = globalListBuku.data[i];
        printf("| %-6s | %-29s | %-27s | %-10s |\n", 
               b.ID_Buku, b.Judul, b.Penulis, b.Status);
    }
    printf("|--------|-------------------------------|-----------------------------|------------|\n");
}

void TAMPILKAN_RANKING_BUKU() {
    printf("\n--- RANKING BUKU TERPOPULER ---\n");
    

    ListBuku listTemp = globalListBuku; 
    
    qsort(listTemp.data, listTemp.count, sizeof(Buku), compareBuku);
    

    int topN = (listTemp.count < 5) ? listTemp.count : 5;
    if (topN == 0) {
        printf("Tidak ada data buku.\n");
        return;
    }

    for (int i = 0; i < topN; i++) {
        Buku b = listTemp.data[i];
        printf("%d. %s (%d kali dipinjam)\n", i + 1, b.Judul, b.JumlahDipinjam);
    }
}


void TAMPILKAN_SEMUA_ANGGOTA() {
    printf("\n--- DAFTAR SEMUA ANGGOTA ---\n");
    printf("| ID         | Nama                       |\n");
    printf("|------------|----------------------------|\n");
    if (globalListAnggota.count == 0) {
        printf("| Tidak ada data anggota.               |\n");
    }
    for (int i = 0; i < globalListAnggota.count; i++) {
        Anggota a = globalListAnggota.data[i];
        printf("| %-10s | %-26s |\n", a.ID_Anggota, a.Nama);
    }
    printf("|------------|----------------------------|\n");
}

void TAMPILKAN_RIWAYAT_PEMINJAMAN_ANGGOTA() {
    char idAnggota[MAX_ID_LEN];
    printf("\n--- RIWAYAT PEMINJAMAN ANGGOTA ---\n");
    printf("Masukkan ID Anggota: ");
    INPUT_STRING(idAnggota, MAX_ID_LEN);


    Anggota* anggota = CARI_ANGGOTA_BY_ID(idAnggota);
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", idAnggota);
        return;
    }

    printf("Riwayat Transaksi untuk %s (%s):\n", anggota->Nama, anggota->ID_Anggota);
    printf("| ID Transaksi | ID Buku | Tanggal Pinjam | Tanggal Kembali | Denda | Status     |\n");
    printf("|--------------|---------|----------------|-----------------|-------|------------|\n");
    
    int ditemukan = 0;
    for (int i = 0; i < globalListTransaksi.count; i++) {
        Transaksi t = globalListTransaksi.data[i];
        if (strcmp(t.ID_Anggota, idAnggota) == 0) {
          
            char tglPinjamStr[20], tglKembaliStr[20];
            struct tm *tm_pinjam = localtime(&t.TanggalPinjam);
            strftime(tglPinjamStr, sizeof(tglPinjamStr), "%d/%m/%Y", tm_pinjam);

            if (t.TanggalKembali != 0) {
                struct tm *tm_kembali = localtime(&t.TanggalKembali);
                strftime(tglKembaliStr, sizeof(tglKembaliStr), "%d/%m/%Y", tm_kembali);
            } else {
                strcpy(tglKembaliStr, "---");
            }
            
            printf("| %-12s | %-7s | %-14s | %-15s | %-5d | %-10s |\n",
                   t.ID_Transaksi, t.ID_Buku, tglPinjamStr, tglKembaliStr, t.Denda, t.StatusTransaksi);
            ditemukan = 1;
        }
    }
    
    if (!ditemukan) {
        printf("| Tidak ada riwayat transaksi ditemukan.                                          |\n");
    }
    printf("|--------------|---------|----------------|-----------------|-------|------------|\n");
}

void ATUR_PENGATURAN_SISTEM() {
    int newDurasi, newDenda;
    printf("\n--- PENGATURAN SISTEM ---\n");
    printf("Durasi Pinjam saat ini: %d hari\n", globalDurasiPinjam);
    printf("Masukkan Durasi Pinjam baru (hari): ");
    newDurasi = INPUT_INTEGER();
    if (newDurasi > 0) globalDurasiPinjam = newDurasi;

    printf("Denda Per Hari saat ini: Rp %d\n", globalDendaPerHari);
    printf("Masukkan Denda Per Hari baru (Rp): ");
    newDenda = INPUT_INTEGER();
    if (newDenda >= 0) globalDendaPerHari = newDenda;

    printf("Pengaturan berhasil disimpan.\n");
}