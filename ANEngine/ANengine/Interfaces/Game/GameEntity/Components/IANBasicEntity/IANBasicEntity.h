#pragma once

class IANBasicEntity
{
protected:
	int m_ID;
	char* m_szEntityClassID;
public:
	virtual int GetEntityID() = 0;
	virtual char* GetEntityClassID() = 0;
};