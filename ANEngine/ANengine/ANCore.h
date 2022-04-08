#pragma once

struct ANInterfaces
{
	ANWindow* m_pANWindow;
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
};

class ANCore
{
public:
	ANCore();
	~ANCore();

	ANWindow* GetWindow();
	ANInput* GetInput();
	ANRenderer* GetRenderer();

	bool Run();

	static ANCore* GetInstance();
private:
	ANInterfaces m_Interfaces;
};

