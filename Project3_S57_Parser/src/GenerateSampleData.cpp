#include "S57Parser.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace {

struct SampleFeature {
    uint8_t type;
    uint32_t id;
    std::vector<S57::Point> vertices;
    std::string name;
};

void writeUint8(std::ofstream& out, uint8_t value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void writeUint16(std::ofstream& out, uint16_t value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void writeUint32(std::ofstream& out, uint32_t value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void writeDouble(std::ofstream& out, double value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void writeString(std::ofstream& out, const std::string& value) {
    out.write(value.data(), value.size());
}

} // anonymous namespace

int main() {
    const std::string filePath = "../data/sample_chart.s57";
    std::ofstream out(filePath, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Failed to open sample output file: " << filePath << std::endl;
        return 1;
    }

    const char magic[8] = {'S','5','7','M','I','N','I','\0'};
    out.write(magic, sizeof(magic));

    uint8_t version = 1;
    writeUint8(out, version);

    std::vector<SampleFeature> features = {
        {static_cast<uint8_t>(S57::FeatureType::Point), 1001, {{120.123456, -4.789012}}, "Buoy A"},
        {static_cast<uint8_t>(S57::FeatureType::Line), 1002, {{-3.456789, 54.123456}, {-2.987654, 54.234567}, {-2.345678, 54.987654}}, "Shipping Lane"},
        {static_cast<uint8_t>(S57::FeatureType::Polygon), 1003, {{-10.0, 50.0}, {-11.0, 50.2}, {-10.8, 49.2}, {-9.6, 49.0}}, "Shallow Area"}
    };

    writeUint32(out, static_cast<uint32_t>(features.size()));

    for (const auto& feature : features) {
        writeUint8(out, feature.type);
        writeUint32(out, feature.id);
        writeUint32(out, static_cast<uint32_t>(feature.vertices.size()));
        for (const auto& point : feature.vertices) {
            writeDouble(out, point.lon);
            writeDouble(out, point.lat);
        }
        writeUint16(out, static_cast<uint16_t>(feature.name.size()));
        writeString(out, feature.name);
    }

    out.close();
    std::cout << "Sample chart generated: " << filePath << std::endl;
    return 0;
}
