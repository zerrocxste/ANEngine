#pragma once

enum CursorKey
{
	MAIN_FIRST,
	MAIN_SECOND,
	SECONDARY,
	ADDITIONAL_1,
	ADDITIONAL_2
};

struct KeyInformation
{
	bool m_bIsDowned;
	bool m_bPrevFrameIsDowned;
	bool m_bIsReleased;
	bool m_bIsClicked;
	float m_flDownTime;
};

class ANInput
{
public:
	ANInput(ANCore* pCore);
	~ANInput();

	void SetCursorKey(int k, bool State);

	bool IsCursorKeyDowned(int k);
	bool IsCursorKeyClicked(int k);
	bool IsCursorKeyReleased(int k);
	bool GetCursorKeyDownTime(int k);

	void SetCursorPos(anVec2 CursorPos);
	anVec2 GetCursorPos();

	void SetStateKey(int k, bool State);

	bool IsKeyDowned(int k);
	bool IsKeyClicked(int k);
	bool IsKeyReleased(int k);
	float GetKeyDownTime(int k);

	void SetCorrectWindowStartPos(anVec2 Pos);

	void Update();

	void ClearMouseData();
	void ClearKeyboardData();
	void ClearData();
private:
	ANCore* m_pCore;

	anVec2 m_CursorPos;
	KeyInformation m_kiCursorKeyMap[5];
	KeyInformation m_kiKeyMap[255];

	anVec2 m_CorrectWindowStartPos;

	void UpdateKeyMap(KeyInformation* pkiKeyMap, bool NeedDisable = false);

	static inline bool IsInArrayRange(int k, int MaxArrSize);
};

