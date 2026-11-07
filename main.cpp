#include "BusinessLogic.h"
void garisPemisah() {
    cout << "============================================================" << endl;
}

void headerMenu(string judul) {
    cout << endl;
    cout << "============================================================" << endl;
    cout << "              " << judul << endl;
    cout << "============================================================" << endl;
}

void tekanEnterUntukLanjut() {
    cout << endl;
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

bool konfirmasi(string pesan) {
    char jawab;
    cout << pesan << " (y/n): ";
    cin >> jawab;
    cin.ignore();
    if (jawab == 'y' || jawab == 'Y') {
        return true;
    }
    return false;
}

void menuInputProduk();
void menuEditProduk();
void menuHapusProduk();
void menuCariProduk();
void menuSortProdukLengkap();
void menuTambahStok();
void menuKelolaStok();
void menuKelolaUser();
void menuPengemasan(int indexUser);
void menuLaporan();
void menuCariTransaksi(int indexUser);
void menuBinarySearch();
void menuFiturRekursi();
void menuMatriksAnalisis();
void menuLogAktivitas();
void menuPelanggan();
void menuAntrian();
void menuKalkulatorLengkap();
void menuSistem();
void menuTransaksi(int indexUser);
int menuLogin();
void menuKasirLengkap(int indexUser);
void menuAdminFinal(int indexUser);

// MENU-MENU UTAMA
// =====================================================

void menuInputProduk() {
    headerMenu("TAMBAH PRODUK BARU");
    string id, nama, ukuran, bahan;
    int harga, stok;

    cout << "ID Produk    : ";
    cin >> id;
    if (id == "") {
        cout << "[!] ID tidak boleh kosong!" << endl;
        return;
    }
    if (cariProdukById(id) != -1) {
        cout << "[!] ID produk sudah ada!" << endl;
        return;
    }

    cin.ignore();
    cout << "Nama Produk  : ";
    getline(cin, nama);
    if (nama == "") {
        cout << "[!] Nama tidak boleh kosong!" << endl;
        return;
    }

    cout << "Ukuran (S/M/L/XL/XXL): ";
    cin >> ukuran;
    if (ukuran != "S" && ukuran != "M" && ukuran != "L" &&
        ukuran != "XL" && ukuran != "XXL") {
        cout << "[!] Ukuran tidak valid!" << endl;
        return;
    }

    cout << "Harga        : Rp ";
    cin >> harga;
    if (harga < 0) {
        cout << "[!] Harga tidak boleh negatif!" << endl;
        return;
    }

    cout << "Stok         : ";
    cin >> stok;
    if (stok < 0) {
        cout << "[!] Stok tidak boleh negatif!" << endl;
        return;
    }

    cin.ignore();
    cout << "Bahan        : ";
    getline(cin, bahan);
    if (bahan == "") {
        cout << "[!] Bahan tidak boleh kosong!" << endl;
        return;
    }

    tambahProduk(id, nama, ukuran, harga, stok, bahan);
    fm.simpanProduk();
}

void menuEditProduk() {
    headerMenu("EDIT PRODUK");
    tampilSemuaProduk();
    string id;
    cout << "Masukkan ID produk yang akan diedit: ";
    cin >> id;
    cin.ignore();
    editProduk(id);
    fm.simpanProduk();
}

void menuHapusProduk() {
    headerMenu("HAPUS PRODUK");
    tampilSemuaProduk();
    string id;
    cout << "Masukkan ID produk yang akan dihapus: ";
    cin >> id;
    if (konfirmasi("Yakin ingin menghapus produk " + id + "?")) {
        hapusProduk(id);
        fm.simpanProduk();
    } else {
        cout << "Penghapusan dibatalkan." << endl;
    }
}

void menuCariProduk() {
    headerMenu("CARI PRODUK");
    cout << "1. Cari by ID" << endl;
    cout << "2. Cari by Nama" << endl;
    cout << "3. Cari by Ukuran" << endl;
    cout << "4. Cari by Bahan" << endl;
    cout << "5. Cari Nama (Binary Search - harus sudah terurut)" << endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        string id;
        cout << "Masukkan ID: ";
        cin >> id;
        int index = cariProdukById(id);
        if (index == -1) {
            cout << "[!] Produk tidak ditemukan!" << endl;
        } else {
            daftarProduk[index].tampilProduk();
        }
    } else if (pilihan == 2) {
        string nama;
        cin.ignore();
        cout << "Masukkan Nama: ";
        getline(cin, nama);
        int index = cariProdukByNama(nama);
        if (index == -1) {
            cout << "[!] Produk tidak ditemukan!" << endl;
        } else {
            daftarProduk[index].tampilProduk();
        }
    } else if (pilihan == 3) {
        string ukuran;
        cout << "Masukkan Ukuran (S/M/L/XL/XXL): ";
        cin >> ukuran;
        cariProdukByUkuran(ukuran);
    } else if (pilihan == 4) {
        string bahan;
        cin.ignore();
        cout << "Masukkan Bahan: ";
        getline(cin, bahan);
        cariProdukByBahan(bahan);
    } else if (pilihan == 5) {
        string nama;
        cin.ignore();
        cout << "Pastikan produk sudah diurutkan nama terlebih dahulu!" << endl;
        cout << "Masukkan Nama: ";
        getline(cin, nama);
        int hasil = binarySearchNamaRekursif(nama, 0, jumlahProduk - 1);
        if (hasil == -1) {
            cout << "[!] Produk '" << nama << "' tidak ditemukan!" << endl;
        } else {
            cout << "[?] Produk ditemukan di indeks ke-" << hasil << ":" << endl;
            daftarProduk[hasil].tampilProduk();
        }
    } else {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
}

void menuSortProdukLengkap() {
    headerMenu("URUTKAN PRODUK - PILIH ALGORITMA");
    cout << "(Praktikum 3 & 7 - Sorting Algorithms)" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "[BUBBLE SORT]" << endl;
    cout << "1. Bubble Sort - Harga Termurah ke Termahal" << endl;
    cout << "2. Bubble Sort - Nama A-Z" << endl;
    cout << "3. Bubble Sort - Stok Terkecil ke Terbesar" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "[SELECTION SORT]" << endl;
    cout << "4. Selection Sort - Harga Termahal ke Termurah" << endl;
    cout << "5. Selection Sort - Nama A-Z" << endl;
    cout << "6. Selection Sort - Stok Terkecil ke Terbesar" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "[INSERTION SORT]" << endl;
    cout << "7. Insertion Sort - Nama A-Z" << endl;
    cout << "8. Insertion Sort - Stok Terkecil ke Terbesar" << endl;
    cout << "9. Insertion Sort - Harga Ascending" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "[DEMO LANGKAH-LANGKAH SORTING]" << endl;
    cout << "10. Demo Langkah Bubble Sort (Edukatif)" << endl;
    cout << "11. Demo Langkah Selection Sort (Edukatif)" << endl;
    cout << "12. Demo Langkah Insertion Sort (Edukatif)" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        sortProdukByHarga();
        tampilSemuaProduk();
    } else if (pilihan == 2) {
        sortProdukByNama();
        tampilSemuaProduk();
    } else if (pilihan == 3) {
        sortProdukByStok();
        tampilSemuaProduk();
    } else if (pilihan == 4) {
        selectionSortProdukHargaDesc();
        tampilSemuaProduk();
    } else if (pilihan == 5) {
        selectionSortProdukByNama();
        tampilSemuaProduk();
    } else if (pilihan == 6) {
        selectionSortProdukByStokAsc();
        tampilSemuaProduk();
    } else if (pilihan == 7) {
        insertionSortProdukByNama();
        tampilSemuaProduk();
    } else if (pilihan == 8) {
        insertionSortProdukByStok();
        tampilSemuaProduk();
    } else if (pilihan == 9) {
        insertionSortProdukByHarga();
        tampilSemuaProduk();
    } else if (pilihan == 10) {
        demoLangkahBubbleSort();
    } else if (pilihan == 11) {
        demoLangkahSelectionSort();
    } else if (pilihan == 12) {
        demoLangkahInsertionSort();
    } else if (pilihan != 0) {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
}

void menuTambahStok() {
    headerMenu("TAMBAH STOK PRODUK");
    tampilSemuaProduk();
    string id;
    int jumlah;

    cout << "ID Produk    : ";
    cin >> id;
    cin.ignore();

    int index = cariProdukById(id);
    if (index == -1) {
        cout << "[!] Produk tidak ditemukan!" << endl;
        return;
    }

    cout << "Stok saat ini: " << daftarProduk[index].getStok() << endl;
    cout << "Tambah Stok  : ";
    cin >> jumlah;
    cin.ignore();

    if (jumlah <= 0) {
        cout << "[!] Jumlah harus lebih dari 0!" << endl;
        return;
    }

    daftarProduk[index].tambahStok(jumlah);
    cout << "Stok sekarang: " << daftarProduk[index].getStok() << endl;
    fm.simpanProduk();
}

void menuKelolaStok() {
    int pilihan;
    do {
        headerMenu("KELOLA STOK");
        cout << "1. Tambah Stok Produk" << endl;
        cout << "2. Tampil Produk Stok Menipis" << endl;
        cout << "3. Tampil Produk Stok Habis" << endl;
        cout << "4. Rekap Stok Per Ukuran" << endl;
        cout << "5. Laporan Nilai Inventori" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuTambahStok();
        } else if (pilihan == 2) {
            tampilStokMenipis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            tampilProdukStokHabis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            laporan.laporanRekapUkuran();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            laporan.laporanNilaiInventori();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuKelolaUser() {
    int pilihan;
    do {
        headerMenu("KELOLA USER");
        cout << "1. Tambah User" << endl;
        cout << "2. Hapus User" << endl;
        cout << "3. Tampil Semua User" << endl;
        cout << "4. Edit Data User" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string u, p, r;
            cout << "Username : ";
            cin >> u;
            cout << "Password : ";
            cin >> p;
            cout << "Role (admin/kasir): ";
            cin >> r;
            if (!User().validasiUsername(u) ||
                !User().validasiPassword(p)) {
                continue;
            }
            if (r != "admin" && r != "kasir") {
                cout << "[!] Role harus admin atau kasir!" << endl;
            } else {
                tambahUser(u, p, r);
                fm.simpanUser();
            }
        } else if (pilihan == 2) {
            tampilSemuaUser();
            string u;
            cout << "Username yang akan dihapus: ";
            cin >> u;
            if (konfirmasi("Yakin ingin menghapus user " + u + "?")) {
                hapusUser(u);
                fm.simpanUser();
            }
        } else if (pilihan == 3) {
            tampilSemuaUser();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            tampilSemuaUser();
            string usernameLama, usernameBaru, passwordBaru, roleBaru;
            cout << "Username yang akan diedit: ";
            cin >> usernameLama;
            int index = -1;
            for (int i = 0; i < jumlahUser; i++) {
                if (daftarUser[i].getUsername() == usernameLama) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "[!] User tidak ditemukan!" << endl;
                continue;
            }

            cout << "Username baru: ";
            cin >> usernameBaru;
            cout << "Password baru: ";
            cin >> passwordBaru;
            cout << "Role baru (admin/kasir): ";
            cin >> roleBaru;
            cin.ignore();

            bool usernameDipakai = false;
            for (int i = 0; i < jumlahUser; i++) {
                if (i != index && daftarUser[i].getUsername() == usernameBaru) {
                    usernameDipakai = true;
                    break;
                }
            }
            if (!daftarUser[index].validasiUsername(usernameBaru) ||
                !daftarUser[index].validasiPassword(passwordBaru)) {
                continue;
            }
            if (usernameDipakai) {
                cout << "[!] Username sudah digunakan!" << endl;
            } else if (roleBaru != "admin" && roleBaru != "kasir") {
                cout << "[!] Role harus admin atau kasir!" << endl;
            } else {
                daftarUser[index].setUsername(usernameBaru);
                daftarUser[index].setPassword(passwordBaru);
                daftarUser[index].setRole(roleBaru);
                fm.simpanUser();
                cout << "[?] Data user berhasil diperbarui." << endl;
            }
        }
    } while (pilihan != 0);
}

void menuPengemasan(int indexUser) {
    int pilihan;
    do {
        headerMenu("MENU PENGEMASAN");
        cout << "1. Tampil Status Pengemasan Produk" << endl;
        cout << "2. Update Status Pengemasan Produk" << endl;
        cout << "3. Laporan Pengemasan Produk" << endl;
        cout << "4. Tampil Status Pengemasan Pesanan" << endl;
        cout << "5. Update Status Pengemasan Pesanan" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "1. Belum Dikemas" << endl;
            cout << "2. Sedang Dikemas" << endl;
            cout << "3. Sudah Dikemas" << endl;
            cout << "Pilihan: ";
            int p;
            cin >> p;
            cin.ignore();
            if (p == 1) tampilProdukByStatus("Belum Dikemas");
            else if (p == 2) tampilProdukByStatus("Sedang Dikemas");
            else if (p == 3) tampilProdukByStatus("Sudah Dikemas");
            else cout << "[!] Pilihan tidak valid!" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            tampilSemuaProduk();
            string id, status;
            cout << "ID Produk: ";
            cin >> id;
            cin.ignore();
            cout << "Status baru (Belum Dikemas/Sedang Dikemas/Sudah Dikemas): ";
            getline(cin, status);
            updateStatusPengemasan(id, status);
            fm.simpanProduk();
        } else if (pilihan == 3) {
            laporan.laporanPengemasan();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            cout << "1. Belum Dikemas" << endl;
            cout << "2. Sedang Dikemas" << endl;
            cout << "3. Sudah Dikemas" << endl;
            cout << "Pilihan: ";
            int p;
            cin >> p;
            cin.ignore();
            if (p == 1) tampilTransaksiByPengemasan("Belum Dikemas");
            else if (p == 2) tampilTransaksiByPengemasan("Sedang Dikemas");
            else if (p == 3) tampilTransaksiByPengemasan("Sudah Dikemas");
            else cout << "[!] Pilihan tidak valid!" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            string noStruk, status;
            cout << "No. Struk: ";
            cin >> noStruk;
            cin.ignore();
            cout << "Status baru (Belum Dikemas/Sedang Dikemas/Sudah Dikemas): ";
            getline(cin, status);
            if (status != "Belum Dikemas" &&
                status != "Sedang Dikemas" &&
                status != "Sudah Dikemas") {
                cout << "[!] Status tidak valid!" << endl;
            } else {
                bool ditemukan = false;
                for (int i = 0; i < jumlahTransaksi; i++) {
                    if (riwayatTransaksi[i].getNoStruk() == noStruk) {
                        riwayatTransaksi[i].setStatusPengemasan(status);
                        ditemukan = true;
                        break;
                    }
                }
                if (ditemukan) {
                    fm.simpanTransaksi();
                    logSistem.tambahLog("Update pengemasan pesanan " + noStruk,
                                        daftarUser[indexUser].getUsername(), "Log");
                    cout << "[?] Status pengemasan pesanan berhasil diperbarui." << endl;
                } else {
                    cout << "[!] Transaksi tidak ditemukan!" << endl;
                }
            }
        }
    } while (pilihan != 0);
}

void menuLaporan() {
    int pilihan;
    do {
        headerMenu("MENU LAPORAN");
        cout << "1.  Laporan Harian" << endl;
        cout << "2.  Laporan Omzet Total" << endl;
        cout << "3.  Laporan Produk Terlaris" << endl;
        cout << "4.  Laporan Stok Menipis" << endl;
        cout << "5.  Laporan Rekap Ukuran" << endl;
        cout << "6.  Laporan Laba Rugi" << endl;
        cout << "7.  Laporan Pengemasan" << endl;
        cout << "8.  Laporan Rentang Harga Produk" << endl;
        cout << "9.  Laporan Nilai Inventori" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string tgl;
            cout << "Tanggal (dd-mm-yyyy): ";
            cin >> tgl;
            laporan.laporanHarian(tgl);
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            laporan.laporanOmzetTotal();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            laporan.laporanProdukTerlaris();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            laporan.laporanStokMenipis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            laporan.laporanRekapUkuran();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            laporan.laporanLabaRugi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            laporan.laporanPengemasan();
            tekanEnterUntukLanjut();
        } else if (pilihan == 8) {
            int hMin, hMax;
            cout << "Harga minimum (Rp): ";
            cin >> hMin;
            cout << "Harga maksimum (Rp): ";
            cin >> hMax;
            cin.ignore();
            laporan.laporanProdukRentangHarga(hMin, hMax);
            tekanEnterUntukLanjut();
        } else if (pilihan == 9) {
            laporan.laporanNilaiInventori();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuCariTransaksi(int indexUser) {
    headerMenu("CARI TRANSAKSI");
    cout << "1. Cari by No Struk" << endl;
    cout << "2. Cari by Nama Pembeli" << endl;
    cout << "3. Cari by Kasir" << endl;
    cout << "4. Cari by Tanggal" << endl;
    cout << "5. Urutkan Transaksi by Total (Terbesar)" << endl;
    cout << "6. Urutkan Transaksi berdasarkan Waktu" << endl;
    cout << "7. Tampilkan yang Menunggu Verifikasi" << endl;
    cout << "8. Verifikasi Pembelian berdasarkan No. Struk" << endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        string noStruk;
        cout << "No Struk: ";
        cin >> noStruk;
        cin.ignore();
        tampilDetailTransaksi(noStruk);
    } else if (pilihan == 2) {
        string nama;
        cout << "Nama Pembeli: ";
        getline(cin, nama);
        cariTransaksiByPembeli(nama);
    } else if (pilihan == 3) {
        string kasir;
        cout << "Username Kasir: ";
        cin >> kasir;
        cin.ignore();
        cariTransaksiByKasir(kasir);
    } else if (pilihan == 4) {
        string tgl;
        cout << "Tanggal (dd-mm-yyyy): ";
        cin >> tgl;
        cin.ignore();
        bool ditemukan = false;
        for (int i = 0; i < jumlahTransaksi; i++) {
            if (riwayatTransaksi[i].getTanggal() == tgl) {
                cout << riwayatTransaksi[i].getNoStruk() << "\t"
                     << riwayatTransaksi[i].getKasir() << "\t\t"
                     << riwayatTransaksi[i].getNamaPembeli() << "\t"
                     << "Rp " << riwayatTransaksi[i].getTotalHarga() << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "[!] Tidak ada transaksi pada " << tgl << endl;
        }
    } else if (pilihan == 5) {
        bubbleSortTransaksiByTotal();
        tampilRiwayatTransaksi();
    } else if (pilihan == 6) {
        sortTransaksiByTanggal();
        tampilRiwayatTransaksi();
    } else if (pilihan == 7) {
        sortTransaksiByVerifikasi();
        tampilRiwayatTransaksi();
    } else if (pilihan == 8) {
        string noStruk;
        cout << "No. Struk: ";
        cin >> noStruk;
        cin.ignore();
        if (!daftarUser[indexUser].isAdmin()) {
            cout << "[!] Hanya admin yang dapat memverifikasi pembelian." << endl;
        } else {
            verifikasiTransaksi(noStruk, daftarUser[indexUser].getUsername());
        }
    } else {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
}

void menuBinarySearch() {
    headerMenu("BINARY SEARCH - CARI PRODUK");
    cout << "Catatan: Produk harus diurutkan dulu sebelum Binary Search!" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "1. Urutkan & Cari berdasarkan Harga (Binary Search)" << endl;
    cout << "2. Cari Nama Produk (Binary Search Rekursif)" << endl;
    cout << "3. Demo Langkah Bubble Sort" << endl;
    cout << "4. Demo Langkah Selection Sort" << endl;
    cout << "5. Demo Langkah Insertion Sort" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        sortProdukByHarga();
        tampilSemuaProduk();
        int harga;
        cout << "Masukkan harga yang dicari: Rp ";
        cin >> harga;
        cin.ignore();
        int hasil = binarySearchHarga(harga);
        if (hasil == -1) {
            cout << "[!] Produk dengan harga Rp " << harga << " tidak ditemukan!" << endl;
        } else {
            cout << "[?] Produk ditemukan pada indeks ke-" << hasil << ":" << endl;
            daftarProduk[hasil].tampilProduk();
        }
    } else if (pilihan == 2) {
        sortProdukByNama();
        tampilSemuaProduk();
        string nama;
        cout << "Masukkan nama produk yang dicari: ";
        getline(cin, nama);
        int hasil = binarySearchNamaRekursif(nama, 0, jumlahProduk - 1);
        if (hasil == -1) {
            cout << "[!] Produk '" << nama << "' tidak ditemukan!" << endl;
        } else {
            cout << "[?] Produk ditemukan pada indeks ke-" << hasil << ":" << endl;
            daftarProduk[hasil].tampilProduk();
        }
    } else if (pilihan == 3) {
        demoLangkahBubbleSort();
    } else if (pilihan == 4) {
        demoLangkahSelectionSort();
    } else if (pilihan == 5) {
        demoLangkahInsertionSort();
    }
}

void menuFiturRekursi() {
    int pilihan;
    do {
        headerMenu("FITUR REKURSI - ANALISIS DATA");
        cout << "Fitur ini menggunakan teknik REKURSI" << endl;
        cout << "(Praktikum 4 & 5 - Iteratif-Rekursif & Rekursi)" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1.  Hitung Total Nilai Stok (Rekursi)" << endl;
        cout << "2.  Hitung Total Omzet (Rekursi)" << endl;
        cout << "3.  Cari Produk Stok Terkecil (Rekursi)" << endl;
        cout << "4.  Cari Produk Harga Tertinggi (Rekursi)" << endl;
        cout << "5.  Hitung Jumlah Produk Stok Menipis (Rekursi)" << endl;
        cout << "6.  Hitung Total Item Terjual (Rekursi)" << endl;
        cout << "7.  Tampil Produk Terbalik / Reverse (Rekursi)" << endl;
        cout << "8.  Demo Fibonacci - Poin Loyalitas (Rekursi)" << endl;
        cout << "9.  Demo Faktorial (Rekursi)" << endl;
        cout << "10. Hitung Jumlah Digit (Rekursi)" << endl;
        cout << "11. Hitung Pangkat (Rekursi)" << endl;
        cout << "12. Hitung Produk per Ukuran (Rekursi)" << endl;
        cout << "0.  Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            if (jumlahProduk == 0) {
                cout << "[!] Belum ada produk!" << endl;
            } else {
                long long nilaiStok = hitungNilaiStokRekursif(0);
                cout << "============================================================" << endl;
                cout << "  TOTAL NILAI STOK SELURUH PRODUK (via Rekursi)" << endl;
                cout << "============================================================" << endl;
                cout << "  Rp " << nilaiStok << endl;
                cout << "  (Harga x Stok setiap produk, dijumlah secara rekursif)" << endl;
                cout << "============================================================" << endl;
            }
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            if (jumlahTransaksi == 0) {
                cout << "[!] Belum ada transaksi!" << endl;
            } else {
                long long omzet = hitungOmzetRekursif(0);
                cout << "============================================================" << endl;
                cout << "  TOTAL OMZET SEMUA TRANSAKSI (via Rekursi)" << endl;
                cout << "============================================================" << endl;
                cout << "  Rp " << omzet << endl;
                cout << "============================================================" << endl;
            }
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            if (jumlahProduk == 0) {
                cout << "[!] Belum ada produk!" << endl;
            } else {
                int idx = cariStokMinRekursif(1, 0);
                cout << "============================================================" << endl;
                cout << "  PRODUK DENGAN STOK PALING SEDIKIT (via Rekursi)" << endl;
                cout << "============================================================" << endl;
                daftarProduk[idx].tampilProduk();
            }
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            if (jumlahProduk == 0) {
                cout << "[!] Belum ada produk!" << endl;
            } else {
                int idx = cariHargaMaxRekursif(1, 0);
                cout << "============================================================" << endl;
                cout << "  PRODUK DENGAN HARGA TERTINGGI (via Rekursi)" << endl;
                cout << "============================================================" << endl;
                daftarProduk[idx].tampilProduk();
            }
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            int jumlah = hitungProdukStokMenipisRekursif(0);
            cout << "============================================================" << endl;
            cout << "  JUMLAH PRODUK STOK MENIPIS (via Rekursi)" << endl;
            cout << "============================================================" << endl;
            cout << "  " << jumlah << " produk perlu segera direstok!" << endl;
            cout << "============================================================" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            int total = hitungTotalItemTerjualRekursif(0);
            cout << "============================================================" << endl;
            cout << "  TOTAL ITEM TERJUAL (via Rekursi)" << endl;
            cout << "============================================================" << endl;
            cout << "  " << total << " item telah terjual dari semua transaksi" << endl;
            cout << "============================================================" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            if (jumlahProduk == 0) {
                cout << "[!] Belum ada produk!" << endl;
            } else {
                cout << "============================================================" << endl;
                cout << "  DAFTAR PRODUK TERBALIK (via Rekursi)" << endl;
                cout << "============================================================" << endl;
                cout << "No\tID\tNama\t\tUkuran\tHarga\t\tStok" << endl;
                cout << "------------------------------------------------------------" << endl;
                cetakProdukReverseRekursif(jumlahProduk - 1);
                cout << "============================================================" << endl;
            }
            tekanEnterUntukLanjut();
        } else if (pilihan == 8) {
            cout << "============================================================" << endl;
            cout << "  DEMO FIBONACCI - SISTEM POIN LOYALITAS (via Rekursi)" << endl;
            cout << "============================================================" << endl;
            cout << "Fibonacci digunakan sebagai contoh perhitungan poin bonus:" << endl;
            cout << "Transaksi ke-n mendapat bonus poin = Fib(n)" << endl;
            cout << "------------------------------------------------------------" << endl;
            for (int i = 1; i <= 10; i++) {
                cout << "  Transaksi ke-" << i << " -> Bonus Poin: "
                     << fibonacciRekursif(i) << " poin" << endl;
            }
            cout << "============================================================" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 9) {
            cout << "============================================================" << endl;
            cout << "  DEMO FAKTORIAL (via Rekursi)" << endl;
            cout << "============================================================" << endl;
            for (int i = 0; i <= 10; i++) {
                cout << "  " << i << "! = " << faktorialRekursif(i) << endl;
            }
            cout << "============================================================" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 10) {
            int angka;
            cout << "Masukkan angka: ";
            cin >> angka;
            cin.ignore();
            cout << "Jumlah digit dari " << angka << " = "
                 << hitungDigitRekursif(angka) << " digit" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 11) {
            int base, exp;
            cout << "Base    : ";
            cin >> base;
            cout << "Eksponen: ";
            cin >> exp;
            cin.ignore();
            cout << base << "^" << exp << " = " << pangkatRekursif(base, exp) << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 12) {
            string ukuran;
            cout << "Ukuran (S/M/L/XL/XXL): ";
            cin >> ukuran;
            cin.ignore();
            int jumlah = hitungProdukByUkuranRekursif(0, ukuran);
            cout << "Jumlah produk ukuran " << ukuran << " : " << jumlah << " jenis" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuMatriksAnalisis() {
    int pilihan;
    do {
        headerMenu("ANALISIS MATRIKS PENJUALAN (Array 2D)");
        cout << "(Praktikum 8 & 9 - Array Dua Dimensi)" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1. Tampil Matriks Penjualan (Bulan x Ukuran)" << endl;
        cout << "2. Konversi Matriks ke Array 1D & Sorting" << endl;
        cout << "3. Ukuran Paling Laris per Bulan" << endl;
        cout << "4. Bulan Penjualan Tertinggi" << endl;
        cout << "5. Transpose Matriks (Ukuran x Bulan)" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tampilMatriksPenjualan();
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            konversiMatriksKe1D();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            bangunMatriksPenjualan();
            cout << "============================================================" << endl;
            cout << "  UKURAN PALING LARIS PER BULAN                           " << endl;
            cout << "============================================================" << endl;
            for (int i = 0; i < MAX_BULAN; i++) {
                int maxQty  = 0;
                int maxUkur = 0;
                bool adaData = false;
                for (int j = 0; j < MAX_UKURAN; j++) {
                    if (matriksPenjualan[i][j] > maxQty) {
                        maxQty  = matriksPenjualan[i][j];
                        maxUkur = j;
                        adaData = true;
                    }
                }
                if (adaData) {
                    cout << namaBulan[i] << ": Ukuran "
                         << namaUkuran[maxUkur] << " terlaris ("
                         << maxQty << " pcs)" << endl;
                }
            }
            cout << "============================================================" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            bangunMatriksPenjualan();
            int maxTotal = 0;
            int bulanMax = 0;
            for (int i = 0; i < MAX_BULAN; i++) {
                int total = 0;
                for (int j = 0; j < MAX_UKURAN; j++) {
                    total += matriksPenjualan[i][j];
                }
                if (total > maxTotal) {
                    maxTotal = total;
                    bulanMax = i;
                }
            }
            cout << "============================================================" << endl;
            cout << "  BULAN DENGAN PENJUALAN TERTINGGI                        " << endl;
            cout << "============================================================" << endl;
            if (maxTotal == 0) {
                cout << "Belum ada data penjualan." << endl;
            } else {
                cout << "Bulan    : " << namaBulan[bulanMax] << endl;
                cout << "Total    : " << maxTotal << " pcs terjual" << endl;
            }
            cout << "============================================================" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            transposeMatriksDisplay();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuLogAktivitas() {
    int pilihan;
    do {
        headerMenu("LOG AKTIVITAS SISTEM (Linked List)");
        cout << "(Praktikum 10 - Pointer & Linked List)" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1. Tampil Semua Log (Terbaru -> Terlama)" << endl;
        cout << "2. Tampil Log Kronologis (Rekursi)" << endl;
        cout << "3. Cari Log by Pengguna" << endl;
        cout << "4. Hapus Log Terbaru" << endl;
        cout << "5. Hapus Log Terlama" << endl;
        cout << "6. Hitung Total Log (Rekursi)" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            logSistem.tampilLog();
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            logSistem.tampilLogKronologis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            string pengguna;
            cout << "Username: ";
            cin >> pengguna;
            cin.ignore();
            logSistem.cariLogByPengguna(pengguna);
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            logSistem.hapusLogTerbaru();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            logSistem.hapusLogTerlama();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            cout << "Total log (dihitung rekursif): "
                 << logSistem.getJumlahLog() << " entri" << endl;
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuPelanggan() {
    int pilihan;
    do {
        headerMenu("MANAJEMEN PELANGGAN & LOYALITAS");
        cout << "(Implementasi Linked List - Praktikum 10)" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1. Daftarkan Pelanggan Baru" << endl;
        cout << "2. Lihat Detail Pelanggan" << endl;
        cout << "3. Tampil Semua Pelanggan" << endl;
        cout << "4. Tambah Poin Pelanggan (Manual)" << endl;
        cout << "5. Tukar Poin dengan Diskon" << endl;
        cout << "6. Urutkan Pelanggan berdasarkan Poin" << endl;
        cout << "7. Urutkan Pelanggan berdasarkan Kunjungan" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama, hp;
            cout << "Nama Lengkap: ";
            getline(cin, nama);
            cout << "No. HP      : ";
            cin >> hp;
            cin.ignore();
            daftarPelanggan.tambahPelanggan(nama, hp);
            daftarPelanggan.simpanKeFile();
            logSistem.tambahLog("Daftar pelanggan baru: " + nama, "admin", "Log");
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            string nama;
            cout << "Nama Pelanggan: ";
            getline(cin, nama);
            daftarPelanggan.tampilDetailPelanggan(nama);
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            daftarPelanggan.tampilSemuaPelanggan();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            string nama;
            int belanja;
            cout << "Nama Pelanggan     : ";
            getline(cin, nama);
            cout << "Total Belanja (Rp) : ";
            cin >> belanja;
            cin.ignore();
            daftarPelanggan.tambahPoinPelanggan(nama, belanja);
            daftarPelanggan.simpanKeFile();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            string nama;
            int poin;
            cout << "Nama Pelanggan: ";
            getline(cin, nama);
            daftarPelanggan.tampilDetailPelanggan(nama);
            cout << "Jumlah Poin Ditukar: ";
            cin >> poin;
            cin.ignore();
            daftarPelanggan.tukarPoin(nama, poin);
            daftarPelanggan.simpanKeFile();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            daftarPelanggan.urutkanByPoin();
            daftarPelanggan.simpanKeFile();
            daftarPelanggan.tampilSemuaPelanggan();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            daftarPelanggan.urutkanByKunjungan();
            daftarPelanggan.simpanKeFile();
            daftarPelanggan.tampilSemuaPelanggan();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuAntrian() {
    int pilihan;
    do {
        headerMenu("SISTEM ANTRIAN PELAYANAN");
        cout << "(Konsep Sekuen, Kondisional & Perulangan - Praktikum 1-3)" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1. Ambil Nomor Antrian" << endl;
        cout << "2. Panggil Antrian Berikutnya" << endl;
        cout << "3. Status Antrian" << endl;
        cout << "4. Reset Antrian (Hari Baru)" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama, layanan;
            cout << "Nama Customer     : ";
            getline(cin, nama);
            cout << "Jenis Layanan:" << endl;
            cout << "  (1=Transaksi Beli, 2=Retur, 3=Info Produk) -> ";
            int jl;
            cin >> jl;
            cin.ignore();
            if (jl == 1) layanan = "Transaksi Beli";
            else if (jl == 2) layanan = "Retur Produk";
            else if (jl == 3) layanan = "Info Produk";
            else layanan = "Umum";
            tambahAntrian(nama, layanan);
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            panggilAntrian();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            tampilStatusAntrian();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            if (konfirmasi("Reset semua antrian hari ini?")) {
                jumlahAntrian     = 0;
                nomorAntrianCount = 1;
                indexFront        = 0;
                cout << "[?] Antrian berhasil direset!" << endl;
            }
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuKalkulatorLengkap() {
    int pilihan;
    do {
        headerMenu("MENU KALKULATOR");
        cout << "1. Kalkulator Diskon Pembelian" << endl;
        cout << "2. Kalkulator Pajak PPN (11%)" << endl;
        cout << "3. Kalkulator Profit Margin" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            kalkulatorDiskonPembelian();
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            kalkulatorPajakPenjualan();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            kalkulatorProfitMargin();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

void menuSistem() {
    int pilihan;
    do {
        headerMenu("MENU SISTEM");
        cout << "1. Info Sistem" << endl;
        cout << "2. Backup Data" << endl;
        cout << "3. Validasi Data" << endl;
        cout << "4. Reset Riwayat Transaksi" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tampilInfoSistem();
            tekanEnterUntukLanjut();
        } else if (pilihan == 2) {
            backupData();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            cekValidasiSemuaData();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            resetSemuaTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// =====================================================
// MENU TRANSAKSI (KASIR)
// =====================================================

void menuTransaksi(int indexUser) {
    string tanggal;
    cout << "Masukkan tanggal transaksi (dd-mm-yyyy): ";
    cin >> tanggal;
    cin.ignore();

    string noStruk = generateNoStruk();
    Transaksi trx(daftarUser[indexUser].getUsername(), tanggal, noStruk);

    string namaPembeli;
    cout << "Nama pembeli: ";
    getline(cin, namaPembeli);
    if (namaPembeli == "") namaPembeli = "Umum";
    trx.setNamaPembeli(namaPembeli);

    int pilihan;
    do {
        headerMenu("MENU TRANSAKSI - " + noStruk);
        cout << "1. Tambah Item ke Keranjang" << endl;
        cout << "2. Hapus Item dari Keranjang" << endl;
        cout << "3. Tampil Keranjang" << endl;
        cout << "4. Bayar & Cetak Struk" << endl;
        cout << "0. Batal Transaksi" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            tampilSemuaProduk();
            string id;
            int qty;
            cout << "ID Produk: ";
            cin >> id;
            int index = cariProdukById(id);
            if (index == -1) {
                cout << "[!] Produk tidak ditemukan!" << endl;
            } else if (daftarProduk[index].cekStokHabis()) {
                cout << "[!] Stok habis!" << endl;
            } else {
                cout << "Qty: ";
                cin >> qty;
                if (qty <= 0) {
                    cout << "[!] Qty harus lebih dari 0!" << endl;
                } else if (qty > daftarProduk[index].getStok()) {
                    cout << "[!] Stok tidak mencukupi! Stok tersedia: "
                         << daftarProduk[index].getStok() << endl;
                } else {
                    trx.tambahItem(
                        daftarProduk[index].getIdProduk(),
                        daftarProduk[index].getNama(),
                        daftarProduk[index].getUkuran(),
                        daftarProduk[index].getHarga(),
                        qty
                    );
                    daftarProduk[index].kurangiStok(qty);
                    fm.simpanProduk();
                    cout << "[?] Item berhasil ditambahkan ke keranjang!" << endl;
                }
            }
        } else if (pilihan == 2) {
            trx.tampilKeranjang();
            int index;
            cout << "Nomor item yang dihapus: ";
            cin >> index;
            cin.ignore();
            if (index < 1 || index > trx.getJumlahItem()) {
                cout << "[!] Nomor tidak valid!" << endl;
            } else {
                ItemBelanja item = trx.getItem(index - 1);
                int idxProduk = cariProdukById(item.idProduk);
                if (idxProduk != -1) {
                    daftarProduk[idxProduk].tambahStok(item.qty);
                    fm.simpanProduk();
                }
                trx.hapusItem(index - 1);
            }
        } else if (pilihan == 3) {
            trx.tampilKeranjang();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            if (trx.getJumlahItem() == 0) {
                cout << "[!] Keranjang kosong!" << endl;
            } else {
                trx.tampilKeranjang();
                int bayar;
                cout << "Total  : Rp " << trx.getTotalHarga() << endl;
                cout << "Bayar  : Rp ";
                cin >> bayar;
                if (bayar < trx.getTotalHarga()) {
                    cout << "[!] Pembayaran kurang!" << endl;
                } else {
                    trx.setBayar(bayar);
                    trx.cetakStruk();
                    // Tambah poin pelanggan otomatis
                    if (trx.getNamaPembeli() != "Umum") {
                        NodePelanggan* p = daftarPelanggan.cariPelanggan(trx.getNamaPembeli());
                        if (p != NULL) {
                            daftarPelanggan.tambahPoinPelanggan(
                                trx.getNamaPembeli(), trx.getTotalHarga(),
                                trx.getTanggal());
                            daftarPelanggan.simpanKeFile();
                        }
                    }
                    simpanRiwayat(trx);
                    fm.simpanTransaksi();
                    logSistem.tambahLog("Transaksi " + trx.getNoStruk(),
                                        daftarUser[indexUser].getUsername(), "Log");
                    cout << "[?] Transaksi berhasil!" << endl;
                    pilihan = 0;
                }
            }
        } else if (pilihan == 0) {
            if (trx.getJumlahItem() > 0) {
                if (konfirmasi("Yakin ingin membatalkan transaksi?")) {
                    for (int i = 0; i < trx.getJumlahItem(); i++) {
                        ItemBelanja item = trx.getItem(i);
                        int idxProduk = cariProdukById(item.idProduk);
                        if (idxProduk != -1) {
                            daftarProduk[idxProduk].tambahStok(item.qty);
                        }
                    }
                    fm.simpanProduk();
                    cout << "Transaksi dibatalkan." << endl;
                } else {
                    pilihan = 1;
                }
            }
        } else {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// =====================================================
// MENU LOGIN
// =====================================================

int menuLogin() {
    headerMenu("LOGIN SISTEM");
    cout << "           JEGGER T-SHIRT                  " << endl;
    cout << "    Jl. Malioboro No.77, Yogyakarta        " << endl;
    garisPemisah();
    string u, p;
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;
    cin.ignore();

    if (u == "" || p == "") {
        cout << "[!] Username dan password tidak boleh kosong!" << endl;
        return -1;
    }

    int index = loginUser(u, p);
    if (index == -1) {
        cout << "[!] Username atau password salah!" << endl;
        return -1;
    }

    cout << "[?] Login berhasil!" << endl;
    cout << "Selamat datang, " << daftarUser[index].getUsername()
         << " (" << daftarUser[index].getRole() << ")" << endl;
    return index;
}

// =====================================================
// MENU KASIR LENGKAP
// =====================================================

void menuKasirLengkap(int indexUser) {
    logSistem.tambahLog("Login sebagai kasir",
                        daftarUser[indexUser].getUsername(), "Log");
    int pilihan;
    do {
        headerMenu("MENU KASIR");
        cout << "Selamat datang, " << daftarUser[indexUser].getUsername() << "!" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[TRANSAKSI]" << endl;
        cout << "1. Buat Transaksi Baru" << endl;
        cout << "2. Riwayat Transaksi" << endl;
        cout << "3. Cari Transaksi" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[PRODUK]" << endl;
        cout << "4. Lihat Semua Produk" << endl;
        cout << "5. Cari Produk" << endl;
        cout << "6. Cek Stok Menipis" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[PELANGGAN]" << endl;
        cout << "7. Manajemen Pelanggan & Loyalitas" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[ANTRIAN]" << endl;
        cout << "8. Sistem Antrian" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[AKUN]" << endl;
        cout << "9. Ganti Password" << endl;
        cout << "10. Info Akun" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            logSistem.tambahLog("Membuat transaksi baru",
                                daftarUser[indexUser].getUsername(), "Log");
            menuTransaksi(indexUser);
        } else if (pilihan == 2) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            menuCariTransaksi(indexUser);
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            tampilSemuaProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            menuCariProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            tampilStokMenipis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            menuPelanggan();
        } else if (pilihan == 8) {
            menuAntrian();
        } else if (pilihan == 9) {
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            cin.ignore();
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan == 10) {
            daftarUser[indexUser].tampilUser();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
    logSistem.tambahLog("Logout kasir",
                        daftarUser[indexUser].getUsername(), "Log");
}

// =====================================================
// MENU ADMIN FINAL LENGKAP
// =====================================================

void menuAdminFinal(int indexUser) {
    logSistem.tambahLog("Login sebagai admin",
                        daftarUser[indexUser].getUsername(), "Log");
    int pilihan;
    do {
        headerMenu("MENU ADMIN");
        cout << "Selamat datang, " << daftarUser[indexUser].getUsername() << "!" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[PRODUK]" << endl;
        cout << "1.  Tambah Produk Baru" << endl;
        cout << "2.  Edit Produk" << endl;
        cout << "3.  Hapus Produk" << endl;
        cout << "4.  Tampil Semua Produk" << endl;
        cout << "5.  Cari Produk" << endl;
        cout << "6.  Urutkan Produk (Bubble/Selection/Insertion Sort)" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[STOK]" << endl;
        cout << "7.  Kelola Stok" << endl;
        cout << "8.  Menu Pengemasan" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[TRANSAKSI]" << endl;
        cout << "9.  Riwayat Transaksi" << endl;
        cout << "10. Cari Transaksi" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[LAPORAN & STATISTIK]" << endl;
        cout << "11. Menu Laporan" << endl;
        cout << "12. Statistik Produk" << endl;
        cout << "13. Statistik Transaksi" << endl;
        cout << "14. Laporan Periode Kustom" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[FITUR ALGORITMA]" << endl;
        cout << "15. Binary Search & Demo Sorting" << endl;
        cout << "16. Fitur Rekursi - Analisis Data" << endl;
        cout << "17. Analisis Matriks (Array 2D)" << endl;
        cout << "18. Menu Kalkulator" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[MANAJEMEN]" << endl;
        cout << "19. Kelola User" << endl;
        cout << "20. Manajemen Pelanggan & Loyalitas" << endl;
        cout << "21. Sistem Antrian" << endl;
        cout << "22. Log Aktivitas Sistem" << endl;
        cout << "23. Menu Sistem" << endl;
        cout << "24. Info Akun" << endl;
        cout << "25. Ganti Password" << endl;
        cout << "26. Rekap Seluruh Kategori Data" << endl;
        cout << "0.  Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuInputProduk();
            logSistem.tambahLog("Tambah produk baru",
                                daftarUser[indexUser].getUsername(), "Log");
        } else if (pilihan == 2) {
            menuEditProduk();
            logSistem.tambahLog("Edit produk",
                                daftarUser[indexUser].getUsername(), "Log");
        } else if (pilihan == 3) {
            menuHapusProduk();
            logSistem.tambahLog("Hapus produk",
                                daftarUser[indexUser].getUsername(), "Log");
        } else if (pilihan == 4) {
            tampilSemuaProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            menuCariProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            menuSortProdukLengkap();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            menuKelolaStok();
        } else if (pilihan == 8) {
            menuPengemasan(indexUser);
        } else if (pilihan == 9) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 10) {
            menuCariTransaksi(indexUser);
            tekanEnterUntukLanjut();
        } else if (pilihan == 11) {
            menuLaporan();
        } else if (pilihan == 12) {
            statistikProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 13) {
            statistikTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 14) {
            laporanPeriodeKustom();
            tekanEnterUntukLanjut();
        } else if (pilihan == 15) {
            menuBinarySearch();
            tekanEnterUntukLanjut();
        } else if (pilihan == 16) {
            menuFiturRekursi();
        } else if (pilihan == 17) {
            menuMatriksAnalisis();
        } else if (pilihan == 18) {
            menuKalkulatorLengkap();
        } else if (pilihan == 19) {
            menuKelolaUser();
        } else if (pilihan == 20) {
            menuPelanggan();
        } else if (pilihan == 21) {
            menuAntrian();
        } else if (pilihan == 22) {
            menuLogAktivitas();
        } else if (pilihan == 23) {
            menuSistem();
        } else if (pilihan == 24) {
            daftarUser[indexUser].tampilUser();
            tekanEnterUntukLanjut();
        } else if (pilihan == 25) {
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            cin.ignore();
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan == 26) {
            laporanRekapEntitas();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
    logSistem.tambahLog("Logout admin",
                        daftarUser[indexUser].getUsername(), "Log");
}

int main() {
    fm.bacaSemua();
    daftarPelanggan.bacaDariFile();

    if (jumlahUser == 0) {
        tambahUser("admin",  "admin123",  "admin");
        tambahUser("kasir",  "kasir123",  "kasir");
        fm.simpanUser();
    }

    logSistem.tambahLog("Sistem dimulai", "sistem", "Log");

    int pilihan;
    do {
        cout << endl;
        cout << "============================================================" << endl;
        cout << "            SISTEM TOKO KAOS JEGGER T-SHIRT               " << endl;
        cout << "         Jl. Malioboro No.77, Yogyakarta                   " << endl;
        cout << "      Praktikum Algoritma Pemrograman - UAD 2026           " << endl;
        cout << "============================================================" << endl;
        cout << "1. Login" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            int indexUser = menuLogin();
            if (indexUser != -1) {
                if (daftarUser[indexUser].isAdmin()) {
                    menuAdminFinal(indexUser);
                } else if (daftarUser[indexUser].isKasir()) {
                    menuKasirLengkap(indexUser);
                }
            }
        } else if (pilihan == 0) {
            logSistem.tambahLog("Sistem dimatikan", "sistem", "Log");
            fm.simpanSemua();
            daftarPelanggan.simpanKeFile();
            cout << "============================================================" << endl;
            cout << "     Terima kasih telah menggunakan sistem ini!            " << endl;
            cout << "     JEGGER T-SHIRT - Jl. Malioboro No.77, Yogyakarta     " << endl;
            cout << "============================================================" << endl;
        } else {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}
