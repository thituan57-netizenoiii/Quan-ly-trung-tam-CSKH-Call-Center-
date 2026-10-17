#include "UseCases/CuocGoiTiepNhanMenu.h"
#include <iostream>
#include <algorithm>
#include "Utils/InputHelper.h"

using namespace std;

CuocGoiTiepNhanMenu::CuocGoiTiepNhanMenu(Repository<CuocGoiTiepNhan>& rCuocGoi, Repository<KenhTiepNhan>& rKenh)
    : repoCuocGoi(rCuocGoi), repoKenh(rKenh) {
    doRongCot = { 8, 8, 8, 8, 11, 7, 13, 28, 14 };
    tieuDeCot = { "Ma CG", "Ma KH", "Ma DTV", "Ma kenh", "Ngay goi", "Gio", "Thoi luong(s)", "Noi dung tom tat", "Trang thai" };
}

bool CuocGoiTiepNhanMenu::kiemTraKenhTonTai(const string& maKenh) const {
    return repoKenh.findById(maKenh) != nullptr;
}

void CuocGoiTiepNhanMenu::hienThiMenu() {
    while (true) {
        InputHelper::clearConsole();
        cout << "========== QUAN LY CUOC GOI TIEP NHAN ==========\n";
        cout << "  1. Them cuoc goi tiep nhan moi\n";
        cout << "  2. Xem danh sach cuoc goi tiep nhan\n";
        cout << "  3. Tim kiem cuoc goi tiep nhan\n";
        cout << "  4. Sap xep danh sach cuoc goi\n";
        cout << "  5. Cap nhat thong tin cuoc goi\n";
        cout << "  6. Xoa cuoc goi tiep nhan\n";
        cout << "  0. Quay lai menu chinh\n";
        cout << "================================================\n";

        int chon = InputHelper::inputMenuOption(0, 6);
        if (chon == 0) break;

        cout << "\n";
        try {
            switch (chon) {
                case 1: themCuocGoiMoi(); break;
                case 2: xemDanhSachCuocGoi(); break;
                case 3: timKiemCuocGoi(); break;
                case 4: sapXepDanhSach(); break;
                case 5: capNhatCuocGoi(); break;
                case 6: xoaCuocGoi(); break;
            }
        } catch (const exception& e) {
            cout << "  " << e.what() << "\n";
        }
        InputHelper::waitEnter();
    }
}

void CuocGoiTiepNhanMenu::themCuocGoiMoi() {
    cout << "--- 1. THEM CUOC GOI TIEP NHAN MOI ---\n";
    CuocGoiTiepNhan cgMoi;

    while (true) {
        string maGoiY = repoCuocGoi.nextAutoId();
        string maNhap = InputHelper::inputOptionalText("Nhap ma cuoc goi (CGxxx, Enter de dung ma " + maGoiY + "): ");
        if (maNhap.empty()) maNhap = maGoiY;
        try {
            cgMoi.setId(maNhap);
            if (repoCuocGoi.findById(cgMoi.getId()) != nullptr) {
                cout << "  [!] Ma cuoc goi '" << cgMoi.getId() << "' da ton tai! Vui long nhap lai.\n";
                continue;
            }
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        try {
            string maKenh = InputHelper::inputRequiredText("Nhap ma kenh tiep nhan (VD: KTN001): ");
            cgMoi.setMaKenh(maKenh);
            if (!kiemTraKenhTonTai(cgMoi.getMaKenh())) {
                cout << "  [!] Ma kenh '" << cgMoi.getMaKenh() << "' chua ton tai trong danh sach Kenh tiep nhan!\n";
                continue;
            }
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        try {
            cgMoi.setMaKhachHang(InputHelper::inputRequiredText("Nhap ma khach hang (VD: KH001): "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        try {
            cgMoi.setMaDienThoaiVien(InputHelper::inputRequiredText("Nhap ma dien thoai vien (VD: DTV001): "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    cgMoi.setNgayGoi(InputHelper::inputRequiredDate("Nhap ngay tiep nhan cuoc goi"));
    cgMoi.setGioBatDau(InputHelper::inputRequiredTime("Nhap gio bat dau cuoc goi"));

    while (true) {
        try {
            cgMoi.setThoiLuongGiay(InputHelper::inputInt("Nhap thoi luong cuoc goi (giay, > 0): "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        try {
            cgMoi.setNoiDungTomTat(InputHelper::inputRequiredText("Nhap noi dung tom tat cuoc goi: "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        cout << "Chon trang thai (1. hoan_tat | 2. chuyen_ticket | 3. nho_may): ";
        int tt = InputHelper::inputMenuOption(1, 3);
        if (tt == 1) cgMoi.setTrangThai("hoan_tat");
        else if (tt == 2) cgMoi.setTrangThai("chuyen_ticket");
        else cgMoi.setTrangThai("nho_may");
        break;
    }

    repoCuocGoi.addRecord(cgMoi);
    cout << "  [+] Them cuoc goi '" << cgMoi.getId() << "' va luu file data/cuocgoi.txt thanh cong!\n";
}

void CuocGoiTiepNhanMenu::xemDanhSachCuocGoi() {
    cout << "--- 2. DANH SACH CUOC GOI TIEP NHAN ---\n";
    Validator::renderTable(doRongCot, tieuDeCot, repoCuocGoi.getTableRows());

    long long tongGiay = 0;
    for (const auto& item : repoCuocGoi.getAll()) {
        tongGiay += item.getThoiLuongGiay();
    }
    cout << "  -> Tong thoi luong tiep nhan: " << tongGiay << " giay\n";
}

void CuocGoiTiepNhanMenu::timKiemCuocGoi() {
    cout << "--- 3. TIM KIEM CUOC GOI TIEP NHAN ---\n";
    cout << "  1. Tim chinh xac theo Ma cuoc goi\n";
    cout << "  2. Tim theo Ma kenh tiep nhan\n";
    cout << "  3. Tim theo Ma khach hang\n";
    cout << "  4. Tim gan dung theo Noi dung tom tat\n";
    cout << "  0. Quay lai\n";

    int chon = InputHelper::inputMenuOption(0, 4);
    if (chon == 0) return;

    const auto& ds = repoCuocGoi.getAll();
    vector<vector<string>> ketQua;

    if (chon == 1) {
        string ma = InputHelper::inputRequiredText("Nhap ma cuoc goi can tim (VD: CG001): ");
        CuocGoiTiepNhan* p = repoCuocGoi.findById(ma);
        if (p == nullptr) cout << "  [!] Khong tim thay cuoc goi co ma: " << ma << "\n";
        else Validator::renderSingleRecord(doRongCot, tieuDeCot, p->toRowCells());
        return;
    } else if (chon == 2) {
        string maKenh = Validator::toUpperText(InputHelper::inputRequiredText("Nhap ma kenh (VD: KTN001): "));
        for (const auto& item : ds) {
            if ( item.getMaKenh() == maKenh ) ketQua.push_back(item.toRowCells());
        }
    } else if (chon == 3) {
        string maKH = Validator::toUpperText(InputHelper::inputRequiredText("Nhap ma khach hang (VD: KH001): "));
        for (const auto& item : ds) {
            if ( item.getMaKhachHang() == maKH ) ketQua.push_back(item.toRowCells());
        }
    } else if (chon == 4) {
        string tuKhoa = InputHelper::inputRequiredText("Nhap tu khoa noi dung: ");
        for (const auto& item : ds) {
            if (Validator::matchKeyword(item.getNoiDungTomTat(), tuKhoa)) {
                ketQua.push_back(item.toRowCells());
            }
        }
    }

    Validator::renderTable(doRongCot, tieuDeCot, ketQua);
}

void CuocGoiTiepNhanMenu::sapXepDanhSach() {
    cout << "--- 4. SAP XEP DANH SACH CUOC GOI ---\n";
    cout << "  1. Theo Thoi luong goi tang dan\n";
    cout << "  2. Theo Thoi luong goi giam dan\n";
    cout << "  3. Theo Thoi gian goi moi nhat -> cu nhat\n";
    cout << "  0. Quay lai\n";

    int chon = InputHelper::inputMenuOption(0, 3);
    if (chon == 0) return;

    vector<CuocGoiTiepNhan> ds = repoCuocGoi.getAll();
    if (chon == 1) {
        sort(ds.begin(), ds.end());
    } else if (chon == 2) {
        sort(ds.begin(), ds.end(), greater<CuocGoiTiepNhan>());
    } else if (chon == 3) {
        sort(ds.begin(), ds.end(), [](const CuocGoiTiepNhan& a, const CuocGoiTiepNhan& b) {
            if (a.getNgayGoi() != b.getNgayGoi()) return a.getNgayGoi() > b.getNgayGoi();
            return a.getGioBatDau() > b.getGioBatDau();
        });
    }

    repoCuocGoi.updateSortedList(ds);
    cout << "  [+] Da sap xep va cap nhat file data/cuocgoi.txt!\n";
    Validator::renderTable(doRongCot, tieuDeCot, repoCuocGoi.getTableRows());
}

void CuocGoiTiepNhanMenu::capNhatCuocGoi() {
    cout << "--- 5. CAP NHAT THONG TIN CUOC GOI ---\n";
    string ma = InputHelper::inputRequiredText("Nhap ma cuoc goi can cap nhat (VD: CG001): ");
    CuocGoiTiepNhan* p = repoCuocGoi.findById(ma);
    if (p == nullptr) {
        cout << "  [!] Khong tim thay cuoc goi co ma: " << ma << "\n";
        return;
    }

    cout << "Thong tin hien tai:\n";
    Validator::renderSingleRecord(doRongCot, tieuDeCot, p->toRowCells());
    cout << "(Bo trong va nhan Enter de giu nguyen - Khong cho phep sua Ma cuoc goi)\n";

    CuocGoiTiepNhan banSao = *p;

    while (true) {
        string kenhMoi = InputHelper::inputOptionalText("Ma kenh moi [" + banSao.getMaKenh() + "]: ");
        if (kenhMoi.empty()) break;
        try {
            banSao.setMaKenh(kenhMoi);
            if (!kiemTraKenhTonTai(banSao.getMaKenh())) {
                cout << "  [!] Ma kenh '" << banSao.getMaKenh() << "' khong ton tai trong danh sach Kenh!\n";
                banSao.setMaKenh(p->getMaKenh());
                continue;
            }
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string khMoi = InputHelper::inputOptionalText("Ma khach hang moi [" + banSao.getMaKhachHang() + "]: ");
        if (khMoi.empty()) break;
        try { banSao.setMaKhachHang(khMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string dtvMoi = InputHelper::inputOptionalText("Ma DTV moi [" + banSao.getMaDienThoaiVien() + "]: ");
        if (dtvMoi.empty()) break;
        try { banSao.setMaDienThoaiVien(dtvMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string ngayStr = InputHelper::inputOptionalText("Ngay goi moi (dd/mm/yyyy) [" + banSao.getNgayGoi().sangChuoi() + "]: ");
        if (ngayStr.empty()) break;
        try { banSao.setNgayGoi(Date(ngayStr)); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string gioStr = InputHelper::inputOptionalText("Gio bat dau moi (hh:mm) [" + banSao.getGioBatDau().sangChuoi() + "]: ");
        if (gioStr.empty()) break;
        try { banSao.setGioBatDau(TimeSlot(gioStr)); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string tlStr = InputHelper::inputOptionalText("Thoi luong moi (giay) [" + to_string(banSao.getThoiLuongGiay()) + "]: ");
        if (tlStr.empty()) break;
        try { banSao.setThoiLuongGiay(Validator::toInt(tlStr)); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string ndMoi = InputHelper::inputOptionalText("Noi dung tom tat moi [" + banSao.getNoiDungTomTat() + "]: ");
        if (ndMoi.empty()) break;
        try { banSao.setNoiDungTomTat(ndMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string ttMoi = InputHelper::inputOptionalText("Trang thai moi (hoan_tat/chuyen_ticket/nho_may) [" + banSao.getTrangThai() + "]: ");
        if (ttMoi.empty()) break;
        try { banSao.setTrangThai(ttMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    repoCuocGoi.updateRecord(banSao);
    cout << "  [+] Cap nhat cuoc goi '" << banSao.getId() << "' va ghi file thanh cong!\n";
}

void CuocGoiTiepNhanMenu::xoaCuocGoi() {
    cout << "--- 6. XOA CUOC GOI TIEP NHAN ---\n";
    string ma = InputHelper::inputRequiredText("Nhap ma cuoc goi can xoa (VD: CG010): ");
    CuocGoiTiepNhan* p = repoCuocGoi.findById(ma);
    if (p == nullptr) {
        cout << "  [!] Khong tim thay cuoc goi co ma: " << ma << "\n";
        return;
    }

    cout << "Ban ghi tim thay:\n";
    Validator::renderSingleRecord(doRongCot, tieuDeCot, p->toRowCells());

    // Kiem tra rang buoc truoc khi xoa: Khong cho xoa neu cuoc goi da chuyen sang Ticket xu ly
    if (p->getTrangThai() == "chuyen_ticket") {
        cout << "  [!] KHONG CHO PHEP XOA: Cuoc goi '" << p->getId()
             << "' dang o trang thai 'chuyen_ticket' (lien ket voi Ticket yeu cau)!\n";
        return;
    }

    if (InputHelper::askConfirm("Ban co chac chan muon xoa cuoc goi nay?")) {
        repoCuocGoi.deleteById(p->getId());
        cout << "  [+] Da xoa cuoc goi va cap nhat file data/cuocgoi.txt!\n";
    } else {
        cout << "  [-] Da huy thao tac xoa.\n";
    }
}