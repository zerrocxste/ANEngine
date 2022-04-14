#pragma once

class ANUniqueResource : public IANError 
{
	friend ANResourceManager;
public:
	ANUniqueResource();
	~ANUniqueResource();

	bool AllocateResource(std::uint32_t iSize);

	void* GetResourceLocation();
	std::uint32_t GetResourceSize();
	bool ResourceIsDone();
	bool Free();
private:
	void* m_pResourceLocation;
	std::uint32_t m_iResourceSize;
};

