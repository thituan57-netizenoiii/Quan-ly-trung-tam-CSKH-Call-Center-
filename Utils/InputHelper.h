#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Utils/Validator.h"

using namespace std;

class InputHelper {
public:
    static void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static void waitEnter() {
        cout << "\nNhan Enter de tiep tuc...";
        string temp;
        getline(cin, temp);
    }

    // Nhap so nguyen an toan (khong bi treo khi nhap chu - Muc 3.5)
    static int inputInt(const string& label) {
        string raw;
        while (true) {
            cout << label;
            getline(cin, raw);
            try {
                return Validator::toInt(raw);
            } catch (const exception& e) {
                cout << "  " << e.what() << " Vui long nhap lai!\n";
            }
        }
    }

    // Nhap lua chon menu trong khoang [minVal, maxVal]
    static int inputMenuOption(int minVal, int maxVal) {
        while (true) {
            int val = inputInt("Nhap lua chon (" + to_string(minVal) + " - " + to_string(maxVal) + "): ");
            if (val >= minVal && val <= maxVal) return val;
            cout << "  [!] Lua chon phai tu " << minVal << " den " << maxVal << "!\n";
        }
    }

    // Nhap so thuc an toan
    static double inputDouble(const string& label) {
        string raw;
        while (true) {
            cout << label;
            getline(cin, raw);
            try {
                return Validator::toDouble(raw);
            } catch (const exception& e) {
                cout << "  " << e.what() << " Vui long nhap lai!\n";
            }
        }
    }

    // Nhap chuoi bat buoc khong rong
    static string inputRequiredText(const string& label) {
        string raw;
        while (true) {
            cout << label;
            getline(cin, raw);
            raw = Validator::cleanSpaces(raw);
            if (Validator::checkNonEmptyText(raw)) return raw;
            cout << "  [!] Chuoi khong duoc de trong va khong chua dau '|'! Vui long nhap lai.\n";
        }
    }

    // Nhap chuoi tuy chon (Enter de bo qua khi cap nhat)
    static string inputOptionalText(const string& label) {
        string raw;
        while (true) {
            cout << label;
            getline(cin, raw);
            raw = Validator::cleanSpaces(raw);
            if (raw.empty()) return "";
            if (raw.find('|') == string::npos) return raw;
            cout << "  [!] Chuoi khong duoc chua ky tu '|'!\n";
        }
    }

    // Nhap Ngay bat buoc
    static Date inputRequiredDate(const string& label) {
        string raw;
        while (true) {
            cout << label << " (dd/mm/yyyy): ";
            getline(cin, raw);
            try {
                Date d(raw);
                if (!d.dangRong()) return d;
                cout << "  [!] Ngay khong duoc de trong!\n";
            } catch (const exception& e) {
                cout << "  " << e.what() << "\n";
            }
        }
    }

    // Nhap Gio bat buoc
    static TimeSlot inputRequiredTime(const string& label) {
        string raw;
        while (true) {
            cout << label << " (hh:mm): ";
            getline(cin, raw);
            try {
                TimeSlot t(raw);
                if (!t.dangRong()) return t;
                cout << "  [!] Gio khong duoc de trong!\n";
            } catch (const exception& e) {
                cout << "  " << e.what() << "\n";
            }
        }
    }

    // Xac nhan thao tac Xoa (y/n)
    static bool askConfirm(const string& question) {
        while (true) {
            string ans = Validator::toLowerText(inputRequiredText(question + " (y/n): "));
            if (ans == "y" || ans == "yes") return true;
            if (ans == "n" || ans == "no") return false;
            cout << "  [!] Vui long nhap 'y' (Dong y) hoac 'n' (Huy bo)!\n";
        }
    }
};