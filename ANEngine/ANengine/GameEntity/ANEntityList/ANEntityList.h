#pragma once

class ANEntityList
{
public:
	ANEntityList();
	~ANEntityList();

	void Reg(IANEntity** ppEntity, const char* pszEntityClassID);
	void Add(IANEntity* pEntity);
	void Remove(IANEntity* pEntity);
	void Unreg(IANEntity* ppEntity);

	void FindFromClassID(const char* pszClassID, std::deque<IANEntity*>* pEntityList);
	IANEntity* FindFromName(const char* pszName);

	ANEntityList* UnregAll();
	ANEntityList* Clear();
private:
	std::deque<IANEntity*> m_vEntityList;
};