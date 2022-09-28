#pragma once

class ANEntityGroupData : public IANEntityGroupData
{
public:
	std::deque<IANEntity*>::iterator it;

	IANEntity* Get() override;
	IANEntityGroupData& operator=(const IANEntityGroupData& other) override;
	IANEntityGroupData& operator++(int) override;
	bool operator!=(const ANInterfacePointer<IANEntityGroupData>& other) override;
	bool operator!=(const IANEntityGroupData& other) override;
};

class ANEntityGroup : public IANEntityGroup
{
public:
	std::deque<IANEntity*> m_EntityGroup;

	ANInterfacePointer<IANEntityGroupData> First() override;
	ANInterfacePointer<IANEntityGroupData> Last() override;

	anSize Size() override;

	ANInterfacePointer<IANEntityGroupData>& erase(ANInterfacePointer<IANEntityGroupData>& obj) override;

	void SetVisible(bool IsVisible) override;
	void SetAnimationDuration(float flDuration) override;
	void SetOrigin(anVec2 Origin) override;
	void MovePoint(IANApi* pApi, float Speed, anVec2 Origin) override;
	void MoveLeft(IANApi* pApi, float Speed) override;
	void MoveRight(IANApi* pApi, float Speed) override;
	void MoveUp(IANApi* pApi, float Speed) override;
	void MoveDown(IANApi* pApi, float Speed) override;
	IANEntityGroup& SortByYOrder() override;
	IANEntityGroup& Update(IANApi* pApi) override;

	void DrawRectRegion(IANApi* pApi, IANWorld* pWorld, anColor Color) override;
	void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) override;
};

