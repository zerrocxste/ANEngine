#pragma once

class ANLoader : public IANLoader
{
public:
	ANLoader(const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame,
		bool bVerticalSync);

	~ANLoader();

	bool InitializeLoader() override;
	bool ConnectScene(IANGameScene* pGameScene) override;
	void RunScene() override;
	bool DestroyContext() override;

private:
	ANCore* m_pInstance;
};
