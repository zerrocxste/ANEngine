#pragma once

class IANBasicEntity
{
public:
	virtual int GetEntityID() = 0;
	virtual char* GetEntityClassID() = 0;
};