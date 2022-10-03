#pragma once

class IANInteractionController
{
public:
	virtual ~IANInteractionController() = default;

	virtual bool ActionHandler(IANApi* pApi,
		const char* pszEventClassID,
		const char* pszEventMessage,
		IANEntity* pThisEntity,
		IANEntity** ppRemoteEntity,
		void* pReversedUserData,
		bool bNeedCancelEvent) = 0;
};