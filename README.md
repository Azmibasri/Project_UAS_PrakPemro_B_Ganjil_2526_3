# 📚 Sistem Peminjaman Buku Perpustakaan Mini

Ini adalah Proyek Ujian Akhir Semester (UAS) untuk mata kuliah **Praktikum Pemrograman B**. Proyek ini diimplementasikan sebagai sistem manajemen perpustakaan sederhana berbasis konsol dan GUI yang ditulis dalam **C**.

Seluruh data dari sistem ini, termasuk data buku, anggota, dan riwayat peminjaman, disimpan secara persisten dalam file `.data` eksternal.

---

## ✨ Fitur Utama

Sistem ini memiliki fungsionalitas penuh untuk mengelola operasi perpustakaan, meliputi:

### Admin/Pustakawan
* **Login Pustakawan:** Mengamankan fitur-fitur administratif.
* **Manajemen Buku:**
    * Menambahkan buku baru.
    * Menghapus buku.
    * Mengedit informasi buku.
* **Manajemen Anggota:** Mendaftarkan anggota perpustakaan baru.
* **Pemantauan:**
    * Melihat daftar seluruh buku.
    * Menampilkan ranking buku yang paling sering dipinjam.

### Fungsionalitas Umum
* **Pencarian Buku:** Mencari buku berdasarkan judul, penulis, atau kategori.
* **Kategorisasi:** Mengelompokkan buku ke dalam kategori (Fiksi, Non-Fiksi, Komik, Majalah, Referensi).
* **Sistem Transaksi:**
    * Melakukan peminjaman buku.
    * Melakukan pengembalian buku.
* **Denda Otomatis:** Sistem secara otomatis menghitung denda jika terjadi keterlambatan pengembalian.
* **Pelacakan:**
    * Mengelola status buku (Tersedia/Dipinjam).
    * Melihat riwayat peminjaman per anggota.

---

## 🛠️ Teknologi yang Digunakan

* **Bahasa Pemrograman:** `C`
* **Penyimpanan Data:** File `.data` (untuk persistensi data)
* **Prinsip/Struktur:** `Modular`

---

## ⚙️ Cara Menjalankan Proyek

#### Persyaratan
* Compiler GCC atau MYS64
* Linux dan Windows

#### Langkah-langkah
1.  Clone repositori ini ke mesin lokal Anda:
    ```bash
    git clone (https://github.com/Azmibasri/Project_UAS_PrakPemro_B_Ganjil_2526_3)
    ```
2.  Masuk ke direktori proyek:
    ```bash
    cd CLI
    ```
3.  Kompilasi semua file source code:
    ```bash
    gcc .\main.c .\fitur\manajemen_file_data_Pencarian\manajemen_file_data_Pencarian.c .\fitur\manajemen_buku_dan_login\manajemen_buku_dan_login.c .\fitur\fitur_transaksi_Denda\fitur_transaksi_Denda.c .\fitur\UI_UX_Konsol_Ranking\UI_UX_Konsol_Ranking.c -I.\fitur\manajemen_file_data_Pencarian -I.\fitur\manajemen_buku_dan_login -I.\fitur\fitur_transaksi_Denda -I.\fitur\UI_UX_Konsol_Ranking -o program -Wall
    ```
4.  Jalankan program yang telah dikompilasi:
    ```bash
    ./main.exe
    
    ./main
    ```

---

## 👥 Anggota Kelompok 3
Proyek ini dikerjakan oleh:

| Nama Anggota | NIM | Kontribusi |
| :--- | :--- | :--- |
| AZMI BASRI | 250810701100044 | Quality Control |
| ALTHAFFIA PUTRI | 250810701100036 | Fitur Transaksi & Denda |
| MUHAMMAD RAUYAN | 250810701100048 | Manajemen File .txt & Pencarian|
| Muhammad Faris Zufar | 250810701100058 | Fitur Manajemen Buku & Login |
| KYANDARU ANNISA PUTRI | 250810701100059| UI/UX Konsol & Ranking |


---

### 📄 Lisensi

Proyek ini dilisensikan di bawah **Lisensi MIT**.
