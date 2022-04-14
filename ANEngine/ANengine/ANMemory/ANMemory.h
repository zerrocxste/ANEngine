#pragma once

class ANMemory : public IANError
{
public:
	ANMemory();
	~ANMemory();

	void* AllocateMemory(std::size_t Size);
	void* AllocateMemoryOfBlocks(std::size_t BlocksCount, std::size_t BlockSize);



	bool FreeMemory(void* Ptr);

	std::size_t GetTotalAllocatedMemory();

	static ANMemory* GetInstance();
private:
	std::size_t m_TotalAllocatedMemory;
};
