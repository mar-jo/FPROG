#include <iostream>
#include <utility>
#include <complex>
#include <string>
#include <sstream>
#include <tuple>

typedef std::complex<double> complex;

const void print(const std::string& output)
{
  std::cout << output;
}

const std::tuple<std::string, double> square(const double& e)
{
	double dummy = e;
	double dummy2 = e;
  double e_value = e;

  std::stringstream output;

  for (int i = 1; i < dummy2; i++)
  {
  	e_value += dummy;
  	output << "i: " << i << " dummy:" << dummy << " e:" << e_value << std::endl;
  }
    
  output << "square:" << e_value << std::endl;
  return {output.str(), e_value};
}

const inline float squareroot(const float& number)
{
    union Conv {
      float    f;
      uint32_t i;
    };

    Conv conv;
    conv.f = number;
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    return 1/conv.f;
}

const std::tuple<std::string, std::pair<complex, complex>> solve_quadratic_equation(const double& a, const double& b, const double& c)
{
  double b_value = b / a;
  double c_value = c / a;

  auto b_square = square(b_value);

  double discriminant = std::get<1>(b_square) - 4 * c_value;

  if (discriminant < 0)
    return {std::get<0>(b_square), std::make_pair(complex(-b_value / 2, squareroot(-discriminant) / 2),
                          complex(-b_value / 2, -squareroot(-discriminant) / 2))};

  double root = std::sqrt(discriminant);
  double solution1 = (b_value > 0)? (-b_value - root) / 2
                            : (-b_value + root) / 2;

  return {std::get<0>(b_square), std::make_pair(solution1, c_value / solution1)};
}

int main()
{
  std::stringstream output;
  std::string output_string;

  auto result = solve_quadratic_equation(3, 4, 5);
  print(std::get<0>(result));

  output << std::get<1>(result).first << ", " << std::get<1>(result).second << std::endl;
  
  output_string = output.str();
  print(output_string);
}