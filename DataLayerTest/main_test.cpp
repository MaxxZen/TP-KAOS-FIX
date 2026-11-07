#include "DataLayer.h"

int main() {
    cout << "=== UJI DATA LAYER: PENGGUNA ===" << endl;
    tambahUser("ujiuser", "pass123", "admin");
    fm.simpanUser();
    jumlahUser = 0;
    fm.bacaUser();
    if (loginUser("ujiuser", "pass123") < 0) {
        cout << "GAGAL: simpan dan baca pengguna." << endl;
        return 1;
    }
    cout << "BERHASIL: pengguna tersimpan dan terbaca." << endl;

    cout << endl << "=== UJI DATA LAYER: PRODUK ===" << endl;
    tambahProduk("UJI01", "Produk Uji", "M", 10000, 5, "Katun");
    fm.simpanProduk();
    jumlahProduk = 0;
    fm.bacaProduk();
    int indexProduk = cariProdukById("UJI01");
    if (indexProduk < 0 ||
        daftarProduk[indexProduk].getNama() != "Produk Uji" ||
        daftarProduk[indexProduk].getStok() != 5) {
        cout << "GAGAL: simpan dan baca produk." << endl;
        return 2;
    }
    cout << "BERHASIL: produk tersimpan dan terbaca." << endl;

    cout << endl << "=== UJI DATA LAYER: TRANSAKSI ===" << endl;
    Transaksi transaksi("ujiuser", "2026-11-08", "TRX-UJI-01");
    transaksi.setNamaPembeli("Pembeli Uji");
    transaksi.setSudahDiverifikasi(true);
    transaksi.setStatusPengemasan("Sudah Dikemas");
    if (!transaksi.tambahItem("UJI01", "Produk Uji", "M", 10000, 2)) {
        cout << "GAGAL: menambahkan item transaksi." << endl;
        return 3;
    }
    transaksi.setBayar(25000);
    simpanRiwayat(transaksi);
    fm.simpanTransaksi();
    jumlahTransaksi = 0;
    fm.bacaTransaksi();
    if (jumlahTransaksi != 1 ||
        riwayatTransaksi[0].getTotalHarga() != 20000 ||
        riwayatTransaksi[0].getBayar() != 25000 ||
        riwayatTransaksi[0].getKembalian() != 5000 ||
        riwayatTransaksi[0].getJumlahItem() != 1 ||
        riwayatTransaksi[0].getItem(0).subtotal != 20000 ||
        !riwayatTransaksi[0].getSudahDiverifikasi() ||
        riwayatTransaksi[0].getStatusPengemasan() != "Sudah Dikemas") {
        cout << "GAGAL: simpan dan baca transaksi." << endl;
        return 4;
    }
    cout << "BERHASIL: transaksi dan item tersimpan dan terbaca." << endl;

    cout << endl << "PENGUJIAN DATA LAYER BERHASIL." << endl;
    cout << "File data pengujian tersimpan di folder DataLayerTest." << endl;
    return 0;
}
