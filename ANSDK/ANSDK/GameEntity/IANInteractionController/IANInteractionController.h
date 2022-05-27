#pragma once

class IANInteractionController
{
public:
	virtual void ActionHandler(const char* pszEventMessage, IANEntity* pRemoteEntity) = 0;
};