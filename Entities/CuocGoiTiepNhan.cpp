#include "Entities/CuocGoiTiepNhan.h"

using namespace std;

CuocGoiTiepNhan::CuocGoiTiepNhan()
    : Entity(), maKhachHang(""), maDienThoaiVien(""), maKenh(""),
      ngayGoi(), gioBatDau(), thoiLuongGiay(1), noiDungTomTat(""), trangThai("hoan_tat") {}

string CuocGoiTiepNhan::getMaKhachHang() const { return maKhachHang; }
string CuocGoiTiepNhan::getMaDienThoaiVien() const { return maDienThoaiVien; }
string CuocGoiTiepNhan::getMaKenh() const { return maKenh; }
Date CuocGoiTiepNhan::getNgayGoi() const { return ngayGoi; }
TimeSlot CuocGoiTiepNhan::getGioBatDau() const { return gioBatDau; }
int CuocGoiTiepNhan::getThoiLuongGiay() const { return thoiLuongGiay; }
string CuocGoiTiepNhan::getNoiDungTomTat() const { return noiDungTomTat; }
string CuocGoiTiepNhan::getTrangThai() const { return trangThai; }

void CuocGoiTiepNhan::setId(const string& maMoi) {
    string s = Validator::toUpperText(Validator::cleanSpaces(maMoi));
    if (!Validator::checkCodeFormat(s, "CG")) {
        throw DataInputException("Ma cuoc goi phai co dinh dang CGxxx (VD: CG001)!");
    }
    this->id = s;
}

void CuocGoiTiepNhan::setMaKhachHang(const string& maKH) {
    string s = Validator::toUpperText(Validator::cleanSpaces(maKH));
    if (!Validator::checkCodeFormat(s, "KH")) {
        throw DataInputException("Ma khach hang phai co dinh dang KHxxx (VD: KH001)!");
    }
    this->maKhachHang = s;
}

void CuocGoiTiepNhan::setMaDienThoaiVien(const string& maDTV) {
    string s = Validator::toUpperText(Validator::cleanSpaces(maDTV));
    if (!Validator::checkCodeFormat(s, "DTV")) {
        throw DataInputException("Ma dien thoai vien phai co dinh dang DTVxxx (VD: DTV001)!");
    }
    this->maDienThoaiVien = s;
}

void CuocGoiTiepNhan::setMaKenh(const string& kenh) {
    string s = Validator::toUpperText(Validator::cleanSpaces(kenh));
    if (!Validator::checkCodeFormat(s, "KTN")) {
        throw DataInputException("Ma kenh tiep nhan phai co dinh dang KTNxxx (VD: KTN001)!");
    }
    this->maKenh = s;
}

void CuocGoiTiepNhan::setNgayGoi(const Date& ngay) {
    if (ngay.dangRong()) {
        throw DataInputException("Ngay goi khong duoc de trong!");
    }
    this->ngayGoi = ngay;
}

void CuocGoiTiepNhan::setGioBatDau(const TimeSlot& gio) {
    if (gio.dangRong()) {
        throw DataInputException("Gio bat dau khong duoc de trong!");
    }
    this->gioBatDau = gio;
}

void CuocGoiTiepNhan::setThoiLuongGiay(int giay) {
    if (giay <= 0) {
        throw DataInputException("Thoi luong cuoc goi phai lon hon 0 giay!");
    }
    this->thoiLuongGiay = giay;
}

void CuocGoiTiepNhan::setNoiDungTomTat(const string& noiDung) {
    string s = Validator::cleanSpaces(noiDung);
    if (!Validator::checkNonEmptyText(s, 150)) {
        throw DataInputException("Noi dung tom tat khong duoc rong va toi da 150 ky tu!");
    }
    this->noiDungTomTat = s;
}

void CuocGoiTiepNhan::setTrangThai(const string& tt) {
    string s = Validator::toLowerText(Validator::cleanSpaces(tt));
    if (s != "hoan_tat" && s != "chuyen_ticket" && s != "nho_may") {
        throw DataInputException("Trang thai cuoc goi phai thuoc: hoan_tat, chuyen_ticket, nho_may!");
    }
    this->trangThai = s;
}

string CuocGoiTiepNhan::toFileRecord() const {
    return id + "|" + maKhachHang + "|" + maDienThoaiVien + "|" + maKenh + "|" +
           ngayGoi.sangChuoi() + "|" + gioBatDau.sangChuoi() + "|" +
           to_string(thoiLuongGiay) + "|" + noiDungTomTat + "|" + trangThai;
}

void CuocGoiTiepNhan::fromFileRecord(const string& line) {
    vector<string> tokens = Validator::splitRecord(line, '|');
    if (tokens.size() != 9) {
        throw FileStorageException("Dong du lieu CuocGoiTiepNhan khong du 9 truong!");
    }
    setId(tokens[0]);
    setMaKhachHang(tokens[1]);
    setMaDienThoaiVien(tokens[2]);
    setMaKenh(tokens[3]);
    setNgayGoi(Date(tokens[4]));
    setGioBatDau(TimeSlot(tokens[5]));
    setThoiLuongGiay(Validator::toInt(tokens[6]));
    setNoiDungTomTat(tokens[7]);
    setTrangThai(tokens[8]);
}

vector<string> CuocGoiTiepNhan::toRowCells() const {
    return {
        id, maKhachHang, maDienThoaiVien, maKenh,
        ngayGoi.sangChuoi(), gioBatDau.sangChuoi(),
        to_string(thoiLuongGiay), noiDungTomTat, trangThai
    };
}

bool CuocGoiTiepNhan::operator<(const CuocGoiTiepNhan& other) const {
    return this->thoiLuongGiay < other.thoiLuongGiay;
}

bool CuocGoiTiepNhan::operator>(const CuocGoiTiepNhan& other) const {
    return this->thoiLuongGiay > other.thoiLuongGiay;
}