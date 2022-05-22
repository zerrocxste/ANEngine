#pragma once

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
private:
	ANCore* m_pCore;

	anVec2 m_CursorPos;
	KeyInformation m_kiCursorKeyMap[5];
	KeyInformation m_kiKeyMap[255];

	anVec2 m_CorrectWindowStartPos;

	void UpdateKeyMap(KeyInformation* pkiKeyMap);

	static inline bool IsInArrayRange(int k, int MaxArrSize);
};

