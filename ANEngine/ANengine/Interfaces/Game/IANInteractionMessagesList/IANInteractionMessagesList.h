#pragma once

struct ANUniqueInteractionMesssage
{
	const char* m_pszEntityName;
	const char* m_pszClassIDName;
	const char* m_pszEventMessage;
	IANEntity* m_pRemoteEntity;
};

class IANInteractionMessagesList
{
public:
	std::vector<ANUniqueInteractionMesssage> m_InteractionMessagesList;

	virtual void AddInteractionMessage(const char* pszEventMessage, IANEntity* pRemoteEntity) = 0;
	virtual void AddInteractionMessageForEntityName(const char* pszEventMessage, const char* pszEntityName, IANEntity* pRemoteEntity) = 0;
	virtual void AddInteractionMessageForEntityClassID(const char* pszEventMessage, const char* pszClassID, IANEntity* pRemoteEntity) = 0;
	virtual void RemoveInteractionMessage(const char* pszEventMessage) = 0;
	
	virtual std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityName(const char* pszName) = 0;
	virtual std::vector<ANUniqueInteractionMesssage*> GetInteractionFromEntityClassID(const char* pszClassIDName) = 0;

	virtual void Clear() = 0;
};