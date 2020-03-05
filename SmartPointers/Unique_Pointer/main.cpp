#include "Unique_Ptr.hpp"
#include <utility>

struct X {};
struct Y : public X {};

int main() {
  Unique_Ptr<X> x(new X);
  Unique_Ptr<Y> y(new Y);

  x = std::move(y);
  Unique_Ptr<X> z(std::move(y));
  Unique_Ptr<X> obj(nullptr);
}
