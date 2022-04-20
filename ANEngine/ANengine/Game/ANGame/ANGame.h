#pragma once

class ANGame : public IANError
{
public:
	ANGame(ANCore* pCore);
	~ANGame();

private:
	ANCore* m_pCore;

};
