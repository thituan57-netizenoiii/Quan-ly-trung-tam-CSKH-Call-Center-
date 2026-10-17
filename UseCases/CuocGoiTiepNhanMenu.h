#pragma once
#include <vector>
#include <string>
#include "Repositories/Repository.h"
#include "Entities/CuocGoiTiepNhan.h"
#include "Entities/KenhTiepNhan.h"

using namespace std;

class CuocGoiTiepNhanMenu {
private:
    Repository<CuocGoiTiepNhan>& repoCuocGoi;
    Repository<KenhTiepNhan>& repoKenh;

    vector<int> doRongCot;
    vector<string> tieuDeCot;

    void themCuocGoiMoi();
    void xemDanhSachCuocGoi();
    void timKiemCuocGoi();
    void sapXepDanhSach();
    void capNhatCuocGoi();
    void xoaCuocGoi();

    bool kiemTraKenhTonTai(const string& maKenh) const;

public:
    CuocGoiTiepNhanMenu(Repository<CuocGoiTiepNhan>& rCuocGoi, Repository<KenhTiepNhan>& rKenh);
    void hienThiMenu();
};