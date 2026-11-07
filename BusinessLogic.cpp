#include "BusinessLogic.h"

Laporan laporan;
LogAktivitas logSistem;
DaftarPelanggan daftarPelanggan;
Antrian dataAntrian[MAX_ANTRIAN];
int jumlahAntrian = 0;
int nomorAntrianCount = 1;
int indexFront = 0;
int noStrukCounter = 1;
int matriksPenjualan[MAX_BULAN][MAX_UKURAN];
string namaUkuran[MAX_UKURAN] = {"S", "M", "L", "XL", "XXL"};
string namaBulan[MAX_BULAN] = {
    "Januari", "Februari", "Maret", "April",
    "Mei", "Juni", "Juli", "Agustus",
    "September", "Oktober", "November", "Desember"
};
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
    ofstream backupProduk("backup_produk.txt");
    ofstream backupTrx("backup_transaksi.txt");
    if (!backupUser.is_open() ||
        !backupProduk.is_open() ||
        !backupTrx.is_open()) {
        cout << "[!] Gagal membuka satu atau lebih file backup!" << endl;
        return;
    }

    for (int i = 0; i < jumlahUser; i++) {
        backupUser << daftarUser[i].getUsername() << "|"
                   << daftarUser[i].getPassword() << "|"
                   << daftarUser[i].getRole() << "\n";
    }
    for (int i = 0; i < jumlahProduk; i++) {
        backupProduk << daftarProduk[i].getIdProduk() << "|"
                     << daftarProduk[i].getNama() << "|"
                     << daftarProduk[i].getUkuran() << "|"
                     << daftarProduk[i].getHarga() << "|"
                     << daftarProduk[i].getStok() << "|"
                     << daftarProduk[i].getBahan() << "|"
                     << daftarProduk[i].getStatus() << "\n";
    }
    for (int i = 0; i < jumlahTransaksi; i++) {
        Transaksi trx = riwayatTransaksi[i];
        backupTrx << trx.getNoStruk() << "|"
                  << trx.getTanggal() << "|"
                  << trx.getKasir() << "|"
                  << trx.getNamaPembeli() << "|"
                  << trx.getTotalHarga() << "|"
                  << trx.getBayar() << "|"
                  << trx.getKembalian() << "|"
                  << trx.getJumlahItem() << "|"
                  << (trx.getSudahDiverifikasi() ? 1 : 0) << "|"
                  << trx.getStatusPengemasan() << "\n";
        for (int j = 0; j < trx.getJumlahItem(); j++) {
            ItemBelanja item = trx.getItem(j);
            backupTrx << item.idProduk << "|"
                      << item.namaProduk << "|"
                      << item.ukuran << "|"
                      << item.hargaSatuan << "|"
                      << item.qty << "|"
                      << item.subtotal << "\n";
        }
    }
    backupUser.close();
    backupProduk.close();
    backupTrx.close();
    if (!backupUser || !backupProduk || !backupTrx ||
        !daftarPelanggan.simpanKeFile("backup_pelanggan.txt")) {
        cout << "[!] Backup tidak berhasil disimpan sepenuhnya!" << endl;
        return;
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

void laporanRekapEntitas() {
    cout << "============================================================" << endl;
    cout << "             REKAP SELURUH KATEGORI DATA                   " << endl;
    cout << "============================================================" << endl;
    int jumlahKaryawan = 0;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].getRole() == "admin" ||
            daftarUser[i].getRole() == "kasir") {
            cout << "Karyawan " << daftarUser[i].getUsername()
                 << " (" << daftarUser[i].getRole() << ")" << endl;
            jumlahKaryawan++;
        }
    }
    cout << "Total karyawan: " << jumlahKaryawan << endl;

    cout << "\nDaftar pelanggan dan jumlah kunjungan:" << endl;
    daftarPelanggan.tampilSemuaPelanggan();

    cout << "\nRiwayat transaksi berdasarkan nomor struk:" << endl;
    long long totalPendapatan = 0;
    int pendapatanTerendah = 0;
    int pendapatanTertinggi = 0;
    for (int i = 0; i < jumlahTransaksi; i++) {
        int pendapatan = riwayatTransaksi[i].getTotalHarga();
        if (i == 0 || pendapatan < pendapatanTerendah) {
            pendapatanTerendah = pendapatan;
        }
        if (i == 0 || pendapatan > pendapatanTertinggi) {
            pendapatanTertinggi = pendapatan;
        }
        totalPendapatan += pendapatan;
        cout << riwayatTransaksi[i].getNoStruk() << "\t"
             << riwayatTransaksi[i].getTanggal() << "\tRp "
             << pendapatan << "\t"
             << (riwayatTransaksi[i].getSudahDiverifikasi()
                 ? "Terverifikasi" : "Menunggu verifikasi") << endl;
    }
    if (jumlahTransaksi > 0) {
        cout << "Pendapatan terendah : Rp " << pendapatanTerendah << endl;
        cout << "Pendapatan tertinggi: Rp " << pendapatanTertinggi << endl;
    } else {
        cout << "[!] Belum ada transaksi." << endl;
    }
    cout << "Total pendapatan     : Rp " << totalPendapatan << endl;

    cout << "\nDaftar produk:" << endl;
    for (int i = 0; i < jumlahProduk; i++) {
        cout << daftarProduk[i].getIdProduk() << "\t"
             << daftarProduk[i].getNama() << "\t"
             << daftarProduk[i].getUkuran() << "\tStok: "
             << daftarProduk[i].getStok() << endl;
    }
    if (jumlahProduk == 0) {
        cout << "[!] Belum ada produk." << endl;
    }
    cout << "============================================================" << endl;
}

// =====================================================
// LINKED LIST: LOG AKTIVITAS SISTEM
// (Praktikum 10 - Pointer & Linked List)
// =====================================================

void tambahLog(string aktivitas, string pengguna) {
    logSistem.tambahLog(aktivitas, pengguna, "Log");
}

// =====================================================
// LINKED LIST: PELANGGAN & LOYALITAS
// (Praktikum 10 - Pointer & Linked List)

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

static int tanggalKeAngka(string tanggal) {
    if (tanggal.length() != 10 ||
        tanggal[2] != '-' || tanggal[5] != '-') {
        return 0;
    }

    int nilai[3] = {0, 0, 0};
    const int posisi[] = {0, 3, 6};
    const int panjang[] = {2, 2, 4};
    for (int bagian = 0; bagian < 3; bagian++) {
        for (int i = 0; i < panjang[bagian]; i++) {
            char digit = tanggal[posisi[bagian] + i];
            if (digit < '0' || digit > '9') return 0;
            nilai[bagian] = nilai[bagian] * 10 + digit - '0';
        }
    }
    if (nilai[0] < 1 || nilai[0] > 31 ||
        nilai[1] < 1 || nilai[1] > 12) {
        return 0;
    }
    return nilai[2] * 10000 + nilai[1] * 100 + nilai[0];
}

void sortTransaksiByTanggal() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        for (int j = 0; j < jumlahTransaksi - i - 1; j++) {
            if (tanggalKeAngka(riwayatTransaksi[j].getTanggal()) >
                tanggalKeAngka(riwayatTransaksi[j + 1].getTanggal())) {
                Transaksi temp = riwayatTransaksi[j];
                riwayatTransaksi[j] = riwayatTransaksi[j + 1];
                riwayatTransaksi[j + 1] = temp;
            }
        }
    }
    cout << "[?] Transaksi diurutkan dari tanggal terlama." << endl;
}

void sortTransaksiByVerifikasi() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        for (int j = 0; j < jumlahTransaksi - i - 1; j++) {
            if (riwayatTransaksi[j].getSudahDiverifikasi() &&
                !riwayatTransaksi[j + 1].getSudahDiverifikasi()) {
                Transaksi temp = riwayatTransaksi[j];
                riwayatTransaksi[j] = riwayatTransaksi[j + 1];
                riwayatTransaksi[j + 1] = temp;
            }
        }
    }
    cout << "[?] Transaksi menunggu verifikasi ditampilkan lebih dahulu." << endl;
}

void verifikasiTransaksi(string noStruk, string pengguna) {
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (riwayatTransaksi[i].getNoStruk() == noStruk) {
            if (riwayatTransaksi[i].getSudahDiverifikasi()) {
                cout << "[!] Transaksi sudah diverifikasi." << endl;
                return;
            }
            riwayatTransaksi[i].setSudahDiverifikasi(true);
            fm.simpanTransaksi();
            logSistem.tambahLog("Verifikasi transaksi " + noStruk,
                                pengguna, "Log");
            cout << "[?] Transaksi berhasil diverifikasi." << endl;
            return;
        }
    }
    cout << "[!] Transaksi tidak ditemukan!" << endl;
}

// =====================================================
