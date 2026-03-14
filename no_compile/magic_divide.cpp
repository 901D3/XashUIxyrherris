
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

unsigned value = 10000;
double divide = 10.;
unsigned int power = 35;

unsigned long long powered = (1ULL << power);
unsigned long long magic = std::ceil(powered / divide);

double dividedMagic = static_cast<double>magic / powered;
double error = dividedMagic - (1. / divide);

int main() {
  std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);

  std::cout << "result: " << ((value * magic) >> power) << '\n';
  std::cout << "divided magic value: " << dividedMagic << '\n';
  std::cout << "error: " << error << '\n';
  std::cout << "hex: " << std::hex << magic << '\n';

  return 0;
}
