#pragma once
#include <vector>
#include <string>
#include "Repositories/Repository.h"
#include "Entities/KenhTiepNhan.h"
#include "Entities/CuocGoiTiepNhan.h"

using namespace std;

class KenhTiepNhanMenu {
private:
    Repository<KenhTiepNhan>& repoKenh;
    Repository<CuocGoiTiepNhan>& repoCuocGoi;

    vector<int> doRongCot;
    vector<string> tieuDeCot;

    void themKenhMoi();
    void xemDanhSachKenh();
    void timKiemKenh();
    void sapXepDanhSach();
    void capNhatKenh();
    void xoaKenh();

    bool kiemTraRangBuocTruocKhiXoa(const string& maKenh) const;

public:
    KenhTiepNhanMenu(Repository<KenhTiepNhan>& rKenh, Repository<CuocGoiTiepNhan>& rCuocGoi);
    void hienThiMenu();
};