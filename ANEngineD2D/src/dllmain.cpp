#include "includes.h"

constexpr auto MODULE_DESC = "AlterNative engine (ANEngine) D2D Renderer module. Timestamp: " __DATE__;

struct D2DInterfaces
{
	ID2D1Factory* m_pFactory;
	IWICImagingFactory* m_pWICFactory;
	IDWriteFactory* pDWriteFactory;
};

struct D2DRenderInformation
{
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pColorBrush;
};

D2DInterfaces g_D2DInterfaces;
std::map<HWND, D2DRenderInformation> g_mWindowContextRenderInformation;
ANRendererFuncionsTable g_ANRendererFuncionsTable;

extern "C" __declspec(dllexport) bool __stdcall BeginFrame(HWND hWnd);
extern "C" __declspec(dllexport) bool __stdcall EndFrame(HWND hWnd);
extern "C" __declspec(dllexport) bool __stdcall ResetScene(HWND hWnd, WPARAM wParam, LPARAM lParam);
extern "C" __declspec(dllexport) bool __stdcall GetScreenSize(HWND hWnd, anVec2 * pAnvec2Out);
extern "C" __declspec(dllexport) bool __stdcall CreateImageFromMemory(HWND hWnd, void* pImageSrc, std::uint32_t iImageSize, ANImageID * pImageIDPtr);
extern "C" __declspec(dllexport) bool __stdcall DrawImage(HWND hWnd, ANImageID pImageID, anRect Pos, float Opacity);
extern "C" __declspec(dllexport) bool __stdcall DrawRectangle(HWND hWnd, anRect Pos, anColor Color, float Rounding);
extern "C" __declspec(dllexport) bool __stdcall DrawFilledRectangle(HWND hWnd, anRect Pos, anColor Color, float Rounding);
extern "C" __declspec(dllexport) bool __stdcall DrawCircle(HWND hWnd, anVec2 Pos, anColor Color, float Radius);
extern "C" __declspec(dllexport) bool __stdcall DrawFilledCircle(HWND hWnd, anVec2 Pos, anColor Color, float Radius);
extern "C" __declspec(dllexport) bool __stdcall CreateFontFromFile(const char* pszPath, float FontSize, ANFontID * pFontID);
extern "C" __declspec(dllexport) bool __stdcall TextDraw(HWND hWnd, const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont);

bool CreateBitmapFromMemory(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pWICFactory, void* pSource, std::uint32_t iSourceSize, ID2D1Bitmap** pOutBitmap)
{
	IWICStream* pWICStream = nullptr;
	IWICBitmapDecoder* pWICDecoder = nullptr;
	IWICBitmapFrameDecode* pWICFrameDecode = nullptr;
	IWICFormatConverter* pWICFormatConverter = nullptr;

	if (!pRenderTarget || !pWICFactory || !pSource || !iSourceSize)
		return false;

	if (!SUCCEEDED(pWICFactory->CreateStream(&pWICStream)))
		return false;

	if (!SUCCEEDED(pWICStream->InitializeFromMemory((WICInProcPointer)pSource, iSourceSize)))
		return false;

	if (!SUCCEEDED(pWICFactory->CreateDecoderFromStream(pWICStream, 0, WICDecodeOptions::WICDecodeMetadataCacheOnLoad, &pWICDecoder)))
		return false;

	if (!SUCCEEDED(pWICDecoder->GetFrame(0, &pWICFrameDecode)))
		return false;

	if (!SUCCEEDED(pWICFactory->CreateFormatConverter(&pWICFormatConverter)))
		return false;

	if (!SUCCEEDED(pWICFormatConverter->Initialize(pWICFrameDecode, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherType::WICBitmapDitherTypeNone, nullptr, 0., WICBitmapPaletteType::WICBitmapPaletteTypeMedianCut)))
		return false;

	if (!SUCCEEDED(pRenderTarget->CreateBitmapFromWicBitmap(pWICFormatConverter, pOutBitmap)))
		return false;

	pWICStream->Release();
	pWICDecoder->Release();
	pWICFrameDecode->Release();
	pWICFormatConverter->Release();

	return true;
}

bool CreateD2D1Factory()
{
	if (g_D2DInterfaces.m_pFactory != nullptr)
		return true;

	return SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_D2DInterfaces.m_pFactory));
}

bool CreateWICFactory()
{
	if (g_D2DInterfaces.m_pWICFactory != nullptr)
		return true;

	return SUCCEEDED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&g_D2DInterfaces.m_pWICFactory));
}

bool CreateDirectWriteFactory()
{
	if (g_D2DInterfaces.pDWriteFactory != nullptr)
		return true;

	return SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(decltype(g_D2DInterfaces.pDWriteFactory)), (IUnknown**)&g_D2DInterfaces.pDWriteFactory));
}

bool CreateRenderTarget(HWND hWnd)
{
	return SUCCEEDED(g_D2DInterfaces.m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU()),
		&g_mWindowContextRenderInformation[hWnd].m_pRenderTarget));
}

bool CreateGlobalBrush(HWND hWnd)
{
	return SUCCEEDED(g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_mWindowContextRenderInformation[hWnd].m_pColorBrush));
}

bool CreateRendererFunctionsTable()
{
	g_ANRendererFuncionsTable.BeginFrame = BeginFrame;
	g_ANRendererFuncionsTable.EndFrame = EndFrame;
	g_ANRendererFuncionsTable.ResetScene = ResetScene;
	g_ANRendererFuncionsTable.GetScreenSize = GetScreenSize;
	g_ANRendererFuncionsTable.CreateImageFromMemory = CreateImageFromMemory;
	g_ANRendererFuncionsTable.DrawImage = DrawImage;
	g_ANRendererFuncionsTable.DrawRectangle = DrawRectangle;
	g_ANRendererFuncionsTable.DrawFilledRectangle = DrawFilledRectangle;
	g_ANRendererFuncionsTable.DrawCircle = DrawCircle;
	g_ANRendererFuncionsTable.DrawFilledCircle = DrawFilledCircle;
	g_ANRendererFuncionsTable.CreateFontFromFile = CreateFontFromFile;
	g_ANRendererFuncionsTable.TextDraw = TextDraw;

	return true;
}

void __forceinline SetBrushColor(HWND hWnd, anColor Color)
{
	g_mWindowContextRenderInformation[hWnd].m_pColorBrush->SetColor(D2D1::ColorF(Color[RED], Color[GREEN], Color[BLUE], Color[ALPHA]));
}

extern "C" __declspec(dllexport) bool __stdcall InitializeRenderer(HINSTANCE hInstance, HWND hWnd, void* pReversed)
{
	CoInitialize(nullptr);

	if (!CreateD2D1Factory())
		return false;

	if (!CreateWICFactory())
		return false;

	if (!CreateDirectWriteFactory())
		return false;

	if (!CreateRenderTarget(hWnd))
		return false;

	if (!CreateGlobalBrush(hWnd))
		return false;

	if (!CreateRendererFunctionsTable())
		return false;

	return true;
}

extern "C" __declspec(dllexport) void* __stdcall GetRendererFunctionsTable()
{
	return &g_ANRendererFuncionsTable;
}

extern "C" __declspec(dllexport) bool __stdcall BeginFrame(HWND hWnd)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->BeginDraw();
	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall EndFrame(HWND hWnd)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->EndDraw();

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall ResetScene(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	if (wParam == SIZE_MINIMIZED)
		return false;

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->Resize(D2D1::SizeU(LOWORD(lParam), HIWORD(lParam)));

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall GetScreenSize(HWND hWnd, anVec2 * pAnvec2Out)
{
	if (!pAnvec2Out || !g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	auto ScreenSize = g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->GetSize();

	pAnvec2Out->x = ScreenSize.width;
	pAnvec2Out->y = ScreenSize.height;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall CreateImageFromMemory(HWND hWnd, void* pImageSrc, std::uint32_t iImageSize, ANImageID * pImageIDPtr)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	ID2D1Bitmap* pD2D1Bitmap = nullptr;

	if (!CreateBitmapFromMemory(g_mWindowContextRenderInformation[hWnd].m_pRenderTarget, g_D2DInterfaces.m_pWICFactory, pImageSrc, iImageSize, &pD2D1Bitmap))
		return false;

	*pImageIDPtr = (ANImageID)pD2D1Bitmap;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawImage(HWND hWnd, ANImageID pImageID, anRect Pos, float Opacity)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->DrawBitmap((ID2D1Bitmap*)pImageID, D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y), Opacity);

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawRectangle(HWND hWnd, anRect Pos, anColor Color, float Rounding)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	SetBrushColor(hWnd, Color);

	auto Rect = D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y);

	if (Rounding > 0.f)
		g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->DrawRectangle(Rect, g_mWindowContextRenderInformation[hWnd].m_pColorBrush);
	else
		g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), g_mWindowContextRenderInformation[hWnd].m_pColorBrush);

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawFilledRectangle(HWND hWnd, anRect Pos, anColor Color, float Rounding)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	SetBrushColor(hWnd, Color);

	auto Rect = D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y);

	if (Rounding > 0.f)
		g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->FillRectangle(Rect, g_mWindowContextRenderInformation[hWnd].m_pColorBrush);
	else
		g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), g_mWindowContextRenderInformation[hWnd].m_pColorBrush);

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawCircle(HWND hWnd, anVec2 Pos, anColor Color, float Radius)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	SetBrushColor(hWnd, Color);

	Radius /= 2.f;

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), g_mWindowContextRenderInformation[hWnd].m_pColorBrush);

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawFilledCircle(HWND hWnd, anVec2 Pos, anColor Color, float Radius)
{
	if (!g_mWindowContextRenderInformation[hWnd].m_pRenderTarget)
		return false;

	SetBrushColor(hWnd, Color);

	Radius /= 2.f;

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), g_mWindowContextRenderInformation[hWnd].m_pColorBrush);

	return true;
}

class CDWriteFontFileEnumerator : public IDWriteFontFileEnumerator
{
public:
	CDWriteFontFileEnumerator(IDWriteFactory* pDWriteFactory, const wchar_t* pwszFontPath) :
		m_lRef(0),
		m_pDWriteFactory(pDWriteFactory),
		m_pwszFontPath(pwszFontPath),
		m_bFontLoaded(false) {}
	
	~CDWriteFontFileEnumerator() {}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject) { return S_OK; }

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		InterlockedIncrement(&m_lRef);
		return m_lRef;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		InterlockedDecrement(&m_lRef);

		if (m_lRef == 0)
		{
			delete this;
			return 0;
		}
		else
			return m_lRef;
	}

	virtual HRESULT STDMETHODCALLTYPE MoveNext(OUT BOOL* hasCurrentFile)
	{
		if (!m_bFontLoaded)
		{
			*hasCurrentFile = TRUE;
			m_bFontLoaded = true;
		}
		else
			*hasCurrentFile = FALSE;

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetCurrentFontFile(OUT IDWriteFontFile** fontFile)
	{
		IDWriteFontFile* pFontFile = nullptr;

		m_pDWriteFactory->CreateFontFileReference(m_pwszFontPath, NULL, &pFontFile);

		*fontFile = pFontFile;

		return S_OK;
	}

private:
	DWORD m_lRef;

	IDWriteFactory* m_pDWriteFactory;

	const wchar_t* m_pwszFontPath;
	bool m_bFontLoaded;
};

class CDWriteFontCollectionLoader : IDWriteFontCollectionLoader
{
public:
	CDWriteFontCollectionLoader(const wchar_t* pwszFontPath) :
		m_lRef(0),
		m_pwszFontPath(pwszFontPath) {}

	~CDWriteFontCollectionLoader() {}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObject) { return S_OK; }

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		InterlockedIncrement(&m_lRef);
		return m_lRef;
	}
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		InterlockedDecrement(&m_lRef);

		if (m_lRef == 0)
		{
			delete this;
			return 0;
		}
		else
			return m_lRef;
	}

	virtual HRESULT STDMETHODCALLTYPE CreateEnumeratorFromKey(
		IDWriteFactory* factory,
		void const* collectionKey,
		UINT32 collectionKeySize,
		OUT IDWriteFontFileEnumerator** fontFileEnumerator)
	{
		*fontFileEnumerator = (IDWriteFontFileEnumerator*)new CDWriteFontFileEnumerator(factory, m_pwszFontPath);
		return S_OK;
	}

private:
	DWORD m_lRef;

	const wchar_t* m_pwszFontPath;
};

extern "C" __declspec(dllexport) bool __stdcall CreateFontFromFile(const char* pszPath, float FontSize, ANFontID * pFontID)
{
	auto ret = false;

	IDWriteFontCollection* pFontCollection = nullptr;
	IDWriteFontFamily* pFontFamily = nullptr;
	IDWriteLocalizedStrings* pFamilyNames = nullptr;
	IDWriteTextFormat* pTextFormat = nullptr;

	auto StrLengthText = strlen(pszPath) + 1;

	wchar_t* pwszPath = new wchar_t[StrLengthText]();

	if (!pwszPath)
		return false;

	if (!MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, pszPath, StrLengthText, pwszPath, StrLengthText))
	{
		delete[] pwszPath;
		return false;
	}

	IDWriteFontCollectionLoader* pFontLoader = (IDWriteFontCollectionLoader*)new CDWriteFontCollectionLoader(pwszPath);

	UINT32 Length = 0;
	wchar_t* pwszLocalName = nullptr;

	*pFontID = nullptr;

	if (!pFontLoader)
		goto failed;

	if (FAILED(g_D2DInterfaces.pDWriteFactory->RegisterFontCollectionLoader(pFontLoader)))
		goto failed;

	if (FAILED(g_D2DInterfaces.pDWriteFactory->CreateCustomFontCollection(pFontLoader, pwszPath, sizeof(void*), &pFontCollection)))
		goto failed;

	if (FAILED(pFontCollection->GetFontFamily(0, &pFontFamily)))
		goto failed;

	if (FAILED(pFontFamily->GetFamilyNames(&pFamilyNames)))
		goto failed;

	if (FAILED(pFamilyNames->GetStringLength(0, &Length)))
		goto failed;

	Length++;

	pwszLocalName = new wchar_t[Length];

	if (FAILED(pFamilyNames->GetString(0, pwszLocalName, Length)))
		goto failed;

	if (FAILED(g_D2DInterfaces.pDWriteFactory->CreateTextFormat(pwszLocalName, pFontCollection, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, FontSize, L"", &pTextFormat)))
		goto failed;

	*pFontID = pTextFormat;

	ret = true;

failed:

	if (pwszLocalName)
		delete[] pwszLocalName;

	if (pwszPath)
		delete[] pwszPath;

	return ret;
}

extern "C" __declspec(dllexport) bool __stdcall TextDraw(HWND hWnd, const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont)
{
	auto StrLengthText = strlen(pszText) + 1;

	wchar_t* pwszText = new wchar_t[StrLengthText]();

	if (!pwszText)
		return false;

	if (!MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, pszText, StrLengthText, pwszText, StrLengthText))
	{
		delete[] pwszText;
		return false;
	}

	SetBrushColor(hWnd, Color);

	g_mWindowContextRenderInformation[hWnd].m_pRenderTarget->DrawTextA(pwszText, wcslen(pwszText), 
		(IDWriteTextFormat*)pFont,
		D2D1::RectF(Pos.x, Pos.y, 3.402823466e+38F, 3.402823466e+38F), 
		g_mWindowContextRenderInformation[hWnd].m_pColorBrush);

	delete[] pwszText;

	return true;
}


BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("%s() -> %s\n", __FUNCTION__, MODULE_DESC);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

