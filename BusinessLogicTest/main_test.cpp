#include "BusinessLogic.h"

void headerMenu(string) {}

bool konfirmasi(string) {
    return false;
}

bool cek(bool kondisi, string namaUji) {
    cout << (kondisi ? "[BERHASIL] " : "[GAGAL] ") << namaUji << endl;
    return kondisi;
}

int main() {
    cout << "=== PENGUJIAN BUSINESS LOGIC ===" << endl;

    jumlahProduk = 3;
    daftarProduk[0] = Produk("P02", "Kaos Beta", "M", 20000, 3, "Katun");
    daftarProduk[1] = Produk("P01", "Kaos Alpha", "S", 10000, 8, "Katun");
    daftarProduk[2] = Produk("P03", "Kaos Gamma", "M", 30000, 2, "Katun");

    if (!cek(hitungProdukStokMenipisRekursif(0) == 2,
             "Perhitungan rekursif produk stok menipis")) {
        return 1;
    }
    if (!cek(cariStokMinRekursif(1, 0) == 2,
             "Pencarian rekursif indeks stok minimum")) {
        return 2;
    }
    if (!cek(cariHargaMaxRekursif(1, 0) == 2,
             "Pencarian rekursif indeks harga maksimum")) {
        return 3;
    }

    insertionSortProdukByNama();
    if (!cek(daftarProduk[0].getNama() == "Kaos Alpha" &&
                 daftarProduk[1].getNama() == "Kaos Beta" &&
                 daftarProduk[2].getNama() == "Kaos Gamma",
             "Insertion sort nama produk A-Z")) {
        return 4;
    }

    selectionSortProdukHargaDesc();
    if (!cek(daftarProduk[0].getHarga() == 30000 &&
                 daftarProduk[1].getHarga() == 20000 &&
                 daftarProduk[2].getHarga() == 10000,
             "Selection sort harga tertinggi ke terendah")) {
        return 5;
    }

    sortProdukByHarga();
    if (!cek(binarySearchHarga(20000) >= 0,
             "Binary search harga pada data terurut")) {
        return 6;
    }

    jumlahTransaksi = 0;
    Transaksi transaksi("kasir-uji", "08/11/2026", "TRX-UJI-01");
    transaksi.tambahItem("P02", "Kaos Beta", "M", 20000, 2);
    transaksi.tambahItem("P03", "Kaos Gamma", "XL", 30000, 1);
    riwayatTransaksi[jumlahTransaksi++] = transaksi;

    bangunMatriksPenjualan();
    if (!cek(matriksPenjualan[10][1] == 2 &&
                 matriksPenjualan[10][3] == 1,
             "Matriks penjualan berdasarkan bulan dan ukuran")) {
        return 7;
    }
    if (!cek(hitungTotalItemTerjualRekursif(0) == 2,
             "Perhitungan rekursif jumlah item transaksi")) {
        return 8;
    }

    noStrukCounter = 1;
    if (!cek(generateNoStruk() == "TRX001",
             "Pembuatan nomor struk")) {
        return 9;
    }

    cout << endl << "PENGUJIAN BUSINESS LOGIC BERHASIL." << endl;
    return 0;
}
