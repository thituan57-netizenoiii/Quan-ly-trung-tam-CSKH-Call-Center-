#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include "Utils/Date.h"

using namespace std;

class Validator {
public:
    // Cat khoang trang thua o 2 dau chuoi
    static string cleanSpaces(const string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, last - first + 1);
    }

    static string toUpperText(string s) {
        for (char& c : s) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        return s;
    }

    static string toLowerText(string s) {
        for (char& c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        return s;
    }

    // Tach cac truong ngan cach boi dau '|' trong 1 dong file
    static vector<string> splitRecord(const string& line, char sep = '|') {
        vector<string> parts;
        stringstream ss(line);
        string item;
        while (getline(ss, item, sep)) {
            parts.push_back(cleanSpaces(item));
        }
        if (!line.empty() && line.back() == sep) {
            parts.push_back("");
        }
        return parts;
    }

    // Kiem tra chuoi con khong phan biet hoa thuong
    static bool matchKeyword(const string& fullText, const string& keyword) {
        return toLowerText(fullText).find(toLowerText(cleanSpaces(keyword))) != string::npos;
    }

    // Kiem tra chuoi văn ban hop le (khong rong, khong chua dau '|')
    static bool checkNonEmptyText(const string& s, size_t maxLen = 150) {
        string cleaned = cleanSpaces(s);
        if (cleaned.empty() || cleaned.length() > maxLen) return false;
        return cleaned.find('|') == string::npos;
    }

    // Kiem tra ma dinh danh theo tien to (VD: KTN001, CG001, KH001, DTV001)
    static bool checkCodeFormat(const string& code, const string& prefix) {
        string s = toUpperText(cleanSpaces(code));
        string pre = toUpperText(prefix);
        if (s.length() <= pre.length() || s.find(pre) != 0) return false;
        for (size_t i = pre.length(); i < s.length(); ++i) {
            if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
        }
        return true;
    }

    // Chuyen chuoi sang so nguyen an toan (nem ngoai le neu sai)
    static int toInt(const string& str) {
        string s = cleanSpaces(str);
        if (s.empty()) throw DataInputException("Gia tri so nguyen bi bo trong!");
        size_t pos = 0;
        try {
            int val = stoi(s, &pos);
            if (pos != s.length()) throw DataInputException("Chuoi chua ky tu khong phai so nguyen!");
            return val;
        } catch (...) {
            throw DataInputException("Khong the chuyen '" + s + "' sang so nguyen!");
        }
    }

    // Chuyen chuoi sang so thuc an toan (nem ngoai le neu sai)
    static double toDouble(const string& str) {
        string s = cleanSpaces(str);
        if (s.empty()) throw DataInputException("Gia tri so thuc bi bo trong!");
        size_t pos = 0;
        try {
            double val = stod(s, &pos);
            if (pos != s.length()) throw DataInputException("Chuoi chua ky tu khong phai so thuc!");
            return val;
        } catch (...) {
            throw DataInputException("Khong the chuyen '" + s + "' sang so thuc!");
        }
    }

    // --- TIEN ICH DINH DANG BANG CAN COT BANG <iomanip> (Muc 3.4 & 3.5) ---
    static string fitColumn(const string& content, int width) {
        if (width <= 3) return content.substr(0, width);
        if (static_cast<int>(content.length()) > width) {
            return content.substr(0, width - 3) + "...";
        }
        return content;
    }

    static void drawLine(const vector<int>& colWidths) {
        cout << "+";
        for (int w : colWidths) cout << string(w + 2, '-') << "+";
        cout << "\n";
    }

    static void drawRow(const vector<int>& colWidths, const vector<string>& cells) {
        cout << "|";
        for (size_t i = 0; i < colWidths.size(); ++i) {
            string text = (i < cells.size()) ? cells[i] : "";
            cout << " " << left << setw(colWidths[i]) << fitColumn(text, colWidths[i]) << " |";
        }
        cout << "\n";
    }

    static void renderTable(const vector<int>& colWidths,
                            const vector<string>& headers,
                            const vector<vector<string>>& rows) {
        if (rows.empty()) {
            cout << "  (Danh sach hien dang trong)\n";
            return;
        }
        drawLine(colWidths);
        drawRow(colWidths, headers);
        drawLine(colWidths);
        for (const auto& r : rows) drawRow(colWidths, r);
        drawLine(colWidths);
        cout << "  -> Tong so ban ghi hien thi: " << rows.size() << "\n";
    }

    static void renderSingleRecord(const vector<int>& colWidths,
                                   const vector<string>& headers,
                                   const vector<string>& row) {
        drawLine(colWidths);
        drawRow(colWidths, headers);
        drawLine(colWidths);
        drawRow(colWidths, row);
        drawLine(colWidths);
    }
};