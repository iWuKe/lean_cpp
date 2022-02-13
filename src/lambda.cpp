#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main(int argc, char* argv[])
{
  std::vector<int> vec(10);

  generate(vec.begin(), vec.end(), std::rand);

  for (size_t i = 0; i < vec.size(); i++)
  {
    std::cout << " " << vec.at(i);
  }
  std::cout << std::endl;

  int count = std::count_if(vec.begin(), vec.end(), [](int x){std::cout << " " << x << std::endl; return 0;});

  return 0;
}