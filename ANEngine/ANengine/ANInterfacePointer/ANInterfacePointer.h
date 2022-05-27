#pragma once

template <class T>
class ANInterfacePointer
{
public:
	T* m_Pointer;

	ANInterfacePointer();
	~ANInterfacePointer();

	template <class O>
	ANInterfacePointer(ANInterfacePointer<O>& o);

	T* operator->();
	T& operator*();

	template<class O>
	ANInterfacePointer<T>& operator=(ANInterfacePointer<O>& o);
};

template <class T>
ANInterfacePointer<T>::ANInterfacePointer()
{
	this->m_Pointer = new T();
}

template <class T>
ANInterfacePointer<T>::~ANInterfacePointer()
{
	if (this->m_Pointer != nullptr)
		delete this->m_Pointer;
}

template<class T>
template<class O>
ANInterfacePointer<T>::ANInterfacePointer(ANInterfacePointer<O>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
}

template<class T>
T* ANInterfacePointer<T>::operator->()
{
	return this->m_Pointer;
}

template<class T>
T& ANInterfacePointer<T>::operator*()
{
	return *this->m_Pointer;
}

template<class T>
template<class O>
ANInterfacePointer<T>& ANInterfacePointer<T>::operator=(ANInterfacePointer<O>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
	return *this;
}