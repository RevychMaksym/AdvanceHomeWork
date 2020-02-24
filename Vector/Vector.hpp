enum { delta = 2 };

template <class T>
class Vector {
public:
  Vector() = delete;
  Vector(const size_t size);
  Vector(std::initializer_list<T> args);
  Vector(const T *begin, const T *const end);
  Vector(const Vector &rhs);
  Vector(Vector &&rhs);
  ~Vector();
  Vector &operator=(const Vector &rhs);
  Vector &operator=(Vector &&rhs);

  T *begin() const;
  T *end() const;
  void push_back(const T &value);
  void push_back(T &&value);
  void push_front(const T &value);
  void pop_back();
  template <class... Arg> void emplace_back(Arg &&... args);

  T *insert(const size_t pos, const T value);
  T *erase(const size_t pos);
  T *erase(const int *pos);
  T *erase(const T *begin, const T *const end);
  T back() const;
  T front() const;

  T &operator[](size_t pos);
  const T &operator[](size_t pos) const;
  void resize(const size_t count);
  void reserve(const size_t new_cap);
  size_t size() const;
  size_t capacity() const;
  bool empty() const;

private:
  size_t capacity_{10};
  T *data_{};
  size_t size_{};
};

template <class T>
class Stack : private Vector<T> {
public:
  Stack() = default;
  Stack(const size_t size) : Vector<T>(size){};
  Stack(const Stack &rhs) : Vector<T>(rhs){};
  Stack(Stack &&rhs) : Vector<T>(rhs){};
  ~Stack() { Vector<T>::~Vector(); };
  Stack &operator=(const Stack &rhs) { Vector<T>::operator=(rhs); };
  Stack &operator=(Stack &&rhs) { Vector<T>::operator=(rhs); };

  void push(T value) { Vector<T>::push_back(value); };
  void top() {
    std::cout << Vector<T>::back();
    ;
  };
  void pop() { Vector<T>::pop_back(); };

private:
};

template <class T>
Vector<T>::Vector(size_t size)
    : data_{new T[size]{}}, capacity_{size * delta}, size_{size} {}

template <class T>
Vector<T>::Vector(const Vector &rhs)
    : data_{new T[rhs.size_]{}}, capacity_{rhs.capacity_}, size_{rhs.size_} {}

template <class T>
Vector<T>::Vector(std::initializer_list<T> args)
    : capacity_{args.size() * delta} {
  data_ = new T[args.size()];
  size_ = 0;
  for (T x : args) {
    data_[size_++] = x;
  }
}

template <class T> Vector<T>::Vector(const T *begin, const T *const end) {
  if (begin == nullptr || end == nullptr || begin == end) {
    return;
  }
  size_ = std::distance(begin, end);
  capacity_ = size_ * delta;
  data_ = new int[size_];
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = *begin++;
  }
}

template <class T>
Vector<T>::Vector(Vector &&rhs)
    : capacity_{rhs.capacity_ * delta}, data_{rhs.data_}, size_{rhs.size_} {
  rhs.data_ = nullptr;
  rhs.capacity_ = 0;
  rhs.size_ = 0;
}

template <class T>
Vector<T>::~Vector() {
  if (data_ == nullptr) {
    return;
  }
  delete[] data_;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector &arg) {
  if (this == &arg) {
    return *this;
  }
  delete[] data_;
  size_ = arg.size_;
  capacity_ = arg.capacity_;
  data_ = new T[size_];
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = arg.data_[i];
  }
  return *this;
}
template <class T>
Vector<T> &Vector<T>::operator=(Vector &&rhs) {
  data_ = rhs.data_;
  capacity_ = rhs.capacity_;
  size_ = rhs.size_;
  rhs.data_ = nullptr;
  rhs.capacity_ = 0;
  rhs.size_ = 0;
  return *this;
}

template <class T>
T *Vector<T>::begin() const {
  if (data_ == nullptr) {
    return 0;
  }
  return data_;
}

template <class T>
T *Vector<T>::end() const {
  if (data_ == nullptr) {
    return 0;
  }
  return data_ + size_;
}

template <class T>
void Vector<T>::push_back(const T &value) {
  if (size_ == capacity_) {
    capacity_ *= delta;
  }
  data_[size_++] = value;
}

template <class T>
void Vector<T>::push_back(T &&value) {
  if (size_ == capacity_) {
    capacity_ *= delta;
  }
  data_[size_++] = std::move(value);
}

template <class T>
void Vector<T>::push_front(const T &value) {
  if (data_ == nullptr) {
    return;
  }
  data_[0] = value;
}

template <class T>
void Vector<T>::pop_back() {
  if (data_ == nullptr) {
    return;
  }
  --size_;
}

template <class T>
template <class... Arg>
void Vector<T>::emplace_back(Arg &&... args) {
  new (&data_[size_++]) T{std::forward<Arg...>(args...)};
}

template <class T>
T *Vector<T>::insert(const size_t pos, const T value) {
  if (size_ < pos) {
    return 0;
  }
  if (size_ == capacity_) {
    capacity_ *= delta;
  }
  ++size_;
  for (size_t i = size_; i > pos; --i) {
    if (i >= pos) {
      std::swap(data_[i - 1], data_[i]);
    }
  }
  data_[pos] = value;
  return data_;
}

template <class T>
T *Vector<T>::erase(const size_t pos) {
  if (size_ < pos&&pos<=0) {
    return 0;
  }
  for (int i = pos; i < size_; ++i) {
    data_[i - 1] = data_[i];
  }
  --size_;
  return data_;
}

template <class T>
T *Vector<T>::erase(const int *pos) {
  if (pos == nullptr) {
    return 0;
  }
  for (size_t i = 0; i < size_; ++i) {
    if (data_[i] == *pos) {
      data_[i] = data_[i + 1];
    }
  }
  --size_;
  return data_;
}

template <class T>
T *Vector<T>::erase(const T *begin, const T *const end) {
  if (begin == nullptr || end == nullptr || begin == end) {
    return 0;
  }
  T *end_erase = end;
  const T *const new_end = begin + std::distance(begin, end);
  while (begin != new_end) {
    *begin++ = *end_erase++;
    --size_;
  }
  return begin;
}

template <class T>
T Vector<T>::back() const { return data_[size_ - 1]; }

template <class T>
T Vector<T>::front() const { return data_[0]; }

template <class T>
T &Vector<T>::operator[](size_t pos) { return data_[pos]; }

template <class T>
const T &Vector<T>::operator[](size_t pos) const {
  return data_[pos];
}

template <class T>
void Vector<T>::resize(const size_t count) {
  if (size_ < count) {
    size_ = count;
    for (int i = size_; i < count; ++i) {
      data_[i] = 0;
    }
  } else if (size_ > count) {
    size_ = count;
  }
}

template <class T>
void Vector<T>::reserve(const size_t new_cap) {
  T *newData_ = new T[new_cap];
  for (size_t i = 0; i < size_; ++i) {
    newData_[i] = data_[i];
  }
  if (size_ > new_cap) {
    size_ = new_cap;
  }
  capacity_ = new_cap;
  delete[] data_;
  data_ = newData_;
}

template <class T>
size_t Vector<T>::size() const { return size_; }

template <class T>
size_t Vector<T>::capacity() const { return capacity_; }

template <class T>
bool Vector<T>::empty() const {
  return size_ == 0 ? false : true;
}
