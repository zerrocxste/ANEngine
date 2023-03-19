#pragma once

class ANMemory : public IANError
{
public:
	ANMemory();
	~ANMemory();

	void* ResourceAllocate(std::size_t Size);
	void* ResourcAllocateeOfBlocks(std::size_t BlocksCount, std::size_t BlockSize);
	bool FreeResource(void* Ptr);

	template<class T, class... A> T* Allocate(A&&... Arg)
	{
		auto ret = new (std::nothrow) T(Arg...);

		if (!ret)
		{
			assert("Memory allocate error");
			__debugbreak();
		}

		this->m_WorkingSetAllocatedMemory += sizeof(T);

		return ret;
	}

	template<class T> void Delete(T* P)
	{
		this->m_WorkingSetAllocatedMemory -= sizeof(T);
		delete P;
	}

	std::size_t GetTotalAllocatedMemory();
	std::size_t GetWorkingSetAllocatedMemory();
	std::size_t GetResourceAllocatedMemory();

	static ANMemory* GetInstance();

private:
	std::size_t m_WorkingSetAllocatedMemory;
	std::size_t m_ResourceAllocatedMemory;
};
