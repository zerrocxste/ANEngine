#include "../ANEngine.h"

ANApi::ANApi(ANCore* pCore) : 
	IANApi(),
	m_pCore(pCore)
{
	this->FPS = 0;
	this->Frametime = 0.;
}

ANApi::~ANApi()
{

}

void ANApi::LeaveApp()
{
	this->m_pCore->GetGame()->LeaveGame();
}

bool ANApi::ConnectToScene(IANGameScene* pGameScene)
{
	return this->m_pCore->GetGame()->ConnectScene(pGameScene);
}

bool ANApi::GetKeyIsDowned(int k)
{
	return this->m_pCore->GetInput()->IsKeyDowned(k);
}

bool ANApi::GetKeyIsClicked(int k)
{
	return this->m_pCore->GetInput()->IsKeyClicked(k);
}

bool ANApi::GetKeyIsReleased(int k)
{
	return this->m_pCore->GetInput()->IsKeyReleased(k);
}

float ANApi::GetKeyDownTime(int k)
{
	return this->m_pCore->GetInput()->GetKeyDownTime(k);
}

anVec2 ANApi::GetScreenSize()
{
	return this->m_pCore->GetRenderer()->GetScreenSize();
}

bool ANApi::CreateImage(const char* pszPath, ANImageID* pImageID)
{
	ANUniqueResource ImageResource;

	if (!this->m_pCore->GetResourceManager()->ReadBinFile(pszPath, &ImageResource))
		return false;

	return this->m_pCore->GetRenderer()->CreateImageFromResource(&ImageResource, pImageID);
}

anVec2 ANApi::GetImageSize(ANImageID ImageID)
{
	anVec2 Size;
	this->m_pCore->GetRenderer()->GetImageSize(ImageID, &Size);
	return Size;
}

void ANApi::FreeImage(ANImageID* pImageIDPtr)
{
	this->m_pCore->GetRenderer()->FreeImage(pImageIDPtr);
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

bool ANApi::TextDraw(const char* pszText, anVec2 Pos, anColor Color)
{
	return this->m_pCore->GetRenderer()->TextDraw(pszText, Pos, Color);
}

anVec2 ANApi::TextCalcSize(const char* pszText)
{
	anVec2 Size;

	if (!this->m_pCore->GetRenderer()->TextCalcSize(pszText, &Size))
		return anVec2();

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

void ANApi::RegEntity(IANEntity** ppEntity, const char* pszEntityClassID)
{
	this->m_pCore->GetGame()->RegEntity(ppEntity, pszEntityClassID);
}

void ANApi::UnregEntity(IANEntity** ppEntity)
{
	this->m_pCore->GetGame()->UnregEntity(ppEntity);
}

ANPointer<IANEntityGroup> ANApi::FindEntityByGroupID(const char* pszGroupID)
{
	ANPointer<ANEntityGroup> EntityGroup;
	this->m_pCore->GetGame()->GetEntityList()->FindFromClassID(pszGroupID, &EntityGroup->m_EntityGroup);
	return EntityGroup;
}

IANEntity* ANApi::GetEntityByName(const char* pszEntName)
{
	return this->m_pCore->GetGame()->GetEntityList()->FindFromName(pszEntName);
}

bool ANApi::CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition)
{
	if (iAnimationLabelsArrSize == 0)
		return false;

	*pAnimationComposition = (ANAnimationComposition)ANMemory::GetInstance()->ResourceAllocate(sizeof(int) + (sizeof(ANAnimationComposition) * iAnimationLabelsArrSize));

	if (!*pAnimationComposition)
		return false;

	*(int*)*pAnimationComposition = iAnimationLabelsArrSize;

	auto AnimationComposition = (ANAnimationComposition**)((std::uintptr_t)*pAnimationComposition + sizeof(int));

	for (auto i = 0; i < iAnimationLabelsArrSize; i++)
	{
		ANImageID Image = 0;

		ANUniqueResource ImageResource;

		if (!this->m_pCore->GetResourceManager()->ReadBinFile(pszAnimationLabelsArr[i], &ImageResource))
			return false;

		if (!this->m_pCore->GetRenderer()->CreateImageFromResource(&ImageResource, &Image))
			return false;

		AnimationComposition[i] = (ANAnimationComposition*)Image;
	}

	return true;
}

void ANApi::DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition)
{
	auto AnimationComposition = (ANAnimationComposition**)((std::uintptr_t)*pAnimationComposition + sizeof(int));

	for (auto i = 0; i < *(int*)*pAnimationComposition; i++)
		this->m_pCore->GetRenderer()->FreeImage((ANImageID*)((std::uintptr_t)AnimationComposition + (sizeof(ANAnimationComposition) * i)));
		
	ANMemory::GetInstance()->FreeResource(*pAnimationComposition);
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

void ANApi::Update()
{
	auto p = this->m_pCore->GetPerfomance();

	this->FPS = p->GetFramePerSecond();
	this->Frametime = p->GetFrameTime();
	this->TotalRenderTime = p->GetTotalRenderTime();
}
