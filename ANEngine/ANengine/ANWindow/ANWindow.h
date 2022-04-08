#pragma once

struct ANWindowData
{
	char m_WindowTitle[256];
	bool m_bHasWindowFrame;
	anvec2 m_vWindowPosition;
	anvec2 m_vWindowSize;
};

class ANWindow : public IANError
{
public:
	ANWindow(const char* szWindowTitle, anvec2 vPosition, anvec2 vSize, bool bHasWindowFrame);
	~ANWindow();

	bool MakeWindow();

	void WindowShow();

	void WindowHide();

private:
	HWND m_hWnd;
	ANWindowData m_WindowData;
	
	ANWindowData* GetWindow();
};

