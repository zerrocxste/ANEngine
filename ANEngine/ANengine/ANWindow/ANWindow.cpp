#include "../ANEngine.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

ANWindow::ANWindow(const char* szWindowTitle, anvec2 vPosition, anvec2 vSize, bool bHasWindowFrame) : 
	IANError()
{
	auto pwd = GetWindow();
	
	strcpy_s(pwd->m_WindowTitle, szWindowTitle);
	pwd->m_bHasWindowFrame = bHasWindowFrame;
	pwd->m_vWindowPosition = vPosition;
	pwd->m_vWindowSize = vSize;
}

ANWindow::~ANWindow()
{

}

bool ANWindow::CreateWindowClass(ANWindowData* pwd)
{
	pwd->m_WndCls.hInstance = GetModuleHandle(nullptr);
	pwd->m_WndCls.lpfnWndProc = WndProc;
	pwd->m_WndCls.lpszClassName = "ANEngineWindow";
	pwd->m_WndCls.style = CS_VREDRAW | CS_HREDRAW;
	pwd->m_WndCls.hCursor = LoadCursor(pwd->m_WndCls.hInstance, IDC_ARROW);
	pwd->m_WndCls.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	pwd->m_WndCls.lpszMenuName = nullptr;
	pwd->m_WndCls.cbWndExtra = 0;

	return RegisterClass(&pwd->m_WndCls);
}

bool ANWindow::CreateNewWindow(ANWindowData* pwd)
{
	return (this->m_hWnd = CreateWindowEx(
		0,
		pwd->m_WndCls.lpszClassName,
		pwd->m_WindowTitle,
		pwd->m_bHasWindowFrame ? WS_OVERLAPPEDWINDOW : WS_POPUPWINDOW,
		pwd->m_vWindowPosition.x, pwd->m_vWindowPosition.y,
		pwd->m_vWindowSize.x, pwd->m_vWindowSize.y,
		0, 0, pwd->m_WndCls.hInstance, nullptr));
}

bool ANWindow::MakeWindow()
{
	auto pwd = GetWindow();

	if (!CreateWindowClass(pwd))
	{
		this->SetError("%s() -> Failed create window class. GetLastError: %d", __FUNCTION__, GetLastError());
		return false;
	}

	if (!CreateNewWindow(pwd))
	{
		this->SetError("%s() -> Failed create window. GetLastError: %d", __FUNCTION__, GetLastError());
		return false;
	}

	return true;
}

void ANWindow::RunWindow()
{
	MSG msg;
	memset(&msg, 0, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		

	}
}

void ANWindow::WindowShow()
{
	ShowWindow(this->m_hWnd, SW_SHOWNORMAL);
}

void ANWindow::WindowHide()
{
	ShowWindow(this->m_hWnd, SW_HIDE);
}

ANWindowData* ANWindow::GetWindow()
{
	return &this->m_WindowData;
}

