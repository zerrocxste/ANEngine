#include "../ANEngine.h"

ANInput::ANInput()
{

}

ANInput::~ANInput()
{

}

void ANInput::SetStateKey(int k, bool State)
{
	if (k > 255)
		return;

	this->m_bKeyMap[k] = State;
}

bool ANInput::GetStateKey(int k)
{
	if (k > 255)
		return false;

	return this->m_bKeyMap[k];
}