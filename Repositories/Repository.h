#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Utils/Validator.h"

using namespace std;

template <typename T>
class Repository {
private:
    vector<T> records;
    string dataFilePath;
    string codePrefix;

public:
    Repository(const string& path, const string& prefix = "")
        : dataFilePath(path), codePrefix(prefix) {
        loadFile();
    }

    virtual ~Repository() {}

    // Sinh ma goi y tiep theo (VD: KTN011, CG011)
    string nextAutoId() const {
        int maxIndex = 0;
        for (const auto& rec : records) {
            string curId = rec.getId();
            if (curId.find(codePrefix) == 0 && curId.length() > codePrefix.length()) {
                try {
                    int num = stoi(curId.substr(codePrefix.length()));
                    if (num > maxIndex) maxIndex = num;
                } catch (...) {}
            }
        }
        ostringstream oss;
        oss << codePrefix << setfill('0') << setw(3) << (maxIndex + 1);
        return oss.str();
    }

    // Nap toan bo du lieu tu file khi khoi dong (Muc 3.2)
    void loadFile() {
        records.clear();
        ifstream inFile(dataFilePath);
        if (!inFile.is_open()) {
            // Tu tao file rong neu chua ton tai
            ofstream createEmpty(dataFilePath);
            createEmpty.close();
            return;
        }

        string line;
        int rowIndex = 0;
        while (getline(inFile, line)) {
            rowIndex++;
            line = Validator::cleanSpaces(line);
            if (line.empty() || line[0] == '#') continue;

            try {
                T item;
                item.fromFileRecord(line);
                if (findById(item.getId()) == nullptr) {
                    records.push_back(item);
                } else {
                    cout << "[Canh bao] File " << dataFilePath << " dong " << rowIndex
                         << ": Trung ma '" << item.getId() << "', da bo qua!\n";
                }
            } catch (const exception& e) {
                cout << "[Canh bao] File " << dataFilePath << " dong " << rowIndex
                     << " sai dinh dang (" << e.what() << "), da bo qua!\n";
            }
        }
        inFile.close();
    }

    // Ghi toan bo danh sach xuong file ngay sau khi Them, Sua, Xoa
    void saveFile() const {
        ofstream outFile(dataFilePath);
        if (!outFile.is_open()) {
            throw FileStorageException("Khong the ghi du lieu vao file: " + dataFilePath);
        }
        for (const auto& rec : records) {
            outFile << rec.toFileRecord() << "\n";
        }
        outFile.close();
    }

    // Tim ban ghi theo ma (Su dung STL find_if + Lambda)
    T* findById(const string& targetId) {
        string key = Validator::toUpperText(Validator::cleanSpaces(targetId));
        auto it = find_if(records.begin(), records.end(), [&](const T& item) {
            return Validator::toUpperText(item.getId()) == key;
        });
        return (it != records.end()) ? &(*it) : nullptr;
    }

    const vector<T>& getAll() const { return records; }

    vector<vector<string>> getTableRows() const {
        vector<vector<string>> matrix;
        for (const auto& rec : records) {
            matrix.push_back(rec.toRowCells());
        }
        return matrix;
    }

    // C - Create
    void addRecord(const T& newItem) {
        if (findById(newItem.getId()) != nullptr) {
            throw DataInputException("Ma '" + newItem.getId() + "' da ton tai trong danh sach!");
        }
        records.push_back(newItem);
        saveFile();
    }

    // U - Update
    void updateRecord(const T& modifiedItem) {
        T* existing = findById(modifiedItem.getId());
        if (existing == nullptr) {
            throw DataInputException("Khong tim thay ban ghi co ma '" + modifiedItem.getId() + "'!");
        }
        *existing = modifiedItem;
        saveFile();
    }

    // D - Delete (Su dung STL remove_if + Lambda)
    bool deleteById(const string& targetId) {
        string key = Validator::toUpperText(Validator::cleanSpaces(targetId));
        size_t oldCount = records.size();
        records.erase(remove_if(records.begin(), records.end(), [&](const T& item) {
            return Validator::toUpperText(item.getId()) == key;
        }), records.end());

        if (records.size() < oldCount) {
            saveFile();
            return true;
        }
        return false;
    }

    // Luu danh sach da sap xep
    void updateSortedList(const vector<T>& sorted) {
        records = sorted;
        saveFile();
    }
};
