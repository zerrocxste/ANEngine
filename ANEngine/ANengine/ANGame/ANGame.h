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

	void RegEntity(IANEntity** ppEntity);
	void UnregEntity(IANEntity** ppEntity);
private:
	ANCore* m_pCore;

	IANGameScene* m_pCurrentScene;
	void DisconnectScene();

	bool m_bNeedLeaveGame;
};
