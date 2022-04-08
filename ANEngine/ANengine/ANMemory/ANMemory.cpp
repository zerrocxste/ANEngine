#include "../ANEngine.h"

ANMemory::ANMemory() :
	IANError(), 
	m_GlobalAllocatedMemory(0)
{

}

ANMemory::~ANMemory()
{

}

void* ANMemory::AllocateMemory(std::size_t Size)
{
	auto ret = std::malloc(Size);

	if (!ret)
	{
		this->SetError("%s() -> Error allocate memory for: %p", __FUNCTION__, Size);
		return nullptr;
	}

	std::memset(ret, 0, Size);

	this->m_GlobalAllocatedMemory += Size;

	return ret;
}

void* ANMemory::AllocateMemoryOfBlocks(std::size_t BlocksCount, std::size_t BlockSize)
{
	auto GlobalSize = BlockSize * BlocksCount;

	auto ret = std::malloc(GlobalSize);

	if (!ret)
	{
		this->SetError("%s() -> Error allocate memory for: %p", __FUNCTION__, GlobalSize);
		return nullptr;
	}

	std::memset(ret, 0, GlobalSize);

	this->m_GlobalAllocatedMemory += GlobalSize;

	return ret;
}

bool ANMemory::FreeMemory(void* Ptr)
{
	if (!Ptr)
		return false;

	std::free(Ptr);

	this->m_GlobalAllocatedMemory -= _msize(Ptr);

	return true;
}

std::size_t ANMemory::GetAllocatedMemory()
{
	this->m_GlobalAllocatedMemory;
}

ANMemory* ANMemory::ANAllocatorInstance()
{
	static auto pAllocator = new ANMemory();
	return pAllocator;
}

