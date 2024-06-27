#pragma once
#include <iostream>
#include "Utility.h"

template<class T>
class Vector
{
public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(const Vector<T>& other);
	Vector& operator=(Vector<T>&& other) noexcept;
	~Vector();

	void push_back(const T& newElem);
	void push_back(T&& newElem);

	void pop_back();

	void setAtIndex(const T& element, size_t index);
	void setAtIndex(T&& element, size_t index);

	size_t getSize() const;
	void clear();
	void erase(size_t index);
	bool isEmpty() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

private:
	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);

	void resize(size_t newCap);

	T* data = nullptr;
	size_t size = Utility::DEFAULT_SIZE;
	size_t capacity = Utility::DEFAULT_CAPACITY;
};

template<class T>
Vector<T>::Vector() : Vector(8) {}

template<class T>
Vector<T>::Vector(size_t capacity) : size(0)
{
	this->capacity = Utility::nextPowerOfTwo(capacity);
	data = new T[this->capacity];
}

template<class T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{

	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	free();
}

template<class T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{

	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
void Vector<T>::copyFrom(const Vector<T>& other)
{

	data = new T[other.capacity];

	for (size_t i = 0; i < other.size; i++)
		data[i] = other.data[i];

	size = other.size;
	capacity = other.capacity;
}

template<class T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	data = other.data;
	other.data = nullptr;
	size = other.size;
	capacity = other.capacity;
}

template<class T>
void Vector<T>::free()
{
	delete[] data;
}

template<class T>
void Vector<T>::resize(size_t newCap)
{
	T* temp = data;
	data = new T[newCap];

	for (size_t i = 0; i < size; i++)
		data[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}

template<class T>
void Vector<T>::push_back(const T& newElem)
{
	if (size >= capacity)
		resize(capacity * 2);

	data[size++] = newElem;
}

template<class T>
void Vector<T>::push_back(T&& newElem)
{
	if (size >= capacity)
		resize(capacity * 2);

	data[size++] = std::move(newElem);
}

template<class T>
void Vector<T>::pop_back()
{
	if (size)
		size--;
	else
		throw std::length_error("Already empty!");

	if (size * 4 <= capacity && capacity > 1)
		resize(capacity / 2);
}

template<class T>
void Vector<T>::setAtIndex(const T& element, size_t index)
{
	if (index >= size)
		throw std::length_error("No such index!");

	data[index] = element;
}

template<class T>
void Vector<T>::setAtIndex(T&& element, size_t index)
{
	if (index >= size)
		throw std::length_error("No such index!");

	data[index] = std::move(element);
}

template <typename T>
void Vector<T>::clear()
{
	free();
	capacity = 8;
	data = new T[capacity];
}

template <typename T>
void Vector<T>::erase(size_t index)
{
	if (index >= size)
		throw std::out_of_range("The index is out of range!");

	for (size_t i = index; i < size - 1; i++)
		data[i] = std::move(data[i + 1]);
	size--;
}

template<class T>
size_t Vector<T>::getSize() const
{
	return size;
}

template<class T>
bool Vector<T>::isEmpty() const
{
	return size == Utility::DEFAULT_SIZE;
}

template<class T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index >= capacity)
		throw std::out_of_range("The index is out of range!");
	return data[index];
}


template<class T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= capacity)
		throw std::out_of_range("The index is out of range!");
	return data[index];
}