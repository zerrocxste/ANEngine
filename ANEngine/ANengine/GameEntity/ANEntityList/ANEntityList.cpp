#include "../../ANEngine.h"

ANEntityList::ANEntityList()
{

}

ANEntityList::~ANEntityList()
{

}

void ANEntityList::Reg(IANEntity** ppEntity, const char* pszEntityClassID)
{
	auto pANEntity = (ANEntity*)((*ppEntity) = ANMemory::GetInstance()->Allocate<ANEntity>());

	pANEntity->m_pAnimCompositionController = ANMemory::GetInstance()->Allocate<ANAnimationCompositionController>();

	if (pszEntityClassID)
	{
		auto LengthEntityName = strlen(pszEntityClassID) + 1;
		memcpy(pANEntity->m_szEntityClassID = new char[LengthEntityName], pszEntityClassID, LengthEntityName);
	}

	pANEntity->m_pUserData = nullptr;
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
	auto pEntity = (ANEntity*)ppEntity;

	if (!pEntity)
		return;

	if (pEntity->m_szEntityClassID)
		delete[] pEntity->m_szEntityClassID;

	if (pEntity->m_szEntityName)
		delete[] pEntity->m_szEntityName;

	ANMemory::GetInstance()->Delete(pEntity->m_pAnimCompositionController);

	ANMemory::GetInstance()->Delete(pEntity);

	if (pEntity->m_pUserData != nullptr)
	{
		delete pEntity->m_pUserData;
		pEntity->m_pUserData = nullptr;
	}
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
	for (auto it = this->m_vEntityList.begin(); it < this->m_vEntityList.end(); )
	{
		auto& entity = *it;

		if (!entity)
		{
			it++;
			continue;
		}

		Unreg(entity);

		it = it = this->m_vEntityList.erase(it);

		if (this->m_vEntityList.size() == 0)
			break;
	}

	return this;
}

ANEntityList* ANEntityList::Clear()
{
	this->m_vEntityList.clear();

	return this;
}
