#include <cstddef>
#include <iostream>
#include <chrono>

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> begin, end;
    Timer()
    {
        begin = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        std::cout <<  std::chrono::duration<double>(end-begin).count()*1000.0f<<"ms" << std::endl; 
    }
};

template <typename LamdaTy>
double integrate(LamdaTy &&lamda, double begin, double end,
                 std::size_t bins = 1000000) {
  Timer timer;
  double area = 0;
  double dx = (end - begin) / bins;
  for (double x = begin; x <= end; x += dx) {
    double y = lamda(x);
    area += dx * y;
  }
  return area;
}

int main() {
  auto f = [](double x) { return x * x; };
  std::cout << integrate(f, 0, 1) << std::endl;
}