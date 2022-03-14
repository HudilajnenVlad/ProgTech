#include <random>

namespace hudilajnen
{
  void fillRandom(double *array, int size)
  {
    static std::random_device randomDevice;
    std::default_random_engine gen(randomDevice());
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for (int i = 0; i < size; i++)
    {
      array[i] = distribution(gen);
    }
  }
}
