#pragma once

class ANInput
{
public:
	ANInput(ANCore* pCore);
	~ANInput();

	void SetCursorKey(int k, bool State);
	bool GetCursorKey(int k);

	bool IsCursorKeyDowned(int k);
	bool IsCursorKeyReleased(int k);
	bool GetCursorKeyDownTime(int k);

	void SetCursorPos(anVec2 CursorPos);
	anVec2 GetCursorPos();

	void SetStateKey(int k, bool State);
	bool GetStateKey(int k);

	bool IsKeyDowned(int k);
	bool IsKeyReleased(int k);
	bool GetKeyDownTime(int k);
private:
	ANCore* m_pCore;

	static inline bool IsInArrayRange(int k, int MaxArrSize);

	bool m_bCursorKeyMap[5];
	anVec2 m_CursorPos;

	bool m_bKeyMap[255];

	KeyInformation m_kiCursorKeyMap[5];
	KeyInformation m_kiKeyMap[255];
};

