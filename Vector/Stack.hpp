#pragma once
#include "Vector.hpp"

template<typename T>
class Stack : private Vector<T> {
public:
	Stack(size_t size) : Vector<T>::Vector(size) {
		std::cout << "Stack size of size" << std::endl;
	}
	void push(T value) {
		Vector<T>::push_back(value);
	}
	/*void emplace() {
		Vector<T>::emplace_back();
	}*/
	void pop() {
		Vector<T>::pop_back();
	}
	void swap(Stack<T>& container){
		Vector<T>::swap(container);
	}
	void print() {
		Vector<T>::print();
	}
};
