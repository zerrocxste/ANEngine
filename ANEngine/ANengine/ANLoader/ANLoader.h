#pragma once

class ANLoader : public IANLoader
{
public:
	ANLoader(RenderTypes RenderType,
		const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame,
		bool bVerticalSync);

	~ANLoader();

	bool InitializeLoader() override;
	bool ConnectScene(IANGameScene* pGameScene) override;
	bool RunScene() override;
	bool DestroyContext() override;

private:
	ANCore* m_pInstance;
};
