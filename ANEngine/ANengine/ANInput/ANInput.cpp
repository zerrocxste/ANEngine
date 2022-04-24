#include "../ANEngine.h"

ANInput::ANInput(ANCore* pCore) :
	m_pCore(pCore)
{
	memset(this->m_bCursorKeyMap, 0, sizeof(this->m_bCursorKeyMap) / sizeof(*this->m_bCursorKeyMap));
	m_CursorPos.Clear();
	memset(this->m_bKeyMap, 0, sizeof(this->m_bKeyMap) / sizeof(*this->m_bKeyMap));
}

ANInput::~ANInput()
{

}

void ANInput::SetCursorKey(int k, bool State)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_bCursorKeyMap)))
		return;

	this->m_bCursorKeyMap[k] = State;
}

bool ANInput::GetCursorKey(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_bCursorKeyMap)))
		return false;

	return this->m_bCursorKeyMap[k];
}

bool ANInput::IsCursorKeyDowned(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiCursorKeyMap)))
		return false;

	return this->m_kiCursorKeyMap[k].m_bIsDowned;
}

bool ANInput::IsCursorKeyReleased(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiCursorKeyMap)))
		return false;

	return this->m_kiCursorKeyMap[k].m_bIsReleased;
}

bool ANInput::GetCursorKeyDownTime(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiCursorKeyMap)))
		return false;

	return this->m_kiCursorKeyMap[k].m_flDownTime;
}

void ANInput::SetCursorPos(anVec2 CursorPos)
{
	this->m_CursorPos = CursorPos;
}

anVec2 ANInput::GetCursorPos()
{
	return this->m_CursorPos;
}

void ANInput::SetStateKey(int k, bool State)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_bKeyMap)))
		return;

	this->m_bKeyMap[k] = State;



	auto& Key = this->m_kiKeyMap[k];

	if (!Key.m_bIsDowned && Key.m_flDownTime > 0.f)
		Key.m_bIsReleased = true;

	Key.m_bIsDowned = State;

	Key.m_bIsDowned ? Key.m_flDownTime += 0.001f /*DELTA?*/ : Key.m_flDownTime = 0.f;
}

bool ANInput::GetStateKey(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_bKeyMap)))
		return false;

	return this->m_bKeyMap[k];
}

bool ANInput::IsKeyDowned(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_bIsDowned;
}

bool ANInput::IsKeyReleased(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_bIsReleased;
}

bool ANInput::GetKeyDownTime(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_flDownTime;
}

inline bool ANInput::IsInArrayRange(int k, int MaxArrSize)
{
	return k < MaxArrSize;
}
