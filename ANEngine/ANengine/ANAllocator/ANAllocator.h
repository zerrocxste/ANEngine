#pragma once

class ANAllocator : public IANError
{
public:
	ANAllocator();
	~ANAllocator();

	void* AllocateMemory(std::size_t Size);
	void* AllocateMemoryOfBlocks(std::size_t BlocksCount, std::size_t BlockSize);

	bool FreeMemory(void* Ptr);

	std::size_t GetAllocatedMemory();

	static ANAllocator* ANAllocatorInstance();
private:
	std::size_t m_GlobalAllocatedMemory;
};
