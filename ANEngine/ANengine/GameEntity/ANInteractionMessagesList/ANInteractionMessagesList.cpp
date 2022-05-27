#include "../../ANEngine.h"

void ANInteractionMessagesList::AddInteractionMessage(const char* pszEventMessage, IANEntity* pRemoteEntity)
{
	ANUniqueInteractionMesssage im{};
	im.m_pszEntityName = nullptr;
	im.m_pszClassIDName = nullptr;
	im.m_pszEventMessage = pszEventMessage;
	im.m_pRemoteEntity = pRemoteEntity;

	this->m_InteractionMessagesList.push_back(im);
}

void ANInteractionMessagesList::AddInteractionMessageForEntityName(const char* pszEventMessage, const char* pszEntityName, IANEntity* pRemoteEntity)
{
	ANUniqueInteractionMesssage im{};
	im.m_pszEntityName = pszEntityName;
	im.m_pszClassIDName = nullptr;
	im.m_pszEventMessage = pszEventMessage;
	im.m_pRemoteEntity = pRemoteEntity;

	this->m_InteractionMessagesList.push_back(im);
}

void ANInteractionMessagesList::AddInteractionMessageForEntityClassID(const char* pszEventMessage, const char* pszClassID, IANEntity* pRemoteEntity)
{
	ANUniqueInteractionMesssage im{};
	im.m_pszEntityName = nullptr;
	im.m_pszClassIDName = pszClassID;
	im.m_pszEventMessage = pszEventMessage;
	im.m_pRemoteEntity = pRemoteEntity;

	this->m_InteractionMessagesList.push_back(im);
}

void ANInteractionMessagesList::RemoveInteractionMessage(const char* pszEventMessage)
{
	for (auto it = this->m_InteractionMessagesList.begin(); it < this->m_InteractionMessagesList.end(); it++)
	{
		if (!strcmp((*it).m_pszEventMessage, pszEventMessage))
			this->m_InteractionMessagesList.erase(it);
	}
}

std::vector<ANUniqueInteractionMesssage*> ANInteractionMessagesList::GetInteractionFromEntityName(const char* pszName)
{
	std::vector<ANUniqueInteractionMesssage*> ret;

	auto it = std::find_if(this->m_InteractionMessagesList.begin(), this->m_InteractionMessagesList.end(), [&](const ANUniqueInteractionMesssage& im) 
		{
			if (im.m_pszEntityName && !strcmp(im.m_pszEntityName, pszName))
				ret.push_back((ANUniqueInteractionMesssage*)&im);

			return false;
		});

	return ret;
}

std::vector<ANUniqueInteractionMesssage*> ANInteractionMessagesList::GetInteractionFromEntityClassID(const char* pszClassIDName)
{
	std::vector<ANUniqueInteractionMesssage*> ret;

	auto it = std::find_if(this->m_InteractionMessagesList.begin(), this->m_InteractionMessagesList.end(), [&](const ANUniqueInteractionMesssage& im) 
		{
			if (im.m_pszEntityName && !strcmp(im.m_pszClassIDName, pszClassIDName))
				ret.push_back((ANUniqueInteractionMesssage*)&im);

			return false;
		});

	return ret;
}

void ANInteractionMessagesList::Clear()
{
	this->m_InteractionMessagesList.clear();
}
