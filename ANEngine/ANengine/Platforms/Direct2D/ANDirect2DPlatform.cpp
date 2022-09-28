#include "../../ANEngine.h"

#ifdef BACKEND_DIRECT2D
#include <corecrt_io.h> 

__forceinline void SetBrushColor(ID2D1SolidColorBrush* m_pColorBrush, anColor Color)
{
	m_pColorBrush->SetColor(D2D1::ColorF(Color.r / 255.f, Color.g / 255.f, Color.b / 255.f, Color.a / 255.f));
}

__forceinline bool CreateBitmapFromMemory(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pWICFactory, void* pSource, std::uint32_t iSourceSize, ID2D1Bitmap** pOutBitmap)
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

__forceinline bool CreateTrinagleGeometry(ID2D1Factory* pD2D1Factory, D2D1_POINT_2F pt1, D2D1_POINT_2F pt2, D2D1_POINT_2F pt3, ID2D1PathGeometry** pD2D1PathGeometry)
{
	ID2D1GeometrySink* pSink = nullptr;

	if (FAILED(pD2D1Factory->CreatePathGeometry(pD2D1PathGeometry)))
		return false;

	if (FAILED(((ID2D1PathGeometry*)(*pD2D1PathGeometry))->Open(&pSink)))
		return false;

	pSink->BeginFigure(pt1, D2D1_FIGURE_BEGIN_FILLED);

	pSink->AddLine(pt2);

	pSink->AddLine(pt3);

	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

	if (FAILED(pSink->Close()))
		return false;

	pSink->Release();

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

__forceinline bool ANRendererlatformD2D::singleton_::ProcessTextCache(const char* pszText, ANFontID FontID, DWriteTextCache* pCachedTextElement)
{
	IDWriteTextFormat* pDWriteTextFormat = (IDWriteTextFormat*)FontID;

	auto& e = ANRendererlatformD2D::singleton_::mDWriteTextCache[(void*)(pszText + (std::uintptr_t)FontID)];

	auto StrLengthText = 1;
	auto TotalSumOfSymStr = 0;

	for (auto i = pszText; *i != '\0'; i++) {
		StrLengthText++;
		TotalSumOfSymStr += *i;
	}

	if (e.m_szText != pszText ||
		e.m_iTextLength != StrLengthText ||
		e.m_iTotalSumOfSymStr != TotalSumOfSymStr ||
		e.m_pDWriteTextFormat != pDWriteTextFormat)
	{
		if (e.m_wszText != nullptr)
			delete[] e.m_wszText;

		if (e.m_pDWriteTextLayout)
			e.m_pDWriteTextLayout->Release();

		e.m_wszText = new wchar_t[StrLengthText]();

		if (!e.m_wszText)
			return false;

		if (!MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, pszText, StrLengthText, e.m_wszText, StrLengthText))
		{
			delete[] e.m_wszText;
			return false;
		}

		e.m_szText = pszText;
		e.m_iTextLength = StrLengthText;
		e.m_iTotalSumOfSymStr = TotalSumOfSymStr;
		e.m_pDWriteTextFormat = pDWriteTextFormat;

		if (FAILED(ANRendererlatformD2D::singleton_::pDWriteFactory->CreateTextLayout(e.m_wszText, StrLengthText, e.m_pDWriteTextFormat, FLT_MAX, FLT_MAX, &e.m_pDWriteTextLayout)))
			return false;

		if (FAILED(e.m_pDWriteTextLayout->GetMetrics(&e.m_dwrTextMetrics)))
			return false;
	}

	*pCachedTextElement = e;

	return true;
}

ANRendererlatformD2D::singleton_ ANRendererlatformD2D::m_singleton{};

bool ANRendererlatformD2D::singleton_::CreateD2D1Factory()
{
	if (this->pFactory != nullptr)
		return true;

	return SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &this->pFactory));
}

bool ANRendererlatformD2D::singleton_::CreateWICFactory()
{
	if (ANRendererlatformD2D::singleton_::pWICFactory != nullptr)
		return true;

	return SUCCEEDED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&(ANRendererlatformD2D::singleton_::pWICFactory)));
}

bool ANRendererlatformD2D::singleton_::CreateDirectWriteFactory()
{
	if (this->pDWriteFactory != nullptr)
		return true;

	return SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(decltype(this->pDWriteFactory)), (IUnknown**)&this->pDWriteFactory));
}

void ANRendererlatformD2D::singleton_::Initialize()
{
	if (!ANRendererlatformD2D::singleton_::bCriticalSectionInitialized)
	{
		ANRendererlatformD2D::singleton_::bCriticalSectionInitialized = true;
		InitializeCriticalSection(&(ANRendererlatformD2D::singleton_::csInitializeRenderer));
	}

	CoInitialize(nullptr);
}

bool ANRendererlatformD2D::CreateRenderTarget(ANWindowHandle WindowHandle, bool bVerticalSyncEnabled)
{
	if (!ANRendererlatformD2D::m_singleton.pFactory)
		return false;

	D2D1_PIXEL_FORMAT pixelFormat{};
	pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	pixelFormat.alphaMode = D2D1_ALPHA_MODE_UNKNOWN;

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties{};
	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
	renderTargetProperties.pixelFormat = pixelFormat;
	renderTargetProperties.dpiX = 0.0;
	renderTargetProperties.dpiY = 0.0;
	renderTargetProperties.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	renderTargetProperties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	D2D1_HWND_RENDER_TARGET_PROPERTIES hwndRenderTargetProperties{};
	hwndRenderTargetProperties.hwnd = (HWND)WindowHandle;
	hwndRenderTargetProperties.pixelSize = D2D1::Size(static_cast<UINT32>(0), static_cast<UINT32>(0));
	hwndRenderTargetProperties.presentOptions = this->m_bEnabledVerticalSync ? D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS : D2D1_PRESENT_OPTIONS_IMMEDIATELY; //VERTYCAL SYNC

	return SUCCEEDED(ANRendererlatformD2D::m_singleton.pFactory->CreateHwndRenderTarget(renderTargetProperties, hwndRenderTargetProperties, &this->m_pRenderTarget));
}

bool ANRendererlatformD2D::CreateGlobalBrush()
{
	if (!this->m_pRenderTarget)
		return false;

	return SUCCEEDED(this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->m_pColorBrush)) &&
		SUCCEEDED(this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->m_pColorBrushBlack));
}

bool ANRendererlatformD2D::Initialize(HWND hWnd, bool bVerticalSyncEnabled)
{
	if (!ANRendererlatformD2D::m_singleton.CreateD2D1Factory())
	{
		this->SetError(__FUNCTION__ " > Failed create D2D1 factory");
		return false;
	}

	if (!ANRendererlatformD2D::m_singleton.CreateWICFactory())
	{
		this->SetError(__FUNCTION__ " > Failed create WIC factory");
		return false;
	}

	if (!ANRendererlatformD2D::m_singleton.CreateDirectWriteFactory())
	{
		this->SetError(__FUNCTION__ " > Failed create DWrite factory");
		return false;
	}

	if (!CreateRenderTarget(hWnd, bVerticalSyncEnabled))
	{
		this->SetError(__FUNCTION__ " > Failed create HwndRenderTarget factory");
		return false;
	}

	if (!CreateGlobalBrush())
	{
		this->SetError(__FUNCTION__ " > Failed create Global brushes factory");
		return false;
	}

	return true;
}

bool ANRendererlatformD2D::InitializeRenderer(ANWindowHandle WindowHandle, void* pReversed)
{
	ANRendererlatformD2D::m_singleton.Initialize();

	EnterCriticalSection(&ANRendererlatformD2D::m_singleton.csInitializeRenderer);

	auto ret = Initialize((HWND)WindowHandle, (bool)pReversed);

	LeaveCriticalSection(&ANRendererlatformD2D::m_singleton.csInitializeRenderer);

	return ret;
}

bool ANRendererlatformD2D::BeginFrame()
{
	this->m_pRenderTarget->BeginDraw();
	this->m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	return true;
}

bool ANRendererlatformD2D::EndFrame()
{
	this->m_pRenderTarget->EndDraw();

	return true;
}

bool ANRendererlatformD2D::ClearScene()
{
	this->m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	return true;
}

bool ANRendererlatformD2D::ResetScene(anVec2 ScreenSize)
{
	this->m_pRenderTarget->Resize(D2D1::SizeU((int)ScreenSize.x, (int)ScreenSize.y));

	return true;
}

bool ANRendererlatformD2D::GetScreenSize(ANInternalGuiWindowID GuiWindow, anVec2 * pAnvec2Out)
{
	if (!pAnvec2Out)
		return false;

	D2D1_SIZE_F ScreenSize;

	if (GuiWindow == 0)
	{
		ScreenSize = this->m_pRenderTarget->GetSize();
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->GetSize();
	}

	pAnvec2Out->x = ScreenSize.width;
	pAnvec2Out->y = ScreenSize.height;

	return true;
}

bool ANRendererlatformD2D::CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID * pImageIDPtr)
{
	ID2D1Bitmap* pD2D1Bitmap = nullptr;

	if (!CreateBitmapFromMemory(this->m_pRenderTarget, ANRendererlatformD2D::m_singleton.pWICFactory, pImageSrc, iImageSize, &pD2D1Bitmap))
		return false;

	*pImageIDPtr = (ANImageID)pD2D1Bitmap;

	return true;
}

bool ANRendererlatformD2D::GetImageSize(ANImageID ImageID, anVec2 * pSize)
{
	if (!ImageID)
		return false;

	auto Size = ((ID2D1Bitmap*)(ImageID))->GetSize();

	pSize->x = Size.width;
	pSize->y = Size.height;

	return true;
}

void ANRendererlatformD2D::FreeImage(ANImageID * pImageIDPtr)
{
	if (!*pImageIDPtr)
		return;

	((ID2D1Bitmap*)(*pImageIDPtr))->Release();
	*pImageIDPtr = nullptr;
}

bool ANRendererlatformD2D::DrawImage(ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity)
{
	if (!pImageID)
		return false;

	if (GuiWindow == 0)
	{
		this->m_pRenderTarget->DrawBitmap((ID2D1Bitmap*)pImageID, D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y), Opacity);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawBitmap((ID2D1Bitmap*)pImageID, D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y), Opacity);
	}

	return true;
}

bool ANRendererlatformD2D::DrawLine(ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	SetBrushColor(this->m_pColorBrush, Color);

	if (GuiWindow == 0)
	{
		this->m_pRenderTarget->DrawLine(D2D1::Point2F(From.x, From.y), D2D1::Point2F(To.x, To.y), this->m_pColorBrush, LineThickness);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawLine(D2D1::Point2F(From.x, From.y), D2D1::Point2F(To.x, To.y), this->m_pColorBrush, LineThickness);
	}

	return true;
}

bool ANRendererlatformD2D::DrawRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding)
{
	SetBrushColor(this->m_pColorBrush, Color);

	auto Rect = D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y);

	if (GuiWindow == 0)
	{
		if (Rounding > 0.f)
			this->m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), this->m_pColorBrush, LineThickness);
		else
			this->m_pRenderTarget->DrawRectangle(Rect, this->m_pColorBrush, LineThickness);
	}
	else
	{
		ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

		if (Rounding > 0.f)
			BitmapRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), this->m_pColorBrush, LineThickness);
		else
			BitmapRenderTarget->DrawRectangle(Rect, this->m_pColorBrush, LineThickness);
	}

	return true;
}

bool ANRendererlatformD2D::DrawFilledRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding)
{
	SetBrushColor(this->m_pColorBrush, Color);

	auto Rect = D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y);

	if (GuiWindow == 0)
	{
		if (Rounding > 0.f)
			this->m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), this->m_pColorBrush);
		else
			this->m_pRenderTarget->FillRectangle(Rect, this->m_pColorBrush);
	}
	else
	{
		ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

		if (Rounding > 0.f)
			BitmapRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), this->m_pColorBrush);
		else
			BitmapRenderTarget->FillRectangle(Rect, this->m_pColorBrush);
	}

	return true;
}

bool ANRendererlatformD2D::DrawTrinagle(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness)
{
	SetBrushColor(this->m_pColorBrush, Color);

	ID2D1PathGeometry* TriGeometry = nullptr;

	if (!CreateTrinagleGeometry(ANRendererlatformD2D::m_singleton.pFactory, D2D1::Point2F(pt1.x, pt1.y), D2D1::Point2F(pt2.x, pt2.y), D2D1::Point2F(pt3.x, pt3.y), &TriGeometry))
		return false;

	if (GuiWindow == 0)
	{
		this->m_pRenderTarget->DrawGeometry(TriGeometry, this->m_pColorBrush, LineThickness);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawGeometry(TriGeometry, this->m_pColorBrush, LineThickness);
	}

	TriGeometry->Release();

	return true;
}

bool ANRendererlatformD2D::DrawTrinagleFilled(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color)
{
	SetBrushColor(this->m_pColorBrush, Color);

	ID2D1PathGeometry* TriGeometry = nullptr;

	if (!CreateTrinagleGeometry(ANRendererlatformD2D::m_singleton.pFactory, D2D1::Point2F(pt1.x, pt1.y), D2D1::Point2F(pt2.x, pt2.y), D2D1::Point2F(pt3.x, pt3.y), &TriGeometry))
		return false;

	if (GuiWindow == 0)
	{
		this->m_pRenderTarget->FillGeometry(TriGeometry, this->m_pColorBrush);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->FillGeometry(TriGeometry, this->m_pColorBrush);
	}

	return true;
}

bool ANRendererlatformD2D::DrawCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness)
{
	SetBrushColor(this->m_pColorBrush, Color);

	Radius /= 2.f;

	if (GuiWindow == 0)
	{
		this->m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), this->m_pColorBrush, LineThickness);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), this->m_pColorBrush, LineThickness);
	}

	return true;
}

bool ANRendererlatformD2D::DrawFilledCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius)
{
	SetBrushColor(this->m_pColorBrush, Color);

	Radius /= 2.f;

	if (GuiWindow == 0)
	{
		this->m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), this->m_pColorBrush);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->FillEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), this->m_pColorBrush);
	}

	return true;
}

bool ANRendererlatformD2D::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID * pFontIDPtr)
{
	auto ret = false;

	if (_access(pszPath, 0) == -1)
		return ret;

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

	*pFontIDPtr = nullptr;

	if (!pFontLoader)
		goto failed;

	if (FAILED(ANRendererlatformD2D::m_singleton.pDWriteFactory->RegisterFontCollectionLoader(pFontLoader)))
		goto failed; 

	if (FAILED(ANRendererlatformD2D::m_singleton.pDWriteFactory->CreateCustomFontCollection(pFontLoader, pwszPath, sizeof(void*), &pFontCollection)))
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

	if (FAILED(ANRendererlatformD2D::m_singleton.pDWriteFactory->CreateTextFormat(pwszLocalName, pFontCollection, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, FontSize, L"", &pTextFormat)))
		goto failed;

	*pFontIDPtr = pTextFormat;

	ret = true;

failed:

	if (pwszLocalName)
		delete[] pwszLocalName;

	if (pwszPath)
		delete[] pwszPath;

	return ret;
}

void ANRendererlatformD2D::FreeFont(ANFontID * pFontIDPtr)
{
	if (!*pFontIDPtr)
		return;

	((IDWriteTextFormat*)(*pFontIDPtr))->Release();
	*pFontIDPtr = nullptr;
}

bool ANRendererlatformD2D::TextCalcSize(const char* pszText, ANFontID FontID, anVec2 * pTextSize)
{
	DWriteTextCache TextElement;

	if (!ANRendererlatformD2D::m_singleton.ProcessTextCache(pszText, FontID, &TextElement))
		return false;

	pTextSize->x = TextElement.m_dwrTextMetrics.widthIncludingTrailingWhitespace;
	pTextSize->y = TextElement.m_dwrTextMetrics.height;

	return true;
}

bool ANRendererlatformD2D::TextDraw(ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID, FontAppierence Appierence)
{
	DWriteTextCache TextElement;

	if (!ANRendererlatformD2D::m_singleton.ProcessTextCache(pszText, FontID, &TextElement))
		return false;

	SetBrushColor(this->m_pColorBrush, Color);

	//(wchar_t*)TextElement.m_pDWriteTextLayout + 0x20 = Text data

	if (GuiWindow == 0)
	{
		if (Appierence & FontAppierence::FONT_SHADOW)
		{
			this->m_pRenderTarget->DrawTextLayout(D2D1::Point2F(Pos.x + 1.f, Pos.y + 1.f), TextElement.m_pDWriteTextLayout, this->m_pColorBrushBlack);
			this->m_pRenderTarget->DrawTextLayout(D2D1::Point2F(Pos.x - 1.f, Pos.y - 1.f), TextElement.m_pDWriteTextLayout, this->m_pColorBrushBlack);
		}

		this->m_pRenderTarget->DrawTextLayout(D2D1::Point2F(Pos.x, Pos.y), TextElement.m_pDWriteTextLayout, this->m_pColorBrush);
	}
	else
	{
		if (Appierence & FontAppierence::FONT_SHADOW)
		{
			((ID2D1BitmapRenderTarget*)GuiWindow)->DrawTextLayout(D2D1::Point2F(Pos.x + 1.f, Pos.y + 1.f), TextElement.m_pDWriteTextLayout, this->m_pColorBrushBlack);
			((ID2D1BitmapRenderTarget*)GuiWindow)->DrawTextLayout(D2D1::Point2F(Pos.x - 1.f, Pos.y - 1.f), TextElement.m_pDWriteTextLayout, this->m_pColorBrushBlack);
		}

		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawTextLayout(D2D1::Point2F(Pos.x, Pos.y), TextElement.m_pDWriteTextLayout, this->m_pColorBrush);
	}

	return true;
}

bool ANRendererlatformD2D::CreateGuiWindow(ANInternalGuiWindowID * pGuiWindow, anVec2 Size)
{
	*pGuiWindow = nullptr;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = nullptr;

	if (FAILED(this->m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(Size.x, Size.y), &BitmapRenderTarget)))
		return false;

	*pGuiWindow = (ANInternalGuiWindowID*)BitmapRenderTarget;

	return true;
}

bool ANRendererlatformD2D::DeleteGuiWindow(ANInternalGuiWindowID * GuiWindow)
{
	if (!GuiWindow)
		return false;

	((ID2D1BitmapRenderTarget*)(*GuiWindow))->Release();
	*GuiWindow = nullptr;

	return true;
}

bool ANRendererlatformD2D::BeginGuiWindow(ANInternalGuiWindowID GuiWindow)
{
	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	BitmapRenderTarget->BeginDraw();
	BitmapRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	BitmapRenderTarget->Clear(D2D1::ColorF(1.f, 1.f, 1.f, 0.f));

	return true;
}

bool ANRendererlatformD2D::EndGuiWindow(ANInternalGuiWindowID GuiWindow)
{
	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	BitmapRenderTarget->EndDraw();

	return true;
}

bool ANRendererlatformD2D::GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2 * pWindowSize)
{
	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	auto Size = BitmapRenderTarget->GetSize();

	pWindowSize->x = Size.width;
	pWindowSize->y = Size.height;

	return true;
}

bool ANRendererlatformD2D::ResizeGuiWindow(ANInternalGuiWindowID * GuiWindow, anVec2 WindowSize)
{
	if (!*GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)(*GuiWindow);

	BitmapRenderTarget->Release();
	*GuiWindow = nullptr;
	this->m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(WindowSize.x, WindowSize.y), (ID2D1BitmapRenderTarget**)GuiWindow);

	return true;
}

bool ANRendererlatformD2D::DrawGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos)
{
	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	ID2D1Bitmap* Bitmap = nullptr;

	if (FAILED(BitmapRenderTarget->GetBitmap(&Bitmap)))
		return false;

	if (!Bitmap)
		return false;

	auto BitmapSize = BitmapRenderTarget->GetSize();

	this->m_pRenderTarget->DrawBitmap(Bitmap, D2D1::RectF(Pos.x, Pos.y, Pos.x + BitmapSize.width, Pos.y + BitmapSize.height), 1.f);

	Bitmap->Release();

	return true;
}
#endif // BACKEND_DIRECT2D