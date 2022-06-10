#pragma once

class ANEntityList
{
public:
	ANEntityList();
	~ANEntityList();

	void Add(IANEntity* pEntity);
	void Remove(IANEntity* pEntity);
	void Unreg(IANEntity* ppEntity);

	void FindFromClassID(const char* pszClassID, std::vector<IANEntity*>* pEntityList);
	IANEntity* FindFromName(const char* pszName);

	ANEntityList* UnregAll();
	ANEntityList* Clear();
private:
	std::vector<IANEntity*> m_vEntityList;
};