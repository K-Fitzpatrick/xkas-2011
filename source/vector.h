#pragma once

#include "base.h"

#define VECTORSTARTLEN 0x10

namespace xkas
{
	template <class T>
	class vector
	{
	public:
		T *data;
		int count, capacity;

		vector();
		~vector();

		T get(int index);
		void set(T val, int index);

		void push(T val);
		T pop();
		T peek();

		void realloc(int size);
	};

	template <class T>
	vector<T>::vector()
	{
		this->data = (T*)malloc(VECTORSTARTLEN * sizeof(T));
		this->capacity = VECTORSTARTLEN;
		this->count = 0;
	}
	
	template <class T>
	vector<T>::~vector()
	{
		free(this->data);
	}

	
	template <class T>
	T vector<T>::get(int index)
	{
		if (index >= this->capacity)
			realloc(index + 1);
        while (index >= this->count)
            this->data[this->count++] = T();
		return this->data[index];
	}

	
	template <class T>
	void vector<T>::set(T val, int index)
	{
		if (index >= this->capacity)
			realloc(index + 1);
		if (index >= this->count)
			this->count = index + 1;
		this->data[index] = val;
	}

	template <class T>
	void vector<T>::push(T val)
	{
		set(val, this->count);
	}
	
	template <class T>
	T vector<T>::pop()
	{
		return this->data[--this->count];
	}
	
	template <class T>
	T vector<T>::peek()
	{
		return this->data[this->count - 1];
	}
	
	template <class T>
	void vector<T>::realloc(int size)
	{
		this->capacity = mallocresize(size);
		this->data = (T*)::realloc(this->data, this->capacity);
	}
}