#pragma once

template <class T>
class ANPointer
{
public:
	T* m_Pointer;

	ANPointer();
	~ANPointer();

	template <class O>
	ANPointer(ANPointer<O>& o);

	T* operator->();

	template<class O>
	ANPointer<T>& operator=(ANPointer<O>& o);
};

template <class T>
ANPointer<T>::ANPointer()
{
	this->m_Pointer = new T();
}

template <class T>
ANPointer<T>::~ANPointer()
{
	if (this->m_Pointer != nullptr)
		delete this->m_Pointer;
}

template<class T>
template<class O>
ANPointer<T>::ANPointer(ANPointer<O>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
}

template<class T>
T* ANPointer<T>::operator->()
{
	return this->m_Pointer;
}

template<class T>
template<class O>
ANPointer<T>& ANPointer<T>::operator=(ANPointer<O>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
	return *this;
}