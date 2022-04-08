#include "../ANEngine.h"

ANAllocator::ANAllocator() : 
	IANError(), 
	m_GlobalAllocatedMemory(0)
{

}

ANAllocator::~ANAllocator()
{

}

void* ANAllocator::AllocateMemory(std::size_t Size)
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

void* ANAllocator::AllocateMemoryOfBlocks(std::size_t BlocksCount, std::size_t BlockSize)
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

bool ANAllocator::FreeMemory(void* Ptr)
{
	if (!Ptr)
		return false;

	std::free(Ptr);

	this->m_GlobalAllocatedMemory -= _msize(Ptr);

	return true;
}

std::size_t ANAllocator::GetAllocatedMemory()
{
	this->m_GlobalAllocatedMemory;
}

ANAllocator* ANAllocator::ANAllocatorInstance()
{
	static auto pAllocator = new ANAllocator();
	return pAllocator;
}

