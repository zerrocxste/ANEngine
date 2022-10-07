#include "../../ANEngine.h"

void ANInteractionMessagesList::AddInteractionMessage(
	const char* pszEventClassID, 
	const char* pszEventMessage, 
	IANEntity** pRemoteEntity, 
	void* pReversedUserData)
{
	ANUniqueInteractionMesssage im{};
	im.m_pszEntityName = nullptr;
	im.m_pszEntityClassIDName = nullptr;
	im.m_pszEventClassID = pszEventClassID;
	im.m_pszEventMessage = pszEventMessage;
	im.m_pRemoteEntity = pRemoteEntity;
	im.m_pReversedUserData = pReversedUserData;

	if (this->m_CurrentIsIterable)
	{
		this->m_TempCollectionIML.push_back(im);
		return;
	}

	this->m_InteractionMessagesList.push_back(im);
}

void ANInteractionMessagesList::AddInteractionMessageForEntityName(
	const char* pszEventClassID,
	const char* pszEventMessage, 
	const char* pszEntityName, 
	IANEntity** pRemoteEntity, 
	void* pReversedUserData)
{
	ANUniqueInteractionMesssage im{};
	im.m_pszEntityName = pszEntityName;
	im.m_pszEntityClassIDName = nullptr;
	im.m_pszEventClassID = pszEventClassID;
	im.m_pszEventMessage = pszEventMessage;
	im.m_pRemoteEntity = pRemoteEntity;
	im.m_pReversedUserData = pReversedUserData;

	if (this->m_CurrentIsIterable)
	{
		this->m_TempCollectionIML.push_back(im);
		return;
	}

	this->m_InteractionMessagesList.push_back(im);
}

void ANInteractionMessagesList::AddInteractionMessageForEntityClassID(
	const char* pszEventClassID, 
	const char* pszEventMessage, 
	const char* pszClassID, 
	IANEntity** pRemoteEntity, 
	void* pReversedUserData)
{
	ANUniqueInteractionMesssage im{};
	im.m_pszEntityName = nullptr;
	im.m_pszEntityClassIDName = pszClassID;
	im.m_pszEventClassID = pszEventClassID;
	im.m_pszEventMessage = pszEventMessage;
	im.m_pRemoteEntity = pRemoteEntity;
	im.m_pReversedUserData = pReversedUserData;

	if (this->m_CurrentIsIterable)
	{
		this->m_TempCollectionIML.push_back(im);
		return;
	}

	this->m_InteractionMessagesList.push_back(im);
}

void ANInteractionMessagesList::SendCancelInteractionMessageForClassID(const char* pszEventClassID)
{
	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		auto& data = *it;

		if (!strcmp(data.m_pszEventClassID, pszEventClassID))
			data.m_bNeedCancelEvent = true;
	}
}

void ANInteractionMessagesList::SendCancelInteractionMessage(const char* pszEventMessage)
{
	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		auto& data = *it;

		if (!strcmp(data.m_pszEventMessage, pszEventMessage))
			data.m_bNeedCancelEvent = true;
	}
}

void ANInteractionMessagesList::RemoveInteractionMessageForClassID(const char* pszEventClassID)
{
	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		if (!(strcmp((*it).m_pszEventClassID, pszEventClassID) == 0))
			continue;

		it = this->m_InteractionMessagesList.erase(it);

		if (it == this->m_InteractionMessagesList.end())
			break;
	}
}

void ANInteractionMessagesList::RemoveInteractionMessage(const char* pszEventMessage)
{
	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		if (!(strcmp((*it).m_pszEventMessage, pszEventMessage) == 0))
			continue;

		it = this->m_InteractionMessagesList.erase(it);

		if (it == this->m_InteractionMessagesList.end())
			break;
	}
}

bool ANInteractionMessagesList::IsEventCanceledByEventName(const char* pszEventName, IANEntity* pExcludeForEntity, bool bSearchForEntityClassID)
{
	auto ret = true;

	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		auto& data = *it;

		if (!strcmp(data.m_pszEventMessage, pszEventName) && data.m_bNeedCancelEvent)
		{
			if (pExcludeForEntity != nullptr && !strcmp(
				bSearchForEntityClassID ? pExcludeForEntity->GetEntityClassID() : pExcludeForEntity->GetEntityName(), 
				data.m_pszEntityName))
				continue;

			ret = false;
		}
	}

	return ret;
}

bool ANInteractionMessagesList::IsEventCanceledByClassID(const char* pszEventClassID, IANEntity* pExcludeForEntity, bool bSearchForEntityClassID)
{
	auto ret = true;

	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		auto& data = *it;

		if (!strcmp(data.m_pszEventClassID, pszEventClassID) && data.m_bNeedCancelEvent)
		{
			if (pExcludeForEntity != nullptr && !strcmp(
				bSearchForEntityClassID ? pExcludeForEntity->GetEntityClassID() : pExcludeForEntity->GetEntityName(), 
				data.m_pszEntityName))
				continue;

			ret = false;
		}
	}

	return ret;
}

ANInteractionMessagesList::InteractionObjectNode ANInteractionMessagesList::First()
{
	auto pInterfaceNode = ANImpPtr<ANInteractionMessagesNode>();
	pInterfaceNode->iter = this->m_InteractionMessagesList.begin();
	return pInterfaceNode;
}

ANInteractionMessagesList::InteractionObjectNode ANInteractionMessagesList::Last()
{
	auto pInterfaceNode = ANImpPtr<ANInteractionMessagesNode>();
	pInterfaceNode->iter = this->m_InteractionMessagesList.end();
	return pInterfaceNode;
}

anSize ANInteractionMessagesList::GetSize()
{
	return this->m_InteractionMessagesList.size() + this->m_TempCollectionIML.size();
}

ANInterfacePointer<IANInteractionMessagesList> ANInteractionMessagesList::GetInteractionFromEntityName(const char* pszName)
{
	auto pipInteractionMessagesList = ANImpPtr<ANInteractionMessagesList>();

	auto it = std::find_if(this->m_InteractionMessagesList.begin(), this->m_InteractionMessagesList.end(), [&](const ANUniqueInteractionMesssage& im) 
		{
			if (im.m_pszEntityName && !strcmp(im.m_pszEntityName, pszName))
			{
				pipInteractionMessagesList->m_InteractionMessagesList.push_back(im);
			}

			return false;
		});

	return pipInteractionMessagesList;
}

ANInterfacePointer<IANInteractionMessagesList> ANInteractionMessagesList::GetInteractionFromEntityClassID(const char* pszClassIDName)
{
	auto pipInteractionMessagesList = ANImpPtr<ANInteractionMessagesList>();

	auto it = std::find_if(this->m_InteractionMessagesList.begin(), this->m_InteractionMessagesList.end(), [&](const ANUniqueInteractionMesssage& im) 
		{
			if (im.m_pszEntityName && !strcmp(im.m_pszEntityClassIDName, pszClassIDName))
			{
				pipInteractionMessagesList->m_InteractionMessagesList.push_back(im);
			}

			return false;
		});

	return pipInteractionMessagesList;
}

void ANInteractionMessagesList::Clear()
{
	this->m_InteractionMessagesList.clear();
}

void ANInteractionMessagesList::LockList()
{
	this->m_CurrentIsIterable = true;
}

void ANInteractionMessagesList::UnlockList()
{
	this->m_InteractionMessagesList.insert(this->m_InteractionMessagesList.end(), this->m_TempCollectionIML.begin(), this->m_TempCollectionIML.end());
	this->m_TempCollectionIML.clear();
	this->m_CurrentIsIterable = false;
}

IANInteractionMessagesNode& ANInteractionMessagesNode::operator++(int)
{
	this->iter++;
	return *this;
}

ANUniqueInteractionMesssage& ANInteractionMessagesNode::operator*()
{
	return *this->iter;
}

bool ANInteractionMessagesNode::operator!=(const IANInteractionMessagesList::InteractionObjectNode& Node)
{
	return this->iter != ((ANInteractionMessagesNode*)Node.m_Pointer)->iter;
}