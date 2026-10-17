#pragma once
#include <string>
#include <vector>
#include "Utils/Validator.h"

using namespace std;

class Entity {
protected:
    string id; // Ma dinh danh duy nhat

public:
    Entity() : id("") {}
    explicit Entity(const string& ma) { setId(ma); }
    virtual ~Entity() {}

    string getId() const { return id; }

    virtual void setId(const string& maMoi) {
        string cleaned = Validator::toUpperText(Validator::cleanSpaces(maMoi));
        if (!Validator::checkNonEmptyText(cleaned, 20)) {
            throw DataInputException("Ma dinh danh khong duoc de trong!");
        }
        this->id = cleaned;
    }

    // Cac ham thuan ao bat buoc lop dan xuat phai dinh nghia (Muc 3.1 & 3.4)
    virtual string toFileRecord() const = 0;
    virtual void fromFileRecord(const string& line) = 0;
    virtual vector<string> toRowCells() const = 0;
};