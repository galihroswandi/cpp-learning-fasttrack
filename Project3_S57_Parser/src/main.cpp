#include "S57Parser.h"

#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
    const std::string filePath = (argc > 1)
        ? argv[1]
        : std::string("../data/sample_chart.s57");

    auto result = S57::S57Parser::parseFile(filePath);
    if (!result.success) {
        std::cerr << "Parser error: " << result.message << std::endl;
        return 1;
    }

    std::cout << "Parse result: " << result.message << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (const auto& feature : result.features) {
        std::cout << "Feature ID: " << feature.id << std::endl;
        std::cout << "Type: " << S57::S57Parser::featureTypeName(feature.type) << std::endl;
        std::cout << "Name: " << feature.name << std::endl;
        std::cout << "Vertices: " << feature.vertices.size() << std::endl;
        for (size_t index = 0; index < feature.vertices.size(); ++index) {
            const auto& point = feature.vertices[index];
            std::cout << "  [" << std::setw(2) << index << "] lon=" << std::fixed << std::setprecision(6)
                      << point.lon << ", lat=" << point.lat << std::endl;
        }

        std::cout << "----------------------------------------" << std::endl;
    }

    return 0;
}
