@echo off
setlocal

cd /d "%~dp0"
if errorlevel 1 (
    echo GAGAL: Tidak dapat membuka folder BusinessLogicTest.
    exit /b 1
)

echo === Kompilasi BusinessLogic.cpp beserta dependensi DataLayer.cpp ===
g++ -std=c++17 -Wall -Wextra -pedantic -I "%~dp0.." "%~dp0..\BusinessLogic.cpp" "%~dp0..\DataLayer.cpp" "%~dp0main_test.cpp" -o "%~dp0test_business_logic.exe"
if errorlevel 1 (
    echo GAGAL: Kompilasi tidak berhasil.
    exit /b 1
)

echo.
echo === Menjalankan pengujian Business Logic ===
"%~dp0test_business_logic.exe"
if errorlevel 1 (
    echo.
    echo HASIL: PENGUJIAN GAGAL.
    exit /b 1
)

echo.
echo HASIL: PENGUJIAN BERHASIL.
exit /b 0
