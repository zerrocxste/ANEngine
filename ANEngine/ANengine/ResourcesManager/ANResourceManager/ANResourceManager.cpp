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
	return ReadBinFile(pszPath, pUniqueResource->m_pResourceLocation, pUniqueResource->m_iResourceSize);
}

bool ANResourceManager::ReadBinFile(const char* pszPath, void*& pBuf, std::uint32_t& iOutFileSize)
{
	std::fstream FileStream(pszPath, std::ios::binary | std::ios::in | std::ios::ate);

	if (!FileStream.is_open())
		return false;

	iOutFileSize = FileStream.tellg();

	if (!iOutFileSize)
		return false;

	pBuf = ANMemory::GetInstance()->ResourceAllocate(iOutFileSize);

	if (!pBuf)
	{
		this->SetError("%s() -> Memory allocation error", __FUNCTION__);
		return false;
	}

	FileStream.seekg(0, std::ios::beg);

	FileStream.read((char*)pBuf, iOutFileSize);

	FileStream.close();

	return true;
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