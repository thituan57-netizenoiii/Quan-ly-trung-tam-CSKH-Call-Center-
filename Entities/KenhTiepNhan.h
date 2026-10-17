#pragma once
#include <string>
#include <vector>
#include "Entities/Entity.h"

using namespace std;

class KenhTiepNhan : public Entity {
private:
    string tenKenh;
    string loaiKenh;
    string dauSoDinhDanh;
    double cuocPhiPhut;
    string trangThai;

public:
    KenhTiepNhan();
    KenhTiepNhan(string ma, string ten, string loai, string dauSo, double cuoc, string tt);

    string getTenKenh() const;
    string getLoaiKenh() const;
    string getDauSoDinhDanh() const;
    double getCuocPhiPhut() const;
    string getTrangThai() const;

    void setId(const string& maMoi) override;
    void setTenKenh(const string& ten);
    void setLoaiKenh(const string& loai);
    void setDauSoDinhDanh(const string& dauSo);
    void setCuocPhiPhut(double cuoc);
    void setTrangThai(const string& tt);

    string toFileRecord() const override;
    void fromFileRecord(const string& line) override;
    vector<string> toRowCells() const override;

    bool operator<(const KenhTiepNhan& other) const;
    bool operator>(const KenhTiepNhan& other) const;
};