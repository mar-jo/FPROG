#include <iostream>
#include <sstream>
#include <cstring>
#include <tuple>
#include <bits/stdc++.h>

auto print = [](const std::string& output)
{
  std::cout << output;
};

auto square = [](const int e) -> const std::tuple<std::string, int>
{
	double dummy = e;
	double dummy2 = e;
  int e_value = e;

  std::stringstream output;

  for (int i = 1; i < dummy2; i++)
  {
  	e_value += dummy;
  	output << "i: " << i << " dummy:" << dummy << " e:" << e_value << std::endl;
  }
    
  output << "square:" << e_value << std::endl;
  return {output.str(), e_value};
};

auto squareroot = [](const double x) -> const std::tuple<std::string, double>
{				/* computes the square root of x */

  if (x == 0)
    return {"guess: 0", 0};

/* the sqrt must be between xhi and xlo */
  std::stringstream output;
  double xhi = x;
  double xlo = 0;
  double guess = x / 2;

/* We stop when guess*guess-x is very small */

  while (std::abs (guess * guess - x) > 0.00001)
  {
    if (guess * guess > x)
    {
      xhi = guess;
    }

    else
    {
      xlo = guess;
    }

    guess = (xhi + xlo) / 2;
  }

  output << "guess:" << guess << std::endl;;
  return {output.str(), guess};
};


auto pythagoras = [](const int x) {
    return [x](const int y) -> const std::tuple<std::string, int> {
        std::stringstream output;

        auto [message_x, result_x] = square(x);
        auto [message_y, result_y] = square(y);

        output << message_x;
        output << message_y;

        auto [message_z, result_z] = squareroot(result_x + result_y);
        output << message_z;
        output << "euklid:" << result_z << std::endl;

        return {output.str(), result_z};
    };
};

int main (int argc, char *argv[])
{
  std::stringstream output;
  std::string output_string;
  int x = 3;
  int y = 4;

  auto [message_pythagoras_z, result_pythagoras_z] = pythagoras(x)(y);
  print(message_pythagoras_z);

  output << result_pythagoras_z << std::endl;
  output_string = output.str();

  print(output_string);
  
  return 0;
}
