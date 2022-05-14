#include "includes.h"

constexpr auto MODULE_DESC = "AlterNative engine (ANEngine) D2D Renderer module. Timestamp: " __DATE__;

struct D2DInterfaces
{
	ID2D1Factory* m_pFactory;
	IWICImagingFactory* m_pWICFactory;
	IDWriteFactory* pDWriteFactory;
};

struct D2DWindowContextRenderInformation
{
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pColorBrush;
};

D2DInterfaces g_D2DInterfaces;
std::map<HWND, D2DWindowContextRenderInformation> g_mD2DWindowContextRenderInformation;
ANRendererFuncionsTable g_ANRendererFuncionsTable;

CRITICAL_SECTION g_csInitializeRenderer;

bool g_EnabledVerticalSync = false;

extern "C" __declspec(dllexport) bool __stdcall BeginFrame(HWND hWnd);
extern "C" __declspec(dllexport) bool __stdcall EndFrame(HWND hWnd);
extern "C" __declspec(dllexport) bool __stdcall ClearScene(HWND hWnd);
extern "C" __declspec(dllexport) bool __stdcall ResetScene(HWND hWnd, anVec2 ScreenSize);
extern "C" __declspec(dllexport) bool __stdcall GetScreenSize(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 * pAnvec2Out);
extern "C" __declspec(dllexport) bool __stdcall CreateImageFromMemory(HWND hWnd, void* pImageSrc, std::uint32_t iImageSize, ANImageID * pImageIDPtr);
extern "C" __declspec(dllexport) bool __stdcall GetImageSize(ANImageID ImageID, anVec2 * pSize);
extern "C" __declspec(dllexport) void __stdcall FreeImage(ANImageID* pImageIDPtr);
extern "C" __declspec(dllexport) bool __stdcall DrawImage(HWND hWnd, ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity);
extern "C" __declspec(dllexport) bool __stdcall DrawLine(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness);
extern "C" __declspec(dllexport) bool __stdcall DrawRectangle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding);
extern "C" __declspec(dllexport) bool __stdcall DrawFilledRectangle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding);
extern "C" __declspec(dllexport) bool __stdcall DrawCircle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness);
extern "C" __declspec(dllexport) bool __stdcall DrawTrinagle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness);
extern "C" __declspec(dllexport) bool __stdcall DrawTrinagleFilled(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color);
extern "C" __declspec(dllexport) bool __stdcall DrawFilledCircle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius);
extern "C" __declspec(dllexport) bool __stdcall CreateFontFromFile(const char* pszPath, float FontSize, ANFontID * pFontIDPtr);
extern "C" __declspec(dllexport) void __stdcall FreeFont(ANFontID* pFontIDPtr);
extern "C" __declspec(dllexport) bool __stdcall TextCalcSize(HWND hWnd, const char* pszText, ANFontID FontID, anVec2 * pTextSize);
extern "C" __declspec(dllexport) bool __stdcall TextDraw(HWND hWnd, ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID);
extern "C" __declspec(dllexport) bool __stdcall CreateGuiWindow(HWND hWnd, ANInternalGuiWindowID * pGuiWindow, anVec2 Size);
extern "C" __declspec(dllexport) bool __stdcall DeleteGuiWindow(ANInternalGuiWindowID * GuiWindow);
extern "C" __declspec(dllexport) bool __stdcall BeginGuiWindow(ANInternalGuiWindowID GuiWindow);
extern "C" __declspec(dllexport) bool __stdcall EndGuiWindow(ANInternalGuiWindowID GuiWindow);
extern "C" __declspec(dllexport) bool __stdcall GetGuiWindowSize(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 * pWindowSize);
extern "C" __declspec(dllexport) bool __stdcall ResizeGuiWindow(HWND hWnd, ANInternalGuiWindowID * GuiWindow, anVec2 WindowSize);
extern "C" __declspec(dllexport) bool __stdcall DrawGuiWindow(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos);

D2DWindowContextRenderInformation& GetWindowContextRenderInformation(HWND hWnd)
{
	return g_mD2DWindowContextRenderInformation[hWnd];
}

bool CreateD2D1Factory()
{
	if (g_D2DInterfaces.m_pFactory != nullptr)
		return true;

	return SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED, &g_D2DInterfaces.m_pFactory));
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
	if (!g_D2DInterfaces.m_pFactory)
		return false;

	auto& ri = GetWindowContextRenderInformation(hWnd);

	D2D1_PIXEL_FORMAT pixelFormat{};
	pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	pixelFormat.alphaMode = D2D1_ALPHA_MODE_UNKNOWN;

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties{};
	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	renderTargetProperties.pixelFormat = pixelFormat;
	renderTargetProperties.dpiX = 0.0;
	renderTargetProperties.dpiY = 0.0;
	renderTargetProperties.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	renderTargetProperties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	printf("%d\n", g_EnabledVerticalSync);

	D2D1_HWND_RENDER_TARGET_PROPERTIES hwndRenderTargetProperties{};
	hwndRenderTargetProperties.hwnd = hWnd;
	hwndRenderTargetProperties.pixelSize = D2D1::Size(static_cast<UINT32>(0), static_cast<UINT32>(0));
	hwndRenderTargetProperties.presentOptions = g_EnabledVerticalSync ? D2D1_PRESENT_OPTIONS_RETAIN_CONTENTS : D2D1_PRESENT_OPTIONS_IMMEDIATELY; //VERTYCAL SYNC

	return SUCCEEDED(g_D2DInterfaces.m_pFactory->CreateHwndRenderTarget(renderTargetProperties, hwndRenderTargetProperties, &ri.m_pRenderTarget));
}

bool CreateGlobalBrush(HWND hWnd)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	return SUCCEEDED(ri.m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &ri.m_pColorBrush));
}

bool CreateRendererFunctionsTable()
{
	g_ANRendererFuncionsTable.BeginFrame = BeginFrame;
	g_ANRendererFuncionsTable.EndFrame = EndFrame;
	g_ANRendererFuncionsTable.ClearScene = ClearScene;
	g_ANRendererFuncionsTable.ResetScene = ResetScene;
	g_ANRendererFuncionsTable.GetScreenSize = GetScreenSize;
	g_ANRendererFuncionsTable.CreateImageFromMemory = CreateImageFromMemory;
	g_ANRendererFuncionsTable.FreeImage = FreeImage;
	g_ANRendererFuncionsTable.GetImageSize = GetImageSize;
	g_ANRendererFuncionsTable.DrawImage = DrawImage;
	g_ANRendererFuncionsTable.DrawRectangle = DrawRectangle;
	g_ANRendererFuncionsTable.DrawLine = DrawLine;
	g_ANRendererFuncionsTable.DrawFilledRectangle = DrawFilledRectangle;
	g_ANRendererFuncionsTable.DrawTrinagle = DrawTrinagle;
	g_ANRendererFuncionsTable.DrawTrinagleFilled = DrawTrinagleFilled;
	g_ANRendererFuncionsTable.DrawCircle = DrawCircle;
	g_ANRendererFuncionsTable.DrawFilledCircle = DrawFilledCircle;
	g_ANRendererFuncionsTable.CreateFontFromFile = CreateFontFromFile;
	g_ANRendererFuncionsTable.FreeFont = FreeFont;
	g_ANRendererFuncionsTable.TextCalcSize = TextCalcSize;
	g_ANRendererFuncionsTable.TextDraw = TextDraw;
	g_ANRendererFuncionsTable.CreateGuiWindow = CreateGuiWindow;
	g_ANRendererFuncionsTable.DeleteGuiWindow = DeleteGuiWindow;
	g_ANRendererFuncionsTable.BeginGuiWindow = BeginGuiWindow;
	g_ANRendererFuncionsTable.EndGuiWindow = EndGuiWindow;
	g_ANRendererFuncionsTable.GetGuiWindowSize = GetGuiWindowSize;
	g_ANRendererFuncionsTable.ResizeGuiWindow = ResizeGuiWindow;
	g_ANRendererFuncionsTable.DrawGuiWindow = DrawGuiWindow;

	return true;
}

void __forceinline SetBrushColor(ID2D1SolidColorBrush* m_pColorBrush, HWND hWnd, anColor Color)
{
	m_pColorBrush->SetColor(D2D1::ColorF(Color.r / 255.f, Color.g / 255.f, Color.b / 255.f, Color.a / 255.f));
}

bool Initialize(HWND hWnd)
{
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

extern "C" __declspec(dllexport) bool __stdcall InitializeRenderer(HINSTANCE hInstance, HWND hWnd, void* pReversed)
{
	CoInitialize(nullptr);

	EnterCriticalSection(&g_csInitializeRenderer);

	g_EnabledVerticalSync = pReversed;

	auto ret = Initialize(hWnd);

	LeaveCriticalSection(&g_csInitializeRenderer);

	return ret;
}

extern "C" __declspec(dllexport) void* __stdcall GetRendererFunctionsTable()
{
	return &g_ANRendererFuncionsTable;
}

extern "C" __declspec(dllexport) bool __stdcall BeginFrame(HWND hWnd)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	ri.m_pRenderTarget->BeginDraw();
	ri.m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall EndFrame(HWND hWnd)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	ri.m_pRenderTarget->EndDraw();

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall ClearScene(HWND hWnd)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	ri.m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall ResetScene(HWND hWnd, anVec2 ScreenSize)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	ri.m_pRenderTarget->Resize(D2D1::SizeU((int)ScreenSize.x, (int)ScreenSize.y));

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall GetScreenSize(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 * pAnvec2Out)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!pAnvec2Out || !ri.m_pRenderTarget)
		return false;

	D2D1_SIZE_F ScreenSize;
		
	if (GuiWindow == 0)
	{
		ScreenSize = ri.m_pRenderTarget->GetSize();
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->GetSize();
	}

	pAnvec2Out->x = ScreenSize.width;
	pAnvec2Out->y = ScreenSize.height;

	return true;
}

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

extern "C" __declspec(dllexport) bool __stdcall CreateImageFromMemory(HWND hWnd, void* pImageSrc, std::uint32_t iImageSize, ANImageID * pImageIDPtr)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	ID2D1Bitmap* pD2D1Bitmap = nullptr;

	if (!CreateBitmapFromMemory(ri.m_pRenderTarget, g_D2DInterfaces.m_pWICFactory, pImageSrc, iImageSize, &pD2D1Bitmap))
		return false;

	*pImageIDPtr = (ANImageID)pD2D1Bitmap;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall GetImageSize(ANImageID ImageID, anVec2* pSize)
{
	if (!ImageID)
		return false;

	auto Size = ((ID2D1Bitmap*)(ImageID))->GetSize();

	pSize->x = Size.width;
	pSize->y = Size.height;

	return true;
}

extern "C" __declspec(dllexport) void __stdcall FreeImage(ANImageID * pImageIDPtr)
{
	if (!*pImageIDPtr)
		return;

	((ID2D1Bitmap*)(*pImageIDPtr))->Release();
	*pImageIDPtr = nullptr;
}

extern "C" __declspec(dllexport) bool __stdcall DrawImage(HWND hWnd, ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity)
{
	if (!pImageID)
		return false;

	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	if (GuiWindow == 0)
	{
		ri.m_pRenderTarget->DrawBitmap((ID2D1Bitmap*)pImageID, D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y), Opacity);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawBitmap((ID2D1Bitmap*)pImageID, D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y), Opacity);
	}

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawLine(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	if (GuiWindow == 0)
	{
		ri.m_pRenderTarget->DrawLine(D2D1::Point2F(From.x, From.y), D2D1::Point2F(To.x, To.y), ri.m_pColorBrush, LineThickness);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawLine(D2D1::Point2F(From.x, From.y), D2D1::Point2F(To.x, To.y), ri.m_pColorBrush, LineThickness);
	}

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawRectangle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	auto Rect = D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y);

	if (GuiWindow == 0)
	{
		if (Rounding > 0.f)
			ri.m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), ri.m_pColorBrush, LineThickness);
		else
			ri.m_pRenderTarget->DrawRectangle(Rect, ri.m_pColorBrush, LineThickness);
	}
	else
	{
		ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

		if (Rounding > 0.f)
			BitmapRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), ri.m_pColorBrush, LineThickness);
		else
			BitmapRenderTarget->DrawRectangle(Rect, ri.m_pColorBrush, LineThickness);
	}

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawFilledRectangle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	auto Rect = D2D1::RectF(Pos.first.x, Pos.first.y, Pos.second.x, Pos.second.y);

	if (GuiWindow == 0)
	{
		if (Rounding > 0.f)
			ri.m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), ri.m_pColorBrush);
		else
			ri.m_pRenderTarget->FillRectangle(Rect, ri.m_pColorBrush);
	}
	else
	{
		ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

		if (Rounding > 0.f)
			BitmapRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(Rect, Rounding, Rounding), ri.m_pColorBrush);
		else
			BitmapRenderTarget->FillRectangle(Rect, ri.m_pColorBrush);
	}

	return true;
}

std::map<void*, ID2D1PathGeometry*>;

bool CreateTrinagleGeometry(ID2D1Factory* pD2D1Factory, D2D1_POINT_2F pt1, D2D1_POINT_2F pt2, D2D1_POINT_2F pt3, ID2D1PathGeometry** pD2D1PathGeometry)
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

extern "C" __declspec(dllexport) bool __stdcall DrawTrinagle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	ID2D1PathGeometry* TriGeometry = nullptr;

	if (!CreateTrinagleGeometry(g_D2DInterfaces.m_pFactory, D2D1::Point2F(pt1.x, pt1.y), D2D1::Point2F(pt2.x, pt2.y), D2D1::Point2F(pt3.x, pt3.y), &TriGeometry))
		return false;

	if (GuiWindow == 0)
	{
		ri.m_pRenderTarget->DrawGeometry(TriGeometry, ri.m_pColorBrush, LineThickness);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawGeometry(TriGeometry, ri.m_pColorBrush, LineThickness);
	}

	TriGeometry->Release();

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawTrinagleFilled(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	ID2D1PathGeometry* TriGeometry = nullptr;

	if (!CreateTrinagleGeometry(g_D2DInterfaces.m_pFactory, D2D1::Point2F(pt1.x, pt1.y), D2D1::Point2F(pt2.x, pt2.y), D2D1::Point2F(pt3.x, pt3.y), &TriGeometry))
		return false;

	if (GuiWindow == 0)
	{
		ri.m_pRenderTarget->FillGeometry(TriGeometry, ri.m_pColorBrush);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->FillGeometry(TriGeometry, ri.m_pColorBrush);
	}

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawCircle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	Radius /= 2.f;

	if (GuiWindow == 0)
	{
		ri.m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), ri.m_pColorBrush, LineThickness);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), ri.m_pColorBrush, LineThickness);
	}

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawFilledCircle(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	Radius /= 2.f;

	if (GuiWindow == 0)
	{
		ri.m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), ri.m_pColorBrush);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->FillEllipse(D2D1::Ellipse(D2D1::Point2F(Pos.x + Radius, Pos.y + Radius), Radius, Radius), ri.m_pColorBrush);
	}

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

extern "C" __declspec(dllexport) bool __stdcall CreateFontFromFile(const char* pszPath, float FontSize, ANFontID * pFontIDPtr)
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

	*pFontIDPtr = pTextFormat;

	ret = true;

failed:

	if (pwszLocalName)
		delete[] pwszLocalName;

	if (pwszPath)
		delete[] pwszPath;

	return ret;
}

extern "C" __declspec(dllexport) void __stdcall FreeFont(ANFontID* pFontIDPtr)
{
	if (!*pFontIDPtr)
		return;

	((IDWriteTextFormat*)(*pFontIDPtr))->Release();
	*pFontIDPtr = nullptr;
}

typedef void* TextCacheID;

struct DWriteTextCache
{
	const char* m_szText;
	wchar_t* m_wszText;
	int m_iTextLength;
	int m_iTotalSumOfSymStr;
	IDWriteTextFormat* m_pDWriteTextFormat;
	IDWriteTextLayout* m_pDWriteTextLayout;
	DWRITE_TEXT_METRICS m_dwrTextMetrics;
};

std::map<TextCacheID, DWriteTextCache> g_DWriteTextCache;

bool ProcessTextCache(const char* pszText, ANFontID FontID, DWriteTextCache* pCachedTextElement)
{
	IDWriteTextFormat* pDWriteTextFormat = (IDWriteTextFormat*)FontID;

	auto& e = g_DWriteTextCache[(void*)(pszText + (std::uintptr_t)FontID)];

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

		if (FAILED(g_D2DInterfaces.pDWriteFactory->CreateTextLayout(e.m_wszText, StrLengthText, e.m_pDWriteTextFormat, FLT_MAX, FLT_MAX, &e.m_pDWriteTextLayout)))
			return false;

		if (FAILED(e.m_pDWriteTextLayout->GetMetrics(&e.m_dwrTextMetrics)))
			return false;
	}

	*pCachedTextElement = e;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall TextCalcSize(HWND hWnd, const char* pszText, ANFontID FontID, anVec2 * pTextSize)
{
	DWriteTextCache TextElement;

	if (!ProcessTextCache(pszText, FontID, &TextElement))
		return false;

	pTextSize->x = TextElement.m_dwrTextMetrics.widthIncludingTrailingWhitespace;
	pTextSize->y = TextElement.m_dwrTextMetrics.height;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall TextDraw(HWND hWnd, ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID)
{
	DWriteTextCache TextElement;

	if (!ProcessTextCache(pszText, FontID, &TextElement))
		return false;

	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	SetBrushColor(ri.m_pColorBrush, hWnd, Color);

	if (GuiWindow == 0)
	{	
		ri.m_pRenderTarget->DrawTextLayout(D2D1::Point2F(Pos.x, Pos.y), TextElement.m_pDWriteTextLayout, ri.m_pColorBrush);
	}
	else
	{
		((ID2D1BitmapRenderTarget*)GuiWindow)->DrawTextLayout(D2D1::Point2F(Pos.x, Pos.y), TextElement.m_pDWriteTextLayout, ri.m_pColorBrush);
	}

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall CreateGuiWindow(HWND hWnd, ANInternalGuiWindowID * pGuiWindow, anVec2 Size)
{
	*pGuiWindow = nullptr;

	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = nullptr;

	if (FAILED(ri.m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(Size.x, Size.y), &BitmapRenderTarget)))
		return false;

	*pGuiWindow = (ANInternalGuiWindowID*)BitmapRenderTarget;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DeleteGuiWindow(ANInternalGuiWindowID * GuiWindow)
{
	if (!GuiWindow)
		return false;

	((ID2D1BitmapRenderTarget*)(*GuiWindow))->Release();
	*GuiWindow = nullptr;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall BeginGuiWindow(ANInternalGuiWindowID GuiWindow)
{
	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	BitmapRenderTarget->BeginDraw();
	BitmapRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	BitmapRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall EndGuiWindow(ANInternalGuiWindowID GuiWindow)
{
	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;
	
	BitmapRenderTarget->EndDraw();

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall GetGuiWindowSize(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2* pWindowSize)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	auto Size = BitmapRenderTarget->GetSize();

	pWindowSize->x = Size.width;
	pWindowSize->y = Size.height;

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall ResizeGuiWindow(HWND hWnd, ANInternalGuiWindowID * GuiWindow, anVec2 WindowSize)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	if (!*GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)(*GuiWindow);

	BitmapRenderTarget->Release();
	*GuiWindow = nullptr;
	ri.m_pRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(WindowSize.x, WindowSize.y), (ID2D1BitmapRenderTarget**)GuiWindow);

	return true;
}

extern "C" __declspec(dllexport) bool __stdcall DrawGuiWindow(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos)
{
	auto& ri = GetWindowContextRenderInformation(hWnd);

	if (!ri.m_pRenderTarget)
		return false;

	if (!GuiWindow)
		return false;

	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)GuiWindow;

	ID2D1Bitmap* Bitmap = nullptr;

	if (FAILED(BitmapRenderTarget->GetBitmap(&Bitmap)))
		return false;	

	if (!Bitmap)
		return false;

	auto BitmapSize = BitmapRenderTarget->GetSize();

	ri.m_pRenderTarget->DrawBitmap(Bitmap, D2D1::RectF(Pos.x, Pos.y, Pos.x + BitmapSize.width, Pos.y + BitmapSize.height), 1.f);

	Bitmap->Release();

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
		InitializeCriticalSection(&g_csInitializeRenderer);
		memset(&g_D2DInterfaces, 0, sizeof(decltype(g_D2DInterfaces)));
		printf("%s() -> %s\n", __FUNCTION__, MODULE_DESC);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		DeleteCriticalSection(&g_csInitializeRenderer);
		break;
	}
	return TRUE;
}