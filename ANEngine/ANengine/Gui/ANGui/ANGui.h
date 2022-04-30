#pragma once

class ANGui : public IANError
{
public:
	ANGui(ANCore* m_pCore);
	~ANGui();

	bool WindowCreate(ANGuiWindowID* pGuiWindow, anVec2 Size);
	bool WindowDelete(ANGuiWindowID* pGuiWindow);
	bool WindowBegin(ANGuiWindowID GuiWindow, anVec2 Pos);
	void WindowEnd();
	bool WindowGetSize(ANGuiWindowID GuiWindow, anVec2* pSize);
	bool WindowResize(ANGuiWindowID* pGuiWindow, anVec2 Size);

	bool Button(const char* pszName, anVec2 Pos, anVec2 Size, IANGuiButtonSkin* pButtonSkin = nullptr);
	bool Checkbox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar, IANCheckboxSkin* pCheckboxSkin = nullptr);
	bool SliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar, IANSliderSkin* pSliderSkin = nullptr);
	bool SliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar, IANSliderSkin* pSliderSkin = nullptr);
private:
	ANCore* m_pCore;
};

