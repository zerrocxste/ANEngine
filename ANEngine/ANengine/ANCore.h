#pragma once

class ANCore
{
public:
	ANCore();
	~ANCore();

	ANWindow* GetWindow();

private:
	ANWindow* m_pANWindow;
};

