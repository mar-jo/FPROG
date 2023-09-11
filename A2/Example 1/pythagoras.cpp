#include <iostream>
#include <sstream>
#include <tuple>

const void print(const std::string& output)
{
  std::cout << output;
}

const std::tuple<std::string, int> square(const int e)
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
}

const std::tuple<std::string, double> squareroot(const double x)
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
}


const std::tuple<std::string, int> pythagoras(const int x, const int y)
{
  std::stringstream output;

  auto square_x = square(x);
  auto square_y = square(y);

  output << std::get<0>(square_x);
  output << std::get<0>(square_y);

  auto z = squareroot (std::get<1>(square_x) + std::get<1>(square_y));
  output << std::get<0>(z);
  output << "euklid:" << std::get<1>(z) << std::endl;

  return {output.str(), std::get<1>(z)};
}

int main (int argc, char *argv[])
{
  std::stringstream output;
  std::string output_string;
  int x = 3;
  int y = 4;

  auto pythagoras_z = pythagoras(x, y);
  print(std::get<0>(pythagoras_z));

  output << std::get<1>(pythagoras_z) << std::endl;
  output_string = output.str();

  print(output_string);
  
  return 0;
}
