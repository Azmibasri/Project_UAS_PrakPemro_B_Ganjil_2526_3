# 📚 Sistem Peminjaman Buku Perpustakaan Mini

Ini adalah Proyek Ujian Akhir Semester (UAS) untuk mata kuliah **[Nama Mata Kuliah Anda]**. Proyek ini diimplementasikan sebagai sistem manajemen perpustakaan sederhana berbasis konsol yang ditulis dalam **[Sebutkan Bahasa, misal: C++]**.

Seluruh data dari sistem ini, termasuk data buku, anggota, dan riwayat peminjaman, disimpan secara persisten dalam file `.txt` eksternal.

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

* **Bahasa Pemrograman:** `[Misalnya: C++]`
* **Penyimpanan Data:** File `.txt` (untuk persistensi data)
* **Prinsip/Struktur:** `[Misalnya: Structs, File I/O, Algoritma Pencarian/Sortir]`

---

## ⚙️ Cara Menjalankan Proyek

#### Persyaratan
* `[Misalnya: Compiler G++ / GCC]`
* `[Misalnya: Sistem Operasi Windows/Linux/macOS]`

#### Langkah-langkah
1.  Clone repositori ini ke mesin lokal Anda:
    ```bash
    git clone [URL_REPOSITORI_ANDA]
    ```
2.  Masuk ke direktori proyek:
    ```bash
    cd [NAMA_DIREKTORI_PROYEK]
    ```
3.  Kompilasi semua file source code:
    ```bash
    # Contoh untuk C++
    g++ -o app main.cpp [file_lain.cpp]
    ```
4.  Jalankan program yang telah dikompilasi:
    ```bash
    # Contoh untuk Windows
    ./app.exe
    
    # Contoh untuk Linux/macOS
    ./app
    ```

---

## 👥 Anggota Kelompok [Nomor Kelompok]

Proyek ini dikerjakan oleh:

| Nama Anggota | NIM | Kontribusi |
| :--- | :--- | :--- |
| `[Nama Lengkap]` | `[NIM]` | `[Misal: Fitur Manajemen Buku & Login]` |
| `[Nama Lengkap]` | `[NIM]` | `[Misal: Fitur Transaksi & Denda]` |
| `[Nama Lengkap]` | `[NIM]` | `[Misal: Manajemen File .txt & Pencarian]` |
| `[Nama Lengkap]` | `[NIM]` | `[Misal: UI/UX Konsol & Ranking]` |

---

### 📄 Lisensi

Proyek ini dilisensikan di bawah **[Misalnya: Lisensi MIT]**.
