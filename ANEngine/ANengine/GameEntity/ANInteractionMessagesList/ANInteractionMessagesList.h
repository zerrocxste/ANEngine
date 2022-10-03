#pragma once

class ANInteractionMessagesList;

class ANInteractionMessagesNode : public IANInteractionMessagesNode
{
	friend ANInteractionMessagesList;
public:
	std::deque<ANUniqueInteractionMesssage>::iterator iter;

	ANUniqueInteractionMesssage& operator*() override;
	IANInteractionMessagesNode& operator++(int) override;
	bool operator!=(const IANInteractionMessagesList::InteractionObjectNode& Node) override;
};

class ANInteractionMessagesList : public IANInteractionMessagesList
{
public:
	std::deque<ANUniqueInteractionMesssage> m_InteractionMessagesList;

	bool m_CurrentIsIterable;
	std::deque<ANUniqueInteractionMesssage> m_TempCollectionIML;

	void AddInteractionMessage(const char* pszEventClassID, const char* pszEventMessage, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void AddInteractionMessageForEntityName(const char* pszEventClassID, const char* pszEventMessage, const char* pszEntityName, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void AddInteractionMessageForEntityClassID(const char* pszEventClassID, const char* pszEventMessage, const char* pszClassID, IANEntity** pRemoteEntity, void* pReversedUserData) override;
	void SendCancelInteractionMessageForClassID(const char* pszEventClassID) override;
	void SendCancelInteractionMessage(const char* pszEventMessage) override;
	void RemoveInteractionMessageForClassID(const char* pszEventClassID) override;
	void RemoveInteractionMessage(const char* pszEventMessage) override;

	bool IsEventCanceledByEventName(const char* pszEventName, IANEntity* pExcludeForEntity, bool bSearchForEntityClassID) override;
	bool IsEventCanceledByClassID(const char* pszEventClassID, IANEntity* pExcludeForEntity, bool bSearchForEntityClassID) override;

	InteractionObjectNode First() override;
	InteractionObjectNode Last() override;

	anSize GetSize() override;

	ANInterfacePointer<IANInteractionMessagesList> GetInteractionFromEntityName(const char* pszName) override;
	ANInterfacePointer<IANInteractionMessagesList> GetInteractionFromEntityClassID(const char* pszClassIDName) override;

	void Clear() override;

	void LockList();
	void UnlockList();
};