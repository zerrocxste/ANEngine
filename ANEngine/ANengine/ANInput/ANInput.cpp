#include "../ANEngine.h"

ANInput::ANInput(ANCore* pCore) :
	m_pCore(pCore)
{
	memset(&this->m_kiCursorKeyMap, 0, sizeof(this->m_kiCursorKeyMap));
	memset(&this->m_kiKeyMap, 0, sizeof(this->m_kiKeyMap));
}

ANInput::~ANInput()
{

}

void ANInput::SetCursorKey(int k, bool State)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiCursorKeyMap)))
		return;

	this->m_kiCursorKeyMap[k].m_bIsDowned = State;
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
	return this->m_CursorPos - this->m_CorrectWindowStartPos;
}

void ANInput::SetStateKey(int k, bool State)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return;

	this->m_kiKeyMap[k].m_bIsDowned = State;
}

bool ANInput::IsKeyDowned(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_bIsDowned;
}

bool ANInput::IsKeyClicked(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_bIsClicked;
}

bool ANInput::IsKeyReleased(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_bIsReleased;
}

float ANInput::GetKeyDownTime(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
		return false;

	return this->m_kiKeyMap[k].m_flDownTime;
}

void ANInput::SetCorrectWindowStartPos(anVec2 Pos)
{
	this->m_CorrectWindowStartPos = Pos;
}

void ANInput::Update()
{
	for (auto& ckm : this->m_kiCursorKeyMap)
		UpdateKeyMap(&ckm);

	for (auto& km : this->m_kiKeyMap)
		UpdateKeyMap(&km);
}

void ANInput::UpdateKeyMap(KeyInformation* pkiKeyMap)
{
	auto& km = *pkiKeyMap;

	km.m_bIsClicked = km.m_bIsDowned && !km.m_bPrevFrameIsDowned;
	km.m_bIsReleased = !km.m_bIsDowned && km.m_bPrevFrameIsDowned;
	km.m_bPrevFrameIsDowned = km.m_bIsDowned;

	if (km.m_bIsDowned)
		km.m_flDownTime += this->m_pCore->GetPerfomance()->GetFrameTime(); /*DELTA?*/
	else
		km.m_flDownTime = 0.f;
}

inline bool ANInput::IsInArrayRange(int k, int MaxArrSize)
{
	return k < MaxArrSize;
}
