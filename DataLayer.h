#ifndef DATALAYER_H
#define DATALAYER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_USER      = 10;
const int MAX_PRODUK    = 100;
const int MAX_ITEM      = 20;
const int MAX_TRANSAKSI = 200;
const int MAX_ANTRIAN   = 50;
const int MAX_BULAN     = 12;
const int MAX_UKURAN    = 5;
class User {
private:
    string username;
    string password;
    string role;

public:
    User() {
        username = "";
        password = "";
        role     = "";
    }

    User(string u, string p, string r) {
        username = u;
        password = p;
        role     = r;
    }

    bool login(string u, string p) {
        if (username == u && password == p) {
            return true;
        }
        return false;
    }

    bool isAdmin() {
        if (role == "admin") {
            return true;
        }
        return false;
    }

    bool isKasir() {
        if (role == "kasir") {
            return true;
        }
        return false;
    }

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getRole()     { return role; }

    void setUsername(string u) { username = u; }
    void setPassword(string p) { password = p; }
    void setRole(string r)     { role = r; }

    bool validasiUsername(string u) {
        if (u == "") {
            cout << "[!] Username tidak boleh kosong!" << endl;
            return false;
        }
        if (u.length() < 4) {
            cout << "[!] Username minimal 4 karakter!" << endl;
            return false;
        }
        return true;
    }

    bool validasiPassword(string p) {
        if (p == "") {
            cout << "[!] Password tidak boleh kosong!" << endl;
            return false;
        }
        if (p.length() < 4) {
            cout << "[!] Password minimal 4 karakter!" << endl;
            return false;
        }
        return true;
    }

    bool gantiPassword(string passwordLama, string passwordBaru) {
        if (password != passwordLama) {
            cout << "[!] Password lama salah!" << endl;
            return false;
        }
        if (!validasiPassword(passwordBaru)) {
            return false;
        }
        password = passwordBaru;
        cout << "[?] Password berhasil diganti!" << endl;
        return true;
    }

    void tampilUser() {
        cout << "=========================" << endl;
        cout << "  DATA USER              " << endl;
        cout << "=========================" << endl;
        cout << "Username : " << username   << endl;
        cout << "Role     : " << role       << endl;
        cout << "=========================" << endl;
    }
};

// =====================================================
// ARRAY GLOBAL USER
// =====================================================

class Produk {
private:
    string idProduk;
    string namaProduk;
    string ukuran;
    int    harga;
    int    stok;
    string bahan;
    string status;

public:
    Produk() {
        idProduk   = "";
        namaProduk = "";
        ukuran     = "";
        harga      = 0;
        stok       = 0;
        bahan      = "";
        status     = "Belum Dikemas";
    }

    Produk(string id, string nama, string uk,
           int h, int s, string b) {
        idProduk   = id;
        namaProduk = nama;
        ukuran     = uk;
        harga      = h;
        stok       = s;
        bahan      = b;
        status     = "Belum Dikemas";
    }

    string getIdProduk() { return idProduk; }
    string getNama()     { return namaProduk; }
    string getUkuran()   { return ukuran; }
    int    getHarga()    { return harga; }
    int    getStok()     { return stok; }
    string getBahan()    { return bahan; }
    string getStatus()   { return status; }

    void setNama(string n)   { namaProduk = n; }
    void setBahan(string b)  { bahan = b; }
    void setUkuran(string u) { ukuran = u; }
    void setStatus(string s) { status = s; }

    void setHarga(int h) {
        if (h < 0) {
            cout << "[!] Harga tidak boleh negatif!" << endl;
            return;
        }
        harga = h;
    }

    void setStok(int s) {
        if (s < 0) {
            cout << "[!] Stok tidak boleh negatif!" << endl;
            return;
        }
        stok = s;
    }

    void tambahStok(int jumlah) {
        if (jumlah <= 0) {
            cout << "[!] Jumlah tambah stok harus lebih dari 0!" << endl;
            return;
        }
        stok += jumlah;
        cout << "[?] Stok berhasil ditambah!" << endl;
    }

    void kurangiStok(int jumlah) {
        if (jumlah <= 0) {
            cout << "[!] Jumlah kurang stok harus lebih dari 0!" << endl;
            return;
        }
        if (jumlah > stok) {
            cout << "[!] Stok tidak mencukupi!" << endl;
            return;
        }
        stok -= jumlah;
    }

    bool cekStokMenipis() {
        if (stok <= 5) return true;
        return false;
    }

    bool cekStokHabis() {
        if (stok == 0) return true;
        return false;
    }

    bool validasiUkuran(string u) {
        if (u == "S" || u == "M" || u == "L" ||
            u == "XL" || u == "XXL") {
            return true;
        }
        cout << "[!] Ukuran harus S/M/L/XL/XXL!" << endl;
        return false;
    }

    void tampilProduk() {
        cout << "======================================" << endl;
        cout << "ID      : " << idProduk   << endl;
        cout << "Nama    : " << namaProduk << endl;
        cout << "Ukuran  : " << ukuran     << endl;
        cout << "Harga   : Rp " << harga   << endl;
        cout << "Stok    : " << stok       << endl;
        cout << "Bahan   : " << bahan      << endl;
        cout << "Status  : " << status     << endl;
        if (cekStokMenipis()) {
            cout << "[!] STOK MENIPIS!" << endl;
        }
        cout << "======================================" << endl;
    }

    void tampilBaris(int no) {
        cout << no << "\t"
             << idProduk << "\t"
             << namaProduk << "\t"
             << ukuran << "\t"
             << "Rp " << harga << "\t"
             << stok << "\t"
             << status << endl;
    }
};

// =====================================================
// ARRAY GLOBAL PRODUK
// =====================================================


struct ItemBelanja {
    string idProduk;
    string namaProduk;
    string ukuran;
    int    hargaSatuan;
    int    qty;
    int    subtotal;
};

// =====================================================
// CLASS TRANSAKSI
// =====================================================

class Transaksi {
private:
    string      noStruk;
    string      namaPembeli;
    string      kasir;
    string      tanggal;
    ItemBelanja keranjang[MAX_ITEM];
    int         jumlahItem;
    int         totalHarga;
    int         bayar;
    int         kembalian;
    bool        sudahDiverifikasi;
    string      statusPengemasan;

public:
    Transaksi() {
        noStruk     = "";
        namaPembeli = "";
        kasir       = "";
        tanggal     = "";
        jumlahItem  = 0;
        totalHarga  = 0;
        bayar       = 0;
        kembalian   = 0;
        sudahDiverifikasi = false;
        statusPengemasan = "Belum Dikemas";
    }

    Transaksi(string k, string tgl, string no) {
        kasir       = k;
        tanggal     = tgl;
        noStruk     = no;
        namaPembeli = "";
        jumlahItem  = 0;
        totalHarga  = 0;
        bayar       = 0;
        kembalian   = 0;
        sudahDiverifikasi = false;
        statusPengemasan = "Belum Dikemas";
    }

    void setNamaPembeli(string nama) { namaPembeli = nama; }
    void setKasir(string k)          { kasir = k; }
    void setTanggal(string tgl)      { tanggal = tgl; }
    void setNoStruk(string no)       { noStruk = no; }
    void setSudahDiverifikasi(bool status) { sudahDiverifikasi = status; }
    void setStatusPengemasan(string status) { statusPengemasan = status; }

    void setBayar(int b) {
        bayar     = b;
        kembalian = b - totalHarga;
    }

    string getNoStruk()     { return noStruk; }
    string getNamaPembeli() { return namaPembeli; }
    string getKasir()       { return kasir; }
    string getTanggal()     { return tanggal; }
    int    getTotalHarga()  { return totalHarga; }
    int    getBayar()       { return bayar; }
    int    getKembalian()   { return kembalian; }
    int    getJumlahItem()  { return jumlahItem; }
    bool   getSudahDiverifikasi() { return sudahDiverifikasi; }
    string getStatusPengemasan() { return statusPengemasan; }

    ItemBelanja getItem(int index) {
        return keranjang[index];
    }

    bool tambahItem(string idProduk, string nama,
                    string ukuran, int harga, int qty) {
        if (jumlahItem >= MAX_ITEM) {
            cout << "[!] Keranjang penuh!" << endl;
            return false;
        }
        if (qty <= 0) {
            cout << "[!] Qty harus lebih dari 0!" << endl;
            return false;
        }
        if (harga < 0) {
            cout << "[!] Harga tidak valid!" << endl;
            return false;
        }
        keranjang[jumlahItem].idProduk    = idProduk;
        keranjang[jumlahItem].namaProduk  = nama;
        keranjang[jumlahItem].ukuran      = ukuran;
        keranjang[jumlahItem].hargaSatuan = harga;
        keranjang[jumlahItem].qty         = qty;
        keranjang[jumlahItem].subtotal    = harga * qty;
        jumlahItem++;
        totalHarga += harga * qty;
        return true;
    }

    bool hapusItem(int index) {
        if (index < 0 || index >= jumlahItem) {
            cout << "[!] Index tidak valid!" << endl;
            return false;
        }
        totalHarga -= keranjang[index].subtotal;
        for (int i = index; i < jumlahItem - 1; i++) {
            keranjang[i] = keranjang[i + 1];
        }
        jumlahItem--;
        cout << "[?] Item berhasil dihapus dari keranjang!" << endl;
        return true;
    }

    void tampilKeranjang() {
        if (jumlahItem == 0) {
            cout << "[!] Keranjang kosong!" << endl;
            return;
        }
        cout << "============================================================" << endl;
        cout << "                   KERANJANG BELANJA                       " << endl;
        cout << "============================================================" << endl;
        cout << "No\tNama\t\tUkuran\tHarga\t\tQty\tSubtotal" << endl;
        cout << "------------------------------------------------------------" << endl;
        for (int i = 0; i < jumlahItem; i++) {
            cout << i + 1 << "\t"
                 << keranjang[i].namaProduk << "\t\t"
                 << keranjang[i].ukuran << "\t"
                 << "Rp " << keranjang[i].hargaSatuan << "\t\t"
                 << keranjang[i].qty << "\t"
                 << "Rp " << keranjang[i].subtotal << endl;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << "TOTAL\t\t\t\t\t\t\tRp " << totalHarga << endl;
        cout << "============================================================" << endl;
    }

    void hitungTotal() {
        totalHarga = 0;
        for (int i = 0; i < jumlahItem; i++) {
            totalHarga += keranjang[i].subtotal;
        }
    }

    void cetakStruk() {
        cout << endl;
        cout << "============================================" << endl;
        cout << "           JEGGER T-SHIRT                  " << endl;
        cout << "    Jl. Malioboro No.77, Yogyakarta        " << endl;
        cout << "  HP: 0013-2006-7888 / 0012-2720-9026     " << endl;
        cout << "============================================" << endl;
        cout << "Tanggal  : " << tanggal     << endl;
        cout << "No. Struk: " << noStruk     << endl;
        cout << "Kasir    : " << kasir       << endl;
        cout << "Pembeli  : " << namaPembeli << endl;
        cout << "Verifikasi: " << (sudahDiverifikasi ? "Terverifikasi" : "Menunggu") << endl;
        cout << "Pengemasan: " << statusPengemasan << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Qty\tNama Barang\t\tHarga\t\tJumlah" << endl;
        cout << "--------------------------------------------" << endl;
        for (int i = 0; i < jumlahItem; i++) {
            cout << keranjang[i].qty << "\t"
                 << keranjang[i].namaProduk
                 << " " << keranjang[i].ukuran << "\t\t"
                 << keranjang[i].hargaSatuan << "\t\t"
                 << keranjang[i].subtotal << endl;
        }
        cout << "--------------------------------------------" << endl;
        cout << "\t\t\tTOTAL     : Rp " << totalHarga  << endl;
        cout << "\t\t\tBAYAR     : Rp " << bayar       << endl;
        cout << "\t\t\tKEMBALIAN : Rp " << kembalian   << endl;
        cout << "============================================" << endl;
        cout << "  Barang yang sudah dibeli tidak dapat     " << endl;
        cout << "  ditukar/dikembalikan tanpa perjanjian    " << endl;
        cout << "          terlebih dahulu.                 " << endl;
        cout << "============================================" << endl;
        cout << "       Terima kasih sudah berbelanja!      " << endl;
        cout << "============================================" << endl;
        cout << endl;
    }

    void reset() {
        noStruk     = "";
        namaPembeli = "";
        jumlahItem  = 0;
        totalHarga  = 0;
        bayar       = 0;
        kembalian   = 0;
        sudahDiverifikasi = false;
        statusPengemasan = "Belum Dikemas";
        for (int i = 0; i < MAX_ITEM; i++) {
            keranjang[i].idProduk    = "";
            keranjang[i].namaProduk  = "";
            keranjang[i].ukuran      = "";
            keranjang[i].hargaSatuan = 0;
            keranjang[i].qty         = 0;
            keranjang[i].subtotal    = 0;
        }
    }
};

// =====================================================
// ARRAY GLOBAL TRANSAKSI
// =====================================================


extern User daftarUser[MAX_USER];
extern int jumlahUser;
extern Produk daftarProduk[MAX_PRODUK];
extern int jumlahProduk;
extern Transaksi riwayatTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;
class FileManager {
public:
    FileManager();
    void simpanUser();
    void bacaUser();
    void simpanProduk();
    void bacaProduk();
    void simpanTransaksi();
    void bacaTransaksi();
    void simpanSemua();
    void bacaSemua();
};
extern FileManager fm;

void tambahUser(string u, string p, string r);
void hapusUser(string u);
int loginUser(string u, string p);
void tampilSemuaUser();
void tambahProduk(string id, string nama, string ukuran, int harga, int stok, string bahan);
int cariProdukById(string id);
int cariProdukByNama(string nama);
void cariProdukByUkuran(string ukuran);
void cariProdukByBahan(string bahan);
void hapusProduk(string id);
void tampilSemuaProduk();
void editProduk(string id);
void updateStatusPengemasan(string id, string status);
void tampilProdukByStatus(string status);
void simpanRiwayat(Transaksi trx);
void tampilRiwayatTransaksi();
void tampilDetailTransaksi(string noStruk);
void tampilTransaksiByPengemasan(string status);

#endif
