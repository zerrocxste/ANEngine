#pragma once

class ANInput
{
public:
	ANInput();
	~ANInput();

	void SetStateKey(int k, bool State);
	bool GetStateKey(int k);
private:
	bool m_bKeyMap[255];
};

