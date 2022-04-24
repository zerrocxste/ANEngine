#pragma once

class ANGui : public IANError
{
public:
	ANGui(ANCore* m_pCore);
	~ANGui();

	bool CheckBox(const char* pszName, bool* pVar);

private:
	ANCore* m_pCore;

};

