#pragma once

class ANInteractionMessagesList : public IANInteractionMessagesList
{
public:
	void AddInteractionMessage(const char* pszEventClassID, const char* pszEventMessage, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void AddInteractionMessageForEntityName(const char* pszEventClassID, const char* pszEventMessage, const char* pszEntityName, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void AddInteractionMessageForEntityClassID(const char* pszEventClassID, const char* pszEventMessage, const char* pszClassID, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void RemoveInteractionMessageForClassID(const char* pszEventClassID) override;
	void RemoveInteractionMessage(const char* pszEventMessage) override;

	std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityName(const char* pszName) override;
	std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityClassID(const char* pszClassIDName) override;

	void Clear() override;
};