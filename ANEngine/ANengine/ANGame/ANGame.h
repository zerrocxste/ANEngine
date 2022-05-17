#pragma once

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

	ANEntityList* GetEntityList();
private:
	ANCore* m_pCore;

	void DisconnectScene();
	bool m_bNeedLeaveGame;

	ANEntityList* m_pEntityList;

	IANGameScene* m_pCurrentScene;
};
