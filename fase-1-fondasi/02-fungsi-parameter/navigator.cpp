#include <iostream>
#include <iomanip>
#include <string>

double knotKeMps(double knot);
double estimasiWaktu(double jarakNauticalMiles, double kecepatanKnot);
void tampilkanRingkasanRute(std::string dari, std::string ke, double jarakNauticalMiles, double kecepatanKnot, double waktuJam);

int main()
{
    std::string dari, ke;
    double jarakNauticalMiles, kecepatanKnot;

    dari = "Jakarta";
    ke = "Surabaya";
    jarakNauticalMiles = 290.5;
    kecepatanKnot = 14.0;

    double waktuJam = estimasiWaktu(jarakNauticalMiles, kecepatanKnot);

    tampilkanRingkasanRute(dari, ke, jarakNauticalMiles, kecepatanKnot, waktuJam);

    return 0;
}

double knotKeMps(double knot)
{
    return knot * 0.5144;
}

double estimasiWaktu(double jarakNauticalMiles, double kecepatanKnot)
{
    return jarakNauticalMiles / kecepatanKnot;
}

void tampilkanRingkasanRute(std::string dari, std::string ke, double jarakNauticalMiles, double kecepatanKnot, double waktuJam)
{
    std::cout << std::string(3, '=') << "RINGKASA RUTE" << std::string(3, '=') << std::endl;
    std::cout << "Dari" << "       : " << dari << std::endl;
    std::cout << "Ke" << "         : " << ke << std::endl;
    std::cout << "Jarak" << "      : " << jarakNauticalMiles << " nm" << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "Kecepatan" << "  : " << kecepatanKnot << " knot" << std::endl;
    std::cout << "ETA" << "        : " << waktuJam << " jam " << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Kec (m/s) " << " : " << knotKeMps(kecepatanKnot) << " m/s" << std::endl;
}