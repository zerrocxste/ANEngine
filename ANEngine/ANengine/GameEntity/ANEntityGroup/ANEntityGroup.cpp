#include "../../ANEngine.h"

IANEntity* ANEntityGroupData::Get()
{
	return *this->it;
}

IANEntityGroupData& ANEntityGroupData::operator=(const IANEntityGroupData& other)
{
	this->it = ((ANEntityGroupData&)other).it;
	return *this;
}

IANEntityGroupData& ANEntityGroupData::operator++(int)
{
	this->it++;
	return *this;
}

bool ANEntityGroupData::operator!=(const ANInterfacePointer<IANEntityGroupData>& other)
{
	return this->it != ((ANEntityGroupData*)other.m_Pointer)->it;
}

bool ANEntityGroupData::operator!=(const IANEntityGroupData& other)
{
	return this->it != ((ANEntityGroupData&)other).it;
}

ANInterfacePointer<IANEntityGroupData> ANEntityGroup::First()
{
	auto pEntityGroupData = ANImpPtr<ANEntityGroupData>();
	pEntityGroupData->it = this->m_EntityGroup.begin();
	return pEntityGroupData;
}

ANInterfacePointer<IANEntityGroupData> ANEntityGroup::Last()
{
	auto pEntityGroupData = ANImpPtr<ANEntityGroupData>();
	pEntityGroupData->it = this->m_EntityGroup.end();
	return pEntityGroupData;
}

anSize ANEntityGroup::Size()
{
	return this->m_EntityGroup.size();
}

ANInterfacePointer<IANEntityGroupData>& ANEntityGroup::erase(ANInterfacePointer<IANEntityGroupData>& obj)
{
	auto& it = ((ANEntityGroupData&)obj).it;
	it = this->m_EntityGroup.erase(it);
	return obj;
}

void ANEntityGroup::SetVisible(bool IsVisible)
{
	for (auto& entity : this->m_EntityGroup)
		entity->SetVisible(IsVisible);
}

void ANEntityGroup::SetAnimationDuration(float flDuration)
{
	for (auto& entity : this->m_EntityGroup)
		entity->GetAnimCompositionController()->SetAnimationDuration(flDuration);
}

void ANEntityGroup::SetOrigin(anVec2 Origin)
{
	for (auto& entity : this->m_EntityGroup)
		entity->SetOrigin(Origin);
}

void ANEntityGroup::MovePoint(IANApi* pApi, float Speed, anVec2 Origin)
{
	for (auto& entity : this->m_EntityGroup)
		entity->MovePoint(pApi, Speed, Origin);
}

void ANEntityGroup::MoveLeft(IANApi* pApi, float Speed)
{
	for (auto& entity : this->m_EntityGroup)
		entity->MoveLeft(pApi, Speed);
}

void ANEntityGroup::MoveRight(IANApi* pApi, float Speed)
{
	for (auto& entity : this->m_EntityGroup)
		entity->MoveRight(pApi, Speed);
}

void ANEntityGroup::MoveUp(IANApi* pApi, float Speed)
{
	for (auto& entity : this->m_EntityGroup)
		entity->MoveUp(pApi, Speed);
}

void ANEntityGroup::MoveDown(IANApi* pApi, float Speed)
{
	for (auto& entity : this->m_EntityGroup)
		entity->MoveDown(pApi, Speed);
}

IANEntityGroup& ANEntityGroup::SortByYOrder()
{
	for (auto it = this->m_EntityGroup.begin(); it < this->m_EntityGroup.end() - 1; it++)
	{
		auto ThisY = (*it)->GetOrigin().y;

		float SmallestY = FLT_MAX;
		decltype(it) ScopedIter;
		for (auto itt = it; itt < this->m_EntityGroup.end() - 1; itt++)
		{
			auto Y = (*itt)->GetOrigin().y;

			if (Y < SmallestY)
			{
				SmallestY = Y;
				ScopedIter = itt;
			}
		}

		if (SmallestY < ThisY)
			std::swap(*it, *ScopedIter);
	}

	return *this;
}

IANEntityGroup& ANEntityGroup::Update(IANApi* pApi)
{
	for (auto entity : this->m_EntityGroup)
		entity->Update(pApi);

	return *this;
}

void ANEntityGroup::DrawRectRegion(IANApi* pApi, IANWorld* pWorld, anColor Color)
{
	for (auto entity : this->m_EntityGroup)
		entity->DrawRectRegion(pApi, pWorld, Color);
}

void ANEntityGroup::DrawFromComposition(IANApi* pApi, IANWorld* pWorld)
{
	for (auto entity : this->m_EntityGroup)
		entity->DrawFromComposition(pApi, pWorld);
}