#pragma once

template <typename T>
class Unique_Ptr {
  T* data;

 public:
  Unique_Ptr() : data(nullptr) {}
  explicit Unique_Ptr(T* data) : data(data) {}
  Unique_Ptr(std::nullptr_t) : data(nullptr) {}
  Unique_Ptr& operator=(std::nullptr_t) {
    reset();
    return *this;
  }
  Unique_Ptr(Unique_Ptr&& moving) noexcept { moving.swap(*this); }
  Unique_Ptr& operator=(Unique_Ptr&& moving) noexcept {
    moving.swap(*this);
    return *this;
  }

  Unique_Ptr(Unique_Ptr const&) = delete;
  Unique_Ptr& operator=(Unique_Ptr const&) = delete;

  T* operator->() const { return data; }
  T& operator*() const { return *data; }

  template <typename U>
  Unique_Ptr(Unique_Ptr<U>&& moving) {
    Unique_Ptr<T> tmp(moving.release());
    tmp.swap(*this);
  }

  template <typename U>
  Unique_Ptr& operator=(Unique_Ptr<U>&& moving) {
    Unique_Ptr<T> tmp(moving.release());
    tmp.swap(*this);
    return *this;
  }
  T* get() const { return data; }
  explicit operator bool() const { return data; }

  T* release() noexcept {
    T* result = nullptr;
    std::swap(result, data);
    return result;
  }

  void swap(Unique_Ptr& src) noexcept { std::swap(data, src.data); }

  void reset() {
    T* tmp = release();
    delete tmp;
  }

  ~Unique_Ptr() { delete data; }
};
