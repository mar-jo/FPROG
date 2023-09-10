#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

const void print(const std::string& output)
{
  std::cout << output;
}

// Helper function to calculate square root without using std::sqrt()
const std::tuple<std::string, double> square_root(const double& x, const double epsilon = 1e-10, const int max_iterations = 1000) {
    std::stringstream output;

    output << "Calculating square root of " << x << "\n";
    if (x < 0) {
        return {output.str(), -1}; // Invalid input
    }
    if (x == 0) {
        return {output.str(), 0};
    }

    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i) {
        mid = (low + high) / 2.0;
        double mid_square = mid * mid;

        output << "Iteration: " << i + 1 << ", mid: " << mid << ", mid_square: " << mid_square << "\n";

        if (mid_square > x) {
            high = mid;
        } else if (mid_square < x) {
            low = mid;
        }

        if (high - low < epsilon) {
            break;
        }
    }

    return {output.str(), mid};
}

const std::tuple<std::string, double, double> calculate_area_and_radii(const double& a, const double& b, const double& c) {
    double s = (a + b + c) / 2;
    auto area = square_root(s * (s - a) * (s - b) * (s - c));
    double inradius = std::get<1>(area) / s;
    double circumradius = (a * b * c) / (4 * std::get<1>(area));

    return {std::get<0>(area), inradius, circumradius};
}

const std::tuple<std::string, double> calculate_distance(const double& circumradius, const double& inradius) {
    auto distance = square_root(circumradius * circumradius - 2 * circumradius * inradius);

    return {std::get<0>(distance), std::get<1>(distance)};
}

int main() {
    double a = 3, b = 4, c = 5;
    double circumradius = 0, inradius = 0, distance = 0;

    std::stringstream output;
    std::string output_string;

    output << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";
    
    output_string = output.str();
    print(output_string);
    output.str("");
    output.clear();

    auto inradius_and_circumradius = calculate_area_and_radii(a, b, c);
    print(std::get<0>(inradius_and_circumradius));

    output << "Inradius: " << std::get<1>(inradius_and_circumradius) << "\n";
    output << "Circumradius: " << std::get<2>(inradius_and_circumradius) << "\n";

    output_string = output.str();
    print(output_string);
    output.str("");
    output.clear();

    auto calculated_distance = calculate_distance(std::get<1>(inradius_and_circumradius), std::get<2>(inradius_and_circumradius));
    print(std::get<0>(calculated_distance));
    
    output << "Distance between circumcenter and incenter: " << std::get<1>(calculated_distance) << "\n";

    output_string = output.str();
    print(output_string);

    return 0;
}
