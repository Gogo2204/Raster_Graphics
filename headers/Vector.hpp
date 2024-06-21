#pragma once
#include <iostream>
#include <exception>

template <typename T>
class Vector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void free();
	void resize();

public:
	Vector();
	Vector(size_t size);

	Vector(const Vector <T>& other);
	Vector<T>& operator=(const Vector<T>& other);

	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	~Vector() noexcept;

	void push_back(const T& elem);
	void push_back(const T&& elem) noexcept;

	void pop_back();

	void insert(const T& elem, size_t index);
	void insert(const T&& elem, size_t index);

	void erase(size_t index);
	void clear();
	bool isEmpty() const;
	size_t getSize() const;
};

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	data = new T[other.size];
	for (size_t i = 0; i < other.size; i++)
	{
		data[i] = other.data[i];
	}
	size = other.size;
	capacity = other.capacity;
}

template<class T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

template <typename T>
void Vector<T>::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

template <typename T>
void Vector<T>::resize()
{
	size_t newCap = (capacity + 1) * 2;
	T* newData = new T[newCap];
	capacity = newCap - 1;

	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}

template <typename T>
Vector<T>::Vector()
{
	size = 0;
	capacity = 8;
	data = new T[capacity];
}

template <typename T>
Vector<T> ::Vector(size_t size)
{
	this->size = 0;
	capacity = size;
	data = new T[capacity];
}

template <typename T>
Vector<T> ::Vector(const Vector <T>& other)
{
	copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T> :: operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Vector<T> ::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= size)
		throw std::out_of_range("The index is out of range!");
	return data[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range("The index is out of range!");
	return data[index];
}

template <typename T>
Vector<T>::~Vector() noexcept
{
	free();
}

template <typename T>
void Vector<T>::push_back(const T& elem)
{
	if (size == capacity)
		resize();
	size++;
	data[size - 1] = elem;
}

template <typename T>
void Vector<T>::push_back(const T&& elem) noexcept
{
	if (size == capacity)
		resize();
	size++;
	data[size - 1] = std::move(elem);
}

template <typename T>
void Vector<T>::pop_back()
{
	if (isEmpty())
		throw std::logic_error("The vector is already empty!");
	size--;
}

template <typename T>
void Vector<T>::insert(const T& elem, size_t index)
{
	if (index >= size)
		throw std::out_of_range("The index is out of range!");

	if (size == capacity)
		resize();

	size++;
	for (int i = size - 1; i > index; i--)
		data[i] = data[i - 1];

	data[index] = elem;
}

template <typename T>
void Vector<T>::insert(const T&& elem, size_t index)
{
	if (index >= size)
		throw std::out_of_range("The index is out of range!");

	if (size == capacity)
		resize();

	size++;
	for (int i = size - 1; i > index; i--)
		data[i] = std::move(data[i - 1]);

	data[index] = std::move(elem);
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

template <typename T>
void Vector<T>::clear()
{
	free();
	capacity = 8;
	data = new T[capacity];
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return this->size;
}
