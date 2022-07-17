#include "../ANEngine.h"

WNDCLASS ANWindow::WndClass{};

#define WNDPROC_GET_ANWINDOW(hWnd) ((ANWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA))

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_NCCREATE)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		SetCapture(WNDPROC_GET_ANWINDOW(hWnd)->GetHWND());
	}
	else
	{
		switch (Msg)
		{
		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED)
				break;

			WNDPROC_GET_ANWINDOW(hWnd)->m_pCore->GetRenderer()->ResetScene(WNDPROC_GET_ANWINDOW(hWnd)->GetWindow()->m_vWindowSize = anVec2(LOWORD(lParam), HIWORD(lParam)));
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

			WNDPROC_GET_ANWINDOW(hWnd)->m_bMouseInWindowArea = TRUE;
			break;
		case WM_MOUSELEAVE:
			WNDPROC_GET_ANWINDOW(hWnd)->m_bMouseInWindowArea = FALSE;
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
				WNDPROC_GET_ANWINDOW(hWnd)->m_bFocusLost = true;
			}
			else
			{
				WNDPROC_GET_ANWINDOW(hWnd)->m_bFocusLost = false;
			}
			break;
		}
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

ANWindow::ANWindow(ANCore* pCore, const char* szWindowTitle, anVec2 vPosition, anVec2 vSize, bool bHasWindowFrame) :
	m_pCore(pCore),
	IANError(), 
	m_bFocusLost(false),
	m_bMouseInWindowArea(false)
{
	auto pwd = GetWindow();
	
	strcpy_s(pwd->m_WindowTitle, szWindowTitle != nullptr ? szWindowTitle : "ANEngine");
	pwd->m_bHasWindowFrame = bHasWindowFrame;
	pwd->m_vWindowPosition = vPosition;
	pwd->m_vWindowSize = vSize;

	memset(&this->m_WindowMSG, 0, sizeof(MSG));
}

ANWindow::~ANWindow()
{

}

bool ANWindow::CreateWindowClass()
{
	ANWindow::WndClass.hInstance = GetModuleHandle(nullptr);
	ANWindow::WndClass.lpfnWndProc = WndProc;
	ANWindow::WndClass.lpszClassName = "ANEngineWindow";
	ANWindow::WndClass.style = CS_HREDRAW | CS_VREDRAW ;
	ANWindow::WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	ANWindow::WndClass.hIcon = LoadIcon(0, 0);
	ANWindow::WndClass.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	ANWindow::WndClass.lpszMenuName = nullptr;
	ANWindow::WndClass.cbWndExtra = 0;

	return (bool)RegisterClass(&ANWindow::WndClass);
}

bool ANWindow::CreateNewWindow(ANWindowData* pwd)
{
	return (this->m_hWnd = CreateWindowEx(
		0,
		ANWindow::WndClass.lpszClassName,
		pwd->m_WindowTitle,
		pwd->m_bHasWindowFrame ? WS_OVERLAPPEDWINDOW : WS_POPUP,
		pwd->m_vWindowPosition.x, pwd->m_vWindowPosition.y,
		pwd->m_vWindowSize.x, pwd->m_vWindowSize.y,
		0, 0, 
		ANWindow::WndClass.hInstance,
		this));
}

bool ANWindow::MakeWindow()
{
	CreateWindowClass();

	auto pwd = GetWindow();

	if (!CreateNewWindow(pwd))
	{
		this->SetError("%s() -> Failed create window. GetLastError: %d", __FUNCTION__, GetLastError());
		return false;
	}

	return true;
}

bool ANWindow::ProcessWindow()
{
	if (PeekMessage(&this->m_WindowMSG, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&this->m_WindowMSG);
		DispatchMessage(&this->m_WindowMSG);
	}

	return this->m_WindowMSG.message == WM_QUIT;
}

void ANWindow::WindowShow()
{
	ShowWindow(this->m_hWnd, SW_SHOWNORMAL);
}

void ANWindow::WindowMinimize()
{
	ShowWindow(this->m_hWnd, SW_MINIMIZE);
}

void ANWindow::WindowHide()
{
	ShowWindow(this->m_hWnd, SW_HIDE);
}

bool ANWindow::IsActivated()
{
	return !this->m_bFocusLost;
}

bool ANWindow::MouseInWindowArea()
{
	return this->m_bMouseInWindowArea;
}

HWND ANWindow::GetHWND()
{
	return this->m_hWnd;
}

ANWindowData* ANWindow::GetWindow()
{
	return &this->m_WindowData;
}

