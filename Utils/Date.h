#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cctype>

using namespace std;

// Lop ngoai le tu dinh nghia cho loi nhap lieu va rang buoc (Muc 3.1)
class DataInputException : public invalid_argument {
public:
    explicit DataInputException(const string& message)
        : invalid_argument("[Loi du lieu] " + message) {}
};

// Lop ngoai le tu dinh nghia cho loi doc/ghi file (Muc 3.1)
class FileStorageException : public runtime_error {
public:
    explicit FileStorageException(const string& message)
        : runtime_error("[Loi luu tru] " + message) {}
};

// Lop quan ly Ngay thang nam (dd/mm/yyyy)
class Date {
private:
    int ngay;
    int thang;
    int nam;

public:
    Date() : ngay(0), thang(0), nam(0) {}

    Date(int d, int m, int y) {
        ganNgayThangNam(d, m, y);
    }

    explicit Date(const string& chuoiNgay) {
        docTuChuoi(chuoiNgay);
    }

    static bool laNamNhuan(int y) {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }

    static int soNgayTrongThang(int m, int y) {
        if (m < 1 || m > 12) return 0;
        const int bangNgay[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (m == 2 && laNamNhuan(y)) return 29;
        return bangNgay[m];
    }

    static bool hopLe(int d, int m, int y) {
        if (y < 1900 || y > 2026) return false;
        if (m < 1 || m > 12) return false;
        return (d >= 1 && d <= soNgayTrongThang(m, y));
    }

    void ganNgayThangNam(int d, int m, int y) {
        if (!hopLe(d, m, y)) {
            throw DataInputException("Ngay thang nam khong hop le (nam tu 1900 den 2026)!");
        }
        ngay = d;
        thang = m;
        nam = y;
    }

    void docTuChuoi(const string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            ngay = thang = nam = 0;
            return;
        }
        string s = str.substr(first, str.find_last_not_of(" \t\r\n") - first + 1);
        if (s == "NONE") {
            ngay = thang = nam = 0;
            return;
        }
        if (s.length() != 10 || s[2] != '/' || s[5] != '/') {
            throw DataInputException("Ngay phai dung dinh dang dd/mm/yyyy (VD: 16/10/2026)!");
        }
        for (size_t i = 0; i < 10; ++i) {
            if (i == 2 || i == 5) continue;
            if (!isdigit(static_cast<unsigned char>(s[i]))) {
                throw DataInputException("Ngay thang nam chi duoc chua chu so!");
            }
        }
        int d = stoi(s.substr(0, 2));
        int m = stoi(s.substr(3, 2));
        int y = stoi(s.substr(6, 4));
        ganNgayThangNam(d, m, y);
    }

    bool dangRong() const { return (ngay == 0 || thang == 0 || nam == 0); }

    string sangChuoi() const {
        if (dangRong()) return "NONE";
        ostringstream oss;
        oss << setfill('0') << setw(2) << ngay << "/"
            << setfill('0') << setw(2) << thang << "/"
            << setw(4) << nam;
        return oss.str();
    }

    bool operator==(const Date& o) const {
        return ngay == o.ngay && thang == o.thang && nam == o.nam;
    }
    bool operator!=(const Date& o) const { return !(*this == o); }
    bool operator<(const Date& o) const {
        if (nam != o.nam) return nam < o.nam;
        if (thang != o.thang) return thang < o.thang;
        return ngay < o.ngay;
    }
    bool operator>(const Date& o) const { return o < *this; }
};

// Lop quan ly Gio phut (hh:mm)
class TimeSlot {
private:
    int gio;
    int phut;

public:
    TimeSlot() : gio(-1), phut(-1) {}

    TimeSlot(int h, int m) { ganGioPhut(h, m); }

    explicit TimeSlot(const string& str) { docTuChuoi(str); }

    void ganGioPhut(int h, int m) {
        if (h < 0 || h > 23 || m < 0 || m > 59) {
            throw DataInputException("Thoi gian khong hop le (Gio: 00-23, Phut: 00-59)!");
        }
        gio = h;
        phut = m;
    }

    void docTuChuoi(const string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            gio = phut = -1;
            return;
        }
        string s = str.substr(first, str.find_last_not_of(" \t\r\n") - first + 1);
        if (s.length() != 5 || s[2] != ':') {
            throw DataInputException("Gio phai dung dinh dang hh:mm (VD: 08:30)!");
        }
        if (!isdigit(static_cast<unsigned char>(s[0])) || !isdigit(static_cast<unsigned char>(s[1])) ||
            !isdigit(static_cast<unsigned char>(s[3])) || !isdigit(static_cast<unsigned char>(s[4]))) {
            throw DataInputException("Gio phut chi duoc chua chu so!");
        }
        ganGioPhut(stoi(s.substr(0, 2)), stoi(s.substr(3, 2)));
    }

    bool dangRong() const { return (gio < 0 || phut < 0); }

    int tongSoPhut() const { return dangRong() ? 0 : (gio * 60 + phut); }

    string sangChuoi() const {
        if (dangRong()) return "00:00";
        ostringstream oss;
        oss << setfill('0') << setw(2) << gio << ":" << setfill('0') << setw(2) << phut;
        return oss.str();
    }

    bool operator<(const TimeSlot& o) const { return tongSoPhut() < o.tongSoPhut(); }
    bool operator>(const TimeSlot& o) const { return tongSoPhut() > o.tongSoPhut(); }
};