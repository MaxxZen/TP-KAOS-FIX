@echo off
setlocal

cd /d "%~dp0"
if errorlevel 1 (
    echo GAGAL: Tidak dapat membuka folder MainTest.
    exit /b 1
)

echo === Kompilasi aplikasi dari main.cpp dan dependensinya ===
g++ -std=c++17 -Wall -Wextra -pedantic -I "%~dp0.." "%~dp0..\main.cpp" "%~dp0..\BusinessLogic.cpp" "%~dp0..\DataLayer.cpp" -o "%~dp0test_main.exe"
if errorlevel 1 (
    echo GAGAL: Kompilasi tidak berhasil.
    exit /b 1
)

echo.
echo === Menjalankan aplikasi, login sebagai admin, lalu logout ===
type "%~dp0main_test_input.txt" | "%~dp0test_main.exe"
if errorlevel 1 (
    echo.
    echo HASIL: UJI JALAN GAGAL.
    exit /b 1
)

echo.
echo Uji jalan selesai. Pastikan tampilan MENU ADMIN dan pesan terima kasih muncul di atas.
echo File data uji berada di folder MainTest.
exit /b 0
