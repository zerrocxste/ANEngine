#pragma once

class IANEntity :
	public IANBasicEntity,
	public IANMovementController,
	public IANAnimationController,
	public IANActionController
{
public:
	virtual void SetEntityName(const char* szEntityName) = 0;
	virtual char* GetEntityName() = 0;

	virtual IANAnimationCompositionController* GetAnimCompositionController() = 0;

	virtual IANEntity& Update(IANApi* pApi) = 0;
};