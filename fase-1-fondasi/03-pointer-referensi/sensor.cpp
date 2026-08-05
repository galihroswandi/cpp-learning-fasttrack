#include <iostream>
#include <string>

void updatePosisi(double &lat, double &lon, double deltaLat, double deltaLon);
void tampilkanPosisi(const double &lat, const double &lon);
void swapKoordinat(double *a, double *b);

int main()
{
    double latitude = 0.0;
    double longitude = 0.0;

    updatePosisi(latitude, longitude, 10.5, 20.5);
    tampilkanPosisi(latitude, longitude);

    updatePosisi(latitude, longitude, -5.0, -10.0);
    tampilkanPosisi(latitude, longitude);

    updatePosisi(latitude, longitude, 15.0, 25.0);
    tampilkanPosisi(latitude, longitude);

    swapKoordinat(&latitude, &longitude);
    std::cout << "\nSetelah swap koordinat:" << std::endl;
    tampilkanPosisi(latitude, longitude);

    return 0;
}

void updatePosisi(double &lat, double &lon, double deltaLat, double deltaLon)
{
    lat += deltaLat;
    lon += deltaLon;
}

void tampilkanPosisi(const double &lat, const double &lon)
{
    std::cout << "\n"
              << std::string(4, '=') << "POSISI KAPAL" << std::string(4, '=') << std::endl;
    std::cout << "Latitude: " << lat << std::endl;
    std::cout << "Longitude: " << lon << std::endl;
}

void swapKoordinat(double *a, double *b)
{
    double temp = *a;

    *a = *b;
    *b = temp;
}