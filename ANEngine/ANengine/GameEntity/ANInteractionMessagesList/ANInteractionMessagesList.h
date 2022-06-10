#pragma once

class ANInteractionMessagesList : public IANInteractionMessagesList
{
public:
	void AddInteractionMessage(const char* pszEventClassID, const char* pszEventMessage, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void AddInteractionMessageForEntityName(const char* pszEventClassID, const char* pszEventMessage, const char* pszEntityName, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void AddInteractionMessageForEntityClassID(const char* pszEventClassID, const char* pszEventMessage, const char* pszClassID, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void SendCancelInteractionMessageForClassID(const char* pszEventClassID) override;
	void SendCancelInteractionMessage(const char* pszEventMessage) override;
	void RemoveInteractionMessageForClassID(const char* pszEventClassID) override;
	void RemoveInteractionMessage(const char* pszEventMessage) override;

	bool IsEventCanceledByEventName(const char* pszEventName, IANEntity* pExcludeForEntity, bool bSearchForEntityClassID) override;
	bool IsEventCanceledByClassID(const char* pszEventClassID, IANEntity* pExcludeForEntity, bool bSearchForEntityClassID) override;

	std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityName(const char* pszName) override;
	std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityClassID(const char* pszClassIDName) override;

	void Clear() override;
};