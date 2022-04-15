#include "../../ANEngine.h"

ANUniqueResource::ANUniqueResource() : 
	IANError(),
	m_pResourceLocation(nullptr),
	m_iResourceSize(0)
{
	
}

ANUniqueResource::~ANUniqueResource()
{
	Free();
}

bool ANUniqueResource::AllocateResource(std::uint32_t iSize)
{
	this->m_iResourceSize = iSize;

	this->m_pResourceLocation = ANMemory::GetInstance()->ResourceAllocate(this->m_iResourceSize);

	if (!this->m_pResourceLocation)
	{
		this->SetError(ANMemory::GetInstance()->What());
		return false;
	}

	return true;
}

void* ANUniqueResource::GetResourceLocation()
{
	return this->m_pResourceLocation;
}

void*& ANUniqueResource::GetResourceLocationPtr()
{
	return this->m_pResourceLocation;
}

std::uint32_t ANUniqueResource::GetResourceSize()
{
	return this->m_iResourceSize;
}

std::uint32_t& ANUniqueResource::GetResourceSizePtr()
{
	return this->m_iResourceSize;
}

bool ANUniqueResource::ResourceIsDone()
{
	return this->m_pResourceLocation != nullptr && this->m_iResourceSize != 0;
}

bool ANUniqueResource::Free()
{
	if (!m_pResourceLocation)
	{
		this->SetError("%s() -> Resource is nullptr", __FUNCTION__);
		return false;
	}

	ANMemory::GetInstance()->FreeResource(this->m_pResourceLocation);
	this->m_pResourceLocation = nullptr;

	this->m_iResourceSize = 0;

	return true;
}