#include "../ANEngine.h"

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
	
	strcpy_s(pwd->m_WindowTitle, szWindowTitle);
	pwd->m_bHasWindowFrame = bHasWindowFrame;
	pwd->m_vWindowPosition = vPosition;
	pwd->m_vWindowSize = vSize;

	memset(&this->m_WindowMSG, 0, sizeof(MSG));
}

ANWindow::~ANWindow()
{

}

bool ANWindow::CreateWindowClass(ANWindowData* pwd)
{
	pwd->m_WndCls.hInstance = GetModuleHandle(nullptr);
	pwd->m_WndCls.lpfnWndProc = WndProc;
	pwd->m_WndCls.lpszClassName = "ANEngineWindow";
	pwd->m_WndCls.style = CS_HREDRAW | CS_VREDRAW ;
	pwd->m_WndCls.hCursor = LoadCursor(0, IDC_ARROW);
	pwd->m_WndCls.hIcon = LoadIcon(0, 0);
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
		0, 0, 
		pwd->m_WndCls.hInstance, 
		this));
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

ANImageID ANWindow::InitImages(const char* pszPath)
{
	ANUniqueResource Image;

	this->m_pCore->GetResourceManager()->ReadBinFile(pszPath, &Image);

	ANImageID ret = 0;

	if (!this->m_pCore->GetRenderer()->CreateImageFromMemory(Image.GetResourceLocation(), Image.GetResourceSize(), &ret))
		return 0;

	return ret;
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

bool ANWindow::RunWindow()
{
	auto Krolik = InitImages("Image.png");

	ANFontID FontID = 0;

	this->m_pCore->GetRenderer()->CreateFontFromFile("bvc.ttf", 72.f, &FontID);

	while (this->m_WindowMSG.message != WM_QUIT)
	{
		if (PeekMessage(&this->m_WindowMSG, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&this->m_WindowMSG);
			DispatchMessage(&this->m_WindowMSG);
			continue;
		}

		this->m_pCore->GetRenderer()->BeginFrame();

		auto ScreenSize = this->m_pCore->GetRenderer()->GetScreenSize();

		{
			this->m_pCore->GetRenderer()->DrawImage(Krolik, anVec2(), anVec2(ScreenSize.x, ScreenSize.y), 0.5f);

			this->m_pCore->GetRenderer()->TextDraw(u8"Тестовый текст, Hello!", anVec2(), anColor::Green(), FontID);

			auto Size = anVec2(50.f, 50.f);

			this->m_pCore->GetRenderer()->DrawRectangle(anVec2(0.f, 100.f), Size, anColor::Green());

			this->m_pCore->GetRenderer()->DrawFilledRectangle(anVec2(0.f, 200.f), Size, anColor::Red(), 30.f);

			this->m_pCore->GetRenderer()->DrawCircle(anVec2(0.f, 300.f), anColor::Blue(), 50.f);

			this->m_pCore->GetRenderer()->DrawFilledCircle(anVec2(0.f, 400.f), anColor::Magenta(), 50.f);
		}

		this->m_pCore->GetRenderer()->EndFrame();
	}

	return true;
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

