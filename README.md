# TP KAOS - Aplikasi Terpisah

## File program

- `main.cpp`: menu dan entry point aplikasi.
- `BusinessLogic.cpp` / `BusinessLogic.h`: logika bisnis, laporan, dan fitur aplikasi.
- `DataLayer.cpp` / `DataLayer.h`: entitas dan penyimpanan data.

Empat file `data_*.txt` disediakan kosong dan akan diisi aplikasi saat data disimpan.

## Build

Tambahkan `main.cpp`, `BusinessLogic.cpp`, dan `DataLayer.cpp` ke proyek Console
Application dengan standar C++11 atau lebih baru. Jangan tambahkan `ver1.cpp`
bersama file tersebut karena `ver1.cpp` merupakan program lama dengan `main()`
sendiri.

Jika menggunakan MinGW:

```sh
g++ -std=c++11 main.cpp BusinessLogic.cpp DataLayer.cpp -o TP-KAOS
```

Jalankan program dari folder proyek agar file data `.txt` ditemukan.
