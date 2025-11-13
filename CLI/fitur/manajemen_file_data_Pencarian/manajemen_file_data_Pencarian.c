#include "manajemen_file_data_Pencarian.h"

Buku globalListBuku[MAX_BUKU];
int jumlahBuku = 0;

Anggota globalListAnggota[MAX_ANGGOTA];
int jumlahAnggota = 0;

Transaksi globalListTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

void LOAD_DATA_DARI_FILE() {
    FILE* file;
    file = fopen("buku.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
                      globalListBuku[jumlahBuku].ID_Buku,
                      globalListBuku[jumlahBuku].Judul,
                      globalListBuku[jumlahBuku].Penulis,
                      globalListBuku[jumlahBuku].Kategori,
                      globalListBuku[jumlahBuku].Status,
                      &globalListBuku[jumlahBuku].JumlahDipinjam) == 6) {
            jumlahBuku++;
        }
        fclose(file);
    }

    file = fopen("anggota.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%[^;];%[^\n]\n",
                      globalListAnggota[jumlahAnggota].ID_Anggota,
                      globalListAnggota[jumlahAnggota].Nama) == 2) {
            jumlahAnggota++;
        }
        fclose(file);
    }

    file = fopen("transaksi.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
                      globalListTransaksi[jumlahTransaksi].ID_Transaksi,
                      globalListTransaksi[jumlahTransaksi].ID_Buku,
                      globalListTransaksi[jumlahTransaksi].ID_Anggota,
                      globalListTransaksi[jumlahTransaksi].TanggalPinjam,
                      globalListTransaksi[jumlahTransaksi].TanggalJatuhTempo,
                      globalListTransaksi[jumlahTransaksi].TanggalKembali,
                      globalListTransaksi[jumlahTransaksi].StatusTransaksi,
                      &globalListTransaksi[jumlahTransaksi].Denda) == 8) {
            jumlahTransaksi++;
        }
        fclose(file);
    }

    printf("Data berhasil dimuat.\n");
}

void SIMPAN_LIST_BUKU() {
    FILE* file = fopen("buku.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahBuku; i++) {
            fprintf(file, "%s;%s;%s;%s;%s;%d\n",
                    globalListBuku[i].ID_Buku,
                    globalListBuku[i].Judul,
                    globalListBuku[i].Penulis,
                    globalListBuku[i].Kategori,
                    globalListBuku[i].Status,
                    globalListBuku[i].JumlahDipinjam);
        }
        fclose(file);
    }
}

void SIMPAN_LIST_ANGGOTA() {
    FILE* file = fopen("anggota.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahAnggota; i++) {
            fprintf(file, "%s;%s\n",
                    globalListAnggota[i].ID_Anggota,
                    globalListAnggota[i].Nama);
        }
        fclose(file);
    }
}

void SIMPAN_LIST_TRANSAKSI() {
    FILE* file = fopen("transaksi.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < jumlahTransaksi; i++) {
            fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%d\n",
                    globalListTransaksi[i].ID_Transaksi,
                    globalListTransaksi[i].ID_Buku,
                    globalListTransaksi[i].ID_Anggota,
                    globalListTransaksi[i].TanggalPinjam,
                    globalListTransaksi[i].TanggalJatuhTempo,
                    globalListTransaksi[i].TanggalKembali,
                    globalListTransaksi[i].StatusTransaksi,
                    globalListTransaksi[i].Denda);
        }
        fclose(file);
    }
}

void SAVE_SEMUA_DATA_KE_FILE() {
    SIMPAN_LIST_BUKU();
    SIMPAN_LIST_ANGGOTA();
    SIMPAN_LIST_TRANSAKSI();
}

Buku* CARI_BUKU_BY_ID(const char* id) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(globalListBuku[i].ID_Buku, id) == 0) {
            return &globalListBuku[i];
        }
    }
    return NULL;
}

Anggota* CARI_ANGGOTA_BY_ID(const char* id) {
    for (int i = 0; i < jumlahAnggota; i++) {
        if (strcmp(globalListAnggota[i].ID_Anggota, id) == 0) {
            return &globalListAnggota[i];
        }
    }
    return NULL;
}

Transaksi* CARI_TRANSAKSI_BY_ID(const char* id) {
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (strcmp(globalListTransaksi[i].ID_Transaksi, id) == 0) {
            return &globalListTransaksi[i];
        }
    }
    return NULL;
}

void CARI_BUKU_BY_JUDUL(const char* judul) {
    bool ditemukan = false;
    printf("Hasil Pencarian (Judul):\n");
    for (int i = 0; i < jumlahBuku; i++) {
        if (strstr(globalListBuku[i].Judul, judul) != NULL) {
            printf("%s | %s | %s | %s\n",
                   globalListBuku[i].ID_Buku,
                   globalListBuku[i].Judul,
                   globalListBuku[i].Penulis,
                   globalListBuku[i].Status);
            ditemukan = true;
        }
    }
    if (!ditemukan) printf("Buku tidak ditemukan.\n");
}

void CARI_BUKU_BY_PENULIS(const char* penulis) {
    bool ditemukan = false;
    printf("Hasil Pencarian (Penulis):\n");
    for (int i = 0; i < jumlahBuku; i++) {
        if (strstr(globalListBuku[i].Penulis, penulis) != NULL) {
            printf("%s | %s | %s | %s\n",
                   globalListBuku[i].ID_Buku,
                   globalListBuku[i].Judul,
                   globalListBuku[i].Penulis,
                   globalListBuku[i].Status);
            ditemukan = true;
        }
    }
    if (!ditemukan) printf("Buku tidak ditemukan.\n");
}

void CARI_BUKU_BY_KATEGORI(const char* kategori) {
    bool ditemukan = false;
    printf("Hasil Pencarian (Kategori):\n");
    for (int i = 0; i < jumlahBuku; i++) {
        if (strstr(globalListBuku[i].Kategori, kategori) != NULL) {
            printf("%s | %s | %s | %s\n",
                   globalListBuku[i].ID_Buku,
                   globalListBuku[i].Judul,
                   globalListBuku[i].Penulis,
                   globalListBuku[i].Status);
            ditemukan = true;
        }
    }
    if (!ditemukan) printf("Buku tidak ditemukan.\n");
}
