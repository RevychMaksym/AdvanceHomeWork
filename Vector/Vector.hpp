#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

template <typename T>
class Vector {
public:
	Vector(size_t size) : _size(0), _capacity(size), _data{ new T[_capacity] } {
		try {
			std::cout << "Size_t constructor!" << std::endl;
			_data = new T[_capacity]{};
		}
		catch (std::bad_array_new_length&) {
			std::cout << "Incorrect length" << std::endl;
		}
		catch (std::bad_alloc&) {
			std::cout << "Incorrect length" << std::endl;
		}
	};

	Vector(const std::initializer_list<T>& init_list)
		: _size(init_list.size()), _capacity(_size * 2) {
		std::cout << "Init_list constructor!" << std::endl;
		copy(init_list.begin(), init_list.end());
	}

	Vector(const T* begin, const T* const end)
		: _size(std::distance(begin, end)), _capacity(_size * 2) {
		std::cout << "Array constructor" << std::endl;
		copy(begin, end);
	}

	Vector(const Vector<T>& object)
		: _size(object._size), _capacity(object._capacity) {
		initialise_object(object);
	}

	const Vector<T>& operator=(const Vector<T>& object) {
		if (this == &object) {
			return *this;
		};
		_size = object._size;
		_capacity = object._capacity;
		initialise_object(object);
		return *this;
	}

	Vector(const Vector&& rhs) : _data{ rhs._data }, _capacity{ rhs._capacity }, _size{ rhs._size }{
		rhs._data = nullptr;
		rhs._size = 0;
		rhs._capacity = 0;
		std::cout << __FUNCTION__ << std::endl;
	}

	Vector<T>& operator=(const Vector&& rhs) {
		_data = rhs._data;
		_capacity = rhs._capacity;
		_size = rhs._size;
		rhs._data = nullptr;
		rhs._size = 0;
		rhs._capacity = 0;
	}

	T& operator[](size_t index) { return _data[index]; }
	~Vector() { delete[] _data; }

	T* begin() { return _data; }

	T* end() { return (_data + _size); }

	void push_back(T value) {
		if (_data != nullptr) {
			insert(value, _size);
		}
		else {
			std::cout << "Error push_back {value} failed!" << std::endl;
		}
	}

	void pop_back() {
		if (_data != nullptr) {
			erase(end() - 1);
			--_size;
		}
		else {
			std::cout << "Error pop_back failed" << std::endl;
		}
	}
	void push_front(T value) {
		if (_data != nullptr) {
			insert(value, 0);
		}
		else {
			std::cout << "Error push_front {value} failed!" << std::endl;
		}
	}

	void swap(Vector<T>& _vector) {
		std::swap(_data, _vector._data);
	}

	size_t insert(T value, size_t pos) {
		if (_data != nullptr) {
			if (needs_alloc() || pos > _capacity) {
				allocate_memory();
			}
			size_t pos_counter = pos;
			for (size_t counter = _size; counter > pos_counter; --counter) {
				_data[counter] = _data[counter - 1];
			}
			_data[pos_counter] = value;
			_size++;
		}
		return pos;
	}

	T* erase(size_t pos) { return eraser(&_data[pos], 1); }

	T* erase(T* pos) {
		std::cout << "Erase T* pos" << std::endl;
		return eraser(pos, 1);
	}

	T* erase(T* _begin, T* _end) {
		std::cout << "Erase T* begin, T* end" << std::endl;
		return eraser(_begin, std::distance(_begin, _end));
	}

	T back() const { return _size; }

	T front() const {
		if (_data != nullptr) {
			return 0;
		}
	}

	void resize(size_t new_size) {
		if (_data == nullptr) {
			std::cout << "Resize Error #0001x1 - resizing failed! " << std::endl;
			return;
		}
		if (new_size == _capacity) {
			return;
		}

		if (new_size < _size) {
			_size = new_size;
		}
		_capacity = new_size;
		allocate_memory();
	}

	void clear() { delete[] _data; };

	void print() {
		for (size_t i = 0; i < _size; ++i) {
			std::cout << _data[i] << " ";
		}
		std::cout << "\n";
	}
	size_t getsize() const { return _size; }
	size_t getcapacity() const { return _capacity; }
	bool empty() const { return _size == 0; }

private:
	bool needs_alloc() const { return _size >= _capacity; }

	void allocate_memory() {
		_capacity *= 2;
		T* temp = new T[_capacity]{};

		for (unsigned i = 0; i < _size; ++i) {
			temp[i] = std::move(_data[i]);
		}
		delete[] _data;
		_data = temp;
	}

	void initialise_object(const Vector<T>& object) {
		std::cout << "Initialise object" << std::endl;
		_data = new T[object._size];
		memcpy(_data, object._data, sizeof(T) * _size);
	}

	T* eraser(T* begin, size_t counter) {
		T* temp_begin = begin;
		while (begin < end()) {
			*begin = *(begin + counter);
			begin++;
		}
		return temp_begin;
	}

	void copy(const T* begin, const T* const end) {
		_data = new T[_capacity];
		T* temp_begin = _data;
		while (begin != end) {
			*temp_begin++ = *begin++;
		}
	}

private:
	T* _data;
	size_t _size;
	size_t _capacity;
};
