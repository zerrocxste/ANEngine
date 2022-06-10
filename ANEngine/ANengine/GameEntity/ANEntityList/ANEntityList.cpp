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

void ANEntityList::Unreg(IANEntity* ppEntity)
{
	auto& pIEntity = ppEntity;
	auto pEntity = (ANEntity*)pIEntity;

	if (!pIEntity)
		return;

	if (pEntity->m_szEntityClassID)
		delete[] pEntity->m_szEntityClassID;

	if (pEntity->m_szEntityName)
		delete[] pEntity->m_szEntityName;

	ANMemory::GetInstance()->Delete(pIEntity->m_pAnimCompositionController);

	ANMemory::GetInstance()->Delete(pIEntity);
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

ANEntityList* ANEntityList::UnregAll()
{
	for (auto it = this->m_vEntityList.begin(); it < this->m_vEntityList.end(); it++)
	{
		auto& entity = *it;

		if (!entity)
			continue;

		Unreg(entity);

		this->m_vEntityList.erase(it);
	}

	return this;
}

ANEntityList* ANEntityList::Clear()
{
	this->m_vEntityList.clear();

	return this;
}
