#pragma once

class ANInput
{
public:
	ANInput(ANCore* pCore);
	~ANInput();

	void SetStateKey(int k, bool State);
	bool GetStateKey(int k);
private:
	ANCore* m_pCore;

	bool m_bKeyMap[255];
};

