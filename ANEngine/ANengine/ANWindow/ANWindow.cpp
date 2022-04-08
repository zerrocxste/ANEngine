#include "../ANEngine.h"

WNDPROC p;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

ANWindow::ANWindow(const char* szWindowTitle, anvec2 vPosition, anvec2 vSize, bool bHasWindowFrame) : 
	IANError()
{
	auto wd = GetWindow();

	wd->m_bHasWindowFrame = bHasWindowFrame;
	wd->m_vWindowPosition = vPosition;
	wd->m_vWindowSize = vSize;
}

ANWindow::~ANWindow()
{

}

bool ANWindow::MakeWindow()
{
	auto wd = GetWindow();

	WNDCLASS WndCls{};
	WndCls.hInstance = GetModuleHandle(nullptr);
	WndCls.lpfnWndProc = WndProc;
	WndCls.lpszClassName = "ANEngineWindow";
	WndCls.style = CS_VREDRAW | CS_HREDRAW;
	WndCls.hCursor = LoadCursor(WndCls.hInstance, IDC_ARROW);
	WndCls.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	WndCls.lpszMenuName = nullptr;	
	WndCls.cbWndExtra = 0;

	if (!RegisterClass(&WndCls))
	{
		this->SetError("%s() -> Failed create window class. GetLastError: %d", __FUNCTION__, GetLastError());
		return false;
	}

	this->m_hWnd = CreateWindowEx(
		0,
		WndCls.lpszClassName,
		wd->m_WindowTitle,
		wd->m_bHasWindowFrame ? WS_OVERLAPPEDWINDOW : WS_POPUPWINDOW,
		wd->m_vWindowPosition.x, wd->m_vWindowPosition.y,
		wd->m_vWindowSize.x, wd->m_vWindowSize.y,
		0, 0, WndCls.hInstance, nullptr);

	if (!this->m_hWnd)
	{
		this->SetError("%s() -> Failed create window. GetLastError: %d", __FUNCTION__, GetLastError());
		return false;
	}

	return true;
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

