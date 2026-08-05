#include <iostream>
#include <cmath>
#include <iomanip>

// Funciton prototype - "janji" ke compiler bahwa fungsi
double hitungJarak(double lat1, double lon1, double lat2, double lon2);
void tampilkanPosisi(double lat, double lon);
double knotKeMph(double knot);

int main()
{
    double lat_jakarta = -6.2088;
    double lon_jakarta = 106.8456;
    double lat_surabaya = -7.2575;
    double lon_surabaya = 112.7521;

    tampilkanPosisi(lat_jakarta, lon_jakarta);
    tampilkanPosisi(lat_surabaya, lon_surabaya);

    double jarak = hitungJarak(lat_jakarta, lon_jakarta, lat_surabaya, lon_surabaya);
    double speed = knotKeMph(20); // Contoh kecepatan dalam knot

    std::cout << "Jarak: " << jarak << " derajat" << std::endl;
    std::cout << "Kecepatan: " << std::fixed << std::setprecision(2) << speed << " km/h" << std::endl;

    return 0;
}

double knotKeMph(double knot)
{
    return knot * 1.852;
}

double hitungJarak(double lat1, double lon1, double lat2, double lon2)
{
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    return std::sqrt(dlat * dlat + dlon * dlon);
}

void tampilkanPosisi(double lat, double lon)
{
    std::cout << std::fixed << std::setprecision(4) << "Posisi -> Lat: " << lat << " Lon: " << lon << std::endl;
}
