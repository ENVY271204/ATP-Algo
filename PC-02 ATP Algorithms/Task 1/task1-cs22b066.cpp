#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cstddef>

using std::cin, std::cout, std::endl;

#define SIZE_CHECK // comment this out if you haven't implemented .size()

#define ACCUMULATE_CHECK /* comment this out if you haven't implemented        \
                            accumulate. Do note that this test calls           \
                            .size() and will fail if .size() is not            \
                            implemented*/

struct Complex {
  int real = 0, imaginary = 0;

  Complex(int _real, int _imaginary) : real(_real), imaginary(_imaginary){};
  Complex() {
    this->real = rand() % 10;
    this->imaginary = rand() % 10;
  };

  Complex operator+(const Complex &addend) {
    return Complex(this->real + addend.real,
                   this->imaginary + addend.imaginary);
  }

  void operator+=(const Complex &addend) {
    this->real += addend.real;
    this->imaginary += addend.imaginary;
  }

  bool operator==(const Complex &c) {
    return (this->real == c.real && this->imaginary == c.imaginary);
  }
};

namespace coa {
  using ::Complex;
    template<typename T>
class vector
{
    private:
    T* vec;
    size_t max_Size;
    size_t curr_Size;

    public:
    vector()
    {
        vec = new T[1];
        max_Size = 1;
        curr_Size = 0;
    }
    void doubleSize()
    {
        T* temp = new T[max_Size*2];
        for(size_t i=0;i<max_Size;i++)
        {
            temp[i]=vec[i];
        }
        max_Size=max_Size*2;
        delete [] vec;
        vec=temp;
    }
    void push_back(T element)
    {
        if(curr_Size==max_Size)
        {
            doubleSize();
        }
        vec[curr_Size++]=element;
    }
    size_t size() const
    {
        return curr_Size;
    }
    T at(size_t position) const
    {
        return vec[position];
    }
    T* begin() const
    {
        return vec;
    }
    T* end() const
    {
        return vec+curr_Size-1;
    }
    T operator[] (size_t position) const
    {
      return vec[position];
    }
};
template<typename T1>
T1 accumulate(auto coavector)
    {
      if(coavector.size()==0)
        return T1();
      auto pt=coavector;
      T1 sum=pt[0];
      for(size_t i=1;i<coavector.size();i++)
      {
        sum=sum+pt[i];
      }
      return sum;
    }
template<typename T2>
T2 accumulate(std::vector<T2> &stdvector)
    {
      if(stdvector.size()==0)
        return T2();
      auto pt=stdvector;
      T2 sum=pt[0];
      for(size_t i=1;i<stdvector.size();i++)
      {
        sum=sum+pt[i];
      }
      return sum;
    }
} // namespace coa

template <typename CoaVector, typename StdVector> class _Test {

public:
  static inline bool size_check(CoaVector &coaVector, StdVector &stdVector) {
#ifdef SIZE_CHECK
    return (coaVector.size() == stdVector.size());
#else
    return false;
#endif
  }

  static bool equality_check(CoaVector &coaVector, StdVector &stdVector) {
    if (!size_check(coaVector, stdVector))
      return false;

    std::size_t len = coaVector.size();
    std::size_t i = 0;

    bool check = true;

    while (i != len) {
      check &= (coaVector[i] == stdVector[i]);
      check &= (coaVector.at(i) == stdVector.at(i));
      i++;
    }
    return check;
  }

  static bool accumulate_check(CoaVector &coaVector, StdVector &stdVector) {

#ifdef ACCUMULATE_CHECK
    if (!size_check(coaVector, stdVector))
      return false;

    if (coaVector.size() == 0)
      return true;

    auto coa_coa = coa::accumulate(coaVector);

    auto coa_std = coa::accumulate(stdVector);

    auto std_coa = coaVector[0];
    int i = 1;
    while (i != coaVector.size())
      std_coa += coaVector[i++];

    auto std_std = std::accumulate(stdVector.begin() + 1, stdVector.end(),
                                   *stdVector.begin());

    return std_coa == std_std && std_std == coa_coa && coa_coa == coa_std;
#else
    return false;
#endif
  }
};

template <typename CoaVector, typename StdVector, typename T>
class Test : public _Test<CoaVector, StdVector> {

public:
  void operator()() {
    CoaVector coaVector;
    StdVector stdVector;
    unsigned int score = 0;
    for (int i = 0; i < 100; i++) {
      unsigned int r = rand();

      unsigned int command = r % 4;
      bool check;

      if (command == 0) {
        check = this->size_check(coaVector, stdVector);

        if (check) {
           cout << "Size Check Passed" << endl;
          score++;
        } else {
          cout << "Size Check Failed" << endl;
        }

      } else if (command == 1) {
        check = this->equality_check(coaVector, stdVector);

        if (check) {
           cout << "Equality Check Passed" << endl;
          score++;
        } else {
          cout << "Equality Check Failed" << endl;
        }

      } else if (command == 2) {
        check = this->accumulate_check(coaVector, stdVector);
        if (check) {
           cout << "Accumulate Check Passed" << endl;
          score++;
        } else {
          cout << "Accumulate Check Failed" << endl;
        }
      } else {
        T e = T();
        coaVector.push_back(e);
        stdVector.push_back(e);
        score++;
      }
    }
    cout << "Total Score : " << score << endl;
  }
};

int main() {
  srand(time(NULL));

  auto t1 = Test<coa::vector<Complex>, std::vector<Complex>, Complex>();
  t1();

  auto t2 = Test<coa::vector<int>, std::vector<int>, int>();
  t2();
}