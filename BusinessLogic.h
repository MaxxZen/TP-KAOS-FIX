#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include "DataLayer.h"
#include <sstream>
#include <utility>
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

struct NodePelanggan {
    string nama;
    string nomorHP;
    string riwayatKunjungan;
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

    bool simpanKeFile(string namaFile = "data_pelanggan.txt") {
        ofstream file(namaFile.c_str());
        if (!file.is_open()) {
            cout << "[!] Gagal membuka file pelanggan: " << namaFile << endl;
            return false;
        }
        NodePelanggan* jalan = kepala;
        while (jalan != NULL) {
            file << jalan->nama << "|"
                 << jalan->nomorHP << "|"
                 << jalan->poin << "|"
                 << jalan->totalBelanja << "|"
                 << jalan->jumlahKunjungan << "|"
                 << jalan->riwayatKunjungan << "\n";
            jalan = jalan->berikut;
        }
        file.close();
        if (!file) {
            cout << "[!] Gagal menyimpan data pelanggan: " << namaFile << endl;
            return false;
        }
        return true;
    }

    void bacaDariFile() {
        ifstream file("data_pelanggan.txt");
        if (!file.is_open()) return;

        NodePelanggan* jalan = kepala;
        while (jalan != NULL) {
            NodePelanggan* hapus = jalan;
            jalan = jalan->berikut;
            delete hapus;
        }
        kepala = NULL;
        jumlahPelanggan = 0;

        NodePelanggan* ekor = NULL;
        string baris;
        while (getline(file, baris)) {
            string data[6];
            string token;
            int kolom = 0;
            for (int i = 0; i <= (int)baris.length(); i++) {
                if (i == (int)baris.length() || baris[i] == '|') {
                    if (kolom >= 6) break;
                    data[kolom++] = token;
                    token = "";
                } else {
                    token += baris[i];
                }
            }
            if ((kolom != 5 && kolom != 6) ||
                data[0] == "" || data[1] == "") continue;

            int nilai[3];
            bool valid = true;
            for (int i = 0; i < 3; i++) {
                stringstream parser(data[i + 2]);
                if (!(parser >> nilai[i]) || (parser >> token) || nilai[i] < 0) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << "[!] Baris data pelanggan tidak valid, dilewati." << endl;
                continue;
            }

            NodePelanggan* baru = new NodePelanggan;
            baru->nama = data[0];
            baru->nomorHP = data[1];
            baru->riwayatKunjungan = kolom == 6 ? data[5] : "";
            baru->poin = nilai[0];
            baru->totalBelanja = nilai[1];
            baru->jumlahKunjungan = nilai[2];
            baru->berikut = NULL;
            if (kepala == NULL) {
                kepala = baru;
            } else {
                ekor->berikut = baru;
            }
            ekor = baru;
            jumlahPelanggan++;
        }
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
        baru->riwayatKunjungan = "";
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

    void tambahPoinPelanggan(
        string nama, int belanja, string tanggal = "Kunjungan manual") {
        if (belanja < 0) {
            cout << "[!] Total belanja tidak boleh negatif!" << endl;
            return;
        }
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
        if (p->riwayatKunjungan != "") p->riwayatKunjungan += "; ";
        p->riwayatKunjungan += tanggal;
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
        cout << "Riwayat       : "
             << (p->riwayatKunjungan == "" ? "-" : p->riwayatKunjungan) << endl;
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

    void urutkanByPoin() {
        for (NodePelanggan* i = kepala; i != NULL; i = i->berikut) {
            for (NodePelanggan* j = i->berikut; j != NULL; j = j->berikut) {
                if (i->poin < j->poin) {
                    swap(i->nama, j->nama);
                    swap(i->nomorHP, j->nomorHP);
                    swap(i->riwayatKunjungan, j->riwayatKunjungan);
                    swap(i->poin, j->poin);
                    swap(i->totalBelanja, j->totalBelanja);
                    swap(i->jumlahKunjungan, j->jumlahKunjungan);
                }
            }
        }
        cout << "[?] Pelanggan diurutkan berdasarkan poin tertinggi." << endl;
    }

    void urutkanByKunjungan() {
        for (NodePelanggan* i = kepala; i != NULL; i = i->berikut) {
            for (NodePelanggan* j = i->berikut; j != NULL; j = j->berikut) {
                if (i->jumlahKunjungan < j->jumlahKunjungan) {
                    swap(i->nama, j->nama);
                    swap(i->nomorHP, j->nomorHP);
                    swap(i->riwayatKunjungan, j->riwayatKunjungan);
                    swap(i->poin, j->poin);
                    swap(i->totalBelanja, j->totalBelanja);
                    swap(i->jumlahKunjungan, j->jumlahKunjungan);
                }
            }
        }
        cout << "[?] Pelanggan diurutkan berdasarkan kunjungan terbanyak." << endl;
    }

    int tukarPoin(string nama, int poinDitukar) {
        if (poinDitukar <= 0) {
            cout << "[!] Jumlah poin yang ditukar harus lebih dari 0!" << endl;
            return 0;
        }
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

struct Antrian {
    string namaCustomer;
    string nomorAntrian;
    string jenisLayanan;
    bool   sudahDilayani;
};


extern Laporan laporan;
extern LogAktivitas logSistem;
extern DaftarPelanggan daftarPelanggan;
extern Antrian dataAntrian[MAX_ANTRIAN];
extern int jumlahAntrian;
extern int nomorAntrianCount;
extern int indexFront;
extern int noStrukCounter;
extern int matriksPenjualan[MAX_BULAN][MAX_UKURAN];
extern string namaUkuran[MAX_UKURAN];
extern string namaBulan[MAX_BULAN];

void garisPemisah();
void headerMenu(string judul);
void tekanEnterUntukLanjut();
bool konfirmasi(string pesan);
void sortProdukByHarga();
void sortProdukByNama();
void sortProdukByStok();
void selectionSortProdukHargaDesc();
void selectionSortProdukByNama();
void selectionSortProdukByStokAsc();
void insertionSortProdukByNama();
void insertionSortProdukByStok();
void insertionSortProdukByHarga();
void tampilStokMenipis();
void tampilProdukStokHabis();
string generateNoStruk();
void statistikProduk();
void statistikTransaksi();
void backupData();
void cekValidasiSemuaData();
void resetSemuaTransaksi();
void tampilInfoSistem();
void laporanRekapEntitas();
void tambahLog(string aktivitas, string pengguna);
string generateNomorAntrian();
void tambahAntrian(string nama, string layanan);
void panggilAntrian();
void tampilStatusAntrian();
long long hitungNilaiStokRekursif(int index);
long long hitungOmzetRekursif(int index);
long long faktorialRekursif(int n);
long long fibonacciRekursif(int n);
int cariStokMinRekursif(int index, int minIndex);
int cariHargaMaxRekursif(int index, int maxIndex);
int hitungProdukStokMenipisRekursif(int index);
int hitungTotalItemTerjualRekursif(int indexTrx);
void cetakProdukReverseRekursif(int index);
int hitungDigitRekursif(int n);
long long pangkatRekursif(int base, int exp);
int jumlahArrayRekursif(int arr[], int n);
int maxArrayRekursif(int arr[], int n);
int hitungProdukByUkuranRekursif(int index, string ukuran);
int binarySearchHarga(int hargaCari);
int binarySearchNoStruk(string cari);
int binarySearchNamaRekursif(string nama, int low, int high);
void demoLangkahBubbleSort();
void demoLangkahSelectionSort();
void demoLangkahInsertionSort();
void inisialisasiMatriks();
int getIndexUkuran(string uk);
int getBulanDariTanggal(string tanggal);
void bangunMatriksPenjualan();
void tampilMatriksPenjualan();
void konversiMatriksKe1D();
void transposeMatriksDisplay();
void kalkulatorDiskonPembelian();
void kalkulatorPajakPenjualan();
void kalkulatorProfitMargin();
void laporanPeriodeKustom();
void cariTransaksiByKasir(string kasir);
void cariTransaksiByPembeli(string pembeli);
void bubbleSortTransaksiByTotal();
void sortTransaksiByTanggal();
void sortTransaksiByVerifikasi();
void verifikasiTransaksi(string noStruk, string pengguna);

#endif
