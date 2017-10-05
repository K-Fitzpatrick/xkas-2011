#pragma once

#include "base.h"

#define LISTSTARTLEN 0x20

namespace xkas
{
	template<class T>
	class list
	{
	public:
		T **data;
		int count, capacity;

		list();
		list(const int size);
		~list();

		T *get(const int index);
		void listalloc(const int size);
	};

	template<class T>
	list<T>::list()
	{
		this->data = (T**)malloc(LISTSTARTLEN * sizeof(T*));
		this->capacity = this->count = LISTSTARTLEN;
		do this->data[--this->count] = new T();
		while (this->count);
	}

	template<class T>
	list<T>::list(const int size)
	{
		this->data = (T**)malloc(size * sizeof(T*));
		this->capacity = this->count = size;
		do this->data[--this->count] = new T();
		while (this->count);
	}

	template<class T>
	list<T>::~list()
	{
		do delete this->data[--this->capacity];
		while (this->capacity);
		free(this->data);
	}
	
	template<class T>
	T *list<T>::get(const int index)
	{
		if (index >= this->capacity)
			listalloc(index + 1);
		if (index >= this->count)
			this->count = index + 1;
		return this->data[index];
	}

	template<class T>
	void list<T>::listalloc(const int size)
	{
		const int x = mallocresize(size);
		this->data = (T**)realloc(this->data, x * sizeof(T*));
		do this->data[this->capacity] = new T();
		while (++this->capacity < x);
	}
}