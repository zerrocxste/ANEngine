#include "../ANEngine.h"

ANInput::ANInput(ANCore* pCore) :
	m_pCore(pCore)
{
	memset(this->m_bKeyMap, 0, sizeof(this->m_bKeyMap) / sizeof(*this->m_bKeyMap));
}

ANInput::~ANInput()
{

}

void ANInput::SetStateKey(int k, bool State)
{
	if (k >= 255)
		return;

	this->m_bKeyMap[k] = State;
}

bool ANInput::GetStateKey(int k)
{
	if (k >= 255)
		return false;

	return this->m_bKeyMap[k];
}