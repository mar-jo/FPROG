#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <cmath>

const void print(const std::string& output)
{
  std::cout << output;
}

// Silly square function that is not immutable and not pure
const std::tuple<std::string, double> silly_square(const double& x) {
    std::stringstream output;
    double result = 0;
    int MAX_ITERATIONS = static_cast<int>(std::round(x));

    output << "Calculating the silly square of " << x << "\n";
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        result += x;
        output << "Iteration " << i + 1 << ": Current result = " << result << "\n";
    }

    return {output.str(), result};
}

// Helper function to calculate square root without using std::sqrt()
const std::tuple<std::string, double> square_root(const double& x, const double epsilon = 1e-10, const int max_iterations = 1000) {
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
}

const std::tuple<std::string, double> calculate_median(const double& a, const double& b, const double& c) {
    std::stringstream output;

    auto square_b = silly_square(b);
    output << std::get<0>(square_b);

    auto square_c = silly_square(c);
    output << std::get<0>(square_c);

    auto square_a = silly_square(a);
    output << std::get<0>(square_a);

    output << "Calculating the median of a triangle with sides a = " << a << ", b = " << b << ", c = " << c << "\n";

    auto square_root_result = square_root(2 * std::get<1>(square_b) + 2 * std::get<1>(square_c) - std::get<1>(square_a));
    output << std::get<0>(square_root_result);

    double result = 0.5 * std::get<1>(square_root_result);

    return {output.str(), result};
}

int main() {
    double a = 3;
    double b = 4;
    double c = 5;

    std::stringstream output;
    std::string output_string;

    output << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    output_string = output.str();
    print(output_string);
    output.str("");
    output.clear();

    auto median_a = calculate_median(a, b, c);
    print(std::get<0>(median_a));

    a = 4, b = 3, c = 5;
    auto median_b = calculate_median(a, b, c);
    print(std::get<0>(median_b));

    a = 5, b = 3, c = 4;
    auto median_c = calculate_median(a, b, c);
    print(std::get<0>(median_c));

    output << "Medians:\n";
    output << "Median from vertex A: " << std::get<1>(median_a) << "\n";
    output << "Median from vertex B: " << std::get<1>(median_b) << "\n";
    output << "Median from vertex C: " << std::get<1>(median_c) << "\n";

    output_string = output.str();
    print(output_string);

    return 0;
}
