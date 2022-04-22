#pragma once

class ANGame : public IANError
{
public:
	ANGame(ANCore* pCore);
	~ANGame();

	bool ConnectScene(IANGameScene* pScene);

	bool RunScene();
private:
	ANCore* m_pCore;

	IANGameScene* m_pCurrentScene;

	void DisconnectScene();
};
