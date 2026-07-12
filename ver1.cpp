#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

const int MAX_USER      = 10;
const int MAX_PRODUK    = 100;
const int MAX_ITEM      = 20;
const int MAX_TRANSAKSI = 200;
const int MAX_ANTRIAN   = 50;
const int MAX_BULAN     = 12;
const int MAX_UKURAN    = 5;

// =====================================================
// CLASS USER
// =====================================================

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

// =====================================================
// CLASS PRODUK
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

void cariProdukByBahan(string bahan) {
    bool ditemukan = false;
    cout << "============================================================" << endl;
    cout << "  PRODUK DENGAN BAHAN : " << bahan << endl;
    cout << "============================================================" << endl;
    cout << "No\tID\tNama\t\tUkuran\tHarga\t\tStok" << endl;
    cout << "------------------------------------------------------------" << endl;
    int no = 1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getBahan() == bahan) {
            cout << no << "\t"
                 << daftarProduk[i].getIdProduk() << "\t"
                 << daftarProduk[i].getNama() << "\t\t"
                 << daftarProduk[i].getUkuran() << "\t"
                 << "Rp " << daftarProduk[i].getHarga() << "\t\t"
                 << daftarProduk[i].getStok() << endl;
            no++;
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "[!] Tidak ada produk dengan bahan " << bahan << endl;
    }
    cout << "============================================================" << endl;
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

// =====================================================
// SORTING PRODUK - BUBBLE SORT
// (Praktikum 3 & 7)
// =====================================================

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

// =====================================================
// SORTING PRODUK - SELECTION SORT
// (Praktikum 7 - Tambahan)
// =====================================================

void selectionSortProdukHargaDesc() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (daftarProduk[j].getHarga() > daftarProduk[maxIndex].getHarga()) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            Produk temp = daftarProduk[i];
            daftarProduk[i] = daftarProduk[maxIndex];
            daftarProduk[maxIndex] = temp;
        }
    }
    cout << "[?] Produk diurutkan harga tertinggi ke terendah (Selection Sort)!" << endl;
}

void selectionSortProdukByNama() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (daftarProduk[j].getNama() < daftarProduk[minIndex].getNama()) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Produk temp = daftarProduk[i];
            daftarProduk[i] = daftarProduk[minIndex];
            daftarProduk[minIndex] = temp;
        }
    }
    cout << "[?] Produk diurutkan nama A-Z (Selection Sort)!" << endl;
}

void selectionSortProdukByStokAsc() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < jumlahProduk; j++) {
            if (daftarProduk[j].getStok() < daftarProduk[minIndex].getStok()) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Produk temp = daftarProduk[i];
            daftarProduk[i] = daftarProduk[minIndex];
            daftarProduk[minIndex] = temp;
        }
    }
    cout << "[?] Produk diurutkan stok terkecil ke terbesar (Selection Sort)!" << endl;
}

// =====================================================
// SORTING PRODUK - INSERTION SORT
// (Praktikum 7 - Tambahan)
// =====================================================

void insertionSortProdukByNama() {
    for (int i = 1; i < jumlahProduk; i++) {
        Produk kunci = daftarProduk[i];
        int j = i - 1;
        while (j >= 0 && daftarProduk[j].getNama() > kunci.getNama()) {
            daftarProduk[j + 1] = daftarProduk[j];
            j--;
        }
        daftarProduk[j + 1] = kunci;
    }
    cout << "[?] Produk diurutkan berdasarkan nama A-Z (Insertion Sort)!" << endl;
}

void insertionSortProdukByStok() {
    for (int i = 1; i < jumlahProduk; i++) {
        Produk kunci = daftarProduk[i];
        int j = i - 1;
        while (j >= 0 && daftarProduk[j].getStok() > kunci.getStok()) {
            daftarProduk[j + 1] = daftarProduk[j];
            j--;
        }
        daftarProduk[j + 1] = kunci;
    }
    cout << "[?] Produk diurutkan berdasarkan stok terkecil (Insertion Sort)!" << endl;
}

void insertionSortProdukByHarga() {
    for (int i = 1; i < jumlahProduk; i++) {
        Produk kunci = daftarProduk[i];
        int j = i - 1;
        while (j >= 0 && daftarProduk[j].getHarga() > kunci.getHarga()) {
            daftarProduk[j + 1] = daftarProduk[j];
            j--;
        }
        daftarProduk[j + 1] = kunci;
    }
    cout << "[?] Produk diurutkan berdasarkan harga ascending (Insertion Sort)!" << endl;
}

// =====================================================
// CEK STOK
// =====================================================

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

// =====================================================
// EDIT & STATUS PENGEMASAN PRODUK
// =====================================================

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

// =====================================================
// STRUCT ITEM BELANJA
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

    void setNamaPembeli(string nama) { namaPembeli = nama; }
    void setKasir(string k)          { kasir = k; }
    void setTanggal(string tgl)      { tanggal = tgl; }
    void setNoStruk(string no)       { noStruk = no; }

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

// =====================================================
// ARRAY GLOBAL TRANSAKSI
// =====================================================

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

// =====================================================
// CLASS LAPORAN
// =====================================================

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

        // Bubble sort terlaris
        for (int i = 0; i < jumlahData - 1; i++) {
            for (int j = 0; j < jumlahData - i - 1; j++) {
                if (terjual[j] < terjual[j + 1]) {
                    int    tmpTerjual = terjual[j];
                    string tmpNama    = namaProduk[j];
                    terjual[j]        = terjual[j + 1];
                    namaProduk[j]     = namaProduk[j + 1];
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
        int  totalPenjualan = 0;
        int  jumlahTrx      = 0;
        bool ada            = false;

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
        int totalOmzet = 0;
        int totalTrx   = jumlahTransaksi;

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
        int belumDikemas  = 0;
        int sedangDikemas = 0;
        int sudahDikemas  = 0;

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

    // Laporan produk per rentang harga
    void laporanProdukRentangHarga(int hargaMin, int hargaMax) {
        bool ada = false;
        int total = 0;
        cout << "============================================================" << endl;
        cout << "  LAPORAN PRODUK RENTANG HARGA" << endl;
        cout << "  Rp " << hargaMin << " - Rp " << hargaMax << endl;
        cout << "============================================================" << endl;
        cout << "No\tID\tNama\t\tUkuran\tHarga\t\tStok" << endl;
        cout << "------------------------------------------------------------" << endl;
        int no = 1;
        for (int i = 0; i < jumlahProduk; i++) {
            if (daftarProduk[i].getHarga() >= hargaMin &&
                daftarProduk[i].getHarga() <= hargaMax) {
                cout << no << "\t"
                     << daftarProduk[i].getIdProduk() << "\t"
                     << daftarProduk[i].getNama() << "\t\t"
                     << daftarProduk[i].getUkuran() << "\t"
                     << "Rp " << daftarProduk[i].getHarga() << "\t\t"
                     << daftarProduk[i].getStok() << endl;
                total += daftarProduk[i].getStok();
                no++;
                ada = true;
            }
        }
        if (!ada) {
            cout << "[!] Tidak ada produk dalam rentang harga tersebut!" << endl;
        } else {
            cout << "------------------------------------------------------------" << endl;
            cout << "Total produk ditemukan : " << no - 1 << endl;
            cout << "Total stok keseluruhan : " << total << " pcs" << endl;
        }
        cout << "============================================================" << endl;
    }

    // Laporan nilai inventori (harga x stok)
    void laporanNilaiInventori() {
        long long totalNilai = 0;
        cout << "============================================================" << endl;
        cout << "           LAPORAN NILAI INVENTORI                         " << endl;
        cout << "============================================================" << endl;
        cout << "No\tNama\t\tHarga\t\tStok\tNilai" << endl;
        cout << "------------------------------------------------------------" << endl;
        for (int i = 0; i < jumlahProduk; i++) {
            long long nilaiProduk = (long long)daftarProduk[i].getHarga()
                                  * daftarProduk[i].getStok();
            cout << i + 1 << "\t"
                 << daftarProduk[i].getNama() << "\t\t"
                 << "Rp " << daftarProduk[i].getHarga() << "\t\t"
                 << daftarProduk[i].getStok() << "\t"
                 << "Rp " << nilaiProduk << endl;
            totalNilai += nilaiProduk;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << "TOTAL NILAI INVENTORI : Rp " << totalNilai << endl;
        cout << "============================================================" << endl;
    }
};

// =====================================================
// CLASS FILEMANAGER
// =====================================================

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
        if (!file.is_open()) return;
        jumlahUser = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string u = "", p = "", r = "";
            int fase = 0;
            for (int i = 0; i < (int)baris.length(); i++) {
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
        if (!file.is_open()) return;
        jumlahProduk = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string id = "", nama = "", ukuran = "",
                   bahan = "", status = "";
            int harga = 0, stok = 0;
            int fase = 0;
            string token = "";

            for (int i = 0; i <= (int)baris.length(); i++) {
                if (i == (int)baris.length() || baris[i] == '|') {
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
        if (!file.is_open()) return;
        jumlahTransaksi = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string token = "";
            int fase = 0;
            string noStruk = "", tanggal = "", kasir = "",
                   pembeli = "";
            int total = 0, bayar = 0, kembalian = 0, jmlItem = 0;

            for (int i = 0; i <= (int)baris.length(); i++) {
                if (i == (int)baris.length() || baris[i] == '|') {
                    if (fase == 0) noStruk   = token;
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

                    for (int k = 0; k <= (int)barisItem.length(); k++) {
                        if (k == (int)barisItem.length() || barisItem[k] == '|') {
                            if (faseItem == 0) idP     = tokenItem;
                            else if (faseItem == 1) namaP   = tokenItem;
                            else if (faseItem == 2) ukuranP = tokenItem;
                            else if (faseItem == 3) hargaP  = stoi(tokenItem);
                            else if (faseItem == 4) qtyP    = stoi(tokenItem);
                            else if (faseItem == 5) subP    = stoi(tokenItem);
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

// =====================================================
// FUNGSI HELPER & UTILITAS GLOBAL
// =====================================================

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

// =====================================================
// STATISTIK PRODUK & TRANSAKSI
// =====================================================

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

// =====================================================
// BACKUP & VALIDASI DATA
// =====================================================

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
                      << riwayatTransaksi[i].getTotalHarga() << "|"
                      << riwayatTransaksi[i].getBayar()      << "|"
                      << riwayatTransaksi[i].getKembalian()  << "\n";
        }
        backupTrx.close();
    }

    cout << "[?] Backup data berhasil!" << endl;
}

void cekValidasiSemuaData() {
    cout << "============================================================" << endl;
    cout << "              VALIDASI DATA SISTEM                         " << endl;
    cout << "============================================================" << endl;
    int masalah = 0;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].getHarga() <= 0) {
            cout << "[!] Produk " << daftarProduk[i].getIdProduk()
                 << " harga tidak valid!" << endl;
            masalah++;
        }
        if (daftarProduk[i].getIdProduk() == "") {
            cout << "[!] Produk index " << i << " ID kosong!" << endl;
            masalah++;
        }
        if (daftarProduk[i].getNama() == "") {
            cout << "[!] Produk " << daftarProduk[i].getIdProduk()
                 << " nama kosong!" << endl;
            masalah++;
        }
    }

    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].getUsername() == "") {
            cout << "[!] User index " << i << " username kosong!" << endl;
            masalah++;
        }
        if (daftarUser[i].getRole() != "admin" &&
            daftarUser[i].getRole() != "kasir") {
            cout << "[!] User " << daftarUser[i].getUsername()
                 << " role tidak valid!" << endl;
            masalah++;
        }
    }

    if (masalah == 0) {
        cout << "[?] Semua data valid! Tidak ada masalah ditemukan." << endl;
    } else {
        cout << "Total masalah ditemukan: " << masalah << endl;
    }
    cout << "============================================================" << endl;
}

void resetSemuaTransaksi() {
    if (jumlahTransaksi == 0) {
        cout << "[!] Tidak ada transaksi untuk direset!" << endl;
        return;
    }
    if (!konfirmasi("Apakah Anda yakin ingin menghapus SEMUA riwayat transaksi?")) {
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

// =====================================================
// INFO SISTEM
// =====================================================

void tampilInfoSistem() {
    cout << "============================================================" << endl;
    cout << "                 INFO SISTEM                               " << endl;
    cout << "============================================================" << endl;
    cout << "Nama Sistem    : JEGGER T-SHIRT Management System" << endl;
    cout << "Versi          : 2.0" << endl;
    cout << "Institusi      : UAD - Informatika S1" << endl;
    cout << "Alamat         : Jl. Malioboro No.77, Yogyakarta" << endl;
    cout << "Telepon        : 0013-2006-7888 / 0012-2720-9026" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Total User     : " << jumlahUser      << " akun" << endl;
    cout << "Total Produk   : " << jumlahProduk    << " jenis" << endl;
    cout << "Total Transaksi: " << jumlahTransaksi << " transaksi" << endl;
    cout << "------------------------------------------------------------" << endl;
    int totalStokAll = 0;
    for (int i = 0; i < jumlahProduk; i++) {
        totalStokAll += daftarProduk[i].getStok();
    }
    cout << "Total Stok     : " << totalStokAll << " pcs" << endl;
    cout << "============================================================" << endl;
}

// =====================================================
// LINKED LIST: LOG AKTIVITAS SISTEM
// (Praktikum 10 - Pointer & Linked List)
// =====================================================

struct NodeLog {
    string aktivitas;
    string waktu;
    string pengguna;
    NodeLog* berikut;
};

class LogAktivitas {
private:
    NodeLog* kepala;
    int jumlahLog;

public:
    LogAktivitas() {
        kepala    = NULL;
        jumlahLog = 0;
    }

    void tambahLog(string aktivitas, string pengguna, string waktu) {
        NodeLog* baru   = new NodeLog;
        baru->aktivitas = aktivitas;
        baru->pengguna  = pengguna;
        baru->waktu     = waktu;
        baru->berikut   = kepala;
        kepala          = baru;
        jumlahLog++;
    }

    void tampilLog() {
        if (kepala == NULL) {
            cout << "[!] Belum ada log aktivitas!" << endl;
            return;
        }
        cout << "============================================================" << endl;
        cout << "              LOG AKTIVITAS SISTEM (Linked List)           " << endl;
        cout << "============================================================" << endl;
        cout << "No\tWaktu\t\tPengguna\tAktivitas" << endl;
        cout << "------------------------------------------------------------" << endl;
        NodeLog* jalan = kepala;
        int no = 1;
        while (jalan != NULL) {
            cout << no << "\t"
                 << jalan->waktu << "\t"
                 << jalan->pengguna << "\t\t"
                 << jalan->aktivitas << endl;
            jalan = jalan->berikut;
            no++;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << "Total log: " << jumlahLog << " entri" << endl;
        cout << "============================================================" << endl;
    }

    int hitungLogRekursif(NodeLog* node) {
        if (node == NULL) return 0;
        return 1 + hitungLogRekursif(node->berikut);
    }

    int getJumlahLog() {
        return hitungLogRekursif(kepala);
    }

    void cariLogByPengguna(string pengguna) {
        bool ditemukan = false;
        NodeLog* jalan = kepala;
        int no = 1;
        cout << "============================================================" << endl;
        cout << "  LOG AKTIVITAS - " << pengguna << endl;
        cout << "============================================================" << endl;
        while (jalan != NULL) {
            if (jalan->pengguna == pengguna) {
                cout << no << ". [" << jalan->waktu << "] "
                     << jalan->aktivitas << endl;
                ditemukan = true;
                no++;
            }
            jalan = jalan->berikut;
        }
        if (!ditemukan) {
            cout << "[!] Tidak ada log untuk pengguna " << pengguna << endl;
        }
        cout << "============================================================" << endl;
    }

    void hapusLogTerlama() {
        if (kepala == NULL) {
            cout << "[!] Log kosong!" << endl;
            return;
        }
        if (kepala->berikut == NULL) {
            delete kepala;
            kepala = NULL;
            jumlahLog--;
            cout << "[?] Log terlama berhasil dihapus!" << endl;
            return;
        }
        NodeLog* jalan = kepala;
        while (jalan->berikut->berikut != NULL) {
            jalan = jalan->berikut;
        }
        delete jalan->berikut;
        jalan->berikut = NULL;
        jumlahLog--;
        cout << "[?] Log terlama berhasil dihapus!" << endl;
    }

    void hapusLogTerbaru() {
        if (kepala == NULL) {
            cout << "[!] Log kosong!" << endl;
            return;
        }
        NodeLog* hapus = kepala;
        kepala = kepala->berikut;
        delete hapus;
        jumlahLog--;
        cout << "[?] Log terbaru berhasil dihapus!" << endl;
    }

    void cetakLogRekursif(NodeLog* node, int no) {
        if (node == NULL) return;
        cetakLogRekursif(node->berikut, no + 1);
        cout << no << ". [" << node->waktu << "] "
             << node->pengguna << " -> " << node->aktivitas << endl;
    }

    void tampilLogKronologis() {
        if (kepala == NULL) {
            cout << "[!] Belum ada log aktivitas!" << endl;
            return;
        }
        cout << "============================================================" << endl;
        cout << "       LOG AKTIVITAS (Kronologis, via Rekursi)             " << endl;
        cout << "============================================================" << endl;
        cetakLogRekursif(kepala, 1);
        cout << "============================================================" << endl;
    }

    ~LogAktivitas() {
        NodeLog* jalan = kepala;
        while (jalan != NULL) {
            NodeLog* hapus = jalan;
            jalan = jalan->berikut;
            delete hapus;
        }
    }
};

LogAktivitas logSistem;

void tambahLog(string aktivitas, string pengguna) {
    logSistem.tambahLog(aktivitas, pengguna, "Log");
}

// =====================================================
// LINKED LIST: PELANGGAN & LOYALITAS
// (Praktikum 10 - Pointer & Linked List)
// =====================================================

struct NodePelanggan {
    string nama;
    string nomorHP;
    int    poin;
    int    totalBelanja;
    int    jumlahKunjungan;
    NodePelanggan* berikut;
};

class DaftarPelanggan {
private:
    NodePelanggan* kepala;
    int jumlahPelanggan;

public:
    DaftarPelanggan() {
        kepala          = NULL;
        jumlahPelanggan = 0;
    }

    void tambahPelanggan(string nama, string hp) {
        NodePelanggan* jalan = kepala;
        while (jalan != NULL) {
            if (jalan->nama == nama && jalan->nomorHP == hp) {
                cout << "[!] Pelanggan sudah terdaftar!" << endl;
                return;
            }
            jalan = jalan->berikut;
        }

        NodePelanggan* baru   = new NodePelanggan;
        baru->nama            = nama;
        baru->nomorHP         = hp;
        baru->poin            = 0;
        baru->totalBelanja    = 0;
        baru->jumlahKunjungan = 0;
        baru->berikut         = kepala;
        kepala                = baru;
        jumlahPelanggan++;
        cout << "[?] Pelanggan " << nama << " berhasil didaftarkan!" << endl;
    }

    NodePelanggan* cariPelanggan(string nama) {
        NodePelanggan* jalan = kepala;
        while (jalan != NULL) {
            if (jalan->nama == nama) {
                return jalan;
            }
            jalan = jalan->berikut;
        }
        return NULL;
    }

    void tambahPoinPelanggan(string nama, int belanja) {
        NodePelanggan* p = cariPelanggan(nama);
        if (p == NULL) {
            cout << "[!] Pelanggan tidak ditemukan!" << endl;
            return;
        }
        // Setiap Rp 10.000 = 1 poin
        int poinBaru        = belanja / 10000;
        p->poin            += poinBaru;
        p->totalBelanja    += belanja;
        p->jumlahKunjungan++;
        cout << "[?] Ditambahkan " << poinBaru << " poin untuk " << nama << endl;
        cout << "    Total poin sekarang: " << p->poin << " poin" << endl;
    }

    void tampilDetailPelanggan(string nama) {
        NodePelanggan* p = cariPelanggan(nama);
        if (p == NULL) {
            cout << "[!] Pelanggan tidak ditemukan!" << endl;
            return;
        }
        string level = "Reguler";
        if (p->poin >= 500) level = "Platinum";
        else if (p->poin >= 200) level = "Gold";
        else if (p->poin >= 50)  level = "Silver";

        cout << "============================================================" << endl;
        cout << "             DATA PELANGGAN                                " << endl;
        cout << "============================================================" << endl;
        cout << "Nama          : " << p->nama << endl;
        cout << "No. HP        : " << p->nomorHP << endl;
        cout << "Total Poin    : " << p->poin << " poin" << endl;
        cout << "Level         : " << level << endl;
        cout << "Total Belanja : Rp " << p->totalBelanja << endl;
        cout << "Kunjungan     : " << p->jumlahKunjungan << " kali" << endl;
        cout << "============================================================" << endl;
    }

    void tampilSemuaPelanggan() {
        if (kepala == NULL) {
            cout << "[!] Belum ada pelanggan terdaftar!" << endl;
            return;
        }
        cout << "============================================================" << endl;
        cout << "              DAFTAR PELANGGAN                             " << endl;
        cout << "============================================================" << endl;
        cout << "No\tNama\t\t\tPoin\tLevel\t\tKunjungan" << endl;
        cout << "------------------------------------------------------------" << endl;
        NodePelanggan* jalan = kepala;
        int no = 1;
        while (jalan != NULL) {
            string level = "Reguler";
            if (jalan->poin >= 500) level = "Platinum";
            else if (jalan->poin >= 200) level = "Gold";
            else if (jalan->poin >= 50)  level = "Silver";

            cout << no << "\t"
                 << jalan->nama << "\t\t\t"
                 << jalan->poin << "\t"
                 << level << "\t\t"
                 << jalan->jumlahKunjungan << " kali" << endl;
            jalan = jalan->berikut;
            no++;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << "Total Pelanggan: " << jumlahPelanggan << endl;
        cout << "============================================================" << endl;
    }

    int tukarPoin(string nama, int poinDitukar) {
        NodePelanggan* p = cariPelanggan(nama);
        if (p == NULL) {
            cout << "[!] Pelanggan tidak ditemukan!" << endl;
            return 0;
        }
        if (p->poin < poinDitukar) {
            cout << "[!] Poin tidak mencukupi! Poin saat ini: "
                 << p->poin << endl;
            return 0;
        }
        // 1 poin = Rp 500 diskon
        int diskon  = poinDitukar * 500;
        p->poin    -= poinDitukar;
        cout << "[?] " << poinDitukar << " poin ditukar dengan diskon Rp "
             << diskon << endl;
        cout << "    Sisa poin: " << p->poin << " poin" << endl;
        return diskon;
    }

    int getJumlahPelanggan() { return jumlahPelanggan; }

    ~DaftarPelanggan() {
        NodePelanggan* jalan = kepala;
        while (jalan != NULL) {
            NodePelanggan* hapus = jalan;
            jalan = jalan->berikut;
            delete hapus;
        }
    }
};

DaftarPelanggan daftarPelanggan;

// =====================================================
// SISTEM ANTRIAN PELAYANAN (Queue dengan Array)
// (Praktikum 1-3: Sekuen, Kondisional, Perulangan)
// =====================================================

struct Antrian {
    string namaCustomer;
    string nomorAntrian;
    string jenisLayanan;
    bool   sudahDilayani;
};

Antrian dataAntrian[MAX_ANTRIAN];
int jumlahAntrian     = 0;
int nomorAntrianCount = 1;
int indexFront        = 0;

string generateNomorAntrian() {
    string no = "A";
    if (nomorAntrianCount < 10) {
        no += "0" + to_string(nomorAntrianCount);
    } else {
        no += to_string(nomorAntrianCount);
    }
    nomorAntrianCount++;
    return no;
}

void tambahAntrian(string nama, string layanan) {
    if (jumlahAntrian >= MAX_ANTRIAN) {
        cout << "[!] Antrian penuh!" << endl;
        return;
    }
    dataAntrian[jumlahAntrian].namaCustomer  = nama;
    dataAntrian[jumlahAntrian].nomorAntrian  = generateNomorAntrian();
    dataAntrian[jumlahAntrian].jenisLayanan  = layanan;
    dataAntrian[jumlahAntrian].sudahDilayani = false;
    jumlahAntrian++;
    cout << "[?] Nomor antrian Anda: "
         << dataAntrian[jumlahAntrian - 1].nomorAntrian << endl;
}

void panggilAntrian() {
    bool ada = false;
    for (int i = 0; i < jumlahAntrian; i++) {
        if (!dataAntrian[i].sudahDilayani) {
            cout << "============================================================" << endl;
            cout << "  MEMANGGIL ANTRIAN: " << dataAntrian[i].nomorAntrian << endl;
            cout << "  Nama    : " << dataAntrian[i].namaCustomer << endl;
            cout << "  Layanan : " << dataAntrian[i].jenisLayanan << endl;
            cout << "============================================================" << endl;
            dataAntrian[i].sudahDilayani = true;
            logSistem.tambahLog("Pelayanan antrian " + dataAntrian[i].nomorAntrian, "kasir", "Log");
            ada = true;
            break;
        }
    }
    if (!ada) {
        cout << "[!] Tidak ada antrian yang menunggu!" << endl;
    }
}

void tampilStatusAntrian() {
    cout << "============================================================" << endl;
    cout << "              STATUS ANTRIAN PELAYANAN                     " << endl;
    cout << "============================================================" << endl;
    cout << "No\tNomor\tNama\t\tLayanan\t\tStatus" << endl;
    cout << "------------------------------------------------------------" << endl;
    int menunggu = 0;
    int selesai  = 0;
    for (int i = 0; i < jumlahAntrian; i++) {
        cout << i + 1 << "\t"
             << dataAntrian[i].nomorAntrian << "\t"
             << dataAntrian[i].namaCustomer << "\t\t"
             << dataAntrian[i].jenisLayanan << "\t\t";
        if (dataAntrian[i].sudahDilayani) {
            cout << "Selesai" << endl;
            selesai++;
        } else {
            cout << "Menunggu" << endl;
            menunggu++;
        }
    }
    cout << "------------------------------------------------------------" << endl;
    cout << "Total Antrian: " << jumlahAntrian
         << " | Menunggu: " << menunggu
         << " | Selesai: "  << selesai << endl;
    cout << "============================================================" << endl;
}

// =====================================================
// PRAKTIKUM 5: REKURSI
// =====================================================

long long hitungNilaiStokRekursif(int index) {
    if (index >= jumlahProduk) return 0;
    long long nilaiProdukIni = (long long)daftarProduk[index].getHarga()
                             * daftarProduk[index].getStok();
    return nilaiProdukIni + hitungNilaiStokRekursif(index + 1);
}

long long hitungOmzetRekursif(int index) {
    if (index >= jumlahTransaksi) return 0;
    return riwayatTransaksi[index].getTotalHarga() + hitungOmzetRekursif(index + 1);
}

long long faktorialRekursif(int n) {
    if (n == 0 || n == 1) return 1;
    return n * faktorialRekursif(n - 1);
}

long long fibonacciRekursif(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacciRekursif(n - 1) + fibonacciRekursif(n - 2);
}

int cariStokMinRekursif(int index, int minIndex) {
    if (index >= jumlahProduk) return minIndex;
    if (daftarProduk[index].getStok() < daftarProduk[minIndex].getStok()) {
        return cariStokMinRekursif(index + 1, index);
    }
    return cariStokMinRekursif(index + 1, minIndex);
}

int cariHargaMaxRekursif(int index, int maxIndex) {
    if (index >= jumlahProduk) return maxIndex;
    if (daftarProduk[index].getHarga() > daftarProduk[maxIndex].getHarga()) {
        return cariHargaMaxRekursif(index + 1, index);
    }
    return cariHargaMaxRekursif(index + 1, maxIndex);
}

int hitungProdukStokMenipisRekursif(int index) {
    if (index >= jumlahProduk) return 0;
    int tambah = 0;
    if (daftarProduk[index].cekStokMenipis()) {
        tambah = 1;
    }
    return tambah + hitungProdukStokMenipisRekursif(index + 1);
}

int hitungTotalItemTerjualRekursif(int indexTrx) {
    if (indexTrx >= jumlahTransaksi) return 0;
    return riwayatTransaksi[indexTrx].getJumlahItem()
         + hitungTotalItemTerjualRekursif(indexTrx + 1);
}

void cetakProdukReverseRekursif(int index) {
    if (index < 0) return;
    daftarProduk[index].tampilBaris(jumlahProduk - index);
    cetakProdukReverseRekursif(index - 1);
}

// Jumlah digit suatu bilangan (rekursif)
int hitungDigitRekursif(int n) {
    if (n < 10) return 1;
    return 1 + hitungDigitRekursif(n / 10);
}

// Pangkat rekursif: base^exp
long long pangkatRekursif(int base, int exp) {
    if (exp == 0) return 1;
    return base * pangkatRekursif(base, exp - 1);
}

// Jumlah elemen array secara rekursif
int jumlahArrayRekursif(int arr[], int n) {
    if (n == 0) return 0;
    return arr[n - 1] + jumlahArrayRekursif(arr, n - 1);
}

// Cari nilai maksimum dalam array secara rekursif
int maxArrayRekursif(int arr[], int n) {
    if (n == 1) return arr[0];
    int maks = maxArrayRekursif(arr, n - 1);
    if (arr[n - 1] > maks) return arr[n - 1];
    return maks;
}

// Hitung jumlah produk berdasarkan ukuran secara rekursif
int hitungProdukByUkuranRekursif(int index, string ukuran) {
    if (index >= jumlahProduk) return 0;
    int tambah = 0;
    if (daftarProduk[index].getUkuran() == ukuran) {
        tambah = 1;
    }
    return tambah + hitungProdukByUkuranRekursif(index + 1, ukuran);
}

// =====================================================
// PRAKTIKUM 7 & 8: BINARY SEARCH
// =====================================================

int binarySearchHarga(int hargaCari) {
    int low  = 0;
    int high = jumlahProduk - 1;
    cout << "--- Proses Binary Search harga Rp " << hargaCari << " ---" << endl;
    while (low <= high) {
        int mid = (low + high) / 2;
        cout << "  Low=" << low << ", Mid=" << mid << ", High=" << high
             << " -> Harga[" << mid << "]=" << daftarProduk[mid].getHarga() << endl;
        if (daftarProduk[mid].getHarga() == hargaCari) {
            return mid;
        } else if (daftarProduk[mid].getHarga() < hargaCari) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int binarySearchNoStruk(string cari) {
    int low  = 0;
    int high = jumlahTransaksi - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (riwayatTransaksi[mid].getNoStruk() == cari) {
            return mid;
        } else if (riwayatTransaksi[mid].getNoStruk() < cari) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Binary search rekursif berdasarkan nama produk (ascending)
int binarySearchNamaRekursif(string nama, int low, int high) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (daftarProduk[mid].getNama() == nama) {
        return mid;
    } else if (daftarProduk[mid].getNama() < nama) {
        return binarySearchNamaRekursif(nama, mid + 1, high);
    } else {
        return binarySearchNamaRekursif(nama, low, mid - 1);
    }
}

// Demo langkah Bubble Sort
void demoLangkahBubbleSort() {
    if (jumlahProduk == 0) {
        cout << "[!] Tidak ada produk untuk diurutkan!" << endl;
        return;
    }
    int arrHarga[MAX_PRODUK];
    string arrNama[MAX_PRODUK];
    int n = jumlahProduk;
    for (int i = 0; i < n; i++) {
        arrHarga[i] = daftarProduk[i].getHarga();
        arrNama[i]  = daftarProduk[i].getNama();
    }

    cout << "============================================================" << endl;
    cout << "    DEMO BUBBLE SORT - LANGKAH DEMI LANGKAH                " << endl;
    cout << "    (Berdasarkan Harga Produk)                              " << endl;
    cout << "============================================================" << endl;
    cout << "Data awal: ";
    for (int i = 0; i < n; i++) {
        cout << arrHarga[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl << endl;

    for (int i = 0; i < n - 1; i++) {
        cout << "--- Pass ke-" << i + 1 << " ---" << endl;
        bool adaPerubahan = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arrHarga[j] > arrHarga[j + 1]) {
                cout << "  Tukar " << arrHarga[j] << " <-> " << arrHarga[j + 1] << endl;
                int tmpH    = arrHarga[j];
                arrHarga[j] = arrHarga[j + 1];
                arrHarga[j + 1] = tmpH;
                string tmpN    = arrNama[j];
                arrNama[j]     = arrNama[j + 1];
                arrNama[j + 1] = tmpN;
                adaPerubahan = true;
            }
        }
        cout << "  Hasil: ";
        for (int i2 = 0; i2 < n; i2++) {
            cout << arrHarga[i2];
            if (i2 < n - 1) cout << ", ";
        }
        cout << endl;
        if (!adaPerubahan) {
            cout << "  (Tidak ada pertukaran, data sudah terurut!)" << endl;
            break;
        }
    }

    cout << endl << "Data akhir (terurut ascending):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << i + 1 << ". " << arrNama[i] << " - Rp " << arrHarga[i] << endl;
    }
    cout << "============================================================" << endl;
}

// Demo langkah Selection Sort
void demoLangkahSelectionSort() {
    if (jumlahProduk == 0) {
        cout << "[!] Tidak ada produk untuk diurutkan!" << endl;
        return;
    }
    int arrHarga[MAX_PRODUK];
    string arrNama[MAX_PRODUK];
    int n = jumlahProduk;
    for (int i = 0; i < n; i++) {
        arrHarga[i] = daftarProduk[i].getHarga();
        arrNama[i]  = daftarProduk[i].getNama();
    }

    cout << "============================================================" << endl;
    cout << "    DEMO SELECTION SORT - LANGKAH DEMI LANGKAH             " << endl;
    cout << "    (Berdasarkan Harga Produk)                              " << endl;
    cout << "============================================================" << endl;
    cout << "Data awal: ";
    for (int i = 0; i < n; i++) {
        cout << arrHarga[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl << endl;

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arrHarga[j] < arrHarga[minIdx]) {
                minIdx = j;
            }
        }
        cout << "--- Pass ke-" << i + 1 << ": Minimum = " << arrHarga[minIdx]
             << " di indeks " << minIdx << " ---" << endl;
        if (minIdx != i) {
            cout << "  Tukar indeks " << i << " (" << arrHarga[i]
                 << ") <-> indeks " << minIdx << " (" << arrHarga[minIdx] << ")" << endl;
            int tmpH       = arrHarga[i];
            arrHarga[i]    = arrHarga[minIdx];
            arrHarga[minIdx] = tmpH;
            string tmpN      = arrNama[i];
            arrNama[i]       = arrNama[minIdx];
            arrNama[minIdx]  = tmpN;
        } else {
            cout << "  (Tidak perlu pertukaran)" << endl;
        }
        cout << "  Hasil: ";
        for (int k = 0; k < n; k++) {
            cout << arrHarga[k];
            if (k < n - 1) cout << ", ";
        }
        cout << endl;
    }

    cout << endl << "Data akhir (terurut ascending via Selection Sort):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << i + 1 << ". " << arrNama[i] << " - Rp " << arrHarga[i] << endl;
    }
    cout << "============================================================" << endl;
}

// Demo langkah Insertion Sort
void demoLangkahInsertionSort() {
    if (jumlahProduk == 0) {
        cout << "[!] Tidak ada produk untuk diurutkan!" << endl;
        return;
    }
    int arrHarga[MAX_PRODUK];
    string arrNama[MAX_PRODUK];
    int n = jumlahProduk;
    for (int i = 0; i < n; i++) {
        arrHarga[i] = daftarProduk[i].getHarga();
        arrNama[i]  = daftarProduk[i].getNama();
    }

    cout << "============================================================" << endl;
    cout << "    DEMO INSERTION SORT - LANGKAH DEMI LANGKAH             " << endl;
    cout << "    (Berdasarkan Harga Produk)                              " << endl;
    cout << "============================================================" << endl;
    cout << "Data awal: ";
    for (int i = 0; i < n; i++) {
        cout << arrHarga[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl << endl;

    for (int i = 1; i < n; i++) {
        int kunciH    = arrHarga[i];
        string kunciN = arrNama[i];
        int j         = i - 1;
        cout << "--- Iterasi ke-" << i << ": kunci = " << kunciH << " ---" << endl;
        while (j >= 0 && arrHarga[j] > kunciH) {
            cout << "  Geser " << arrHarga[j] << " ke posisi " << j + 1 << endl;
            arrHarga[j + 1] = arrHarga[j];
            arrNama[j + 1]  = arrNama[j];
            j--;
        }
        arrHarga[j + 1] = kunciH;
        arrNama[j + 1]  = kunciN;
        cout << "  Sisipkan " << kunciH << " di posisi " << j + 1 << endl;
        cout << "  Hasil: ";
        for (int k = 0; k < n; k++) {
            cout << arrHarga[k];
            if (k < n - 1) cout << ", ";
        }
        cout << endl;
    }

    cout << endl << "Data akhir (terurut ascending via Insertion Sort):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << i + 1 << ". " << arrNama[i] << " - Rp " << arrHarga[i] << endl;
    }
    cout << "============================================================" << endl;
}

// =====================================================
// PRAKTIKUM 9: ARRAY 2 DIMENSI
// Matriks penjualan produk per ukuran per bulan
// =====================================================

int matriksPenjualan[MAX_BULAN][MAX_UKURAN];
string namaUkuran[MAX_UKURAN] = {"S", "M", "L", "XL", "XXL"};
string namaBulan[MAX_BULAN]   = {
    "Januari", "Februari", "Maret",    "April",
    "Mei",     "Juni",     "Juli",     "Agustus",
    "September","Oktober", "November", "Desember"
};

void inisialisasiMatriks() {
    for (int i = 0; i < MAX_BULAN; i++) {
        for (int j = 0; j < MAX_UKURAN; j++) {
            matriksPenjualan[i][j] = 0;
        }
    }
}

int getIndexUkuran(string uk) {
    if (uk == "S")   return 0;
    if (uk == "M")   return 1;
    if (uk == "L")   return 2;
    if (uk == "XL")  return 3;
    if (uk == "XXL") return 4;
    return -1;
}

int getBulanDariTanggal(string tanggal) {
    if ((int)tanggal.length() < 7) return -1;
    string bulanStr = "";
    bulanStr += tanggal[3];
    bulanStr += tanggal[4];
    int bulan = 0;
    for (int i = 0; i < (int)bulanStr.length(); i++) {
        bulan = bulan * 10 + (bulanStr[i] - '0');
    }
    if (bulan < 1 || bulan > 12) return -1;
    return bulan - 1;
}

void bangunMatriksPenjualan() {
    inisialisasiMatriks();
    for (int i = 0; i < jumlahTransaksi; i++) {
        string tgl    = riwayatTransaksi[i].getTanggal();
        int idxBulan  = getBulanDariTanggal(tgl);
        if (idxBulan < 0) continue;

        for (int j = 0; j < riwayatTransaksi[i].getJumlahItem(); j++) {
            ItemBelanja item  = riwayatTransaksi[i].getItem(j);
            int idxUk         = getIndexUkuran(item.ukuran);
            if (idxUk >= 0) {
                matriksPenjualan[idxBulan][idxUk] += item.qty;
            }
        }
    }
}

void tampilMatriksPenjualan() {
    bangunMatriksPenjualan();
    cout << "============================================================" << endl;
    cout << "   MATRIKS PENJUALAN PER BULAN x UKURAN (Array 2D)        " << endl;
    cout << "============================================================" << endl;
    cout << "Bulan\t\t\tS\tM\tL\tXL\tXXL\tTotal" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < MAX_BULAN; i++) {
        int totalBulan = 0;
        bool adaData   = false;
        for (int j = 0; j < MAX_UKURAN; j++) {
            if (matriksPenjualan[i][j] > 0) adaData = true;
            totalBulan += matriksPenjualan[i][j];
        }
        if (!adaData) continue;

        cout << namaBulan[i];
        if ((int)namaBulan[i].length() < 8) cout << "\t\t";
        else cout << "\t";

        for (int j = 0; j < MAX_UKURAN; j++) {
            cout << matriksPenjualan[i][j] << "\t";
        }
        cout << totalBulan << endl;
    }
    cout << "------------------------------------------------------------" << endl;
    cout << "TOTAL\t\t\t";
    int grandTotal = 0;
    for (int j = 0; j < MAX_UKURAN; j++) {
        int totKolom = 0;
        for (int i = 0; i < MAX_BULAN; i++) {
            totKolom += matriksPenjualan[i][j];
        }
        cout << totKolom << "\t";
        grandTotal += totKolom;
    }
    cout << grandTotal << endl;
    cout << "============================================================" << endl;
}

void konversiMatriksKe1D() {
    bangunMatriksPenjualan();
    int arr1D[MAX_BULAN * MAX_UKURAN];
    int n = 0;
    for (int i = 0; i < MAX_BULAN; i++) {
        for (int j = 0; j < MAX_UKURAN; j++) {
            arr1D[n++] = matriksPenjualan[i][j];
        }
    }

    // Bubble sort array 1D
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr1D[j] > arr1D[j + 1]) {
                int tmp      = arr1D[j];
                arr1D[j]     = arr1D[j + 1];
                arr1D[j + 1] = tmp;
            }
        }
    }

    cout << "============================================================" << endl;
    cout << "  ARRAY 1D HASIL KONVERSI MATRIKS (Terurut Ascending)     " << endl;
    cout << "============================================================" << endl;
    cout << "Total " << n << " elemen:" << endl;
    int jumlahTampil = 0;
    for (int i = 0; i < n; i++) {
        if (arr1D[i] > 0) {
            cout << arr1D[i] << " ";
            jumlahTampil++;
        }
    }
    if (jumlahTampil == 0) {
        cout << "(Belum ada data penjualan)";
    }
    cout << endl;
    cout << "============================================================" << endl;
}

// Operasi matriks: transpose (kolom jadi baris)
void transposeMatriksDisplay() {
    bangunMatriksPenjualan();
    cout << "============================================================" << endl;
    cout << "   TRANSPOSE MATRIKS (Ukuran x Bulan)                     " << endl;
    cout << "============================================================" << endl;
    cout << "Ukuran\t";
    for (int i = 0; i < MAX_BULAN; i++) {
        // Singkatan nama bulan (3 huruf)
        cout << namaBulan[i].substr(0, 3) << "\t";
    }
    cout << "Total" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int j = 0; j < MAX_UKURAN; j++) {
        cout << namaUkuran[j] << "\t";
        int totalUkuran = 0;
        for (int i = 0; i < MAX_BULAN; i++) {
            cout << matriksPenjualan[i][j] << "\t";
            totalUkuran += matriksPenjualan[i][j];
        }
        cout << totalUkuran << endl;
    }
    cout << "============================================================" << endl;
}

// =====================================================
// KALKULATOR DISKON & HARGA
// (Praktikum 2 - Kondisional Bertingkat)
// =====================================================

void kalkulatorDiskonPembelian() {
    headerMenu("KALKULATOR DISKON PEMBELIAN");
    cout << "(Konsep Kondisional - Praktikum 2)" << endl;
    cout << "------------------------------------------------------------" << endl;
    int totalBelanja;
    cout << "Total belanja (Rp): ";
    cin >> totalBelanja;
    cin.ignore();

    if (totalBelanja <= 0) {
        cout << "[!] Total belanja tidak valid!" << endl;
        return;
    }

    int    diskon    = 0;
    double persen    = 0.0;
    string infoDiskon = "";

    if (totalBelanja >= 500000) {
        persen     = 0.25;
        infoDiskon = "Belanja >= Rp 500.000 -> Diskon 25%";
    } else if (totalBelanja >= 300000) {
        persen     = 0.20;
        infoDiskon = "Belanja >= Rp 300.000 -> Diskon 20%";
    } else if (totalBelanja >= 200000) {
        persen     = 0.15;
        infoDiskon = "Belanja >= Rp 200.000 -> Diskon 15%";
    } else if (totalBelanja >= 100000) {
        persen     = 0.10;
        infoDiskon = "Belanja >= Rp 100.000 -> Diskon 10%";
    } else if (totalBelanja >= 50000) {
        persen     = 0.05;
        infoDiskon = "Belanja >= Rp 50.000  -> Diskon 5%";
    } else {
        infoDiskon = "Belanja < Rp 50.000 -> Tidak ada diskon";
    }

    diskon = (int)(totalBelanja * persen);
    int totalBayar = totalBelanja - diskon;

    cout << "============================================================" << endl;
    cout << "              HASIL KALKULASI DISKON                       " << endl;
    cout << "============================================================" << endl;
    cout << "Subtotal       : Rp " << totalBelanja << endl;
    cout << "Keterangan     : " << infoDiskon << endl;
    cout << "Diskon         : Rp " << diskon << endl;
    cout << "Total Bayar    : Rp " << totalBayar << endl;
    cout << "============================================================" << endl;
}

// Kalkulator pajak penjualan
void kalkulatorPajakPenjualan() {
    headerMenu("KALKULATOR PAJAK PENJUALAN");
    cout << "Masukkan harga jual produk (Rp): ";
    int harga;
    cin >> harga;
    cin.ignore();

    if (harga <= 0) {
        cout << "[!] Harga tidak valid!" << endl;
        return;
    }

    // PPN 11%
    int pajak     = (int)(harga * 0.11);
    int hargaFinal = harga + pajak;

    cout << "============================================================" << endl;
    cout << "  PERHITUNGAN PAJAK (PPN 11%)                              " << endl;
    cout << "============================================================" << endl;
    cout << "Harga sebelum pajak : Rp " << harga << endl;
    cout << "PPN (11%)           : Rp " << pajak << endl;
    cout << "Harga setelah pajak : Rp " << hargaFinal << endl;
    cout << "============================================================" << endl;
}

// Kalkulator profit margin
void kalkulatorProfitMargin() {
    headerMenu("KALKULATOR PROFIT MARGIN");
    int modal, hargaJual;
    cout << "Harga modal (Rp)  : ";
    cin >> modal;
    cout << "Harga jual (Rp)   : ";
    cin >> hargaJual;
    cin.ignore();

    if (modal <= 0 || hargaJual <= 0) {
        cout << "[!] Input tidak valid!" << endl;
        return;
    }

    int profit      = hargaJual - modal;
    double margin   = (double)profit / hargaJual * 100.0;
    double markup   = (double)profit / modal * 100.0;

    cout << "============================================================" << endl;
    cout << "  HASIL KALKULASI PROFIT                                   " << endl;
    cout << "============================================================" << endl;
    cout << "Harga Modal     : Rp " << modal << endl;
    cout << "Harga Jual      : Rp " << hargaJual << endl;
    cout << "Profit          : Rp " << profit << endl;
    if (margin >= 0) {
        cout << "Profit Margin   : " << (int)margin << "%" << endl;
        cout << "Markup          : " << (int)markup << "%" << endl;
    } else {
        cout << "Keterangan      : RUGI" << endl;
    }
    cout << "============================================================" << endl;
}

// =====================================================
// LAPORAN PERIODE KUSTOM
// (Perulangan - Praktikum 3)
// =====================================================

void laporanPeriodeKustom() {
    headerMenu("LAPORAN PERIODE KUSTOM");
    cout << "(Konsep Perulangan - Praktikum 3)" << endl;
    cout << "------------------------------------------------------------" << endl;

    if (jumlahTransaksi == 0) {
        cout << "[!] Belum ada data transaksi!" << endl;
        return;
    }

    string tglMulai, tglAkhir;
    cout << "Tanggal mulai (dd-mm-yyyy): ";
    cin >> tglMulai;
    cout << "Tanggal akhir (dd-mm-yyyy): ";
    cin >> tglAkhir;
    cin.ignore();

    int  totalTrx   = 0;
    int  totalOmzet = 0;
    int  totalItem  = 0;
    bool ada        = false;

    cout << "============================================================" << endl;
    cout << "  LAPORAN PERIODE " << tglMulai << " s.d. " << tglAkhir << endl;
    cout << "============================================================" << endl;
    cout << "No\tNo Struk\tKasir\t\tTotal" << endl;
    cout << "------------------------------------------------------------" << endl;

    int no = 1;
    for (int i = 0; i < jumlahTransaksi; i++) {
        string tgl = riwayatTransaksi[i].getTanggal();
        if (tgl >= tglMulai && tgl <= tglAkhir) {
            cout << no << "\t"
                 << riwayatTransaksi[i].getNoStruk() << "\t"
                 << riwayatTransaksi[i].getKasir() << "\t\t"
                 << "Rp " << riwayatTransaksi[i].getTotalHarga() << endl;
            totalOmzet += riwayatTransaksi[i].getTotalHarga();
            totalItem  += riwayatTransaksi[i].getJumlahItem();
            totalTrx++;
            no++;
            ada = true;
        }
    }

    if (!ada) {
        cout << "[!] Tidak ada transaksi pada periode tersebut!" << endl;
    } else {
        cout << "------------------------------------------------------------" << endl;
        cout << "Total Transaksi : " << totalTrx << endl;
        cout << "Total Item      : " << totalItem << " pcs" << endl;
        cout << "Total Omzet     : Rp " << totalOmzet << endl;
        if (totalTrx > 0) {
            cout << "Rata-rata/Trx   : Rp " << totalOmzet / totalTrx << endl;
        }
    }
    cout << "============================================================" << endl;
}

// =====================================================
// CARI TRANSAKSI
// =====================================================

void cariTransaksiByKasir(string kasir) {
    bool ada    = false;
    int  total  = 0;
    int  jumlah = 0;

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

void bubbleSortTransaksiByTotal() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        for (int j = 0; j < jumlahTransaksi - i - 1; j++) {
            if (riwayatTransaksi[j].getTotalHarga() < riwayatTransaksi[j + 1].getTotalHarga()) {
                Transaksi temp             = riwayatTransaksi[j];
                riwayatTransaksi[j]        = riwayatTransaksi[j + 1];
                riwayatTransaksi[j + 1]    = temp;
            }
        }
    }
    cout << "[?] Transaksi diurutkan dari total terbesar!" << endl;
}

// =====================================================
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

void menuCariTransaksi() {
    headerMenu("CARI TRANSAKSI");
    cout << "1. Cari by No Struk" << endl;
    cout << "2. Cari by Nama Pembeli" << endl;
    cout << "3. Cari by Kasir" << endl;
    cout << "4. Cari by Tanggal" << endl;
    cout << "5. Urutkan Transaksi by Total (Terbesar)" << endl;
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
                                trx.getNamaPembeli(), trx.getTotalHarga());
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
        } else if (pilihan != 0) {
            cout << "[!] Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
    logSistem.tambahLog("Logout admin",
                        daftarUser[indexUser].getUsername(), "Log");
}

// =====================================================
// MAIN FUNCTION
// =====================================================

int main() {
    fm.bacaSemua();

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
