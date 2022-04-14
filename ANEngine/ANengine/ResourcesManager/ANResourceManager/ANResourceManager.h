#pragma once

class ANResourceManager : public IANError
{
public:
	ANResourceManager();
	~ANResourceManager();

	bool ReadBinFile(const char* pszPath, ANUniqueResource* pUniqueResource);
	bool ReadBinFile(const char* pszPath, void*& pBuf, std::uint32_t& iOutFileSize);

	bool WriteBinFile(const char* pszPath, void*& pBuf, std::uint32_t iWriteSize);

	bool FileDelete(const char* pszPath);

private:

};