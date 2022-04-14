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
			pANWindow->m_pCore->GetRenderer()->ResetScene(wParam, lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			pANWindow->m_pCore->GetInput()->SetStateKey(wParam, true);
			break;
		case WM_KEYUP:
			pANWindow->m_pCore->GetInput()->SetStateKey(wParam, false);
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

