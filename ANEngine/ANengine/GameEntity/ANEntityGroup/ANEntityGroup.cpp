#include "../../ANEngine.h"

void ANEntityGroup::SetVisible(bool IsVisible)
{
	for (auto& entity : this->m_EntityGroup)
		entity->SetVisible(IsVisible);
}

void ANEntityGroup::SetAnimationDuration(float flDuration)
{
	for (auto& entity : this->m_EntityGroup)
		entity->m_pIANAnimationCompositionController->SetAnimationDuration(flDuration);
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

void ANEntityGroup::Draw(IANApi* pApi, IANWorld* pWorld)
{
	for (auto entity : this->m_EntityGroup)
		entity->DrawFromComposition(pApi, pWorld);
}
