#pragma once

template <class T>
class ANInterfacePointer
{
public:
	mutable T* m_Pointer;

	ANInterfacePointer();
	~ANInterfacePointer();

	template <class O>
	ANInterfacePointer(ANInterfacePointer<O>& o);

	T* get();

	T* operator->();
	T& operator*();

	ANInterfacePointer<T>& operator=(const ANInterfacePointer<T>& o);

	template<class O>
	ANInterfacePointer<T>& operator=(const ANInterfacePointer<O>& o);
	
	void release();
private:
};

template <class T>
ANInterfacePointer<T>::ANInterfacePointer()
{
	this->m_Pointer = new T();
}

template <class T>
ANInterfacePointer<T>::~ANInterfacePointer()
{
	release();
}

template<class T>
template<class O>
ANInterfacePointer<T>::ANInterfacePointer(ANInterfacePointer<O>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
}

template <class T>
T* ANInterfacePointer<T>::get()
{
	return this->m_Pointer;
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
ANInterfacePointer<T>& ANInterfacePointer<T>::operator=(const ANInterfacePointer<T>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
	return *this;
}

template<class T>
template<class O>
ANInterfacePointer<T>& ANInterfacePointer<T>::operator=(const ANInterfacePointer<O>& o)
{
	this->m_Pointer = o.m_Pointer;
	o.m_Pointer = nullptr;
	return *this;
}

template<class T>
void ANInterfacePointer<T>::release()
{
	if (this->m_Pointer != nullptr)
	{
		delete this->m_Pointer;
		this->m_Pointer = nullptr;
	}
}