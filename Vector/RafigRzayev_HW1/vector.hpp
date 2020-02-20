#pragma once

#include <cstddef>
#include <initializer_list>

template <typename T> class Vector {
public:
  // Constructor 1
  Vector(size_t size) : size_{size}, capacity_{size} {
    if (size) {
      data_ = new T[capacity_]{};
    }
  }

  // Constructor 2
  Vector(std::initializer_list<T> list) {
    const size_t COUNT{list.size()};
    if (COUNT) {
      size_ = capacity_ = COUNT;
      alloc(list.begin(), list.end());
    }
  }

  // Constructor 3
  Vector(T *begin, T *end) {
    if (begin == nullptr || end == nullptr || begin >= end) {
      return;
    }
    size_ = capacity_ = end - begin;
    alloc(begin, end);
  }

  // Copy Constructor
  Vector(const Vector &rhs) : size_{rhs.size_}, capacity_{rhs.capacity_} {
    if (rhs.data_ == nullptr) {
      return;
    }
    alloc(rhs.data_, rhs.data_ + size_);
  }

  // Destructor
  ~Vector() { delete[] data_; }

  // Copy Assignment
  Vector &operator=(const Vector &rhs) {
    if (this == &rhs) {
      return *this;
    }
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    delete[] data_;
    if (rhs.data_ == nullptr) {
      data_ = nullptr;
      return *this;
    }
    alloc(rhs.data_, rhs.data_ + size_);
    return *this;
  }

  void push_back(T value) { add(value); }

  void push_front(T value) {
    if (data_ == nullptr) {
      data_ = new T{value};
      capacity_ = size_ = 1;
      return;
    }
    if (size_ == capacity_) {
      reserve(capacity_ * 2);
    }
    // Shift values
    T *new_data = new T[capacity_];
    copy(new_data + 1, data_, data_ + size_);
    delete[] data_;
    data_ = new_data;
    *data_ = value;
    ++size_;
  }

  // IN PROGRESS
  // этот метод являеться опциональным
  /*template <typename T1>
  void emplace_back(T1 value)*/

  T *insert(T value) {
    add(value);
    return data_ + size_ - 1;
  }

  T *erase(size_t pos) {
    // CASE 1: Invalid input or Empty vector
    if (pos >= size_) {
      return nullptr;
    }
    // CASE 2: Delete whole vector
    if (size_ == 1) {
      clear();
      return data_;
    }
    // CASE 3: Shift vector and decrease size
    T *element{data_ + pos};
    copy(element, element + 1, data_ + size_--);
    return element;
  }

  // IN PROGRESS
  // call to erase(0) ->  error: call of overloaded ‘erase(int)’ is ambiguous
  // T *erase(int *pos);

  T *erase(T *begin, T *end) {
    // CASE 1: Invalid input or Empty vector
    if (begin < data_ || begin >= data_ + size_) {
      return nullptr;
    }
    if (end <= begin || end > data_ + size_) {
      return nullptr;
    }
    // CASE 2: Delete whole vector
    const size_t ERASE_COUNT = end - begin;
    if (size_ == ERASE_COUNT) {
      clear();
      return data_;
    }
    // CASE 3: Shift vector and decrease size
    T *new_data = new T[size_ - ERASE_COUNT];
    copy(new_data, data_, begin);
    const ptrdiff_t CURRENT_POS{begin - data_};
    copy(new_data + CURRENT_POS, end, data_ + size_);
    delete[] data_;
    data_ = new_data;
    size_ -= ERASE_COUNT;
    return data_;
  }

  void resize(size_t count) {
    if (count == size_) {
      return;
    }
    if (count == 0) {
      clear();
      return;
    }
    if (count > size_) {
      if (count > capacity_) {
        reserve(count);
      }
      T *begin = data_ + size_;
      const T *const end = data_ + count;
      while (begin != end) {
        *begin++ = T{};
      }
    }
    size_ = count;
    return;
  }

  void reserve(size_t new_cap) {
    if (new_cap <= capacity_) {
      return;
    }
    capacity_ = new_cap;
    T *new_data = new T[capacity_]{};
    copy(new_data, data_, data_ + size_);
    delete[] data_;
    data_ = new_data;
  }

  T *begin() const { return data_; }
  T *end() const { return data_ + size_; }
  T back() const { return *(data_ + size_ - 1); }
  T front() const { return *data_; }
  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
  bool empty() const { return !size_; }
  T &operator[](size_t pos) { return data_[pos]; }
  const T &operator[](size_t pos) const { return data_[pos]; }

private:
  T *data_{};
  size_t size_{};
  size_t capacity_{};

  // Copies values from source sequence to destination
  void copy(T *dst, const T *src_begin, const T *const src_end) {
    while (src_begin != src_end) {
      *dst++ = *src_begin++;
    }
  }

  // Deletes vector data. Sets size_ and capacity_ to 0.
  void clear() {
    size_ = capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
  }

  // Allocates memory for data_ by capacity_, then copies values
  void alloc(const T *begin, const T *const end) {
    data_ = new T[capacity_];
    copy(data_, begin, end);
  }

  // Add element to the end of vector
  void add(T &value) {
    if (data_ == nullptr) {
      data_ = new T{value};
      capacity_ = size_ = 1;
    } else {
      if (size_ == capacity_) {
        reserve(capacity_ * 2);
      }
      *(data_ + size_++) = value;
    }
  }
};