@echo off
setlocal

cd /d "%~dp0"
if errorlevel 1 (
    echo GAGAL: Tidak dapat membuka folder DataLayerTest.
    exit /b 1
)

echo === Kompilasi DataLayer.cpp dan main_test.cpp ===
g++ -std=c++17 -Wall -Wextra -pedantic -I "%~dp0.." "%~dp0..\DataLayer.cpp" "%~dp0main_test.cpp" -o "%~dp0test_data.exe"
if errorlevel 1 (
    echo GAGAL: Kompilasi tidak berhasil.
    exit /b 1
)

echo.
echo === Menjalankan pengujian ===
"%~dp0test_data.exe"
if errorlevel 1 (
    echo.
    echo HASIL: PENGUJIAN GAGAL.
    exit /b 1
)

echo.
echo HASIL: PENGUJIAN BERHASIL.
echo File data uji berada di folder DataLayerTest.
exit /b 0
