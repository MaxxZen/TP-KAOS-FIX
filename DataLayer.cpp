#include "DataLayer.h"

User daftarUser[MAX_USER];
int jumlahUser = 0;
Produk daftarProduk[MAX_PRODUK];
int jumlahProduk = 0;
Transaksi riwayatTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;
FileManager fm;
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
    cout << "No\tNo Struk\tTanggal\t\tKasir\t\tTotal\tVerifikasi\tPengemasan" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahTransaksi; i++) {
        cout << i + 1 << "\t"
             << riwayatTransaksi[i].getNoStruk() << "\t"
             << riwayatTransaksi[i].getTanggal() << "\t"
             << riwayatTransaksi[i].getKasir() << "\t\t"
             << "Rp " << riwayatTransaksi[i].getTotalHarga() << "\t"
             << (riwayatTransaksi[i].getSudahDiverifikasi()
                 ? "Terverifikasi" : "Menunggu") << "\t"
             << riwayatTransaksi[i].getStatusPengemasan() << endl;
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

void tampilTransaksiByPengemasan(string status) {
    bool ditemukan = false;
    cout << "============================================================" << endl;
    cout << "PESANAN DENGAN STATUS: " << status << endl;
    cout << "============================================================" << endl;
    cout << "No Struk\tTanggal\t\tPembeli\t\tTotal" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (riwayatTransaksi[i].getStatusPengemasan() == status) {
            cout << riwayatTransaksi[i].getNoStruk() << "\t"
                 << riwayatTransaksi[i].getTanggal() << "\t"
                 << riwayatTransaksi[i].getNamaPembeli() << "\t\tRp "
                 << riwayatTransaksi[i].getTotalHarga() << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "[!] Tidak ada pesanan dengan status tersebut." << endl;
    }
    cout << "============================================================" << endl;
}

// =====================================================
// CLASS LAPORAN
// =====================================================

    FileManager::FileManager() {}

    void FileManager::simpanUser() {
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

    void FileManager::bacaUser() {
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

    void FileManager::simpanProduk() {
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

    void FileManager::bacaProduk() {
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

    void FileManager::simpanTransaksi() {
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
                 << riwayatTransaksi[i].getJumlahItem() << "|"
                 << (riwayatTransaksi[i].getSudahDiverifikasi() ? 1 : 0) << "|"
                 << riwayatTransaksi[i].getStatusPengemasan()
                 << "\n";
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

    void FileManager::bacaTransaksi() {
        ifstream file("data_transaksi.txt");
        if (!file.is_open()) return;
        jumlahTransaksi = 0;
        string baris;
        while (getline(file, baris)) {
            if (baris == "") continue;
            string token = "";
            int fase = 0;
            string noStruk = "", tanggal = "", kasir = "",
                   pembeli = "", statusPengemasan = "Belum Dikemas";
            int total = 0, bayar = 0, kembalian = 0, jmlItem = 0;
            bool sudahDiverifikasi = false;

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
                    else if (fase == 8) sudahDiverifikasi = (stoi(token) == 1);
                    else if (fase == 9) statusPengemasan = token;
                    token = "";
                    fase++;
                } else {
                    token += baris[i];
                }
            }

            if (jumlahTransaksi < MAX_TRANSAKSI) {
                Transaksi trx(kasir, tanggal, noStruk);
                trx.setNamaPembeli(pembeli);
                trx.setSudahDiverifikasi(sudahDiverifikasi);
                trx.setStatusPengemasan(statusPengemasan);

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
                trx.setBayar(bayar);
                riwayatTransaksi[jumlahTransaksi] = trx;
                jumlahTransaksi++;
            }
        }
        file.close();
    }

    void FileManager::simpanSemua() {
        simpanUser();
        simpanProduk();
        simpanTransaksi();
        cout << "[?] Semua data berhasil disimpan!" << endl;
    }

    void FileManager::bacaSemua() {
        bacaUser();
        bacaProduk();
        bacaTransaksi();
    }
