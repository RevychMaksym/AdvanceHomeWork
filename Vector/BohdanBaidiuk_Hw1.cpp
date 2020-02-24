#include "Vector.h"
#include <iostream>

int main() {
  Stack<int> v(5);
  Stack<int> v1(v);
  v.push(1);
  v.top();
  v.push(2);
  v.pop();

  return 0;
};
