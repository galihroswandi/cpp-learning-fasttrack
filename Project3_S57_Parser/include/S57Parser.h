#ifndef S57PARSER_H
#define S57PARSER_H

#include <cstdint>
#include <string>
#include <vector>

namespace S57 {

enum class FeatureType : uint8_t {
    Point = 1,
    Line = 2,
    Polygon = 3,
};

struct Point {
    double lon;
    double lat;
};

struct Feature {
    uint32_t id;
    FeatureType type;
    std::string name;
    std::vector<Point> vertices;
};

struct ParseResult {
    bool success;
    std::string message;
    std::vector<Feature> features;
};

class S57Parser {
public:
    static ParseResult parseFile(const std::string& path);
    static std::string featureTypeName(FeatureType type);
};

} // namespace S57

#endif // S57PARSERH
