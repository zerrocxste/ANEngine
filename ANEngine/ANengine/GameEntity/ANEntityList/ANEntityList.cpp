#include "../../ANEngine.h"

ANEntityList::ANEntityList()
{

}

ANEntityList::~ANEntityList()
{

}

void ANEntityList::Add(IANEntity* pEntity)
{
	this->m_vEntityList.push_back(pEntity);
}

void ANEntityList::Remove(IANEntity* pEntity)
{
	auto it = std::find(this->m_vEntityList.begin(), this->m_vEntityList.end(), pEntity);

	if (it == this->m_vEntityList.end())
		return;

	this->m_vEntityList.erase(it);
}

void ANEntityList::FindFromClassID(const char* pszClassID, std::vector<IANEntity*>* pEntityList)
{
	for (auto it = this->m_vEntityList.begin(); it < this->m_vEntityList.end(); it++)
	{
		if (!strcmp((*it)->GetEntityClassID(), pszClassID))
			pEntityList->push_back(*it);
	}
}

IANEntity* ANEntityList::FindFromName(const char* pszName)
{
	auto it = 
		std::find_if(this->m_vEntityList.begin(), this->m_vEntityList.end(), [&](IANEntity* Entity) 
		{
			return !strcmp(Entity->GetEntityClassID(), pszName);
		});

	if (it == this->m_vEntityList.end())
		return nullptr;

	return *it;
}

void ANEntityList::Clear()
{
	this->m_vEntityList.clear();
}
