#pragma once

class ANCore
{
public:
	ANCore();
	~ANCore();

	bool Run();
private:
	ANWindow* m_pANWindow;

	ANWindow* GetWindow();
};

