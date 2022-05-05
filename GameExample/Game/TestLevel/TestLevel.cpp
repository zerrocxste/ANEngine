#include "../../includes.h"

CTestLevel::CTestLevel()
{

	

}

CTestLevel::~CTestLevel()
{

}

void CTestLevel::OnLoadScene(IANApi* pApi)
{
	pApi->CreateImage("XMHf4PJ.jpg", &this->LevelBG);

	pApi->RegGuiWindow(&this->m_GuiWindow, anVec2(500.f));
}

void CTestLevel::OnUnloadScene(IANApi* pApi)
{
	pApi->FreeImage(&this->LevelBG);
}

//class ANWorld
//{
//public:
//	ANWorld(anVec2 WorldSize);
//	~ANWorld();
//
//	void Update(IANApi* pApi);
//	void SetCameraToEntity(anVec2 WorldEntPos);
//	void Draw(IANApi* pApi, ANImageID pImageID);
//
//private:
//	anVec2 m_WorldSize;
//	anVec2 m_WorldScreenPos;
//	anVec2 m_WorldScreenSize;
//	anVec2 m_CameraWorld;
//	anVec2 m_CameraScreen;
//};
//
//ANWorld::ANWorld(anVec2 WorldSize) :
//	m_WorldSize(WorldSize)
//{
//
//}
//
//ANWorld::~ANWorld()
//{
//
//}
//
//void ANWorld::Update(IANApi* pApi)
//{
//	auto ScreenSize = pApi->GetScreenSize();
//
//	this->m_WorldScreenSize = CalcSizeAtImageAspectRatio(ScreenSize, this->m_WorldSize);
//	this->m_WorldScreenPos = CalcPosToCenter(ScreenSize, this->m_WorldScreenSize);
//	CorrectSizeToOutRect(ScreenSize, this->m_WorldScreenPos, this->m_WorldScreenSize);
//	ApplyZoom(this->m_WorldScreenPos, this->m_WorldScreenSize, 700.f);
//	this->m_CameraScreen = CameraToScreen(this->m_WorldSize, this->m_WorldScreenPos, this->m_WorldScreenSize, this->m_CameraWorld);
//}
//
//void ANWorld::SetCameraToEntity(anVec2 WorldEntPos)
//{
//
//}
//
//void ANWorld::Draw(IANApi* pApi, ANImageID pImageID)
//{
//	pApi->DrawImage(pImageID, this->m_CameraScreen, this->m_WorldScreenSize, 1.f);
//}

double Interpolation(double t, double start, double end)
{
	return start + t * (end - start);
}

double LinearInterpolation(double t_start, double floating_t, double t_end, double start, double end)
{
	if (floating_t == t_start)
		return start;

	if (floating_t == t_end)
		return end;

	if (t_start == t_end)
		return start;

	auto t = (floating_t - t_start) / (t_end - t_start);

	return Interpolation(t, start, end);
}

anVec2 CalcDegDifferentBetweenParties(anVec2 SourceSize)
{
	return anVec2(
		LinearInterpolation(0.f, SourceSize.x, SourceSize.y, 0.f, 1.f), 
		LinearInterpolation(0.f, SourceSize.y, SourceSize.x, 0.f, 1.f)
	);
}

anVec2 CalcSizeAtImageAspectRatio(anVec2 OutRectSize, anVec2 SourceSize)
{
	anVec2 ret;

	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	if (OutRectSize.x < SourceSize.x)
	{
		auto DiffBetweenSrcSizeAndSizeOfContainedRect = SourceSize.x - OutRectSize.x;
		SourceSize.x = OutRectSize.x;
		SourceSize.y -= DiffBetweenSrcSizeAndSizeOfContainedRect * DegOfSidesDifferent.y;
	}

	if (OutRectSize.y < SourceSize.y)
	{
		auto DiffBetweenSrcSizeAndSizeOfContainedRect = SourceSize.y - OutRectSize.y;
		SourceSize.y = OutRectSize.y;
		SourceSize.x -= DiffBetweenSrcSizeAndSizeOfContainedRect * DegOfSidesDifferent.x;
	}

	ret = SourceSize;

	return ret;
}

anVec2 CalcPosToCenter(anVec2 OutRectSize, anVec2 SourceSize)
{
	return (OutRectSize * 0.5f) - (SourceSize * 0.5f);
}

void ZoomVerticalAligment(anVec2& SourcePos, anVec2& SourceSize, float Zoom)
{
	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	SourcePos.x -= Zoom;
	SourcePos.y -= Zoom * DegOfSidesDifferent.y;
	SourceSize.x += (Zoom * 2.f);
	SourceSize.y += (Zoom * 2.f) * DegOfSidesDifferent.y;
}

void ZoomHorizontalAligment(anVec2& SourcePos, anVec2& SourceSize, float Zoom)
{
	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	SourcePos.x -= Zoom * DegOfSidesDifferent.x;
	SourcePos.y -= Zoom;
	SourceSize.x += (Zoom * 2.f) * DegOfSidesDifferent.x;
	SourceSize.y += (Zoom * 2.f);
}

anVec2 CorrectSizeToOutRect(anVec2 OutRectSize, anVec2& SourcePos, anVec2& SourceSize)
{
	anVec2 ret;

	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	if (SourceSize.x < OutRectSize.x)
	{
		auto FreeSegments = (OutRectSize.x - SourceSize.x) * 0.5f;
		ZoomVerticalAligment(SourcePos, SourceSize, FreeSegments);
	}

	if (SourceSize.y < OutRectSize.y)
	{
		auto FreeSegments = (OutRectSize.y - SourceSize.y) * 0.5f;
		ZoomHorizontalAligment(SourcePos, SourceSize, FreeSegments);
	}

	return ret;
}

anVec2 PointToScreen(anVec2 WorldSize, anRect ScreenWorldRect, anVec2 PointPos)
{
	return anVec2(
		LinearInterpolation(0.f, PointPos.x, WorldSize.x, ScreenWorldRect.first.x, ScreenWorldRect.second.x),
		LinearInterpolation(0.f, PointPos.y, WorldSize.y, ScreenWorldRect.first.y, ScreenWorldRect.second.y)
	);
}

anVec2 CameraToScreen(anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2 PointWorld)
{
	return PointToScreen(WorldSize, anRect(WorldScreenPos, WorldScreenPos + WorldScreenSize), anVec2(-PointWorld.x, -PointWorld.y)) + (WorldScreenSize * 0.5f);
}

anVec2 WorldToScreen(anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2 CameraWorld, anVec2 PointWorld)
{
	return PointToScreen(WorldSize, anRect(WorldScreenPos, WorldScreenPos + WorldScreenSize), PointWorld - CameraWorld) + (WorldScreenSize * 0.5f);
}

void ApplyZoom(anVec2& From, anVec2& To, float Zoom)
{
	ZoomVerticalAligment(From, To, Zoom);
}

float Step = 0.3f;

void ClampCamera(anVec2 ScreenSize, anVec2 WorldScreenSize, anVec2 CameraScreen, anVec2& CameraWorld)
{
	if (CameraScreen.x > 0.f)
		printf("INTERSECTED 1\n", CameraWorld.x);
	if (CameraScreen.y > 0.f)
		printf("INTERSECTED 2\n");
	if (CameraScreen.x - ScreenSize.x < -WorldScreenSize.x)
		printf("INTERSECTED 3\n");
	if (CameraScreen.y - ScreenSize.y < -WorldScreenSize.y)
		printf("INTERSECTED 4\n");
}

void CTestLevel::Entry(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	auto WorldSize = pApi->GetImageSize(this->LevelBG);

	auto WorldScreenSize = CalcSizeAtImageAspectRatio(ScreenSize, WorldSize);
	auto WorldScreenPos = CalcPosToCenter(ScreenSize, WorldScreenSize);

	CorrectSizeToOutRect(ScreenSize, WorldScreenPos, WorldScreenSize);

	static anVec2 CameraWorld = anVec2(WorldSize * 0.5f);

	if (GetAsyncKeyState(VK_RBUTTON))
		ApplyZoom(WorldScreenPos, WorldScreenSize, 700.f);

	static anVec2 ActorWorld;

	if (GetAsyncKeyState('W'))
		CameraWorld.y -= Step;
	if (GetAsyncKeyState('S'))
		CameraWorld.y += Step;
	if (GetAsyncKeyState('A'))
		CameraWorld.x -= Step;
	if (GetAsyncKeyState('D'))
		CameraWorld.x += Step;

	if (GetAsyncKeyState(VK_UP))
		ActorWorld.y -= Step;
	if (GetAsyncKeyState(VK_DOWN))
		ActorWorld.y += Step;
	if (GetAsyncKeyState(VK_LEFT))
		ActorWorld.x -= Step;
	if (GetAsyncKeyState(VK_RIGHT))
		ActorWorld.x += Step;

	if (GetAsyncKeyState('V'))
		CameraWorld = ActorWorld;

	auto CameraScreen = CameraToScreen(WorldSize, WorldScreenPos, WorldScreenSize, CameraWorld);

	auto ActorScreen = WorldToScreen(WorldSize, WorldScreenPos, WorldScreenSize, CameraWorld, ActorWorld);

	pApi->DrawImage(this->LevelBG, CameraScreen, WorldScreenSize, 1.f);

	pApi->DrawRectangle(ActorScreen, anVec2(50.f, 50.f), anColor::Red(), 50.f, 1.f, true);

	char buff[512] = { 0 };
	sprintf_s(buff, "FPS: %d\nFrametime: %lf\nScreen size: %.1f:%.1f\nWorld Size: %.1f:%.1f\nWorld screen size: %.1f:%.1f\nCamera world: %.1f:%.1f\nCamera screen: %.1f:%.1f\nActor world: %.1f:%.1f\nActor screen: %.1f:%.1f",
		pApi->FPS, 
		pApi->Frametime, 
		ScreenSize.x, ScreenSize.y, 
		WorldSize.x, WorldSize.y,
		WorldScreenSize.x, WorldScreenSize.y,
		CameraWorld.x, CameraWorld.y,
		CameraScreen.x, CameraScreen.y,
		ActorWorld.x, ActorWorld.y,
		ActorScreen.x, ActorScreen.y);

	pApi->TextDraw(buff, anVec2(10.f, 20.f), anColor::White());

	if (pApi->AddButton("Go to menu", anVec2(ScreenSize.x - 130.f - 5.f, ScreenSize.y - 50.f - 5.f), anVec2(130.f, 50.f)))
		pApi->ConnectToScene(new CTestGameScene());

	pApi->DrawLine(anVec2(ScreenSize.x * 0.5f, 0.f), anVec2(ScreenSize.x * 0.5f, ScreenSize.y), anColor::White(), 5.f);
	pApi->DrawLine(anVec2(0.f, ScreenSize.y * 0.5f), anVec2(ScreenSize.x, ScreenSize.y * 0.5f), anColor::White(), 5.f);

	ClampCamera(ScreenSize, WorldScreenSize, CameraScreen, CameraWorld);
}
