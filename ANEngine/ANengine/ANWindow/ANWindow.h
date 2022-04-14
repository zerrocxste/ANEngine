#pragma once

struct ANWindowData
{
	char m_WindowTitle[256];
	bool m_bHasWindowFrame;
	anvec2 m_vWindowPosition;
	anvec2 m_vWindowSize;
	WNDCLASS m_WndCls;
};

class ANWindow : public IANError
{
public:
	ANWindow(const char* szWindowTitle, anvec2 vPosition, anvec2 vSize, bool bHasWindowFrame);
	~ANWindow();

	bool MakeWindow();
	void RunWindow();

	void WindowShow();
	void WindowMinimize();
	void WindowHide();

	HWND GetHWND();
private:
	HWND m_hWnd;
	MSG m_WindowMSG;
	ANWindowData m_WindowData;
	ANWindowData* GetWindow();

	bool CreateWindowClass(ANWindowData* wd);
	bool CreateNewWindow(ANWindowData* wd);
};

