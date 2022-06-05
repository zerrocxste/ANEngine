#pragma once

class IANInteractionController
{
public:
	virtual bool ActionHandler(IANApi* pApi, const char* pszEventClassID, const char* pszEventMessage, IANEntity* pThisEntity, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
};