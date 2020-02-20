#include "vector.hpp"
#include <iostream>

// Print vector contents
template <typename T> void print(Vector<T> &v) {
  std::cout << "-------------------------------------\n";
  std::cout << "Capacity: " << v.capacity() << std::endl;
  std::cout << "Size: " << v.size() << std::endl;
  std::cout << "Data: ";
  if (v.empty()) {
    std::cout << "Empty\n";
    return;
  }
  for (auto &i : v) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

// Demo code using vector class
int main() {
  std::cout << "\n****************** CONSTRUCTORS ******************\n";
  // Ctor 1 Vector(size_t size) 
  Vector<double> v1(4);
  // Ctor 2 Vector(std::initializer_list<T> list)
  Vector<int> v2({1, 2, 3, 4, 5, 6});
  // Ctor 3 Vector(T *begin, T *end)
  float a[3]{0.5, 1, 1.5};
  Vector<float> v3(a, a + 3);
  // Copy ctor
  Vector<int> v4{v2};
  // Copy oper
  Vector<float> v5(0);
  v5 = v3;
  // Show vectors
  print(v1);
  print(v2);
  print(v3);
  print(v4);
  print(v5);

  std::cout << "\n****************** INSERTION ******************\n";
  Vector<int> v({1, 2, 3, 4, 5, 6});
  print(v);
  v.insert(7);
  v.push_back(8);
  v.push_front(0);
  print(v);

  std::cout << "\n****************** DELETION ******************\n";
  Vector<int> v_({1, 2, 3, 4, 5, 6});
  print(v_);
  v_.erase(0);
  print(v_);
  v_.erase(v_.begin(), v_.end() - 1);
  print(v_);
  v_.erase(0);
  print(v_);

  std::cout << "\n****************** RESIZE ******************\n";
  Vector<int> _v({1, 2, 3, 4, 5, 6});
  print(_v);
  _v.resize(3);
  print(_v);
  _v.resize(6);
  print(_v);
  _v.resize(0);
  print(_v);
  _v.resize(10);
  print(_v);
  return 0;
}