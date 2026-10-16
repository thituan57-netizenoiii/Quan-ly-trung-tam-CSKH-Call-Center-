// =========================================================================
// HOC VIEN CONG NGHE BUU CHINH VIEN THONG - KHOA VIEN THONG 1
// HOC PHAN: KY THUAT LAP TRINH
// DE TAI 4: QUAN LY TRUNG TAM CSKH (CALL CENTER) - NHOM 8
// Tich hop he thong: Lop Application va ham main()
// =========================================================================
#include <iostream>
#include "Repositories/Repository.h"
#include "Entities/KenhTiepNhan.h"
#include "Entities/CuocGoiTiepNhan.h"
#include "UseCases/KenhTiepNhanMenu.h"
#include "UseCases/CuocGoiTiepNhanMenu.h"
#include "Utils/InputHelper.h"

using namespace std;

// Lop Application khoi tao cac Repository va dieu phoi menu chinh (Bang 4 - Muc 3.4)
class Application {
private:
    Repository<KenhTiepNhan> repoKenh;
    Repository<CuocGoiTiepNhan> repoCuocGoi;

public:
    Application()
        : repoKenh("data/kenhtiepnhan.txt", "KTN"),
          repoCuocGoi("data/cuocgoi.txt", "CG") {}

    void run() {
        while (true) {
            InputHelper::clearConsole();
            cout << "==========================================================\n";
            cout << "      HE THONG QUAN LY TRUNG TAM CSKH - CALL CENTER       \n";
            cout << "                         NHOM 8                           \n";
            cout << "==========================================================\n";
            cout << "  1. Quan ly Nhom dich vu            (Nguyen Viet Chien)\n";
            cout << "  2. Quan ly Muc cam ket SLA         (Nguyen Viet Chien)\n";
            cout << "  3. Quan ly Kenh tiep nhan          (Tu Anh Duc)\n";
            cout << "  4. Quan ly Cuoc goi tiep nhan      (Tu Anh Duc)\n";
            cout << "  5. Quan ly Dien thoai vien         (Vu Xuan Thanh)\n";
            cout << "  6. Quan ly Ca truc                 (Vu Xuan Thanh)\n";
            cout << "  7. Quan ly Khach hang              (Ngo Cong Dat)\n";
            cout << "  8. Quan ly Phieu danh gia hai long (Ngo Cong Dat)\n";
            cout << "  9. Quan ly Ticket yeu cau          (Nguyen Le Minh)\n";
            cout << " 10. Quan ly Phieu chuyen xu ly      (Nguyen Le Minh)\n";
            cout << "----------------------------------------------------------\n";
            cout << "  0. Thoat chuong trinh\n";
            cout << "==========================================================\n";

            int luaChon = InputHelper::inputMenuOption(0, 10);
            if (luaChon == 0) {
                cout << "\nCam on ban da su dung Phan mem Quan ly Call Center - Nhom 8!\n";
                break;
            }

            switch (luaChon) {
                case 3: {
                    KenhTiepNhanMenu menuKenh(repoKenh, repoCuocGoi);
                    menuKenh.hienThiMenu();
                    break;
                }
                case 4: {
                    CuocGoiTiepNhanMenu menuCuocGoi(repoCuocGoi, repoKenh);
                    menuCuocGoi.hienThiMenu();
                    break;
                }
                default:
                    cout << "\n  [Thong bao] Phan he so " << luaChon
                         << " dang cho thanh vien phu trach ghep code!\n";
                    InputHelper::waitEnter();
                    break;
            }
        }
    }
};

int main() {
    try {
        Application app;
        app.run();
    } catch (const exception& e) {
        cout << "\n[Loi nghiem trong] " << e.what() << "\n";
    }
    return 0;
}