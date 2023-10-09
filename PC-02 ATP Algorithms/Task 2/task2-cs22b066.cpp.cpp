#include <cstddef>
#include <iostream>
#include <future>
#include <chrono>
//Slow async
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

void Area(double* area,double dx,double y)
{
    *area+=dx*y;
}

template <typename LamdaTy>
double integrate(LamdaTy &&lamda, double begin, double end, std::size_t bins = 1000000) 
{
    Timer timer;
    double area = 0;
    double dx = (end - begin) / bins;
    for (double x = begin; x <= end; x += dx) 
    {
        auto future=std::async(std::launch::async,Area,&area,dx,lamda(x));
    }
    return area;
}

int main() {
  auto f = [](double x) { return x * x; };
  std::cout << integrate(f, 0, 1) << std::endl;
}



/*
Fast async

#include <cstddef>
#include <iostream>
#include <future>
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

double integrate(double begin, double end, std::size_t bins) 
{
    double area = 0;
    double dx = (end - begin) / bins;
    for (double x = begin; x <= end; x += dx) 
    {
        area+=dx*(x*x);
    }
    return area;
}

int main() 
{
    Timer timer;
    int n_threads = 8;
    std::future<double> group_future[n_threads];
    size_t bins=1000000;
    size_t group_size=bins/n_threads;
    double area=0.0;
    for(int i=0;i<n_threads;i++)
    {
        group_future[i]=std::async(std::launch::async,integrate,((double)(i)*1.0)/n_threads,((double)(i+1)*1.0)/n_threads,group_size);
        area+=group_future[i].get();
    }
    std::cout<<area<< std::endl;;
}
*/