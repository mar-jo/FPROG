#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

const auto print = [](const std::string& output)
{
  std::cout << output;
};

// Helper function to calculate square root without using std::sqrt()
const auto square_root = [](const double& x)
{
    return [x](const double epsilon = 1e-10)
    {
        return [x, epsilon](const int max_iterations = 1000) -> const std::tuple<std::string, double>
        {
            std::stringstream output;

            output << "Calculating the square root of " << x << "\n";
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
                output << "Iteration " << i + 1 << ": Midpoint = " << mid << ", Midpoint squared = " << mid_square << "\n";

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
        };
    };
};

const auto calculate_area_and_radii = [](const double& a)
{
    return [a](const double& b)
    {
        return [a, b](const double& c) -> const std::tuple<std::string, double, double>
        {
            double s = (a + b + c) / 2;
            auto [message, area] = square_root(s * (s - a) * (s - b) * (s - c))()();
            double inradius = area / s;
            double circumradius = (a * b * c) / (4 * area);

            return {message, inradius, circumradius};  
        };
    };
};

const auto calculate_distance = [](const double& circumradius)
{
    return [circumradius](const double& inradius) -> const std::tuple<std::string, double>
    {
        auto [message, distance] = square_root(circumradius * circumradius - 2 * circumradius * inradius)()();

        return {message, distance};
    };
};

int main() {
    double a = 3, b = 4, c = 5;

    std::stringstream output;
    std::string output_string;

    output << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";
    
    output_string = output.str();
    print(output_string);
    output.str("");
    output.clear();

    auto [message_inradius_and_circumradius, inradius, circumradius] = calculate_area_and_radii(a)(b)(c);
    print(message_inradius_and_circumradius);

    output << "Inradius: " << inradius << "\n";
    output << "Circumradius: " << circumradius << "\n";

    output_string = output.str();
    print(output_string);
    output.str("");
    output.clear();

    auto [message_calculated_distance, distance] = calculate_distance(inradius)(circumradius);
    print(message_calculated_distance);
    
    output << "Distance between circumcenter and incenter: " << distance << "\n";

    output_string = output.str();
    print(output_string);

    return 0;
}
