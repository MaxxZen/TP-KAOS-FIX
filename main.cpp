#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

#include "user.cpp"
#include "produk.cpp"
#include "transaksi.cpp"
#include "laporan.cpp"
#include "filemanager.cpp"

// FUNGSI HELPER

FileManager fm;
Laporan laporan;

int noStrukCounter = 1;

string generateNoStruk() {
    string no = "TRX";
    if (noStrukCounter < 10) {
        no += "00" + to_string(noStrukCounter);
    } else if (noStrukCounter < 100) {
        no += "0" + to_string(noStrukCounter);
    } else {
        no += to_string(noStrukCounter);
    }
    noStrukCounter++;
    return no;
}

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

// MENU PRODUK (ADMIN)

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
    } else {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
}

void menuSortProduk() {
    headerMenu("URUTKAN PRODUK");
    cout << "1. Urutkan by Harga" << endl;
    cout << "2. Urutkan by Nama" << endl;
    cout << "3. Urutkan by Stok" << endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        sortProdukByHarga();
    } else if (pilihan == 2) {
        sortProdukByNama();
    } else if (pilihan == 3) {
        sortProdukByStok();
    } else {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
    tampilSemuaProduk();
}

void menuKelolaUser() {
    int pilihan;
    do {
        headerMenu("KELOLA USER");
        cout << "1. Tambah User" << endl;
        cout << "2. Hapus User" << endl;
        cout << "3. Tampil Semua User" << endl;
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
        }
    } while (pilihan != 0);
}

void menuPengemasan() {
    int pilihan;
    do {
        headerMenu("MENU PENGEMASAN");
        cout << "1. Tampil Status Pengemasan" << endl;
        cout << "2. Update Status Pengemasan" << endl;
        cout << "3. Laporan Pengemasan" << endl;
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
        }
    } while (pilihan != 0);
}

void menuLaporan() {
    int pilihan;
    do {
        headerMenu("MENU LAPORAN");
        cout << "1. Laporan Harian" << endl;
        cout << "2. Laporan Omzet Total" << endl;
        cout << "3. Laporan Produk Terlaris" << endl;
        cout << "4. Laporan Stok Menipis" << endl;
        cout << "5. Laporan Rekap Ukuran" << endl;
        cout << "6. Laporan Laba Rugi" << endl;
        cout << "7. Laporan Pengemasan" << endl;
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
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// MENU ADMIN

void menuAdmin(int indexUser) {
    int pilihan;
    do {
        headerMenu("MENU ADMIN");
        cout << "Selamat datang, " << daftarUser[indexUser].getUsername() << "!" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1.  Tambah Produk" << endl;
        cout << "2.  Edit Produk" << endl;
        cout << "3.  Hapus Produk" << endl;
        cout << "4.  Tampil Semua Produk" << endl;
        cout << "5.  Cari Produk" << endl;
        cout << "6.  Urutkan Produk" << endl;
        cout << "7.  Stok Menipis" << endl;
        cout << "8.  Menu Laporan" << endl;
        cout << "9.  Kelola User" << endl;
        cout << "10. Menu Pengemasan" << endl;
        cout << "11. Riwayat Transaksi" << endl;
        cout << "12. Ganti Password" << endl;
        cout << "0.  Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuInputProduk();
        } else if (pilihan == 2) {
            menuEditProduk();
        } else if (pilihan == 3) {
            menuHapusProduk();
        } else if (pilihan == 4) {
            tampilSemuaProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            menuCariProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            menuSortProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            tampilStokMenipis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 8) {
            menuLaporan();
        } else if (pilihan == 9) {
            menuKelolaUser();
        } else if (pilihan == 10) {
            menuPengemasan();
        } else if (pilihan == 11) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 12) {
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// MENU TRANSAKSI (KASIR)

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
                    cout << "[OK] Item berhasil ditambahkan ke keranjang!" << endl;
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
                    simpanRiwayat(trx);
                    fm.simpanTransaksi();
                    cout << "[OK] Transaksi berhasil!" << endl;
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

// MENU KASIR

void menuKasir(int indexUser) {
    int pilihan;
    do {
        headerMenu("MENU KASIR");
        cout << "Selamat datang, " << daftarUser[indexUser].getUsername() << "!" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "1. Buat Transaksi Baru" << endl;
        cout << "2. Lihat Produk" << endl;
        cout << "3. Cari Produk" << endl;
        cout << "4. Riwayat Transaksi" << endl;
        cout << "5. Detail Transaksi" << endl;
        cout << "6. Ganti Password" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuTransaksi(indexUser);
        } else if (pilihan == 2) {
            tampilSemuaProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            menuCariProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 4) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            string noStruk;
            cout << "Masukkan No Struk: ";
            cin >> noStruk;
            tampilDetailTransaksi(noStruk);
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// MENU LOGIN

int menuLogin() {
    headerMenu("LOGIN SISTEM");
    cout << "           TOKO KAOS                  " << endl;
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

    cout << "[OK] Login berhasil!" << endl;
    cout << "Selamat datang, " << daftarUser[index].getUsername()
         << " (" << daftarUser[index].getRole() << ")" << endl;
    return index;
}

// MAIN

int main() {
    fm.bacaSemua();

    if (jumlahUser == 0) {
        tambahUser("admin", "admin123", "admin");
        tambahUser("kasir", "kasir123", "kasir");
        fm.simpanUser();
    }

    int pilihan;
    do {
        cout << endl;
        cout << "============================================================" << endl;
        cout << "                 SISTEM TOKO KAOS              " << endl;
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
                    menuAdmin(indexUser);
                } else if (daftarUser[indexUser].isKasir()) {
                    menuKasir(indexUser);
                }
            }
        } else if (pilihan == 0) {
            fm.simpanSemua();
            cout << "============================================================" << endl;
            cout << "     Terima kasih telah menggunakan sistem ini!            " << endl;
            cout << "============================================================" << endl;
        } else {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}

// FUNGSI TAMBAHAN - STATISTIK & ANALISIS

void statistikProduk() {
    if (jumlahProduk == 0) {
        cout << "[!] Belum ada data produk!" << endl;
        return;
    }

    int totalStok   = 0;
    int totalHarga  = 0;
    int hargaMin    = daftarProduk[0].getHarga();
    int hargaMax    = daftarProduk[0].getHarga();
    int stokMin     = daftarProduk[0].getStok();
    int stokMax     = daftarProduk[0].getStok();
    string produkHargaMin = daftarProduk[0].getNama();
    string produkHargaMax = daftarProduk[0].getNama();
    string produkStokMin  = daftarProduk[0].getNama();
    string produkStokMax  = daftarProduk[0].getNama();

    for (int i = 0; i < jumlahProduk; i++) {
        totalStok  += daftarProduk[i].getStok();
        totalHarga += daftarProduk[i].getHarga();

        if (daftarProduk[i].getHarga() < hargaMin) {
            hargaMin = daftarProduk[i].getHarga();
            produkHargaMin = daftarProduk[i].getNama();
        }
        if (daftarProduk[i].getHarga() > hargaMax) {
            hargaMax = daftarProduk[i].getHarga();
            produkHargaMax = daftarProduk[i].getNama();
        }
        if (daftarProduk[i].getStok() < stokMin) {
            stokMin = daftarProduk[i].getStok();
            produkStokMin = daftarProduk[i].getNama();
        }
        if (daftarProduk[i].getStok() > stokMax) {
            stokMax = daftarProduk[i].getStok();
            produkStokMax = daftarProduk[i].getNama();
        }
    }

    int rataHarga = totalHarga / jumlahProduk;

    cout << "============================================================" << endl;
    cout << "              STATISTIK PRODUK                             " << endl;
    cout << "============================================================" << endl;
    cout << "Total Jenis Produk : " << jumlahProduk << endl;
    cout << "Total Stok         : " << totalStok << " pcs" << endl;
    cout << "Rata-rata Harga    : Rp " << rataHarga << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Harga Termurah     : Rp " << hargaMin << " (" << produkHargaMin << ")" << endl;
    cout << "Harga Termahal     : Rp " << hargaMax << " (" << produkHargaMax << ")" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Stok Paling Sedikit: " << stokMin << " pcs (" << produkStokMin << ")" << endl;
    cout << "Stok Paling Banyak : " << stokMax << " pcs (" << produkStokMax << ")" << endl;
    cout << "============================================================" << endl;
}

void statistikTransaksi() {
    if (jumlahTransaksi == 0) {
        cout << "[!] Belum ada data transaksi!" << endl;
        return;
    }

    int totalOmzet  = 0;
    int trxMin      = riwayatTransaksi[0].getTotalHarga();
    int trxMax      = riwayatTransaksi[0].getTotalHarga();
    string noMin    = riwayatTransaksi[0].getNoStruk();
    string noMax    = riwayatTransaksi[0].getNoStruk();

    for (int i = 0; i < jumlahTransaksi; i++) {
        totalOmzet += riwayatTransaksi[i].getTotalHarga();

        if (riwayatTransaksi[i].getTotalHarga() < trxMin) {
            trxMin = riwayatTransaksi[i].getTotalHarga();
            noMin  = riwayatTransaksi[i].getNoStruk();
        }
        if (riwayatTransaksi[i].getTotalHarga() > trxMax) {
            trxMax = riwayatTransaksi[i].getTotalHarga();
            noMax  = riwayatTransaksi[i].getNoStruk();
        }
    }

    int rataOmzet = totalOmzet / jumlahTransaksi;

    cout << "============================================================" << endl;
    cout << "              STATISTIK TRANSAKSI                          " << endl;
    cout << "============================================================" << endl;
    cout << "Total Transaksi    : " << jumlahTransaksi << endl;
    cout << "Total Omzet        : Rp " << totalOmzet << endl;
    cout << "Rata-rata/Transaksi: Rp " << rataOmzet << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Transaksi Terkecil : Rp " << trxMin << " (" << noMin << ")" << endl;
    cout << "Transaksi Terbesar : Rp " << trxMax << " (" << noMax << ")" << endl;
    cout << "============================================================" << endl;
}

// FUNGSI TAMBAH STOK (ADMIN)

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

// FUNGSI BACKUP DATA

void backupData() {
    ofstream backupUser("backup_user.txt");
    if (backupUser.is_open()) {
        for (int i = 0; i < jumlahUser; i++) {
            backupUser << daftarUser[i].getUsername() << "|"
                       << daftarUser[i].getPassword() << "|"
                       << daftarUser[i].getRole() << "\n";
        }
        backupUser.close();
    }

    ofstream backupProduk("backup_produk.txt");
    if (backupProduk.is_open()) {
        for (int i = 0; i < jumlahProduk; i++) {
            backupProduk << daftarProduk[i].getIdProduk()  << "|"
                         << daftarProduk[i].getNama()       << "|"
                         << daftarProduk[i].getUkuran()     << "|"
                         << daftarProduk[i].getHarga()      << "|"
                         << daftarProduk[i].getStok()       << "|"
                         << daftarProduk[i].getBahan()      << "|"
                         << daftarProduk[i].getStatus()     << "\n";
        }
        backupProduk.close();
    }

    ofstream backupTrx("backup_transaksi.txt");
    if (backupTrx.is_open()) {
        for (int i = 0; i < jumlahTransaksi; i++) {
            backupTrx << riwayatTransaksi[i].getNoStruk()    << "|"
                      << riwayatTransaksi[i].getTanggal()    << "|"
                      << riwayatTransaksi[i].getKasir()      << "|"
                      << riwayatTransaksi[i].getNamaPembeli()<< "|"
                      << riwayatTransaksi[i].getTotalHarga() << "\n";
        }
        backupTrx.close();
    }

    cout << "[OK] Backup data berhasil!" << endl;
}

// MENU ADMIN TAMBAHAN

void menuAdminLengkap(int indexUser) {
    int pilihan;
    do {
        headerMenu("MENU ADMIN");
        cout << "Selamat datang, " << daftarUser[indexUser].getUsername() << "!" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[PRODUK]" << endl;
        cout << "1.  Tambah Produk Baru" << endl;
        cout << "2.  Edit Produk" << endl;
        cout << "3.  Hapus Produk" << endl;
        cout << "4.  Tambah Stok Produk" << endl;
        cout << "5.  Tampil Semua Produk" << endl;
        cout << "6.  Cari Produk" << endl;
        cout << "7.  Urutkan Produk" << endl;
        cout << "8.  Cek Stok Menipis" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[LAPORAN]" << endl;
        cout << "9.  Menu Laporan" << endl;
        cout << "10. Statistik Produk" << endl;
        cout << "11. Statistik Transaksi" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "[USER & SISTEM]" << endl;
        cout << "12. Kelola User" << endl;
        cout << "13. Menu Pengemasan" << endl;
        cout << "14. Riwayat Transaksi" << endl;
        cout << "15. Detail Transaksi" << endl;
        cout << "16. Backup Data" << endl;
        cout << "17. Ganti Password" << endl;
        cout << "0.  Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuInputProduk();
        } else if (pilihan == 2) {
            menuEditProduk();
        } else if (pilihan == 3) {
            menuHapusProduk();
        } else if (pilihan == 4) {
            menuTambahStok();
        } else if (pilihan == 5) {
            tampilSemuaProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            menuCariProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            menuSortProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 8) {
            tampilStokMenipis();
            tekanEnterUntukLanjut();
        } else if (pilihan == 9) {
            menuLaporan();
        } else if (pilihan == 10) {
            statistikProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 11) {
            statistikTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 12) {
            menuKelolaUser();
        } else if (pilihan == 13) {
            menuPengemasan();
        } else if (pilihan == 14) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 15) {
            string noStruk;
            cout << "Masukkan No Struk: ";
            cin >> noStruk;
            tampilDetailTransaksi(noStruk);
            tekanEnterUntukLanjut();
        } else if (pilihan == 16) {
            backupData();
            tekanEnterUntukLanjut();
        } else if (pilihan == 17) {
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// TAMPIL INFO SISTEM

void tampilInfoSistem() {
    cout << "============================================================" << endl;
    cout << "              INFO SISTEM                                  " << endl;
    cout << "============================================================" << endl;
    cout << "Nama Toko      : Jegger T-Shirt" << endl;
    cout << "Alamat         : Jl. Malioboro No.77, Yogyakarta" << endl;
    cout << "Telepon        : 0013-2006-7888 / 0012-2720-9026" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Jumlah User    : " << jumlahUser << endl;
    cout << "Jumlah Produk  : " << jumlahProduk << endl;
    cout << "Jumlah Transaksi: " << jumlahTransaksi << endl;
    cout << "============================================================" << endl;
}

// PENCARIAN TRANSAKSI dari KASIR

void cariTransaksiByKasir(string kasir) {
    bool ada = false;
    int total = 0;
    int jumlah = 0;

    cout << "============================================================" << endl;
    cout << "  TRANSAKSI KASIR: " << kasir << endl;
    cout << "============================================================" << endl;
    cout << "No\tNo Struk\tTanggal\t\tTotal" << endl;
    cout << "------------------------------------------------------------" << endl;

    int no = 1;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (riwayatTransaksi[i].getKasir() == kasir) {
            cout << no << "\t"
                 << riwayatTransaksi[i].getNoStruk() << "\t"
                 << riwayatTransaksi[i].getTanggal() << "\t"
                 << "Rp " << riwayatTransaksi[i].getTotalHarga() << endl;
            total += riwayatTransaksi[i].getTotalHarga();
            jumlah++;
            no++;
            ada = true;
        }
    }

    if (!ada) {
        cout << "[!] Tidak ada transaksi dari kasir " << kasir << endl;
    } else {
        cout << "------------------------------------------------------------" << endl;
        cout << "Total Transaksi : " << jumlah << endl;
        cout << "Total Omzet     : Rp " << total << endl;
    }
    cout << "============================================================" << endl;
}

// PENCARIAN TRANSAKSI BY PEMBELI

void cariTransaksiByPembeli(string pembeli) {
    bool ada = false;
    cout << "============================================================" << endl;
    cout << "  TRANSAKSI PEMBELI: " << pembeli << endl;
    cout << "============================================================" << endl;
    cout << "No\tNo Struk\tTanggal\t\tTotal" << endl;
    cout << "------------------------------------------------------------" << endl;

    int no = 1;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (riwayatTransaksi[i].getNamaPembeli() == pembeli) {
            cout << no << "\t"
                 << riwayatTransaksi[i].getNoStruk() << "\t"
                 << riwayatTransaksi[i].getTanggal() << "\t"
                 << "Rp " << riwayatTransaksi[i].getTotalHarga() << endl;
            no++;
            ada = true;
        }
    }

    if (!ada) {
        cout << "[!] Tidak ada transaksi dari pembeli " << pembeli << endl;
    }
    cout << "============================================================" << endl;
}

// MENU CARI TRANSAKSI (ADMIN)

void menuCariTransaksi() {
    headerMenu("CARI TRANSAKSI");
    cout << "1. Cari by No Struk" << endl;
    cout << "2. Cari by Kasir" << endl;
    cout << "3. Cari by Pembeli" << endl;
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        string noStruk;
        cout << "No Struk: ";
        cin >> noStruk;
        tampilDetailTransaksi(noStruk);
    } else if (pilihan == 2) {
        string kasir;
        cout << "Nama Kasir: ";
        cin >> kasir;
        cariTransaksiByKasir(kasir);
    } else if (pilihan == 3) {
        string pembeli;
        cin.ignore();
        cout << "Nama Pembeli: ";
        getline(cin, pembeli);
        cariTransaksiByPembeli(pembeli);
    } else {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
}

// VALIDASI & CEK DATA

void cekValidasiSemuaData() {
    int produkTidakValid = 0;
    int userTidakValid   = 0;

    cout << "============================================================" << endl;
    cout << "              CEK VALIDASI DATA                            " << endl;
    cout << "============================================================" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        bool valid = true;
        if (daftarProduk[i].getIdProduk() == "") {
            cout << "[!] Produk index " << i << " ID kosong!" << endl;
            valid = false;
            produkTidakValid++;
        }
        if (daftarProduk[i].getNama() == "") {
            cout << "[!] Produk index " << i << " Nama kosong!" << endl;
            valid = false;
            produkTidakValid++;
        }
        if (daftarProduk[i].getHarga() < 0) {
            cout << "[!] Produk " << daftarProduk[i].getIdProduk()
                 << " harga negatif!" << endl;
            valid = false;
            produkTidakValid++;
        }
        if (daftarProduk[i].getStok() < 0) {
            cout << "[!] Produk " << daftarProduk[i].getIdProduk()
                 << " stok negatif!" << endl;
            valid = false;
            produkTidakValid++;
        }
    }

    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].getUsername() == "") {
            cout << "[!] User index " << i << " username kosong!" << endl;
            userTidakValid++;
        }
        if (daftarUser[i].getRole() != "admin" &&
            daftarUser[i].getRole() != "kasir") {
            cout << "[!] User " << daftarUser[i].getUsername()
                 << " role tidak valid!" << endl;
            userTidakValid++;
        }
    }

    if (produkTidakValid == 0 && userTidakValid == 0) {
        cout << "[OK] Semua data valid!" << endl;
    } else {
        cout << "Total masalah produk : " << produkTidakValid << endl;
        cout << "Total masalah user   : " << userTidakValid << endl;
    }
    cout << "============================================================" << endl;
}

// RESET DATA (ADMIN)

void resetSemuaTransaksi() {
    if (!konfirmasi("PERINGATAN! Yakin ingin menghapus semua riwayat transaksi?")) {
        cout << "Reset dibatalkan." << endl;
        return;
    }
    if (!konfirmasi("Konfirmasi sekali lagi, data tidak bisa dikembalikan!")) {
        cout << "Reset dibatalkan." << endl;
        return;
    }
    jumlahTransaksi = 0;
    noStrukCounter  = 1;
    fm.simpanTransaksi();
    cout << "[OK] Semua riwayat transaksi berhasil dihapus!" << endl;
}

// TAMPIL PRODUK STOK HABIS

void tampilProdukStokHabis() {
    bool ada = false;
    cout << "============================================================" << endl;
    cout << "              PRODUK STOK HABIS                           " << endl;
    cout << "============================================================" << endl;
    cout << "No\tID\tNama\t\tUkuran" << endl;
    cout << "------------------------------------------------------------" << endl;
    int no = 1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].cekStokHabis()) {
            cout << no << "\t"
                 << daftarProduk[i].getIdProduk() << "\t"
                 << daftarProduk[i].getNama() << "\t\t"
                 << daftarProduk[i].getUkuran() << endl;
            no++;
            ada = true;
        }
    }
    if (!ada) {
        cout << "[OK] Tidak ada produk dengan stok habis!" << endl;
    }
    cout << "============================================================" << endl;
}

// MENU STOK (ADMIN)

void menuKelolaStok() {
    int pilihan;
    do {
        headerMenu("KELOLA STOK");
        cout << "1. Tambah Stok Produk" << endl;
        cout << "2. Tampil Produk Stok Menipis" << endl;
        cout << "3. Tampil Produk Stok Habis" << endl;
        cout << "4. Rekap Stok Per Ukuran" << endl;
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
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// MENU SISTEM (ADMIN)

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

// MENU KASIR

void menuKasirLengkap(int indexUser) {
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
        cout << "[AKUN]" << endl;
        cout << "7. Ganti Password" << endl;
        cout << "8. Info Akun" << endl;
        cout << "0. Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuTransaksi(indexUser);
        } else if (pilihan == 2) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 3) {
            menuCariTransaksi();
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
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan == 8) {
            daftarUser[indexUser].tampilUser();
            tekanEnterUntukLanjut();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}

// MENU ADMIN

void menuAdminFinal(int indexUser) {
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
        cout << "6.  Urutkan Produk" << endl;
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
        cout << "------------------------------------------------------------" << endl;
        cout << "[USER & SISTEM]" << endl;
        cout << "14. Kelola User" << endl;
        cout << "15. Menu Sistem" << endl;
        cout << "16. Info Akun" << endl;
        cout << "17. Ganti Password" << endl;
        cout << "0.  Logout" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            menuInputProduk();
        } else if (pilihan == 2) {
            menuEditProduk();
        } else if (pilihan == 3) {
            menuHapusProduk();
        } else if (pilihan == 4) {
            tampilSemuaProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 5) {
            menuCariProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 6) {
            menuSortProduk();
            tekanEnterUntukLanjut();
        } else if (pilihan == 7) {
            menuKelolaStok();
        } else if (pilihan == 8) {
            menuPengemasan();
        } else if (pilihan == 9) {
            tampilRiwayatTransaksi();
            tekanEnterUntukLanjut();
        } else if (pilihan == 10) {
            menuCariTransaksi();
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
            menuKelolaUser();
        } else if (pilihan == 15) {
            menuSistem();
        } else if (pilihan == 16) {
            daftarUser[indexUser].tampilUser();
            tekanEnterUntukLanjut();
        } else if (pilihan == 17) {
            string passLama, passBaru;
            cout << "Password lama: ";
            cin >> passLama;
            cout << "Password baru: ";
            cin >> passBaru;
            daftarUser[indexUser].gantiPassword(passLama, passBaru);
            fm.simpanUser();
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
}
