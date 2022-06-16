#pragma once

class ANApi : public IANApi
{
	friend ANGame;
public:
	ANApi(ANCore* pCore);
	~ANApi();

	void LeaveApp() override;
	bool ConnectToScene(IANGameScene* pGameScene) override;

	bool GetCursorKeyIsDowned(int k) override;
	bool GetCursorKeyIsClicked(int k) override;
	bool GetCursorKeyIsReleased(int k) override;
	float GetCursorKeyDownTime(int k) override;
	anVec2 GetCursorPos() override;
	bool GetKeyIsDowned(int k) override;
	bool GetKeyIsClicked(int k) override;
	bool GetKeyIsReleased(int k) override;
	float GetKeyDownTime(int k) override;

	anVec2 GetScreenSize() override;

	bool CreateImage(const char* pszPath, ANImageID* pImageID) override;
	anVec2 GetImageSize(ANImageID ImageID) override;
	void FreeImage(ANImageID* pImageIDPtr) override;
	bool DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity) override;
	bool DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness = 1.f) override;
	bool DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness = 1.f, float Rounding = 0.f, bool Filled = false) override;
	bool DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness = 1.f, bool Filled = false) override;
	bool DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness = 1.f, bool Filled = false) override;
	bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID) override;
	void FreeFont(ANFontID* pFontIDPtr) override;
	void PushFont(ANFontID FontID) override;
	void PopFont() override;
	void PushFontColor(anColor Color) override;
	void PopFontColor() override;
	bool TextDraw(const char* pszText, anVec2 Pos, anColor Color) override;
	anVec2 TextCalcSize(const char* pszText) override;

	ANPerfomanceTick GetTickMicroseconds() override;
	ANPerfomanceTick GetPrevFrameTickMicroseconds() override;

	void RegWorld(IANWorld** ppWorld) override;
	void UnregWorld(IANWorld** ppWorld) override;

	anVec2 ScreenPointToWorld(IANWorld* pWorld, anVec2 ScreenPoint) override;

	anVec2 WorldToScreen(IANWorld* pWorld, anVec2 PointWorld) override;
	anVec2 WorldToScreen(IANWorld* pWorld, IANEntity* pEntity) override;

	void RegEntity(IANEntity** ppEntity, const char* pszEntityClassID) override;
	void UnregEntity(IANEntity** ppEntity) override;
	void UnregAndDeleteAllEntity() override;
	ANInterfacePointer<IANEntityGroup> FindEntityByGroupID(const char* pszGroupID) override;
	IANEntity* GetEntityByName(const char* pszEntName) override;

	IANInteractionMessagesList* GetInteractionMessagesList() override;

	bool CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition) override;
	void DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition) override;
	int GetAnimationCompositionSize(ANAnimationComposition AnimationComposition) override;
	ANImageID GetAnimationCompositionFrameFromID(ANAnimationComposition AnimationComposition, int ID) override;

	bool RegGuiWindow(ANGuiWindowID* pGuiWindowID, anVec2 Size) override;
	bool UnregGuiWindow(ANGuiWindowID* pGuiWindowID) override;

	bool BeginGuiWindow(ANGuiWindowID GuiWindow, anVec2 Pos) override;
	void EndGuiWindow() override;

	anVec2 GetGuiWindowSize(ANGuiWindowID GuiWindow) override;
	bool ResizeGuiWindow(ANGuiWindowID* pGuiWindow, anVec2 Size) override;

	bool AddButton(const char* pszName, anVec2 Pos, anVec2 Size, IANGuiButtonSkin* pButtonSkin = nullptr) override;
	bool AddCheckbox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar, IANCheckboxSkin* pCheckboxSkin = nullptr) override;
	bool AddSliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar, IANSliderSkin* pSliderSkin = nullptr) override;
	bool AddSliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar, IANSliderSkin* pSliderSkin = nullptr) override;
private:
	ANCore* m_pCore;

	void Update();
};