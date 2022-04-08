#pragma once

class ANMemory : public IANError
{
public:
	ANMemory();
	~ANMemory();

	void* AllocateMemory(std::size_t Size);
	void* AllocateMemoryOfBlocks(std::size_t BlocksCount, std::size_t BlockSize);

	bool FreeMemory(void* Ptr);

	std::size_t GetAllocatedMemory();

	static ANMemory* ANAllocatorInstance();
private:
	std::size_t m_GlobalAllocatedMemory;
};
