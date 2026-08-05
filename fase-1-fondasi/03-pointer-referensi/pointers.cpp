#include <iostream>

void tambahOffset(double &lat);

int main()
{
    double latitude = -6.2088;

    double *ptr = &latitude;
    double **ptr2 = &ptr;

    double pos = -6.2088;
    std::cout << "Sebelum: " << pos << std::endl;
    tambahOffset(pos);
    std::cout << "Sesudah: " << pos << std::endl;

    std::cout << "Nilai latitude     : " << latitude << std::endl;
    std::cout << "Alamat latitude    : " << &latitude << std::endl;
    std::cout << "Isi ptr            : " << ptr << std::endl;
    std::cout << "Via ptr2           : " << **ptr2 << std::endl;

    *ptr = -7.2575;

    std::cout << "Alamat ptr sendiri : " << &ptr << std::endl;
    std::cout << "\nSetelah *ptr    = -7.2575: " << std::endl;
    std::cout << "latitude sekarang = " << latitude << std::endl;

    latitude = -1.2345;

    std::cout << "\nNilai via ptr sekarang: " << *ptr << std::endl;

    return 0;
}

void tambahOffset(double &lat)
{
    lat += 0.5;
}