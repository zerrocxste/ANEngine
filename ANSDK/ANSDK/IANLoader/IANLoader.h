#pragma once

class IANLoader : public IANError
{
public:
	virtual bool InitializeLoader() = 0;
	virtual bool ConnectScene(IANGameScene* pGameScene) = 0;
	virtual void RunScene() = 0;
	virtual bool DestroyContext() = 0;
};
