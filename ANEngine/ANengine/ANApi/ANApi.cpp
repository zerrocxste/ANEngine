#include "../ANEngine.h"

ANApi::ANApi(ANCore* pCore) : 
	m_pCore(pCore)
{
	this->FPS = 0;
	this->Frametime = 0.;
}

ANApi::~ANApi()
{

}

const char* ANApi::GetVersion()
{
	return this->m_pCore->GetVersion();
}

void ANApi::LeaveApp()
{
	this->m_pCore->GetGame()->LeaveGame();
}

bool ANApi::ConnectToScene(IANGameScene* pGameScene)
{
	return this->m_pCore->GetGame()->ConnectScene(pGameScene);
}

bool ANApi::GetCursorKeyIsDowned(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->IsCursorKeyDowned(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

bool ANApi::GetCursorKeyIsClicked(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->IsCursorKeyClicked(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

bool ANApi::GetCursorKeyIsReleased(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->IsCursorKeyReleased(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

float ANApi::GetCursorKeyDownTime(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->GetCursorKeyDownTime(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

anVec2 ANApi::GetCursorPos()
{
	return this->m_pCore->GetInput()->GetCursorPos();
}

bool ANApi::GetKeyIsDowned(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->IsKeyDowned(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

bool ANApi::GetKeyIsClicked(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->IsKeyClicked(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

bool ANApi::GetKeyIsReleased(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->IsKeyReleased(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

float ANApi::GetKeyDownTime(int k)
{
	auto Input = this->m_pCore->GetInput();

	auto ret = Input->GetKeyDownTime(k);

	if (!ret)
		this->SetError(Input->What());

	return ret;
}

anVec2 ANApi::GetScreenSize()
{
	return this->m_pCore->GetRenderer()->GetScreenSize();
}

bool ANApi::CreateImage(const char* pszPath, ANImageID* pImageID, bool bLinkToDataList)
{
	auto ResourceData = this->m_pCore->GetGame()->GetGameResourcesData();

	auto ret = ResourceData->CreateImage(pszPath, pImageID, bLinkToDataList);

	if (!ret)
		this->SetError(ResourceData->What());

	return ret;
}

anVec2 ANApi::GetImageSize(ANImageID ImageID)
{
	anVec2 Size;
	this->m_pCore->GetRenderer()->GetImageSize(ImageID, &Size);
	return Size;
}

void ANApi::FreeImage(ANImageID* pImageID)
{
	this->m_pCore->GetGame()->GetGameResourcesData()->DeleteImage(pImageID);
}

bool ANApi::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pCore->GetRenderer()->DrawImage(pImageID, Pos, Size, Opacity);
}

bool ANApi::DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	return this->m_pCore->GetRenderer()->DrawLine(From, To, Color, LineThickness);
}

bool ANApi::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness, float Rounding, bool Filled)
{
	auto r = this->m_pCore->GetRenderer();

	return Filled ? r->DrawFilledRectangle(Pos, Size, Color, Rounding) : r->DrawRectangle(Pos, Size, Color, LineThickness, Rounding);
}

bool ANApi::DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness, bool Filled)
{
	return Filled ? this->m_pCore->GetRenderer()->DrawFilledTrinagle(pt1, pt2, pt3, Color) : this->m_pCore->GetRenderer()->DrawTrinagle(pt1, pt2, pt3, Color, LineThickness);
}

bool ANApi::DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness, bool Filled)
{
	auto r = this->m_pCore->GetRenderer();

	return Filled ? r->DrawFilledCircle(Pos, Color, Radius) : r->DrawCircle(Pos, Color, Radius, LineThickness);
}

bool ANApi::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID)
{
	return this->m_pCore->GetRenderer()->CreateFontFromFile(pszPath, FontSize, pFontID);
}

void ANApi::FreeFont(ANFontID* pFontIDPtr)
{
	this->m_pCore->GetRenderer()->FreeFont(pFontIDPtr);
}

void ANApi::PushFont(ANFontID FontID)
{
	this->m_pCore->GetRenderer()->PushFont(FontID);
}

void ANApi::PopFont()
{
	this->m_pCore->GetRenderer()->PopFont();
}

void ANApi::PushFontColor(anColor Color)
{
	this->m_pCore->GetGui()->SetFontColor(Color);
}

void ANApi::PopFontColor()
{
	this->m_pCore->GetGui()->SetFontColor(anColor::Black());
}

void ANApi::PushFontAppierence(FontAppierence Appierence)
{
	this->m_pCore->GetRenderer()->PushFontAppierence(Appierence);
}

void ANApi::PopFontAppierence()
{
	this->m_pCore->GetRenderer()->PopFontAppierence();
}

bool ANApi::TextDraw(const char* pszText, anVec2 Pos, anColor Color)
{
	auto Renderer = this->m_pCore->GetRenderer();

	auto ret = Renderer->TextDraw(pszText, Pos, Color);

	if (!ret)
		this->SetError(Renderer->What());

	return ret;
}

anVec2 ANApi::TextCalcSize(const char* pszText)
{
	auto Renderer = this->m_pCore->GetRenderer();

	anVec2 Size;

	if (!Renderer->TextCalcSize(pszText, &Size))
	{
		this->SetError(Renderer->What());
		return anVec2();
	}

	return Size;
}

ANPerfomanceTick ANApi::GetTickMicroseconds()
{
	return this->m_pCore->GetPerfomance()->GetTick();
}

ANPerfomanceTick ANApi::GetPrevFrameTickMicroseconds()
{
	return this->m_pCore->GetPerfomance()->GetPrevFrameTick();
}

void ANApi::RegWorld(IANWorld** ppWorld)
{
	this->m_pCore->GetGame()->RegWorld(ppWorld);
}

void ANApi::UnregWorld(IANWorld** ppWorld)
{
	this->m_pCore->GetGame()->UnregWorld(ppWorld);
}

anVec2 ANApi::ScreenPointToWorld(IANWorld* pWorld, anVec2 ScreenPoint)
{
	auto WorldMetrics = pWorld->GetMetrics();

	return ANMathUtils::ScreenPointToWorld(WorldMetrics.m_CameraScreen, WorldMetrics.m_WorldScreenSize, WorldMetrics.m_WorldSize, ScreenPoint);
}

void ANApi::RegEntity(IANEntity** ppEntity, const char* pszEntityClassID)
{
	this->m_pCore->GetGame()->RegEntity(ppEntity, pszEntityClassID);
}

void ANApi::UnregEntity(IANEntity** ppEntity)
{
	this->m_pCore->GetGame()->UnregEntity(ppEntity);
}

void ANApi::UnregAndDeleteAllEntity()
{
	this->m_pCore->GetGame()->GetEntityList()->UnregAll()->Clear();
}

ANInterfacePointer<IANEntityGroup> ANApi::FindEntityByGroupID(const char* pszGroupID)
{
	auto pEntityGroup = ANImpPtr<ANEntityGroup>();
	this->m_pCore->GetGame()->GetEntityList()->FindFromClassID(pszGroupID, &pEntityGroup->m_EntityGroup);
	return pEntityGroup;
}

IANEntity* ANApi::GetEntityByName(const char* pszEntName)
{
	return this->m_pCore->GetGame()->GetEntityList()->FindFromName(pszEntName);
}

IANInteractionMessagesList* ANApi::GetInteractionMessagesList()
{
	return this->m_pCore->GetGame()->GetInteractionList();
}

void ANApi::AddDefaultAnimationComposition(IANEntity* pEntity, ANAnimationComposition AnimationComposition, float flAnimationDuration)
{
	this->m_pCore->GetGame()->AddDefaultAnimationComposition(pEntity, AnimationComposition, flAnimationDuration);
}

void ANApi::DeleteDefaultAnimationComposition(IANEntity* pEntity)
{
	this->m_pCore->GetGame()->DeleteDefaultAnimationComposition(pEntity);
}

void ANApi::ClearDefaultAnimationComposition()
{
	this->m_pCore->GetGame()->ClearDefaultAnimationComposition();
}

bool ANApi::CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition, bool bLinkToDataList)
{
	auto ResourceData = this->m_pCore->GetGame()->GetGameResourcesData();

	auto ret = ResourceData->CreateAnimationComposition(pszAnimationLabelsArr, iAnimationLabelsArrSize, pAnimationComposition, bLinkToDataList);

	if (!ret)
		this->SetError(ResourceData->What());

	return ret;
}

void ANApi::InsertAnimationFrameTo(ANAnimationComposition AnimationCompositionSource, int iAnimationFrameIdxSource, ANAnimationComposition* pAnimationCompositionDest, int iAnimationFrameDest)
{
	this->m_pCore->GetGame()->GetGameResourcesData()->InsertAnimationFrameTo(AnimationCompositionSource, iAnimationFrameIdxSource, pAnimationCompositionDest, iAnimationFrameDest);
}

void ANApi::DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition)
{
	this->m_pCore->GetGame()->GetGameResourcesData()->DeleteAnimationComposition(pAnimationComposition);
}

anFramesLength ANApi::GetAnimationCompositionSize(ANAnimationComposition AnimationComposition)
{
	return *(anFramesLength*)AnimationComposition;
}

ANImageID ANApi::GetAnimationCompositionFrameFromID(ANAnimationComposition AnimationComposition, int ID)
{
	return ((ANAnimationComposition)((std::uintptr_t)AnimationComposition + sizeof(anFramesLength)))[ID].m_Frame;
}

void ANApi::ClearAndDeleteLinkedImages()
{
	this->m_pCore->GetGame()->GetGameResourcesData()->ClearImageData();
}

void ANApi::ClearAndDeleteLinkedAnimationCompositions()
{
	this->m_pCore->GetGame()->GetGameResourcesData()->ClearAnimationCompositionData();
}

bool ANApi::RegGuiWindow(ANGuiWindowID* pGuiWindowID, anVec2 Size)
{
	return this->m_pCore->GetGui()->WindowCreate(pGuiWindowID, Size);
}

bool ANApi::UnregGuiWindow(ANGuiWindowID* pGuiWindowID)
{
	return this->m_pCore->GetGui()->WindowDelete(pGuiWindowID);
}

bool ANApi::BeginGuiWindow(ANGuiWindowID GuiWindow, anVec2 Pos)
{
	return this->m_pCore->GetGui()->WindowBegin(GuiWindow, Pos);
}

void ANApi::EndGuiWindow()
{
	this->m_pCore->GetGui()->WindowEnd();
}

bool ANApi::ResizeGuiWindow(ANGuiWindowID* pGuiWindow, anVec2 Size)
{
	return this->m_pCore->GetGui()->WindowResize(pGuiWindow, Size);
}

anVec2 ANApi::GetGuiWindowSize(ANGuiWindowID GuiWindow)
{
	anVec2 WindowSize;

	if (!this->m_pCore->GetGui()->WindowGetSize(GuiWindow, &WindowSize))
		return anVec2();

	return WindowSize;
}

bool ANApi::AddButton(const char* pszName, anVec2 Pos, anVec2 Size, IANGuiButtonSkin* pButtonSkin)
{
	return this->m_pCore->GetGui()->Button(pszName, Pos, Size, pButtonSkin);
}

bool ANApi::AddCheckbox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar, IANCheckboxSkin* pCheckboxSkin)
{
	return this->m_pCore->GetGui()->Checkbox(pszName, Pos, Size, pVar, pCheckboxSkin);
}

bool ANApi::AddSliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar, IANSliderSkin* pSliderSkin)
{
	return this->m_pCore->GetGui()->SliderInt(pszName, Pos, Size, iMin, iMax, pVar, pSliderSkin);
}

bool ANApi::AddSliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar, IANSliderSkin* pSliderSkin)
{
	return this->m_pCore->GetGui()->SliderFloat(pszName, Pos, Size, flMin, flMax, pVar, pSliderSkin);
}

anVec2 ANApi::WorldToScreen(IANWorld* pWorld, anVec2 PointWorld)
{
	auto wm = pWorld->GetMetrics();

	return ANMathUtils::WorldToScreen(wm.m_WorldSize, wm.m_WorldScreenPos, wm.m_WorldScreenSize, wm.m_CameraWorld, PointWorld);
}

anVec2 ANApi::WorldToScreen(IANWorld* pWorld, IANEntity* pEntity)
{
	auto wm = pWorld->GetMetrics();

	return ANMathUtils::WorldToScreen(wm.m_WorldSize, wm.m_WorldScreenPos, wm.m_WorldScreenSize, wm.m_CameraWorld, pEntity->GetOrigin());
}

anRect ANApi::CalcBBox(anVec2 Origin, anVec2 ObjectSize)
{
	return ANMathUtils::CalcBBox(Origin, ObjectSize);
}

anRect ANApi::CalcScreenBBox(IANWorld* pWorld, anVec2 Origin, anVec2 ObjectSize)
{
	return ANMathUtils::CalcScreenBBox(pWorld->GetMetrics(), Origin, ObjectSize);
}

void ANApi::Update()
{
	auto p = this->m_pCore->GetPerfomance();

	this->FPS = p->GetFramePerSecond();
	this->Frametime = p->GetFrameTime();
	this->TotalRenderTime = p->GetTotalRenderTime();
}
