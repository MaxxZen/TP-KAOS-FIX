#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

// FORWARD DECLARATIONS

void statistikProduk();
void statistikTransaksi();
void menuTambahStok();
void backupData();
void menuAdminLengkap(int indexUser);
void tampilInfoSistem();
void cariTransaksiByKasir(string kasir);
void cariTransaksiByPembeli(string pembeli);
void menuCariTransaksi();
void resetSemuaTransaksi();
void tampilProdukStokHabis();
void menuKelolaStok();
void menuSistem();
void menuKasirLengkap(int indexUser);
void menuAdminFinal(int indexUser);
void menuAdminLengkapFinal(int indexUser);
void menuLaporanFinal();
void tampilDashboard();
void menuAnalisisLanjutan();
void tampilBantuan();
void menuPembelian();
void menuSupplier();
void menuRestock();
void menuRetur();
void menuFeedback();
void menuProfilToko();
void menuRiwayatHarga();
void tampilRingkasanSesi(string username);
bool tambahFeedback(string nama, string isi, int rating, string tanggal);
void simpanFeedback();
void bacaFeedback();
void bacaSupplier();
void bacaRestock();
void bacaRetur();
void simpanSupplier();
void simpanRestock();
void simpanRetur();
void inisialisasiProdukContoh();
void cekDanUpdateStatusOtomatis();
void cekNotifikasiAdmin();
void menuLabel();
void tampilLogAktivitas();
void catatLog(string username, string waktu, string aksi);
void menuEksporLaporan();
void laporanKinerjaSemuaKasir();
void tampilDaftarTanggalTransaksi();
void tabelProdukDetail();
void tabelTransaksiDetail();
void menuSearchLanjutan();
void menuSortLanjutan();
void garisTebal();
void garisTipis();
void menuKelolaStok();
bool prosesRetur(string noStruk, string idProduk, int qty, string alasan, string tanggal);
void tampilDaftarRetur();
bool tambahSupplier(string nama, string kontak, string alamat);
void tampilSemuaSupplier();
int cariSupplierByNama(string nama);
void hapusSupplier(string nama);
bool tambahRestock(string supplier, string idProduk, int jumlah, string tanggal);
void tampilRiwayatRestock();
void tampilSemuaFeedback();
void tampilRataRataRating();
void tampilProfilToko();
void editProfilToko();
void tampilRiwayatHarga();
void menuCetakLabel();
void cetakLabelSemuaProduk();
void cetakLabelHarga(string id);
void hitungTotalAset();
void tampilInfoDiskon(int total);
int hitungDiskon(int total);
void searchProdukRangeHarga(int hargaMin, int hargaMax);
void searchProdukByBahan(string bahan);
void selectionSortProdukByStok();
void insertionSortProdukByHarga();
void sortTransaksiByTotal();
void eksporLaporanHarianKeFile(string tanggal);
void eksporLaporanProdukKeFile();
void eksporLaporanOmzetKeFile();
void tampilDaftarTanggalTransaksi();
void tampilSplashScreen();

// CLASS USER

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

    string getUsername() {
        return username;
    }

    string getPassword() {
        return password;
    }

    string getRole() {
        return role;
    }

    void setUsername(string u) {
        username = u;
    }

    void setPassword(string p) {
        password = p;
    }

    void setRole(string r) {
        role = r;
    }

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

const int MAX_USER = 10;
User daftarUser[MAX_USER];
int jumlahUser = 0;

void tambahUser(string u, string p, string r) {
    if (jumlahUser >= MAX_USER) {
        cout << "[!] Data user penuh!" << endl;
        return;
    }
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].getUsername() == u) {
            cout << "[!] Username sudah digunakan!" << endl;
            return;
        }
    }
    daftarUser[jumlahUser] = User(u, p, r);
    jumlahUser++;
}

void hapusUser(string u) {
    int index = -1;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].getUsername() == u) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "[!] User tidak ditemukan!" << endl;
        return;
    }
    for (int i = index; i < jumlahUser - 1; i++) {
        daftarUser[i] = daftarUser[i + 1];
    }
    jumlahUser--;
    cout << "[?] User berhasil dihapus!" << endl;
}

int loginUser(string u, string p) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].login(u, p)) {
            return i;
        }
    }
    return -1;
}

void tampilSemuaUser() {
    if (jumlahUser == 0) {
        cout << "[!] Belum ada data user!" << endl;
        return;
    }
    cout << "======================================" << endl;
    cout << "           DAFTAR USER                " << endl;
    cout << "======================================" << endl;
    cout << "No\tUsername\tRole" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < jumlahUser; i++) {
        cout << i + 1 << "\t"
             << daftarUser[i].getUsername() << "\t\t"
             << daftarUser[i].getRole() << endl;
    }
    cout << "======================================" << endl;
}

// CLASS PRODUK

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

    string getIdProduk() {
        return idProduk;
    }

    string getNama() {
        return namaProduk;
    }

    string getUkuran() {
        return ukuran;
    }

    int getHarga() {
        return harga;
    }

    int getStok() {
        return stok;
    }

    string getBahan() {
        return bahan;
    }

    string getStatus() {
        return status;
    }

    void setNama(string n) {
        namaProduk = n;
    }

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

    void setBahan(string b) {
        bahan = b;
    }

    void setUkuran(string u) {
        ukuran = u;
    }

    void setStatus(string st) {
        status = st;
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
        if (stok <= 5) {
            return true;
        }
        return false;
    }

    bool cekStokHabis() {
        if (stok == 0) {
            return true;
        }
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

const int MAX_PRODUK = 100;
Produk daftarProduk[MAX_PRODUK];
int jumlahProduk = 0;

void tambahProduk(string id, string nama, string ukuran,
                  int harga, int stok, string bahan) {
    if (jumlahProduk >= MAX_PRODUK) {
        cout << "[!] Data produk penuh!" << endl;
        return;
    }
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getIdProduk() == id) {
            cout << "[!] ID produk sudah ada!" << endl;
            return;
        }
    }
    if (harga < 0) {
        cout << "[!] Harga tidak boleh negatif!" << endl;
        return;
    }
    if (stok < 0) {
        cout << "[!] Stok tidak boleh negatif!" << endl;
        return;
    }
    daftarProduk[jumlahProduk] = Produk(id, nama, ukuran, harga, stok, bahan);
    jumlahProduk++;
    cout << "[?] Produk berhasil ditambahkan!" << endl;
}

int cariProdukById(string id) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getIdProduk() == id) {
            return i;
        }
    }
    return -1;
}

int cariProdukByNama(string nama) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getNama() == nama) {
            return i;
        }
    }
    return -1;
}

void cariProdukByUkuran(string ukuran) {
    bool ditemukan = false;
    cout << "======================================" << endl;
    cout << "  PRODUK UKURAN : " << ukuran          << endl;
    cout << "======================================" << endl;
    cout << "No\tID\tNama\t\tHarga\t\tStok" << endl;
    cout << "--------------------------------------" << endl;
    int no = 1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getUkuran() == ukuran) {
            cout << no << "\t"
                 << daftarProduk[i].getIdProduk() << "\t"
                 << daftarProduk[i].getNama() << "\t\t"
                 << "Rp " << daftarProduk[i].getHarga() << "\t\t"
                 << daftarProduk[i].getStok() << endl;
            no++;
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "[!] Tidak ada produk dengan ukuran " << ukuran << endl;
    }
    cout << "======================================" << endl;
}

void hapusProduk(string id) {
    int index = cariProdukById(id);
    if (index == -1) {
        cout << "[!] Produk tidak ditemukan!" << endl;
        return;
    }
    for (int i = index; i < jumlahProduk - 1; i++) {
        daftarProduk[i] = daftarProduk[i + 1];
    }
    jumlahProduk--;
    cout << "[?] Produk berhasil dihapus!" << endl;
}

void tampilSemuaProduk() {
    if (jumlahProduk == 0) {
        cout << "[!] Belum ada data produk!" << endl;
        return;
    }
    cout << "============================================================" << endl;
    cout << "                   DAFTAR PRODUK                           " << endl;
    cout << "============================================================" << endl;
    cout << "No\tID\tNama\t\tUkuran\tHarga\t\tStok\tStatus" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        daftarProduk[i].tampilBaris(i + 1);
        if (daftarProduk[i].cekStokMenipis()) {
            cout << "\t\t\t\t\t\t\t[!] STOK MENIPIS" << endl;
        }
    }
    cout << "============================================================" << endl;
    cout << "Total Produk: " << jumlahProduk << endl;
    cout << "============================================================" << endl;
}

void sortProdukByHarga() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (daftarProduk[j].getHarga() > daftarProduk[j + 1].getHarga()) {
                Produk temp = daftarProduk[j];
                daftarProduk[j] = daftarProduk[j + 1];
                daftarProduk[j + 1] = temp;
            }
        }
    }
    cout << "[?] Produk diurutkan berdasarkan harga!" << endl;
}

void sortProdukByNama() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (daftarProduk[j].getNama() > daftarProduk[j + 1].getNama()) {
                Produk temp = daftarProduk[j];
                daftarProduk[j] = daftarProduk[j + 1];
                daftarProduk[j + 1] = temp;
            }
        }
    }
    cout << "[?] Produk diurutkan berdasarkan nama!" << endl;
}

void sortProdukByStok() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (daftarProduk[j].getStok() > daftarProduk[j + 1].getStok()) {
                Produk temp = daftarProduk[j];
                daftarProduk[j] = daftarProduk[j + 1];
                daftarProduk[j + 1] = temp;
            }
        }
    }
    cout << "[?] Produk diurutkan berdasarkan stok!" << endl;
}

void tampilStokMenipis() {
    bool ada = false;
    cout << "======================================" << endl;
    cout << "       PRODUK STOK MENIPIS            " << endl;
    cout << "======================================" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].cekStokMenipis()) {
            cout << "ID     : " << daftarProduk[i].getIdProduk() << endl;
            cout << "Nama   : " << daftarProduk[i].getNama() << endl;
            cout << "Ukuran : " << daftarProduk[i].getUkuran() << endl;
            cout << "Stok   : " << daftarProduk[i].getStok() << endl;
            cout << "--------------------------------------" << endl;
            ada = true;
        }
    }
    if (!ada) {
        cout << "[?] Semua stok produk masih aman!" << endl;
    }
    cout << "======================================" << endl;
}

void editProduk(string id) {
    int index = cariProdukById(id);
    if (index == -1) {
        cout << "[!] Produk tidak ditemukan!" << endl;
        return;
    }
    int pilihan;
    cout << "======================================" << endl;
    cout << "         EDIT PRODUK                  " << endl;
    cout << "======================================" << endl;
    cout << "1. Edit Nama" << endl;
    cout << "2. Edit Harga" << endl;
    cout << "3. Edit Stok" << endl;
    cout << "4. Edit Bahan" << endl;
    cout << "5. Edit Ukuran" << endl;
    cout << "6. Edit Status" << endl;
    cout << "0. Batal" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        string nama;
        cout << "Nama baru: ";
        getline(cin, nama);
        if (nama == "") {
            cout << "[!] Nama tidak boleh kosong!" << endl;
            return;
        }
        daftarProduk[index].setNama(nama);
        cout << "[?] Nama berhasil diubah!" << endl;
    } else if (pilihan == 2) {
        int harga;
        cout << "Harga baru: ";
        cin >> harga;
        if (harga < 0) {
            cout << "[!] Harga tidak boleh negatif!" << endl;
            return;
        }
        daftarProduk[index].setHarga(harga);
        cout << "[?] Harga berhasil diubah!" << endl;
    } else if (pilihan == 3) {
        int stok;
        cout << "Stok baru: ";
        cin >> stok;
        if (stok < 0) {
            cout << "[!] Stok tidak boleh negatif!" << endl;
            return;
        }
        daftarProduk[index].setStok(stok);
        cout << "[?] Stok berhasil diubah!" << endl;
    } else if (pilihan == 4) {
        string bahan;
        cin.ignore();
        cout << "Bahan baru: ";
        getline(cin, bahan);
        if (bahan == "") {
            cout << "[!] Bahan tidak boleh kosong!" << endl;
            return;
        }
        daftarProduk[index].setBahan(bahan);
        cout << "[?] Bahan berhasil diubah!" << endl;
    } else if (pilihan == 5) {
        string ukuran;
        cout << "Ukuran baru (S/M/L/XL/XXL): ";
        cin >> ukuran;
        if (ukuran != "S" && ukuran != "M" && ukuran != "L" &&
            ukuran != "XL" && ukuran != "XXL") {
            cout << "[!] Ukuran tidak valid!" << endl;
            return;
        }
        daftarProduk[index].setUkuran(ukuran);
        cout << "[?] Ukuran berhasil diubah!" << endl;
    } else if (pilihan == 6) {
        string status;
        cout << "Status (Belum Dikemas/Sedang Dikemas/Sudah Dikemas): ";
        cin.ignore();
        getline(cin, status);
        if (status != "Belum Dikemas" &&
            status != "Sedang Dikemas" &&
            status != "Sudah Dikemas") {
            cout << "[!] Status tidak valid!" << endl;
            return;
        }
        daftarProduk[index].setStatus(status);
        cout << "[?] Status berhasil diubah!" << endl;
    } else if (pilihan == 0) {
        cout << "Edit dibatalkan." << endl;
    } else {
        cout << "[!] Pilihan tidak valid!" << endl;
    }
}

void updateStatusPengemasan(string id, string status) {
    int index = cariProdukById(id);
    if (index == -1) {
        cout << "[!] Produk tidak ditemukan!" << endl;
        return;
    }
    if (status != "Belum Dikemas" &&
        status != "Sedang Dikemas" &&
        status != "Sudah Dikemas") {
        cout << "[!] Status tidak valid!" << endl;
        return;
    }
    daftarProduk[index].setStatus(status);
    cout << "[?] Status pengemasan berhasil diupdate!" << endl;
}

void tampilProdukByStatus(string status) {
    bool ada = false;
    cout << "============================================================" << endl;
    cout << "  STATUS : " << status << endl;
    cout << "============================================================" << endl;
    cout << "No\tID\tNama\t\tUkuran\tStok" << endl;
    cout << "------------------------------------------------------------" << endl;
    int no = 1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getStatus() == status) {
            cout << no << "\t"
                 << daftarProduk[i].getIdProduk() << "\t"
                 << daftarProduk[i].getNama() << "\t\t"
                 << daftarProduk[i].getUkuran() << "\t"
                 << daftarProduk[i].getStok() << endl;
            no++;
            ada = true;
        }
    }
    if (!ada) {
        cout << "[!] Tidak ada produk dengan status " << status << endl;
    }
    cout << "============================================================" << endl;
}

// CLASS TRANSAKSI

struct ItemBelanja {
    string idProduk;
    string namaProduk;
    string ukuran;
    int    hargaSatuan;
    int    qty;
    int    subtotal;
};

const int MAX_ITEM      = 20;
const int MAX_TRANSAKSI = 200;

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
    }

    void setNamaPembeli(string nama) {
        namaPembeli = nama;
    }

    void setKasir(string k) {
        kasir = k;
    }

    void setTanggal(string tgl) {
        tanggal = tgl;
    }

    void setNoStruk(string no) {
        noStruk = no;
    }

    void setBayar(int b) {
        bayar     = b;
        kembalian = b - totalHarga;
    }

    string getNoStruk() {
        return noStruk;
    }

    string getNamaPembeli() {
        return namaPembeli;
    }

    string getKasir() {
        return kasir;
    }

    string getTanggal() {
        return tanggal;
    }

    int getTotalHarga() {
        return totalHarga;
    }

    int getBayar() {
        return bayar;
    }

    int getKembalian() {
        return kembalian;
    }

    int getJumlahItem() {
        return jumlahItem;
    }

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
        keranjang[jumlahItem].idProduk   = idProduk;
        keranjang[jumlahItem].namaProduk = nama;
        keranjang[jumlahItem].ukuran     = ukuran;
        keranjang[jumlahItem].hargaSatuan = harga;
        keranjang[jumlahItem].qty        = qty;
        keranjang[jumlahItem].subtotal   = harga * qty;
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

Transaksi riwayatTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

void simpanRiwayat(Transaksi trx) {
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        cout << "[!] Riwayat transaksi penuh!" << endl;
        return;
    }
    riwayatTransaksi[jumlahTransaksi] = trx;
    jumlahTransaksi++;
}

void tampilRiwayatTransaksi() {
    if (jumlahTransaksi == 0) {
        cout << "[!] Belum ada riwayat transaksi!" << endl;
        return;
    }
    cout << "============================================================" << endl;
    cout << "               RIWAYAT TRANSAKSI                           " << endl;
    cout << "============================================================" << endl;
    cout << "No\tNo Struk\tTanggal\t\tKasir\t\tTotal" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahTransaksi; i++) {
        cout << i + 1 << "\t"
             << riwayatTransaksi[i].getNoStruk() << "\t"
             << riwayatTransaksi[i].getTanggal() << "\t"
             << riwayatTransaksi[i].getKasir() << "\t\t"
             << "Rp " << riwayatTransaksi[i].getTotalHarga() << endl;
    }
    cout << "============================================================" << endl;
    cout << "Total Transaksi: " << jumlahTransaksi << endl;
    cout << "============================================================" << endl;
}

void tampilDetailTransaksi(string noStruk) {
    bool ditemukan = false;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (riwayatTransaksi[i].getNoStruk() == noStruk) {
            riwayatTransaksi[i].cetakStruk();
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "[!] Transaksi tidak ditemukan!" << endl;
    }
}

// CLASS LAPORAN

class Laporan {
public:
    Laporan() {}

    void laporanStokMenipis() {
        bool ada = false;
        cout << "============================================================" << endl;
        cout << "              LAPORAN STOK MENIPIS                         " << endl;
        cout << "============================================================" << endl;
        cout << "No\tID\tNama\t\tUkuran\tStok" << endl;
        cout << "------------------------------------------------------------" << endl;
        int no = 1;
        for (int i = 0; i < jumlahProduk; i++) {
            if (daftarProduk[i].cekStokMenipis()) {
                cout << no << "\t"
                     << daftarProduk[i].getIdProduk() << "\t"
                     << daftarProduk[i].getNama() << "\t\t"
                     << daftarProduk[i].getUkuran() << "\t"
                     << daftarProduk[i].getStok() << endl;
                no++;
                ada = true;
            }
        }
        if (!ada) {
            cout << "[?] Tidak ada produk dengan stok menipis!" << endl;
        }
        cout << "============================================================" << endl;
    }

    void laporanProdukTerlaris() {
        if (jumlahTransaksi == 0) {
            cout << "[!] Belum ada transaksi!" << endl;
            return;
        }
        string namaProduk[MAX_PRODUK];
        int    terjual[MAX_PRODUK];
        int    jumlahData = 0;

        for (int i = 0; i < jumlahTransaksi; i++) {
            for (int j = 0; j < riwayatTransaksi[i].getJumlahItem(); j++) {
                ItemBelanja item = riwayatTransaksi[i].getItem(j);
                bool sudahAda = false;
                for (int k = 0; k < jumlahData; k++) {
                    if (namaProduk[k] == item.namaProduk) {
                        terjual[k] += item.qty;
                        sudahAda = true;
                        break;
                    }
                }
                if (!sudahAda) {
                    namaProduk[jumlahData] = item.namaProduk;
                    terjual[jumlahData]    = item.qty;
                    jumlahData++;
                }
            }
        }

        for (int i = 0; i < jumlahData - 1; i++) {
            for (int j = 0; j < jumlahData - i - 1; j++) {
                if (terjual[j] < terjual[j + 1]) {
                    int    tmpTerjual = terjual[j];
                    string tmpNama    = namaProduk[j];
                    terjual[j]    = terjual[j + 1];
                    namaProduk[j] = namaProduk[j + 1];
                    terjual[j + 1]    = tmpTerjual;
                    namaProduk[j + 1] = tmpNama;
                }
            }
        }

        cout << "============================================================" << endl;
        cout << "              LAPORAN PRODUK TERLARIS                      " << endl;
        cout << "============================================================" << endl;
        cout << "No\tNama Produk\t\tTotal Terjual" << endl;
        cout << "------------------------------------------------------------" << endl;
        for (int i = 0; i < jumlahData; i++) {
            cout << i + 1 << "\t"
                 << namaProduk[i] << "\t\t"
                 << terjual[i] << " pcs" << endl;
        }
        cout << "============================================================" << endl;
    }

    void laporanHarian(string tanggal) {
        int    totalPenjualan = 0;
        int    jumlahTrx      = 0;
        bool   ada            = false;

        cout << "============================================================" << endl;
        cout << "           LAPORAN HARIAN - " << tanggal                      << endl;
        cout << "============================================================" << endl;
        cout << "No\tNo Struk\tKasir\t\tTotal" << endl;
        cout << "------------------------------------------------------------" << endl;

        int no = 1;
        for (int i = 0; i < jumlahTransaksi; i++) {
            if (riwayatTransaksi[i].getTanggal() == tanggal) {
                cout << no << "\t"
                     << riwayatTransaksi[i].getNoStruk() << "\t"
                     << riwayatTransaksi[i].getKasir() << "\t\t"
                     << "Rp " << riwayatTransaksi[i].getTotalHarga() << endl;
                totalPenjualan += riwayatTransaksi[i].getTotalHarga();
                jumlahTrx++;
                no++;
                ada = true;
            }
        }

        if (!ada) {
            cout << "[!] Tidak ada transaksi pada tanggal " << tanggal << endl;
        }

        cout << "------------------------------------------------------------" << endl;
        cout << "Total Transaksi : " << jumlahTrx << endl;
        cout << "Total Penjualan : Rp " << totalPenjualan << endl;
        cout << "============================================================" << endl;
    }

    void laporanOmzetTotal() {
        int totalOmzet   = 0;
        int totalTrx     = jumlahTransaksi;

        for (int i = 0; i < jumlahTransaksi; i++) {
            totalOmzet += riwayatTransaksi[i].getTotalHarga();
        }

        cout << "============================================================" << endl;
        cout << "              LAPORAN OMZET TOTAL                          " << endl;
        cout << "============================================================" << endl;
        cout << "Total Transaksi : " << totalTrx << endl;
        cout << "Total Omzet     : Rp " << totalOmzet << endl;
        cout << "Rata-rata/Trx   : Rp ";
        if (totalTrx > 0) {
            cout << totalOmzet / totalTrx << endl;
        } else {
            cout << 0 << endl;
        }
        cout << "============================================================" << endl;
    }

    void laporanRekapUkuran() {
        int stokS   = 0;
        int stokM   = 0;
        int stokL   = 0;
        int stokXL  = 0;
        int stokXXL = 0;

        for (int i = 0; i < jumlahProduk; i++) {
            if (daftarProduk[i].getUkuran() == "S") {
                stokS += daftarProduk[i].getStok();
            } else if (daftarProduk[i].getUkuran() == "M") {
                stokM += daftarProduk[i].getStok();
            } else if (daftarProduk[i].getUkuran() == "L") {
                stokL += daftarProduk[i].getStok();
            } else if (daftarProduk[i].getUkuran() == "XL") {
                stokXL += daftarProduk[i].getStok();
            } else if (daftarProduk[i].getUkuran() == "XXL") {
                stokXXL += daftarProduk[i].getStok();
            }
        }

        cout << "============================================================" << endl;
        cout << "           LAPORAN REKAP STOK PER UKURAN                   " << endl;
        cout << "============================================================" << endl;
        cout << "Ukuran\t\tJumlah Stok" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "S\t\t" << stokS   << " pcs" << endl;
        cout << "M\t\t" << stokM   << " pcs" << endl;
        cout << "L\t\t" << stokL   << " pcs" << endl;
        cout << "XL\t\t" << stokXL  << " pcs" << endl;
        cout << "XXL\t\t" << stokXXL << " pcs" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Total\t\t" << stokS + stokM + stokL + stokXL + stokXXL
             << " pcs" << endl;
        cout << "============================================================" << endl;
    }

    void laporanLabaRugi() {
        int totalPenjualan = 0;
        for (int i = 0; i < jumlahTransaksi; i++) {
            totalPenjualan += riwayatTransaksi[i].getTotalHarga();
        }

        cout << "============================================================" << endl;
        cout << "              LAPORAN LABA RUGI                            " << endl;
        cout << "============================================================" << endl;
        cout << "Total Penjualan : Rp " << totalPenjualan << endl;
        cout << "============================================================" << endl;
        cout << "Catatan: Laporan laba rugi lengkap membutuhkan" << endl;
        cout << "         data harga modal produk." << endl;
        cout << "============================================================" << endl;
    }

    void laporanPengemasan() {
        int belumDikemas   = 0;
        int sedangDikemas  = 0;
        int sudahDikemas   = 0;

        for (int i = 0; i < jumlahProduk; i++) {
            if (daftarProduk[i].getStatus() == "Belum Dikemas") {
                belumDikemas++;
            } else if (daftarProduk[i].getStatus() == "Sedang Dikemas") {
                sedangDikemas++;
            } else if (daftarProduk[i].getStatus() == "Sudah Dikemas") {
                sudahDikemas++;
            }
        }

        cout << "============================================================" << endl;
        cout << "              LAPORAN STATUS PENGEMASAN                    " << endl;
        cout << "============================================================" << endl;
        cout << "Belum Dikemas   : " << belumDikemas  << " produk" << endl;
        cout << "Sedang Dikemas  : " << sedangDikemas << " produk" << endl;
        cout << "Sudah Dikemas   : " << sudahDikemas  << " produk" << endl;
        cout << "============================================================" << endl;
    }
};

// CLASS FILEMANAGER

class FileManager {
public:
    FileManager() {}

    void simpanUser() {
        ofstream file("data_user.txt");
        if (!file.is_open()) {
            cout << "[!] Gagal menyimpan data user!" << endl;
            return;
        }
        for (int i = 0; i < jumlahUser; i++) {
            file << daftarUser[i].getUsername() << "|"
                 << daftarUser[i].getPassword() << "|"
                 << daftarUser[i].getRole() << "\n";
        }
        file.close();
    }

    void bacaUser() {
        ifstream file("data_user.txt");
        if (!file.is_open()) {
            return;
        }
        jumlahUser = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string u = "", p = "", r = "";
            int fase = 0;
            for (int i = 0; i < baris.length(); i++) {
                if (baris[i] == '|') {
                    fase++;
                } else if (fase == 0) {
                    u += baris[i];
                } else if (fase == 1) {
                    p += baris[i];
                } else if (fase == 2) {
                    r += baris[i];
                }
            }
            if (jumlahUser < MAX_USER) {
                daftarUser[jumlahUser] = User(u, p, r);
                jumlahUser++;
            }
        }
        file.close();
    }

    void simpanProduk() {
        ofstream file("data_produk.txt");
        if (!file.is_open()) {
            cout << "[!] Gagal menyimpan data produk!" << endl;
            return;
        }
        for (int i = 0; i < jumlahProduk; i++) {
            file << daftarProduk[i].getIdProduk()  << "|"
                 << daftarProduk[i].getNama()       << "|"
                 << daftarProduk[i].getUkuran()     << "|"
                 << daftarProduk[i].getHarga()      << "|"
                 << daftarProduk[i].getStok()       << "|"
                 << daftarProduk[i].getBahan()      << "|"
                 << daftarProduk[i].getStatus()     << "\n";
        }
        file.close();
    }

    void bacaProduk() {
        ifstream file("data_produk.txt");
        if (!file.is_open()) {
            return;
        }
        jumlahProduk = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string id = "", nama = "", ukuran = "",
                   bahan = "", status = "";
            int harga = 0, stok = 0;
            int fase = 0;
            string token = "";

            for (int i = 0; i <= baris.length(); i++) {
                if (i == baris.length() || baris[i] == '|') {
                    if (fase == 0) id     = token;
                    else if (fase == 1) nama   = token;
                    else if (fase == 2) ukuran = token;
                    else if (fase == 3) harga  = stoi(token);
                    else if (fase == 4) stok   = stoi(token);
                    else if (fase == 5) bahan  = token;
                    else if (fase == 6) status = token;
                    token = "";
                    fase++;
                } else {
                    token += baris[i];
                }
            }

            if (jumlahProduk < MAX_PRODUK) {
                daftarProduk[jumlahProduk] = Produk(id, nama, ukuran,
                                                     harga, stok, bahan);
                daftarProduk[jumlahProduk].setStatus(status);
                jumlahProduk++;
            }
        }
        file.close();
    }

    void simpanTransaksi() {
        ofstream file("data_transaksi.txt");
        if (!file.is_open()) {
            cout << "[!] Gagal menyimpan data transaksi!" << endl;
            return;
        }
        for (int i = 0; i < jumlahTransaksi; i++) {
            file << riwayatTransaksi[i].getNoStruk()    << "|"
                 << riwayatTransaksi[i].getTanggal()    << "|"
                 << riwayatTransaksi[i].getKasir()      << "|"
                 << riwayatTransaksi[i].getNamaPembeli()<< "|"
                 << riwayatTransaksi[i].getTotalHarga() << "|"
                 << riwayatTransaksi[i].getBayar()      << "|"
                 << riwayatTransaksi[i].getKembalian()  << "|"
                 << riwayatTransaksi[i].getJumlahItem() << "\n";
            for (int j = 0; j < riwayatTransaksi[i].getJumlahItem(); j++) {
                ItemBelanja item = riwayatTransaksi[i].getItem(j);
                file << item.idProduk    << "|"
                     << item.namaProduk  << "|"
                     << item.ukuran      << "|"
                     << item.hargaSatuan << "|"
                     << item.qty         << "|"
                     << item.subtotal    << "\n";
            }
        }
        file.close();
    }

    void bacaTransaksi() {
        ifstream file("data_transaksi.txt");
        if (!file.is_open()) {
            return;
        }
        jumlahTransaksi = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string token = "";
            int fase = 0;
            string noStruk = "", tanggal = "", kasir = "",
                   pembeli = "";
            int total = 0, bayar = 0, kembalian = 0, jmlItem = 0;

            for (int i = 0; i <= baris.length(); i++) {
                if (i == baris.length() || baris[i] == '|') {
                    if (fase == 0) noStruk  = token;
                    else if (fase == 1) tanggal  = token;
                    else if (fase == 2) kasir     = token;
                    else if (fase == 3) pembeli   = token;
                    else if (fase == 4) total     = stoi(token);
                    else if (fase == 5) bayar     = stoi(token);
                    else if (fase == 6) kembalian = stoi(token);
                    else if (fase == 7) jmlItem   = stoi(token);
                    token = "";
                    fase++;
                } else {
                    token += baris[i];
                }
            }

            if (jumlahTransaksi < MAX_TRANSAKSI) {
                Transaksi trx(kasir, tanggal, noStruk);
                trx.setNamaPembeli(pembeli);
                trx.setBayar(bayar);

                for (int j = 0; j < jmlItem; j++) {
                    string barisItem;
                    if (!getline(file, barisItem)) break;
                    string idP = "", namaP = "", ukuranP = "";
                    int hargaP = 0, qtyP = 0, subP = 0;
                    string tokenItem = "";
                    int faseItem = 0;

                    for (int k = 0; k <= barisItem.length(); k++) {
                        if (k == barisItem.length() || barisItem[k] == '|') {
                            if (faseItem == 0) idP    = tokenItem;
                            else if (faseItem == 1) namaP  = tokenItem;
                            else if (faseItem == 2) ukuranP = tokenItem;
                            else if (faseItem == 3) hargaP = stoi(tokenItem);
                            else if (faseItem == 4) qtyP   = stoi(tokenItem);
                            else if (faseItem == 5) subP   = stoi(tokenItem);
                            tokenItem = "";
                            faseItem++;
                        } else {
                            tokenItem += barisItem[k];
                        }
                    }
                    trx.tambahItem(idP, namaP, ukuranP, hargaP, qtyP);
                }
                riwayatTransaksi[jumlahTransaksi] = trx;
                jumlahTransaksi++;
            }
        }
        file.close();
    }

    void simpanSemua() {
        simpanUser();
        simpanProduk();
        simpanTransaksi();
        cout << "[?] Semua data berhasil disimpan!" << endl;
    }

    void bacaSemua() {
        bacaUser();
        bacaProduk();
        bacaTransaksi();
    }
};

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
                    simpanRiwayat(trx);
                    fm.simpanTransaksi();
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
        cout << "            SISTEM TOKO KAOS JEGGER T-SHIRT               " << endl;
        cout << "         Jl. Malioboro No.77, Yogyakarta                   " << endl;
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

// FUNGSI TAMBAHAN STATISTIK & ANALISIS

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

    cout << "[?] Backup data berhasil!" << endl;
}

// MENU ADMIN TAMBAHAN

void menuAdminLengkap(int indexUser) {
    int pilihan;
    do {
        headerMenu("MENU ADMIN LENGKAP");
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

// PENCARIAN TRANSAKSI BY KASIR

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

// PENCARIAN TRANSAKSI DARI PEMBELI

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
        cout << "[?] Semua data valid!" << endl;
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
    cout << "[?] Semua riwayat transaksi berhasil dihapus!" << endl;
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
        cout << "[?] Tidak ada produk dengan stok habis!" << endl;
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
