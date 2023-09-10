#include <iostream>
#include <sstream>
#include <tuple>

using namespace std;

const void print(const string& output)
{
  cout << output;
}

const tuple<string, int> square(const int e)
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

const tuple<string, double> squareroot(const double x)
{				/* computes the square root of x */

  if (x == 0)
    return {"guess: 0", 0};

/* the sqrt must be between xhi and xlo */
  stringstream output;
  double xhi = x;
  double xlo = 0;
  double guess = x / 2;

/* We stop when guess*guess-x is very small */

  while (abs (guess * guess - x) > 0.00001)
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

  output << "guess:" << guess << endl;;
  return {output.str(), guess};
}


const tuple<string, int> pythagoras(const int x, const int y)
{
  stringstream output;

  auto square_x = square(x);
  auto square_y = square(y);

  print(get<0>(square_x));
  print(get<0>(square_y));

  auto z = squareroot (get<1>(square_x) + get<1>(square_y));
  print(get<0>(z));
  output << "euklid:" << get<1>(z) << endl;

  return {output.str(), get<1>(z)};
}

int main (int argc, char *argv[])
{
  stringstream output;
  string output_string;
  int x = 3;
  int y = 4;

  auto pythagoras_z = pythagoras(x, y);
  print(get<0>(pythagoras_z));

  output << get<1>(pythagoras_z) << endl;
  output_string = output.str();

  print(output_string);
  
  return 0;
}
