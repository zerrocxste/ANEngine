#include "../../ANEngine.h"

#ifdef _WIN32
bool ANPlatformWin32::g_bCreatedWindowClass = false;
WNDCLASS ANPlatformWin32::g_WndClass{};

ANPlatformWin32::ANPlatformWin32(ANCore* pCore, const char* szWindowTitle, anVec2 vPosition, anVec2 vSize, bool bHasWindowFrame) :
	IANError(),
	m_pCore(pCore),
	m_bFocusLost(false),
	m_bMouseInWindowArea(false)
{
	auto pwd = GetWindowData();

	strcpy_s(pwd->m_WindowTitle, szWindowTitle != nullptr ? szWindowTitle : "ANEngine");
	pwd->m_bHasWindowFrame = bHasWindowFrame;
	pwd->m_vWindowPosition = vPosition;
	pwd->m_vWindowSize = vSize;
}

ANPlatformWin32::~ANPlatformWin32()
{

}

#define WNDPROC_GET_ANWINDOW(hWnd) ((ANPlatformWin32*)GetWindowLongPtr(hWnd, GWLP_USERDATA))

LRESULT CALLBACK ANPlatformWin32::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_NCCREATE)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
	}
	else
	{
		switch (Msg)
		{
		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED)
				break;

			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetRenderer()->ResetScene(WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetPlatform()->GetWindowData()->m_vWindowSize = anVec2(LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		{
			int button = 0;
			if (Msg == WM_LBUTTONDOWN || Msg == WM_LBUTTONDBLCLK) button = 0;
			if (Msg == WM_RBUTTONDOWN || Msg == WM_RBUTTONDBLCLK) button = 1;
			if (Msg == WM_MBUTTONDOWN || Msg == WM_MBUTTONDBLCLK) button = 2;

			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetInput()->SetCursorKey(button, true);
			break;
		}
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		{
			int button = 0;
			if (Msg == WM_LBUTTONUP) button = 0;
			if (Msg == WM_RBUTTONUP) button = 1;
			if (Msg == WM_MBUTTONUP) button = 2;
			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetInput()->SetCursorKey(button, false);
			break;
		}
		case WM_MOUSEMOVE:
			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetInput()->SetCursorPos(anVec2(LOWORD(lParam), HIWORD(lParam)));

			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hWnd;
			tme.dwFlags = TME_LEAVE;
			TrackMouseEvent(&tme);

			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetPlatform()->m_bMouseInWindowArea = TRUE;
			break;
		case WM_MOUSELEAVE:
			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetPlatform()->m_bMouseInWindowArea = FALSE;
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetInput()->SetStateKey(wParam, Msg == WM_KEYDOWN);
			break;
			break;
		case WM_KILLFOCUS:
		case WM_SETFOCUS:
			if (Msg == WM_KILLFOCUS)
			{
				WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetInput()->ClearData();
				WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetPlatform()->m_bFocusLost = true;
			}
			else
			{
				WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetPlatform()->m_bFocusLost = false;
			}
			break;
		}
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

ANModuleHandle ANPlatformWin32::GetBase()
{
	return GetModuleHandle(nullptr);
}

ANModuleHandle ANPlatformWin32::LoadLib(const char* pszLibraryPath)
{
	return LoadLibrary(pszLibraryPath);
}

template <class Type> Type ANPlatformWin32::GetProcedureAddress(ANModuleHandle pModuleHandle, const char* pszProcedureName)
{
	return GetProcAddress((HMODULE)pModuleHandle, pszProcedureName);
}

bool ANPlatformWin32::WindowCreate()
{
	if (!ANPlatformWin32::g_bCreatedWindowClass)
	{
		ANPlatformWin32::g_WndClass.hInstance = GetModuleHandle(nullptr);
		ANPlatformWin32::g_WndClass.lpfnWndProc = WndProc;
		ANPlatformWin32::g_WndClass.lpszClassName = "ANEngineWindow";
		ANPlatformWin32::g_WndClass.style = CS_HREDRAW | CS_VREDRAW;
		ANPlatformWin32::g_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
		ANPlatformWin32::g_WndClass.hIcon = LoadIcon(0, 0);
		ANPlatformWin32::g_WndClass.hbrBackground = 0;
		ANPlatformWin32::g_WndClass.lpszMenuName = nullptr;
		ANPlatformWin32::g_WndClass.cbWndExtra = 0;

		auto ClassIsCreated = (bool)RegisterClass(&ANPlatformWin32::g_WndClass);

		if (!ClassIsCreated)
		{
			this->SetError(__FUNCTION__ " > Error RegisterClass. GetLastError", GetLastError());
			return false;
		}

		ANPlatformWin32::g_bCreatedWindowClass = true;
	}

	auto pwd = this->GetWindowData();

	this->m_hWnd = CreateWindowEx(
		0,
		ANPlatformWin32::g_WndClass.lpszClassName,
		pwd->m_WindowTitle,
		pwd->m_bHasWindowFrame ? WS_OVERLAPPEDWINDOW : WS_POPUP,
		pwd->m_vWindowPosition.x, pwd->m_vWindowPosition.y,
		pwd->m_vWindowSize.x, pwd->m_vWindowSize.y,
		0, 0,
		ANPlatformWin32::g_WndClass.hInstance,
		this);

	if (!this->m_hWnd)
	{
		this->SetError(__FUNCTION__ " > Error CreateWindowEx. GetLastError", GetLastError());
		return false;
	}

	return true;
}

bool ANPlatformWin32::ProcessWindow()
{
	if (PeekMessage(&this->m_Msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&this->m_Msg);
		DispatchMessage(&this->m_Msg);
	}

	return this->m_Msg.message == WM_QUIT;
}

ANWindowHandle ANPlatformWin32::GetWindowHandle()
{
	return (ANWindowHandle)this->m_hWnd;
}

ANWindowData* ANPlatformWin32::GetWindowData()
{
	return &this->m_WindowData;
}

void ANPlatformWin32::GetPerfomanceTick(ANPerfomanceTick& PerfomanceTick)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&PerfomanceTick);
}

void ANPlatformWin32::WindowShow()
{
	ShowWindow(this->m_hWnd, SW_SHOWNORMAL);
}

void ANPlatformWin32::WindowMinimize()
{
	ShowWindow(this->m_hWnd, SW_MINIMIZE);
}

void ANPlatformWin32::WindowHide()
{
	ShowWindow(this->m_hWnd, SW_HIDE);
}

bool ANPlatformWin32::WindowIsActivated()
{
	return !this->m_bFocusLost;
}

bool ANPlatformWin32::MouseInWindowArea()
{
	return this->m_bMouseInWindowArea;
}
#endif