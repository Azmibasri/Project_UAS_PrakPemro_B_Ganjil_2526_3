#include "fitur/manajemen_file_data_Pencarian/manajemen_file_data_Pencarian.h"
#include "fitur/UI_UX_Konsol_Ranking/UI_UX_Konsol_Ranking.h"
#include "fitur/manajemen_buku_dan_login/manajemen_buku_dan_login.h"
#include <stdio.h>

void Main() {

    LOAD_DATA_DARI_FILE();

    printf("\n");
    if (TAMPILKAN_LOGIN()) {

        printf("Login berhasil. Selamat datang!\n");
        TAMPILKAN_MENU_UTAMA();
    } else {
        printf("Login gagal. Program berakhir.\n");
    }
    
    printf("Program selesai.\n");
}

int main() {
    Main();
    return 0;
}