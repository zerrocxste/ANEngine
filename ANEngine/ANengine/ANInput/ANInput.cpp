#include "../ANEngine.h"

ANInput::ANInput(ANCore* pCore) :
	m_pCore(pCore)
{
	ClearData();
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
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiCursorKeyMap[k].m_bIsDowned;
}

bool ANInput::IsCursorKeyClicked(int k)
{
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiCursorKeyMap[k].m_bIsClicked;
}

bool ANInput::IsCursorKeyReleased(int k)
{
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiCursorKeyMap[k].m_bIsReleased;
}

float ANInput::GetCursorKeyDownTime(int k)
{
	if (!CheckArrayRange(k))
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
	{
		this->SetError("Bad cursor key, not equal array range");
		return;
	}

	this->m_kiKeyMap[k].m_bIsDowned = State;
}

bool ANInput::IsKeyDowned(int k)
{
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiKeyMap[k].m_bIsDowned;
}

bool ANInput::IsKeyClicked(int k)
{
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiKeyMap[k].m_bIsClicked;
}

bool ANInput::IsKeyReleased(int k)
{
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiKeyMap[k].m_bIsReleased;
}

float ANInput::GetKeyDownTime(int k)
{
	if (!CheckArrayRange(k))
		return false;

	return this->m_kiKeyMap[k].m_flDownTime;
}

void ANInput::SetCorrectWindowStartPos(anVec2 Pos)
{
	this->m_CorrectWindowStartPos = Pos;
}

void ANInput::Update()
{
	auto plt = this->m_pCore->GetPlatform();

	if (!plt->WindowIsActivated())
		return;

	auto MouseNoOnArea = !plt->MouseInWindowArea();

	for (auto& ckm : this->m_kiCursorKeyMap)
		UpdateKeyMap(&ckm, MouseNoOnArea);

	for (auto& km : this->m_kiKeyMap)
		UpdateKeyMap(&km);
}

void ANInput::ClearMouseData()
{
	memset(&this->m_kiCursorKeyMap, 0, sizeof(this->m_kiCursorKeyMap));
}

void ANInput::ClearKeyboardData()
{
	memset(&this->m_kiKeyMap, 0, sizeof(this->m_kiKeyMap));
}

void ANInput::ClearData()
{
	ClearMouseData();
	ClearKeyboardData();
}

void ANInput::UpdateKeyMap(KeyInformation* pkiKeyMap, bool NeedDisable)
{
	auto& km = *pkiKeyMap;

	if (!NeedDisable)
	{
		km.m_bIsClicked = km.m_bIsDowned && !km.m_bPrevFrameIsDowned;
		km.m_bIsReleased = !km.m_bIsDowned && km.m_bPrevFrameIsDowned;
		km.m_bPrevFrameIsDowned = km.m_bIsDowned;
	}
	else
	{
		km.m_bIsClicked = km.m_bIsReleased = km.m_bPrevFrameIsDowned = km.m_bIsDowned = false;
	}

	if (km.m_bIsDowned)
		km.m_flDownTime += this->m_pCore->GetPerfomance()->GetFrameTime();
	else
		km.m_flDownTime = 0.f;
}

bool ANInput::CheckArrayRange(int k)
{
	if (!IsInArrayRange(k, ARRSIZE(this->m_kiKeyMap)))
	{
		this->SetError(__FUNCTION__ ": Bad key, not equal array range");
		return false;
	}

	return true;
}

inline bool ANInput::IsInArrayRange(int k, int MaxArrSize)
{
	return k < MaxArrSize;
}
