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

void ANEntityGroup::Draw(IANApi* pApi, IANWorld* pWorld)
{
	if (this->m_EntityGroup.size() > 1)
	{
		auto EntList = this->m_EntityGroup;

		for (auto it = EntList.begin(); it < EntList.end() - 1; it++)
		{
			std::vector<IANEntity*>::iterator EntityIter;
			float D = -FLT_MAX;

			for (auto iter = it; iter < EntList.end() - 1; iter++)
			{
				auto Current = (*iter)->GetOrigin().y;
				auto Next = (*(iter + 1))->GetOrigin().y;

				if (Current < Next)
				{
					D = Current;
					EntityIter = iter;
					continue;
				}

				D = Next;
				EntityIter = iter + 1;
			}

			auto Save = *EntityIter;
			*EntityIter = *it;
			*it = Save;
		}

		for (auto& entity : EntList)
			entity->DrawFromComposition(pApi, pWorld);

		return;
	}
	
	for (auto& entity : this->m_EntityGroup)
		entity->DrawFromComposition(pApi, pWorld);
}
