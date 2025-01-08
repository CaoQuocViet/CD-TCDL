// Program to input and display student's name and ID

#include <iostream>
#include <string>

int main() {
    std::string tenSinhVien;
    std::string maSoSinhVien;

    std::cout << "Nhap ten sinh vien: ";
    std::getline(std::cin, tenSinhVien);

    std::cout << "Nhap ma so sinh vien: ";
    std::getline(std::cin, maSoSinhVien);

    std::cout << "\nThong tin sinh vien:\n";
    std::cout << "Ten: " << tenSinhVien << "\n";
    std::cout << "Ma so: " << maSoSinhVien << "\n";

    return 0;
}