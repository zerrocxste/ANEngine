#include "../ANEngine.h"

ANMemory::ANMemory() :
	IANError(), 
	m_WorkingSetAllocatedMemory(0),
	m_ResourceAllocatedMemory(0)
{

}

ANMemory::~ANMemory()
{

}

void* ANMemory::ResourceAllocate(std::size_t Size)
{
	auto ret = std::malloc(Size);

	if (!ret)
	{
		this->SetError("%s() -> Error allocate memory for: %p", __FUNCTION__, Size);
		return nullptr;
	}

	std::memset(ret, 0, Size);

	this->m_ResourceAllocatedMemory += Size;

	return ret;
}

void* ANMemory::ResourcAllocateeOfBlocks(std::size_t BlocksCount, std::size_t BlockSize)
{
	auto GlobalSize = BlockSize * BlocksCount;

	auto ret = std::malloc(GlobalSize);

	if (!ret)
	{
		this->SetError("%s() -> Error allocate memory for: %p", __FUNCTION__, GlobalSize);
		return nullptr;
	}

	std::memset(ret, 0, GlobalSize);

	this->m_ResourceAllocatedMemory += GlobalSize;

	return ret;
}

bool ANMemory::FreeResource(void* Ptr)
{
	if (!Ptr)
		return false;

	this->m_ResourceAllocatedMemory -= _msize(Ptr);

	std::free(Ptr);

	return true;
}

std::size_t ANMemory::GetTotalAllocatedMemory()
{
	return this->m_WorkingSetAllocatedMemory + this->m_ResourceAllocatedMemory;
}

std::size_t ANMemory::GetWorkingSetAllocatedMemory()
{
	return this->m_WorkingSetAllocatedMemory;
}

std::size_t ANMemory::GetResourceAllocatedMemory()
{
	return this->m_ResourceAllocatedMemory;
}

ANMemory* ANMemory::GetInstance()
{
	static auto pAllocator = new ANMemory();
	return pAllocator;
}

