#pragma once

class IANGameScene
{
public:
	virtual void OnLoadScene(IANApi* pApi) = 0;
	virtual void OnUnloadScene(IANApi* pApi) = 0;
	virtual void Entry(IANApi* pApi) = 0;
};
