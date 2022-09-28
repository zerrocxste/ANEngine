#pragma once

class IANEntityGroupData
{
public:
	virtual IANEntity* Get() = 0;
	virtual IANEntityGroupData& operator=(const IANEntityGroupData& other) = 0;
	virtual IANEntityGroupData& operator++(int) = 0;
	virtual bool operator!=(const ANInterfacePointer<IANEntityGroupData>& other) = 0;
	virtual bool operator!=(const IANEntityGroupData& other) = 0;
};

class IANEntityGroup
{
public:
	virtual ANInterfacePointer<IANEntityGroupData> First() = 0;
	virtual ANInterfacePointer<IANEntityGroupData> Last() = 0;

	virtual anSize Size() = 0;

	virtual ANInterfacePointer<IANEntityGroupData>& erase(ANInterfacePointer<IANEntityGroupData>& obj) = 0;

	virtual void SetVisible(bool IsVisible) = 0;
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual void SetOrigin(anVec2 Origin) = 0;
	virtual void MovePoint(IANApi* pApi, float Speed, anVec2 Origin) = 0;
	virtual void MoveLeft(IANApi* pApi, float Speed) = 0;
	virtual void MoveRight(IANApi* pApi, float Speed) = 0;
	virtual void MoveUp(IANApi* pApi, float Speed) = 0;
	virtual void MoveDown(IANApi* pApi, float Speed) = 0;
	virtual IANEntityGroup& SortByYOrder() = 0;
	virtual IANEntityGroup& Update(IANApi* pApi) = 0;

	virtual void DrawRectRegion(IANApi* pApi, IANWorld* pWorld, anColor Color) = 0;
	virtual void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) = 0;
};