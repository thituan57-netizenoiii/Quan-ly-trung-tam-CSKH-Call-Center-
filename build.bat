@echo off
cd /d "%~dp0"
echo [NHOM 8] Dang bien dich ung dung Call Center...
g++ -std=c++17 -g main.cpp Entities/KenhTiepNhan.cpp Entities/CuocGoiTiepNhan.cpp UseCases/KenhTiepNhanMenu.cpp UseCases/CuocGoiTiepNhanMenu.cpp -I"%~dp0." -o Nhom8_CallCenter.exe
if %ERRORLEVEL% EQU 0 (
    echo [THANH CONG] Da tao file Nhom8_CallCenter.exe!
) else (
    echo [THAT BAI] Vui long kiem tra thong bao loi phia tren.
    pause
)