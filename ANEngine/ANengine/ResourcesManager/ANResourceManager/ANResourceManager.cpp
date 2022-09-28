#include "../../ANEngine.h"

ANResourceManager::ANResourceManager() : 
	IANError()
{

}

ANResourceManager::~ANResourceManager()
{

}

bool ANResourceManager::ReadBinFile(const char* pszPath, ANUniqueResource* pUniqueResource)
{
	return ReadFile(pszPath, pUniqueResource->m_pResourceLocation, pUniqueResource->m_iResourceSize, true);
}

bool ANResourceManager::ReadBinFile(const char* pszPath, void*& pBuf, std::uint32_t& iOutFileSize)
{
	return ReadFile(pszPath, pBuf, iOutFileSize, true);
}

bool ANResourceManager::ReadTextFile(const char* pszPath, ANUniqueResource* pUniqueResource)
{
	return ReadFile(pszPath, pUniqueResource->m_pResourceLocation, pUniqueResource->m_iResourceSize, false);
}

bool ANResourceManager::ReadTextFile(const char* pszPath, void*& pBuf, std::uint32_t& iOutFileSize)
{
	return ReadFile(pszPath, pBuf, iOutFileSize, false);
}

bool ANResourceManager::WriteBinFile(const char* pszPath, void*& pBuf, std::uint32_t iWriteSize)
{
	std::fstream FileStream(pszPath, std::ios::binary | std::ios::out | std::ios::ate);

	if (!FileStream.is_open())
		return false;

	FileStream.seekp(0, std::ios::beg);

	FileStream.write((char*)pBuf, iWriteSize);

	FileStream.close();

	return true;
}

bool ANResourceManager::FileDelete(const char* pszPath)
{
	return std::remove(pszPath) == 0;
}

bool ANResourceManager::ReadFile(const char* pszPath, void*& pBuf, std::uint32_t& iOutFileSize, bool IsBinary)
{
	std::fstream FileStream(pszPath, std::ios::in | std::ios::ate | std::ios::binary);

	if (!FileStream.is_open())
	{
		this->SetError(__FUNCTION__ " > File '%s' not found", pszPath);
		return false;
	}

	iOutFileSize = FileStream.tellg();

	if (!iOutFileSize)
		return false;

	pBuf = ANMemory::GetInstance()->ResourceAllocate(iOutFileSize);

	if (!pBuf)
	{
		this->SetError(__FUNCTION__ " > Memory allocation error for '%s'", pszPath);
		return false;
	}

	FileStream.seekg(0, std::ios::beg);

	FileStream.read((char*)pBuf, iOutFileSize);

	FileStream.close();

	if (!IsBinary)
	{
		*((char*)pBuf + iOutFileSize) = 0;
		iOutFileSize++;
	}

	return true;
}
