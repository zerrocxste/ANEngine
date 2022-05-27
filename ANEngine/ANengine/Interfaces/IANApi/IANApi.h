#pragma once

class IANApi
{
public:
	//FRAME | RUNTIME STATISTICS
	int FPS;
	float Frametime;
	double TotalRenderTime;

	//MAIN
	virtual void LeaveApp() = 0;
	virtual bool ConnectToScene(IANGameScene* pGameScene) = 0;

	//INPUT
	virtual bool GetCursorKeyIsDowned(int k) = 0;
	virtual bool GetCursorKeyIsClicked(int k) = 0;
	virtual bool GetCursorKeyIsReleased(int k) = 0;
	virtual float GetCursorKeyDownTime(int k) = 0;
	virtual anVec2 GetCursorPos() = 0;
	virtual bool GetKeyIsDowned(int k) = 0;
	virtual bool GetKeyIsClicked(int k) = 0;
	virtual bool GetKeyIsReleased(int k) = 0;
	virtual float GetKeyDownTime(int k) = 0;

	//SCREEN
	virtual anVec2 GetScreenSize() = 0;

	//DRAWING
	virtual bool CreateImage(const char* pszPath, ANImageID* pImageID) = 0;
	virtual anVec2 GetImageSize(ANImageID ImageID) = 0;
	virtual void FreeImage(ANImageID* pImageID) = 0;
	virtual bool DrawImage(ANImageID ImageID, anVec2 Pos, anVec2 Size, float Opacity) = 0;
	virtual bool DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness = 1.f) = 0;
	virtual bool DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness = 1.f, float Rounding = 0.f, bool Filled = false) = 0;
	virtual bool DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness = 1.f, bool Filled = false) = 0;
	virtual bool DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness = 1.f, bool Filled = false) = 0;
	virtual bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID) = 0;
	virtual void FreeFont(ANFontID* pFontID) = 0;
	virtual void PushFont(ANFontID FontID) = 0;
	virtual void PopFont() = 0;
	virtual void PushFontColor(anColor Color) = 0;
	virtual void PopFontColor() = 0;
	virtual bool TextDraw(const char* pszText, anVec2 Pos, anColor Color) = 0;
	virtual anVec2 TextCalcSize(const char* pszText) = 0;

	//PERFOMANCE
	virtual ANPerfomanceTick GetTickMicroseconds() = 0;
	virtual ANPerfomanceTick GetPrevFrameTickMicroseconds() = 0;

	//GAME UTILITY
	virtual void RegWorld(IANWorld** ppWorld) = 0;
	virtual void UnregWorld(IANWorld** ppWorld) = 0;

	virtual anVec2 WorldToScreen(IANWorld* pWorld, anVec2 PointWorld) = 0;
	virtual anVec2 WorldToScreen(IANWorld* pWorld, IANEntity* pEntity) = 0;

	virtual void RegEntity(IANEntity** ppEntity, const char* pszEntityClassID) = 0;
	virtual void UnregEntity(IANEntity** ppEntity) = 0;
	virtual ANInterfacePointer<IANEntityGroup> FindEntityByGroupID(const char* pszGroupID) = 0;
	virtual IANEntity* GetEntityByName(const char* pszEntName) = 0;

	//DRAWING HELPERS
	virtual bool CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition) = 0;
	virtual void DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition) = 0;
	virtual int GetAnimationCompositionSize(ANAnimationComposition AnimationComposition) = 0;
	virtual ANImageID GetAnimationCompositionFrameFromID(ANAnimationComposition AnimationComposition, int ID) = 0;

	//GUI WINDOW
	virtual bool RegGuiWindow(ANGuiWindowID* pGuiWindowID, anVec2 Size) = 0;
	virtual bool UnregGuiWindow(ANGuiWindowID* pGuiWindowID) = 0;

	virtual bool BeginGuiWindow(ANGuiWindowID GuiWindow, anVec2 Pos) = 0;
	virtual void EndGuiWindow() = 0;

	virtual anVec2 GetGuiWindowSize(ANGuiWindowID GuiWindow) = 0;
	virtual bool ResizeGuiWindow(ANGuiWindowID* pGuiWindow, anVec2 Size) = 0;

	//GUI HELPERS
	virtual bool AddButton(const char* pszName, anVec2 Pos, anVec2 Size, IANGuiButtonSkin* pButtonSkin = nullptr) = 0;
	virtual bool AddCheckbox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar, IANCheckboxSkin* pCheckboxSkin = nullptr) = 0;
	virtual bool AddSliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar, IANSliderSkin* pSliderSkin = nullptr) = 0;
	virtual bool AddSliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar, IANSliderSkin* pSliderSkin = nullptr) = 0;
};
