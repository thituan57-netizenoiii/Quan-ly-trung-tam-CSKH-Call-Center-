#include "Entities/KenhTiepNhan.h"

using namespace std;

KenhTiepNhan::KenhTiepNhan()
    : Entity(), tenKenh(""), loaiKenh("thoai"), dauSoDinhDanh(""), cuocPhiPhut(0.0), trangThai("hoat_dong") {}

KenhTiepNhan::KenhTiepNhan(string ma, string ten, string loai, string dauSo, double cuoc, string tt) {
    setId(ma);
    setTenKenh(ten);
    setLoaiKenh(loai);
    setDauSoDinhDanh(dauSo);
    setCuocPhiPhut(cuoc);
    setTrangThai(tt);
}

string KenhTiepNhan::getTenKenh() const { return tenKenh; }
string KenhTiepNhan::getLoaiKenh() const { return loaiKenh; }
string KenhTiepNhan::getDauSoDinhDanh() const { return dauSoDinhDanh; }
double KenhTiepNhan::getCuocPhiPhut() const { return cuocPhiPhut; }
string KenhTiepNhan::getTrangThai() const { return trangThai; }

void KenhTiepNhan::setId(const string& maMoi) {
    string s = Validator::toUpperText(Validator::cleanSpaces(maMoi));
    if (!Validator::checkCodeFormat(s, "KTN")) {
        throw DataInputException("Ma kenh phai co dinh dang KTNxxx (VD: KTN001)!");
    }
    this->id = s;
}

void KenhTiepNhan::setTenKenh(const string& ten) {
    string s = Validator::cleanSpaces(ten);
    if (!Validator::checkNonEmptyText(s, 100)) {
        throw DataInputException("Ten kenh khong duoc de trong va toi da 100 ky tu!");
    }
    this->tenKenh = s;
}

void KenhTiepNhan::setLoaiKenh(const string& loai) {
    string s = Validator::toLowerText(Validator::cleanSpaces(loai));
    if (s != "thoai" && s != "livechat" && s != "email" && s != "ung_dung") {
        throw DataInputException("Loai kenh phai thuoc: thoai, livechat, email, ung_dung!");
    }
    this->loaiKenh = s;
}

void KenhTiepNhan::setDauSoDinhDanh(const string& dauSo) {
    string s = Validator::cleanSpaces(dauSo);
    if (!Validator::checkNonEmptyText(s, 50)) {
        throw DataInputException("Dau so/Dinh danh khong duoc de trong va toi da 50 ky tu!");
    }
    this->dauSoDinhDanh = s;
}

void KenhTiepNhan::setCuocPhiPhut(double cuoc) {
    if (cuoc < 0.0) {
        throw DataInputException("Cuoc phi tren phut phai lon hon hoac bang 0!");
    }
    this->cuocPhiPhut = cuoc;
}

void KenhTiepNhan::setTrangThai(const string& tt) {
    string s = Validator::toLowerText(Validator::cleanSpaces(tt));
    if (s != "hoat_dong" && s != "bao_tri" && s != "ngung_hoat_dong") {
        throw DataInputException("Trang thai phai thuoc: hoat_dong, bao_tri, ngung_hoat_dong!");
    }
    this->trangThai = s;
}

string KenhTiepNhan::toFileRecord() const {
    return id + "|" + tenKenh + "|" + loaiKenh + "|" + dauSoDinhDanh + "|" +
           to_string(static_cast<long long>(cuocPhiPhut)) + "|" + trangThai;
}

void KenhTiepNhan::fromFileRecord(const string& line) {
    vector<string> tokens = Validator::splitRecord(line, '|');
    if (tokens.size() != 6) {
        throw FileStorageException("Dong du lieu KenhTiepNhan khong du 6 truong!");
    }
    setId(tokens[0]);
    setTenKenh(tokens[1]);
    setLoaiKenh(tokens[2]);
    setDauSoDinhDanh(tokens[3]);
    setCuocPhiPhut(Validator::toDouble(tokens[4]));
    setTrangThai(tokens[5]);
}

vector<string> KenhTiepNhan::toRowCells() const {
    return {
        id, tenKenh, loaiKenh, dauSoDinhDanh,
        to_string(static_cast<long long>(cuocPhiPhut)), trangThai
    };
}

bool KenhTiepNhan::operator<(const KenhTiepNhan& other) const {
    return this->cuocPhiPhut < other.cuocPhiPhut;
}

bool KenhTiepNhan::operator>(const KenhTiepNhan& other) const {
    return this->cuocPhiPhut > other.cuocPhiPhut;
}