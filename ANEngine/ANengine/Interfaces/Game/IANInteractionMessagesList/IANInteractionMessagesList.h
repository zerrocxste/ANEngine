#pragma once

struct ANUniqueInteractionMesssage
{
	const char* m_pszEntityName;
	const char* m_pszEntityClassIDName;
	const char* m_pszEventClassID;
	const char* m_pszEventMessage;
	IANEntity** m_pRemoteEntity;
	void* m_pReversedUserData;
};

class IANInteractionMessagesList
{
public:
	std::vector<ANUniqueInteractionMesssage> m_InteractionMessagesList;

	virtual void AddInteractionMessage(const char* pszEventClassID, const char* pszEventMessage, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
	virtual void AddInteractionMessageForEntityName(const char* pszEventClassID, const char* pszEventMessage, const char* pszEntityName, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
	virtual void AddInteractionMessageForEntityClassID(const char* pszEventClassID, const char* pszEventMessage, const char* pszClassID, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
	virtual void RemoveInteractionMessageForClassID(const char* pszEventClassID) = 0;
	virtual void RemoveInteractionMessage(const char* pszEventMessage) = 0;
	
	virtual std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityName(const char* pszName) = 0;
	virtual std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityClassID(const char* pszClassIDName) = 0;

	virtual void Clear() = 0;
};