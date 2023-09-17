#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <cmath>

auto print = [](const std::string& output)
{
  std::cout << output;
};

// Silly square function that is not immutable and not pure
auto silly_square = [](const double& x) -> const std::tuple<std::string, double>
{
    std::stringstream output;
    double result = 0;
    int MAX_ITERATIONS = static_cast<int>(std::round(x));

    output << "Calculating the silly square of " << x << "\n";
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        result += x;
        output << "Iteration " << i + 1 << ": Current result = " << result << "\n";
    }

    return {output.str(), result};
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

auto calculate_median = [](const double& a)
{
    return [a](const double& b)
    {
        return [a, b](const double& c) -> const std::tuple<std::string, double>
        {
            std::stringstream output;

            auto [message_b, square_b] = silly_square(b);
            output << message_b;

            auto [message_c, square_c] = silly_square(c);
            output << message_c;

            auto [message_a, square_a] = silly_square(a);
            output << message_a;

            output << "Calculating the median of a triangle with sides a = " << a << ", b = " << b << ", c = " << c << "\n";

            auto [square_root_message, square_root_result] = square_root(2 * square_b + 2 * square_c - square_a)()();
            output << square_root_message;

            double result = 0.5 * square_root_result;

            return {output.str(), result};   
        };
    };
};

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

    auto [message_a, median_a] = calculate_median(a)(b)(c);
    print(message_a);

    a = 4, b = 3, c = 5;
    auto [message_b, median_b] = calculate_median(a)(b)(c);
    print(message_b);

    a = 5, b = 3, c = 4;
    auto [message_c, median_c] = calculate_median(a)(b)(c);
    print(message_c);

    output << "Medians:\n";
    output << "Median from vertex A: " << median_a << "\n";
    output << "Median from vertex B: " << median_b << "\n";
    output << "Median from vertex C: " << median_c << "\n";

    output_string = output.str();
    print(output_string);

    return 0;
}
