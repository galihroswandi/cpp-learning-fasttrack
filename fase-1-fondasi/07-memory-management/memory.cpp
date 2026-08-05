#include <iostream>
#include <memory>
#include <string>

class Sensor
{
public:
    std::string tipe;

    Sensor(std::string t) : tipe(t)
    {
        std::cout << "[+] Sensor dibuat: " << tipe << std::endl;
    }

    ~Sensor()
    {
        std::cout << "[-] Sensor dihapus: " << tipe << std::endl;
    }

    void baca()
    {
        std::cout << "Membaca sensor: " << tipe << std::endl;
    }
};

int main()
{
    std::cout << "=== RAW POINTER ===" << std::endl;
    Sensor *raw = new Sensor("GPS");
    raw->baca();
    delete raw;

    std::cout << "\n=== UNIQUE POINTER ===" << std::endl;
    std::unique_ptr<Sensor> uptr = std::make_unique<Sensor>("RADAR");
    uptr->baca();
    // tidak perlu delete - otomatis saat keluar scope

    std::cout << "\n=== SHARED POINTER ===" << std::endl;
    std::shared_ptr<Sensor> sptr1 = std::make_shared<Sensor>("AIS");
    {
        std::shared_ptr<Sensor> sptr2 = sptr1; // dua pemilik
        std::cout << "Pemilik: " << sptr1.use_count() << std::endl;
    } // sptr2 hancur disini
    std::cout << "Pemilik: " << sptr1.use_count() << std::endl;

    return 0;
}