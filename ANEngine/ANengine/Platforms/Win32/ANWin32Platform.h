#pragma once

#ifdef _WIN32
class ANPlatformWin32 : public IANError
{
private:
	ANCore* m_pCore;

	HWND m_hWnd;
	MSG m_Msg;

	bool m_bFocusLost;
	bool m_bMouseInWindowArea;

	ANWindowData m_WindowData;

	static bool g_bCreatedWindowClass;
	static WNDCLASS g_WndClass;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
public:
	static ANModuleHandle GetBase();
	static ANModuleHandle LoadLib(const char* pszLibraryPath);
	template <class Type> static Type GetProcedureAddress(ANModuleHandle pModuleHandle, const char* pszProcedureName);

	static void GetPerfomanceTick(ANPerfomanceTick& PerfomanceTick);

	ANPlatformWin32(ANCore* pCore, const char* szWindowTitle, anVec2 vPosition, anVec2 vSize, bool bHasWindowFrame);
	~ANPlatformWin32();

	bool WindowCreate();
	bool ProcessWindow();

	ANWindowHandle GetWindowHandle();

	ANWindowData* GetWindowData();
	
	void WindowShow();
	void WindowMinimize();
	void WindowHide();

	bool WindowIsActivated();
	bool MouseInWindowArea();
};
#endif