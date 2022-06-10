#pragma once

class IANEntity : 
	public IANBasicEntity,
	public IANMovementController,
	public IANAnimationController,
	public IANActionController
{
protected:
	char* m_szEntityName;
public:
	IANAnimationCompositionController* m_pAnimCompositionController;

	virtual void SetEntityName(const char* szEntityName) = 0;
	virtual char* GetEntityName() = 0;

	virtual IANEntity& Update(IANApi* pApi) = 0;
};