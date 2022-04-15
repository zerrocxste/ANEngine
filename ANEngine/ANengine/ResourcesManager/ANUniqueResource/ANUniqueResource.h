#pragma once

class ANUniqueResource : public IANError 
{
	friend ANResourceManager;
public:
	ANUniqueResource();
	~ANUniqueResource();

	bool AllocateResource(std::uint32_t iSize);

	void* GetResourceLocation();
	void*& GetResourceLocationPtr();
	std::uint32_t GetResourceSize();
	std::uint32_t& GetResourceSizePtr();
	bool ResourceIsDone();
	bool Free();
private:
	void* m_pResourceLocation;
	std::uint32_t m_iResourceSize;
};

