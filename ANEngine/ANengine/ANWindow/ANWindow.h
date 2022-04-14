#pragma once

struct ANWindowData
{
	char m_WindowTitle[256];
	bool m_bHasWindowFrame;
	anVec2 m_vWindowPosition;
	anVec2 m_vWindowSize;
};

class ANWindow : public IANError
{
public:
	ANWindow(ANCore* pCore, const char* szWindowTitle, anVec2 vPosition, anVec2 vSize, bool bHasWindowFrame);
	~ANWindow();

	bool MakeWindow();

	bool ProcessWindow();
	bool IsAllowRender();

	void WindowShow();
	void WindowMinimize();
	void WindowHide();

	HWND GetHWND();

	static bool bWindowClassIsCreated;
	static WNDCLASS WndClass;

private:
	ANCore* m_pCore;

	HWND m_hWnd;
	MSG m_WindowMSG;
	ANWindowData m_WindowData;
	ANWindowData* GetWindow();

	bool m_bAllowRender;

	bool CreateWindowClass();
	bool CreateNewWindow(ANWindowData* wd);

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

