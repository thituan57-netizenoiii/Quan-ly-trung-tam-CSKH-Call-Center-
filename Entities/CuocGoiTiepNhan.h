#pragma once
#include <string>
#include <vector>
#include "Utils/Date.h"
#include "Entities/Entity.h"

using namespace std;

class CuocGoiTiepNhan : public Entity {
private:
    string maKhachHang;
    string maDienThoaiVien;
    string maKenh;
    Date ngayGoi;
    TimeSlot gioBatDau;
    int thoiLuongGiay;
    string noiDungTomTat;
    string trangThai;

public:
    CuocGoiTiepNhan();

    string getMaKhachHang() const;
    string getMaDienThoaiVien() const;
    string getMaKenh() const;
    Date getNgayGoi() const;
    TimeSlot getGioBatDau() const;
    int getThoiLuongGiay() const;
    string getNoiDungTomTat() const;
    string getTrangThai() const;

    void setId(const string& maMoi) override;
    void setMaKhachHang(const string& maKH);
    void setMaDienThoaiVien(const string& maDTV);
    void setMaKenh(const string& kenh);
    void setNgayGoi(const Date& ngay);
    void setGioBatDau(const TimeSlot& gio);
    void setThoiLuongGiay(int giay);
    void setNoiDungTomTat(const string& noiDung);
    void setTrangThai(const string& tt);

    string toFileRecord() const override;
    void fromFileRecord(const string& line) override;
    vector<string> toRowCells() const override;

    bool operator<(const CuocGoiTiepNhan& other) const;
    bool operator>(const CuocGoiTiepNhan& other) const;
};