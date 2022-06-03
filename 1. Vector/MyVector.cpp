#include<iostream>
using namespace std;
#include"MyVector.h"

template<typename T>
Vector<T>::Vector(size_t initSize,size_t initCapacity,int x):siz(initSize),cap(initCapacity)
{
	v = new T[cap];
	for(int i=0 ; i<siz ; i++)
		v[i] = x;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] v;
}

template<typename T>
size_t Vector<T>::size() const {return siz;}

template<typename T>
size_t Vector<T>::capacity() const {return cap;}

template<typename T>
bool Vector<T>::empty() const {return siz==0;}

template<typename T>
void Vector<T>::reserve(size_t n)
{
	T* tmp = new T[cap = n];
	siz = std::move(n,siz);
	for(int i=0 ; i<siz ; i++)
		tmp[i] = v[i];
	delete[] v;
	v = t;
}

