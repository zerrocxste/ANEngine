#pragma once

template <class T>
class ANImpPtr
{
public:
	ANImpPtr();
	T* operator->();
	T* m_Pointer;
private:
};

template <class T>
ANImpPtr<T>::ANImpPtr()
{
	this->m_Pointer = new (std::nothrow) T();
}

template<class T>
T* ANImpPtr<T>::operator->()
{
	return this->m_Pointer;
}

template <class T>
class ANInterfacePointer
{
public:
	T* m_Pointer;

	ANInterfacePointer()
	{
		this->m_Pointer = new (std::nothrow) T();
	}

	~ANInterfacePointer()
	{
		release();
	}

	template <class O>
	ANInterfacePointer(ANImpPtr<O>& o)
	{
		this->m_Pointer = o.m_Pointer;
	}

	T* get()
	{
		return this->m_Pointer;
	}

	T* operator->()
	{
		return this->m_Pointer;
	}

	T& operator*()
	{
		return *this->m_Pointer;
	}

	ANInterfacePointer<T>& operator=(const ANInterfacePointer<T>& o)
	{
		this->m_Pointer = o.m_Pointer;
		return *this;
	}

	ANInterfacePointer<T>& operator=(ANInterfacePointer<T>& o)
	{
		release();
		this->m_Pointer = o.m_Pointer;
		o.m_Pointer = nullptr;
		return *this;
	}

	template<class O>
	ANInterfacePointer<T>& operator=(const ANInterfacePointer<O>& o)
	{
		this->m_Pointer = o.m_Pointer;
		return *this;
	}

	template<class O>
	ANInterfacePointer<T>& operator=(ANInterfacePointer<O>& o)
	{
		release();
		this->m_Pointer = o.m_Pointer;
		o.m_Pointer = nullptr;
		return *this;
	}

	//DELEGATE != OPERATOR
	bool operator!=(const ANInterfacePointer<T>& o)
	{
		return *this->m_Pointer != o;
	}

	//DELEGATE ++ OPERATOR
	T& operator++(int)
	{
		return (*this->m_Pointer)++;
	}

	void release()
	{
		if (this->m_Pointer != nullptr)
		{
			delete this->m_Pointer;
			this->m_Pointer = nullptr;
		}
	}
private:
};