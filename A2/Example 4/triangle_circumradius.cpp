#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

auto print = [](const std::string& output)
{
  std::cout << output;
};

// Helper function to calculate square root without using std::sqrt()
auto square_root = [](const double& x)
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

auto calculate_circumradius = [](const double& a)
{
    return [a](const double& b)
    {
        return [a, b](const double& c) -> const std::tuple<std::string, double>
        {
            double s = 0;

            s = (a + b + c) / 2;
            auto [message, area] = square_root(s * (s - a) * (s - b) * (s - c))()();

            return {message, (a * b * c) / (4 * area)};
        };
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

    auto [message, circumradius] = calculate_circumradius(a)(b)(c);
    print(message);

    output << "Circumradius: " << circumradius << "\n";
    
    output_string = output.str();
    print(output_string);

    return 0;
}
