#include <iostream>
#include <string>

int main()
{
    int kecepatan = 12;
    float latitude = -6.2088;
    double longitude = 106.8456;
    bool berlayar = true;
    std::string nama_kapal = "KM Nusantara";

    std::cout << "Kapal: " << nama_kapal << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Kecepatan: " << kecepatan << " knot" << std::endl;
    std::cout << "Sedang berlayar: " << berlayar << std::endl;
    std::cout << std::boolalpha << berlayar << std::endl;

    return 0;
}
