#include "../ANEngine.h"

WNDCLASS ANWindow::WndClass{};

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_NCCREATE)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
	}
	else
	{
		auto pANWindow = (ANWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		switch (Msg)
		{
		case WM_SIZE:
			if (wParam == SIZE_MINIMIZED)
				break;

			pANWindow->m_pCore->GetRenderer()->ResetScene(anVec2(LOWORD(lParam), HIWORD(lParam)));
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
			pANWindow->m_pCore->GetInput()->SetCursorKey(button, true);
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
			pANWindow->m_pCore->GetInput()->SetCursorKey(button, false);
			break;
		}
		case WM_MOUSEMOVE:
			pANWindow->m_pCore->GetInput()->SetCursorPos(anVec2(LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
			pANWindow->m_pCore->GetInput()->SetStateKey(wParam, Msg == WM_KEYDOWN);
			break;
		default:
			break;
		}
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

ANWindow::ANWindow(ANCore* pCore, const char* szWindowTitle, anVec2 vPosition, anVec2 vSize, bool bHasWindowFrame) :
	m_pCore(pCore),
	IANError()
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
		pwd->m_bHasWindowFrame ? WS_OVERLAPPEDWINDOW : WS_POPUPWINDOW,
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
	this->m_bAllowRender = true;

	auto ret = this->m_WindowMSG.message != WM_QUIT;

	if (PeekMessage(&this->m_WindowMSG, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&this->m_WindowMSG);
		DispatchMessage(&this->m_WindowMSG);
		this->m_bAllowRender = false;
	}

	return ret;
}

bool ANWindow::IsAllowRender()
{
	return this->m_bAllowRender;
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

HWND ANWindow::GetHWND()
{
	return this->m_hWnd;
}

ANWindowData* ANWindow::GetWindow()
{
	return &this->m_WindowData;
}

