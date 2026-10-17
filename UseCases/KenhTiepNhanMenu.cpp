#include "UseCases/KenhTiepNhanMenu.h"
#include <iostream>
#include <algorithm>
#include "Utils/InputHelper.h"

using namespace std;

KenhTiepNhanMenu::KenhTiepNhanMenu(Repository<KenhTiepNhan>& rKenh, Repository<CuocGoiTiepNhan>& rCuocGoi)
    : repoKenh(rKenh), repoCuocGoi(rCuocGoi) {
    doRongCot = { 10, 26, 12, 16, 15, 16 };
    tieuDeCot = { "Ma kenh", "Ten kenh tiep nhan", "Loai kenh", "Dau so/Dinh danh", "Cuoc/phut(VND)", "Trang thai" };
}

bool KenhTiepNhanMenu::kiemTraRangBuocTruocKhiXoa(const string& maKenh) const {
    string key = Validator::toUpperText(Validator::cleanSpaces(maKenh));
    const auto& dsCuocGoi = repoCuocGoi.getAll();
    return any_of(dsCuocGoi.begin(), dsCuocGoi.end(), [&](const CuocGoiTiepNhan& cg) {
        return Validator::toUpperText(cg.getMaKenh()) == key;
    });
}

void KenhTiepNhanMenu::hienThiMenu() {
    while (true) {
        InputHelper::clearConsole();
        cout << "============ QUAN LY KENH TIEP NHAN ============\n";
        cout << "  1. Them kenh tiep nhan moi\n";
        cout << "  2. Xem danh sach kenh tiep nhan\n";
        cout << "  3. Tim kiem kenh tiep nhan\n";
        cout << "  4. Sap xep danh sach kenh\n";
        cout << "  5. Cap nhat thong tin kenh\n";
        cout << "  6. Xoa kenh tiep nhan\n";
        cout << "  0. Quay lai menu chinh\n";
        cout << "================================================\n";

        int chon = InputHelper::inputMenuOption(0, 6);
        if (chon == 0) break;

        cout << "\n";
        try {
            switch (chon) {
                case 1: themKenhMoi(); break;
                case 2: xemDanhSachKenh(); break;
                case 3: timKiemKenh(); break;
                case 4: sapXepDanhSach(); break;
                case 5: capNhatKenh(); break;
                case 6: xoaKenh(); break;
            }
        } catch (const exception& e) {
            cout << "  " << e.what() << "\n";
        }
        InputHelper::waitEnter();
    }
}

void KenhTiepNhanMenu::themKenhMoi() {
    cout << "--- 1. THEM KENH TIEP NHAN MOI ---\n";
    KenhTiepNhan kenhMoi;

    while (true) {
        string maGoiY = repoKenh.nextAutoId();
        string maNhap = InputHelper::inputOptionalText("Nhap ma kenh (KTNxxx, Enter de dung ma " + maGoiY + "): ");
        if (maNhap.empty()) maNhap = maGoiY;
        try {
            kenhMoi.setId(maNhap);
            if (repoKenh.findById(kenhMoi.getId()) != nullptr) {
                cout << "  [!] Ma kenh '" << kenhMoi.getId() << "' da ton tai! Vui long nhap lai.\n";
                continue;
            }
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        try {
            kenhMoi.setTenKenh(InputHelper::inputRequiredText("Nhap ten kenh tiep nhan: "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        cout << "Chon loai kenh (1. thoai | 2. livechat | 3. email | 4. ung_dung): ";
        int loai = InputHelper::inputMenuOption(1, 4);
        if (loai == 1) kenhMoi.setLoaiKenh("thoai");
        else if (loai == 2) kenhMoi.setLoaiKenh("livechat");
        else if (loai == 3) kenhMoi.setLoaiKenh("email");
        else kenhMoi.setLoaiKenh("ung_dung");
        break;
    }

    while (true) {
        try {
            kenhMoi.setDauSoDinhDanh(InputHelper::inputRequiredText("Nhap dau so hoac ma dinh danh (VD: 18001166): "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        try {
            kenhMoi.setCuocPhiPhut(InputHelper::inputDouble("Nhap cuoc phi/phut (VND, >= 0): "));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        cout << "Chon trang thai (1. hoat_dong | 2. bao_tri | 3. ngung_hoat_dong): ";
        int tt = InputHelper::inputMenuOption(1, 3);
        if (tt == 1) kenhMoi.setTrangThai("hoat_dong");
        else if (tt == 2) kenhMoi.setTrangThai("bao_tri");
        else kenhMoi.setTrangThai("ngung_hoat_dong");
        break;
    }

    repoKenh.addRecord(kenhMoi);
    cout << "  [+] Them kenh '" << kenhMoi.getId() << "' va luu file data/kenhtiepnhan.txt thanh cong!\n";
}

void KenhTiepNhanMenu::xemDanhSachKenh() {
    cout << "--- 2. DANH SACH KENH TIEP NHAN ---\n";
    Validator::renderTable(doRongCot, tieuDeCot, repoKenh.getTableRows());
}

void KenhTiepNhanMenu::timKiemKenh() {
    cout << "--- 3. TIM KIEM KENH TIEP NHAN ---\n";
    cout << "  1. Tim chinh xac theo Ma kenh\n";
    cout << "  2. Tim gan dung theo Ten kenh (khong phan biet hoa thuong)\n";
    cout << "  3. Tim theo Khoang cuoc phi/phut\n";
    cout << "  0. Quay lai\n";

    int chon = InputHelper::inputMenuOption(0, 3);
    if (chon == 0) return;

    const auto& ds = repoKenh.getAll();
    vector<vector<string>> ketQua;

    if (chon == 1) {
        string ma = InputHelper::inputRequiredText("Nhap ma kenh can tim (VD: KTN001): ");
        KenhTiepNhan* p = repoKenh.findById(ma);
        if (p == nullptr) cout << "  [!] Khong tim thay kenh co ma: " << ma << "\n";
        else Validator::renderSingleRecord(doRongCot, tieuDeCot, p->toRowCells());
        return;
    } else if (chon == 2) {
        string tuKhoa = InputHelper::inputRequiredText("Nhap tu khoa ten kenh: ");
        for (const auto& item : ds) {
            if (Validator::matchKeyword(item.getTenKenh(), tuKhoa)) {
                ketQua.push_back(item.toRowCells());
            }
        }
    } else if (chon == 3) {
        double tuGia = InputHelper::inputDouble("Nhap muc cuoc toi thieu (VND): ");
        double denGia = InputHelper::inputDouble("Nhap muc cuoc toi da (VND): ");
        for (const auto& item : ds) {
            if (item.getCuocPhiPhut() >= tuGia && item.getCuocPhiPhut() <= denGia) {
                ketQua.push_back(item.toRowCells());
            }
        }
    }

    Validator::renderTable(doRongCot, tieuDeCot, ketQua);
}

void KenhTiepNhanMenu::sapXepDanhSach() {
    cout << "--- 4. SAP XEP DANH SACH KENH TIEP NHAN ---\n";
    cout << "  1. Theo Ten kenh A -> Z\n";
    cout << "  2. Theo Cuoc phi/phut tang dan\n";
    cout << "  3. Theo Cuoc phi/phut giam dan\n";
    cout << "  0. Quay lai\n";

    int chon = InputHelper::inputMenuOption(0, 3);
    if (chon == 0) return;

    vector<KenhTiepNhan> ds = repoKenh.getAll();
    if (chon == 1) {
        sort(ds.begin(), ds.end(), [](const KenhTiepNhan& a, const KenhTiepNhan& b) {
            return Validator::toLowerText(a.getTenKenh()) < Validator::toLowerText(b.getTenKenh());
        });
    } else if (chon == 2) {
        sort(ds.begin(), ds.end());
    } else if (chon == 3) {
        sort(ds.begin(), ds.end(), greater<KenhTiepNhan>());
    }

    repoKenh.updateSortedList(ds);
    cout << "  [+] Da sap xep va cap nhat file data/kenhtiepnhan.txt!\n";
    Validator::renderTable(doRongCot, tieuDeCot, repoKenh.getTableRows());
}

void KenhTiepNhanMenu::capNhatKenh() {
    cout << "--- 5. CAP NHAT THONG TIN KENH TIEP NHAN ---\n";
    string ma = InputHelper::inputRequiredText("Nhap ma kenh can cap nhat (VD: KTN001): ");
    KenhTiepNhan* p = repoKenh.findById(ma);
    if (p == nullptr) {
        cout << "  [!] Khong tim thay kenh co ma: " << ma << "\n";
        return;
    }

    cout << "Thong tin hien tai:\n";
    Validator::renderSingleRecord(doRongCot, tieuDeCot, p->toRowCells());
    cout << "(Bo trong va nhan Enter de giu nguyen - Khong cho phep sua Ma kenh)\n";

    // Tao ban sao tam de dam bao an toan trang thai bo nho neu nhap sai
    KenhTiepNhan banSao = *p;

    while (true) {
        string tenMoi = InputHelper::inputOptionalText("Ten kenh moi [" + banSao.getTenKenh() + "]: ");
        if (tenMoi.empty()) break;
        try { banSao.setTenKenh(tenMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string loaiMoi = InputHelper::inputOptionalText("Loai kenh moi (thoai/livechat/email/ung_dung) [" + banSao.getLoaiKenh() + "]: ");
        if (loaiMoi.empty()) break;
        try { banSao.setLoaiKenh(loaiMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string dauSoMoi = InputHelper::inputOptionalText("Dau so/Dinh danh moi [" + banSao.getDauSoDinhDanh() + "]: ");
        if (dauSoMoi.empty()) break;
        try { banSao.setDauSoDinhDanh(dauSoMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string cuocStr = InputHelper::inputOptionalText("Cuoc phi/phut moi [" + to_string(static_cast<long long>(banSao.getCuocPhiPhut())) + "]: ");
        if (cuocStr.empty()) break;
        try {
            banSao.setCuocPhiPhut(Validator::toDouble(cuocStr));
            break;
        } catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    while (true) {
        string ttMoi = InputHelper::inputOptionalText("Trang thai moi (hoat_dong/bao_tri/ngung_hoat_dong) [" + banSao.getTrangThai() + "]: ");
        if (ttMoi.empty()) break;
        try { banSao.setTrangThai(ttMoi); break; }
        catch (const exception& e) { cout << "  " << e.what() << "\n"; }
    }

    repoKenh.updateRecord(banSao);
    cout << "  [+] Cap nhat kenh '" << banSao.getId() << "' va ghi file thanh cong!\n";
}

void KenhTiepNhanMenu::xoaKenh() {
    cout << "--- 6. XOA KENH TIEP NHAN ---\n";
    string ma = InputHelper::inputRequiredText("Nhap ma kenh can xoa (VD: KTN010): ");
    KenhTiepNhan* p = repoKenh.findById(ma);
    if (p == nullptr) {
        cout << "  [!] Khong tim thay kenh co ma: " << ma << "\n";
        return;
    }

    cout << "Ban ghi tim thay:\n";
    Validator::renderSingleRecord(doRongCot, tieuDeCot, p->toRowCells());

    if (kiemTraRangBuocTruocKhiXoa(p->getId())) {
        cout << "  [!] KHONG CHO PHEP XOA: Kenh '" << p->getId()
             << "' dang duoc tham chieu trong danh sach Cuoc goi tiep nhan!\n";
        return;
    }

    if (InputHelper::askConfirm("Ban co chac chan muon xoa kenh tiep nhan nay?")) {
        repoKenh.deleteById(p->getId());
        cout << "  [+] Da xoa kenh va cap nhat file data/kenhtiepnhan.txt!\n";
    } else {
        cout << "  [-] Da huy thao tac xoa.\n";
    }
}