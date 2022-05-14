#pragma once

class IANBasicEntity
{
protected:
	int m_ID;
public:
	virtual int GetEntityID() = 0;
};