#include "S57Parser.h"

#include <fstream>
#include <sstream>
#include <cstring>

namespace S57 {

namespace {

template<typename T>
bool readValue(std::ifstream& input, T& value) {
    input.read(reinterpret_cast<char*>(&value), sizeof(T));
    return input.good();
}

bool readString(std::ifstream& input, uint16_t length, std::string& output) {
    output.resize(length);
    input.read(output.data(), length);
    return input.good();
}

} // anonymous namespace

std::string S57Parser::featureTypeName(FeatureType type) {
    switch (type) {
        case FeatureType::Point: return "Point";
        case FeatureType::Line: return "Line";
        case FeatureType::Polygon: return "Polygon";
        default: return "Unknown";
    }
}

ParseResult S57Parser::parseFile(const std::string& path) {
    ParseResult result;
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        result.success = false;
        result.message = "Cannot open file: " + path;
        return result;
    }

    char magic[8];
    file.read(magic, sizeof(magic));
    if (!file.good()) {
        result.success = false;
        result.message = "Failed to read file header.";
        return result;
    }

    const char expectedMagic[8] = {'S','5','7','M','I','N','I','\0'};
    if (std::memcmp(magic, expectedMagic, sizeof(magic)) != 0) {
        result.success = false;
        result.message = "Invalid file magic header. Not a mini S-57 file.";
        return result;
    }

    uint8_t version = 0;
    if (!readValue(file, version)) {
        result.success = false;
        result.message = "Failed to read version.";
        return result;
    }

    if (version != 1) {
        result.success = false;
        result.message = "Unsupported mini S-57 version: " + std::to_string(version);
        return result;
    }

    uint32_t recordCount = 0;
    if (!readValue(file, recordCount)) {
        result.success = false;
        result.message = "Failed to read record count.";
        return result;
    }

    for (uint32_t i = 0; i < recordCount; ++i) {
        uint8_t rawType = 0;
        if (!readValue(file, rawType)) {
            result.success = false;
            result.message = "Failed to read feature type at record " + std::to_string(i);
            return result;
        }

        Feature feature;
        feature.type = static_cast<FeatureType>(rawType);

        if (!readValue(file, feature.id)) {
            result.success = false;
            result.message = "Failed to read feature id at record " + std::to_string(i);
            return result;
        }

        uint32_t vertexCount = 0;
        if (!readValue(file, vertexCount)) {
            result.success = false;
            result.message = "Failed to read vertex count at record " + std::to_string(i);
            return result;
        }

        feature.vertices.reserve(vertexCount);
        for (uint32_t v = 0; v < vertexCount; ++v) {
            Point point;
            if (!readValue(file, point.lon) || !readValue(file, point.lat)) {
                result.success = false;
                result.message = "Failed to read vertex " + std::to_string(v) + " for record " + std::to_string(i);
                return result;
            }
            feature.vertices.push_back(point);
        }

        uint16_t nameLength = 0;
        if (!readValue(file, nameLength)) {
            result.success = false;
            result.message = "Failed to read name length at record " + std::to_string(i);
            return result;
        }

        if (!readString(file, nameLength, feature.name)) {
            result.success = false;
            result.message = "Failed to read feature name at record " + std::to_string(i);
            return result;
        }

        result.features.push_back(std::move(feature));
    }

    if (!file.eof() && file.fail()) {
        result.success = false;
        result.message = "File parsing ended unexpectedly.";
        return result;
    }

    result.success = true;
    result.message = "Successfully parsed " + std::to_string(result.features.size()) + " features.";
    return result;
}

} // namespace S57
