#pragma once

struct ANDefaultAnimationCompositionData
{
	IANEntity* m_pEntity;
	ANAnimationComposition m_AnimationComposition;
	float m_flAnimationDuration;
};

class ANEveryFrameTask
{
public:
	std::vector<ANDefaultAnimationCompositionData> m_vDefaultAnimationCompositionData;
};

class ANGame : public IANError
{
public:
	ANGame(ANCore* pCore);
	~ANGame();

	bool ConnectScene(IANGameScene* pScene);
	bool RunScene();
	void LeaveGame();

	void RegWorld(IANWorld** ppWorld);
	void UnregWorld(IANWorld** ppWorld);

	void RegEntity(IANEntity** ppEntity, const char* pszEntityClassID);
	void UnregEntity(IANEntity** ppEntity);

	void AddDefaultAnimationComposition(IANEntity* pEntity, ANAnimationComposition AnimationComposition, float flAnimationDuration);
	void DeleteDefaultAnimationComposition(IANEntity* pEntity);
	void ClearDefaultAnimationComposition(); 

	ANGameResourcesData* GetGameResourcesData();
	ANEntityList* GetEntityList();
	ANInteractionMessagesList* GetInteractionList();
private:
	ANCore* m_pCore;

	void DisconnectScene();
	bool m_bNeedLeaveGame;

	ANGameResourcesData* m_pGameResourcesData;
	ANEntityList* m_pEntityList;
	ANInteractionMessagesList* m_pInteractionMessagesList;

	ANEveryFrameTask m_EveryFrameTask;

	IANGameScene* m_pNewGameScene;
	IANGameScene* m_pCurrentScene;
};
