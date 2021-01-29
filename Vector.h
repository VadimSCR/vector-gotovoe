#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include "VectorException.h"


template<typename T>
class Vector
{
	size_t size, capacity, maxSize;
	T* ptrData;

	void changeCapacity(const size_t newCapacity);
public:
	Vector(size_t = 0);
	Vector(size_t, const T&);
	Vector(const Vector&, size_t = -1);
	~Vector();

	// ELEMENT ACCESS
	T& operator[](const size_t);
	const T& operator[](const size_t) const;

	T& at(const size_t);
	const T& at(const size_t) const;

	// MODIFIERS
	void insert(const size_t, const T&);
	void insert(const size_t index, const Vector& other);
	void pushBack(const T&);
	void pushBack(const Vector& other);
	void clear();
	T remove(const size_t);
	T popBack();

	// CAPACITY
	bool isEmpty() const;
	void resize(const size_t);
	size_t getMaxSize() const;
	size_t getSize() const;
	size_t getCapacity() const;

	// NON-MEMBER FUNCTINS
	const Vector& operator=(const Vector&);
	bool operator==(const Vector&) const;

	template<typename OT> 
	friend std::ostream& operator<<(std::ostream&, const Vector<OT>&);
};


template<typename T>
Vector<T>::Vector(size_t _size) : maxSize(-1) {
	if (_size == maxSize) throw VectorException<T>();
	size = _size;
	if (size) capacity = 8;
	else {
		capacity = (size << 1);
		capacity = capacity < maxSize && capacity <= size ? maxSize : capacity;
	}
	ptrData = new T[capacity]{};
}

template<typename T>
Vector<T>::Vector(size_t _size, const T& value) : Vector<T>(_size) {
	for (size_t i = 0; i < size; i++) ptrData[i] = value;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& v, size_t _size) : maxSize(-1) {
	if (_size == maxSize) {
		size = v.size;
		capacity = v.capacity;
	}
	else {
		size = _size;
		capacity = (size << 1);
		capacity = capacity < maxSize && capacity <= size ? maxSize : capacity;
	}
	ptrData = new T[capacity]{};

	for (size_t i = 0; i < v.size; i++) ptrData[i] = v.ptrData[i];
}

template<typename T>
Vector<T>::~Vector() {
	if (ptrData != 0) delete[] ptrData;
}


// ELEMENT ACCESS
template<typename T>
T& Vector<T>::operator[](const size_t index) {
	return ptrData[index];
}

template<typename T>
const T& Vector<T>::operator[](const size_t index) const {
	return ptrData[index];
}

template<typename T>
T& Vector<T>::at(const size_t index) {
	if (index < size) return ptrData[index];
	else throw VectorException<T>();
}

template<typename T>
const T& Vector<T>::at(const size_t index) const {
	if (index < size) return ptrData[index];
	else throw VectorException<T>();
}


// CAPACITY
template<typename T>
bool Vector<T>::isEmpty() const { return size == 0; }

template<typename T>
void Vector<T>::resize(const size_t newSize) {
	if (size == newSize) return;
	if (newSize == maxSize) throw VectorException<T>();
	if (newSize > capacity)
		*this = Vector<T>(*this, newSize);
	else if (newSize < size)
		for (size_t i = newSize; i < size; i++)
			ptrData[i] = 0;
	
}

template<typename T>
size_t Vector<T>::getMaxSize() const { return maxSize; }

template<typename T>
size_t Vector<T>::getSize() const { return size; }

template<typename T>
size_t Vector<T>::getCapacity() const { return capacity; }



// MODIFIERS
template<typename T>
void Vector<T>::insert(const size_t pos, const T& value) {
	if (pos > size) throw VectorException<T>();
	if (size == capacity) changeCapacity(size + 1);
	for (size_t i = size - 1; i >= pos; i--)
		ptrData[i + 1] = ptrData[i];
	ptrData[pos] = value;
	size++;
}

template<typename T>
void Vector<T>::insert(const size_t pos, const Vector<T>& v) {
	if (pos > size) throw VectorException<T>();
	if ((size + v.size) >= capacity)
		changeCapacity(size + v.size + 1);

	for (size_t i = size + v.size - 1; i >= pos + v.size; i--)
		ptrData[i] = ptrData[i - v.size];

	for (size_t i = v.size - 1; i >= 0 && i != maxSize; i--)
		ptrData[pos + i] = v.ptrData[i];
	size += v.size;
}

template<typename T>
void Vector<T>::pushBack(const T& value) {
	insert(size, value);
}

template<typename T>
void Vector<T>::pushBack(const Vector<T>& v) {
	insert(size, v);
}

template<typename T>
void Vector<T>::clear() {
	for (size_t i = 0; i < size; i++) ptrData[i] = 0;
}

template<typename T>
T Vector<T>::remove(const size_t index) {
	if (index >= size) throw VectorException<T>();

	T removedItem = ptrData[index];
	for (size_t i = index; i < size - 1; i++)
		ptrData[i] = ptrData[i + 1];

	ptrData[--size] = 0;
	return removedItem;
}

template<typename T>
T Vector<T>::popBack() { return remove(size - 1); }




// NON-MEMBER FUNCTINS
template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
	if (this != &v) {
		if (ptrData != 0) delete[] ptrData;

		size = v.size;
		capacity = v.capacity;
		ptrData = new T[size]{};

		for (size_t i = 0; i < size; i++)
			ptrData[i] = v.ptrData[i];
	}
	return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& v) const {
	if (this == &v) return true;
	if (size == v.size) {
		for (size_t i = 0; i < size; i++)
			if (ptrData[i] != v.ptrData[i])
				return false;
		return true;
	}
	return false;
}

template<typename OT>
std::ostream& operator<<(std::ostream& out, const Vector<OT>& v) {
	for (size_t i = 0; i < v.getSize(); i++) 
		out << v.ptrData[i] << " ";
	return out;
}



// PRIVATE METHODS
template<typename T>
void Vector<T>::changeCapacity(const size_t newCapacity) {
	capacity = newCapacity < (capacity << 1) ? (capacity << 1) : newCapacity;

	T* newData = new T[capacity]{};
	for (size_t i = 0; i < size; i++)
		newData[i] = ptrData[i];

	delete[] ptrData;
	ptrData = newData;
}

#endif