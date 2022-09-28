#pragma once

class IANInteractionMessagesList;
class IANInteractionMessagesNode;
struct ANUniqueInteractionMesssage;

struct ANUniqueInteractionMesssage
{
	const char* m_pszEntityName;
	const char* m_pszEntityClassIDName;
	const char* m_pszEventClassID;
	const char* m_pszEventMessage;
	IANEntity** m_pRemoteEntity;
	void* m_pReversedUserData;
	bool m_bNeedCancelEvent;
};

class IANInteractionMessagesNode
{
public:
	virtual ANUniqueInteractionMesssage& operator*() = 0;
	virtual IANInteractionMessagesNode& operator++(int) = 0;
	virtual bool operator!=(const ANInterfacePointer<IANInteractionMessagesNode>& Node) = 0;
};

class IANInteractionMessagesList
{
public:
	using InteractionObjectNode = ANInterfacePointer<IANInteractionMessagesNode>;

	virtual void AddInteractionMessage(const char* pszEventClassID, const char* pszEventMessage, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
	virtual void AddInteractionMessageForEntityName(const char* pszEventClassID, const char* pszEventMessage, const char* pszEntityName, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
	virtual void AddInteractionMessageForEntityClassID(const char* pszEventClassID, const char* pszEventMessage, const char* pszClassID, IANEntity** pRemoteEntity, void* pReversedUserData) = 0;
	virtual void SendCancelInteractionMessageForClassID(const char* pszEventClassID) = 0;
	virtual void SendCancelInteractionMessage(const char* pszEventMessage) = 0;
	virtual void RemoveInteractionMessageForClassID(const char* pszEventClassID) = 0;
	virtual void RemoveInteractionMessage(const char* pszEventMessage) = 0;

	virtual bool IsEventCanceledByEventName(const char* pszEventName, IANEntity* pExcludeForEntity = nullptr, bool bSearchForEntityClassID = false) = 0;
	virtual bool IsEventCanceledByClassID(const char* pszEventClassID, IANEntity* pExcludeForEntity = nullptr, bool bSearchForEntityClassID = false) = 0;

	virtual InteractionObjectNode First() = 0;
	virtual InteractionObjectNode Last() = 0;

	virtual anSize GetSize() = 0;

	virtual ANInterfacePointer<IANInteractionMessagesList> GetInteractionFromEntityName(const char* pszName) = 0;
	virtual ANInterfacePointer<IANInteractionMessagesList> GetInteractionFromEntityClassID(const char* pszClassIDName) = 0;

	virtual void Clear() = 0;
};