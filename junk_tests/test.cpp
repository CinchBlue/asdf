#include <iostream>
#include <exception>

template <typename T>
struct Maybe {
  T data;
  bool g;

  Maybe<T> (T data) :
    data(data),
    g(true) { }

  bool good() const {
    return g;
  }

  bool fail() {
    g = false;
  }

  T operator() () {
    if (good) {
      return data;
    } else {
      throw std::ios_base::failure("ERROR: Bad Maybe cast.");
    }
  }
};


int main() {
  auto data = Maybe<int>(1);
}