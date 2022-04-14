#pragma once

struct ANWindowData
{
	char m_WindowTitle[256];
	bool m_bHasWindowFrame;
	anVec2 m_vWindowPosition;
	anVec2 m_vWindowSize;
	WNDCLASS m_WndCls;
};

class ANWindow : public IANError
{
public:
	ANWindow(ANCore* pCore, const char* szWindowTitle, anVec2 vPosition, anVec2 vSize, bool bHasWindowFrame);
	~ANWindow();

	bool MakeWindow();

	bool ProcessWindow();
	bool IsAllowRender();

	bool RunWindow();

	void WindowShow();
	void WindowMinimize();
	void WindowHide();

	HWND GetHWND();

private:
	ANCore* m_pCore;

	HWND m_hWnd;
	MSG m_WindowMSG;
	ANWindowData m_WindowData;
	ANWindowData* GetWindow();

	bool m_bAllowRender;

	bool CreateWindowClass(ANWindowData* wd);
	bool CreateNewWindow(ANWindowData* wd);

	ANImageID InitImages(const char* pszPath);

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

