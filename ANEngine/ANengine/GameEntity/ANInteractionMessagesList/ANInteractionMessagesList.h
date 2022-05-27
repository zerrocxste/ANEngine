#pragma once

class ANInteractionMessagesList : public IANInteractionMessagesList
{
public:
	void AddInteractionMessage(const char* pszEventMessage, IANEntity* pRemoteEntity) override;
	void AddInteractionMessageForEntityName(const char* pszEventMessage, const char* pszEntityName, IANEntity* pRemoteEntity) override;
	void AddInteractionMessageForEntityClassID(const char* pszEventMessage, const char* pszClassID, IANEntity* pRemoteEntity) override;
	void RemoveInteractionMessage(const char* pszEventMessage) override;

	std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityName(const char* pszName) override;
	std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityClassID(const char* pszClassIDName) override;

	void Clear() override;
};