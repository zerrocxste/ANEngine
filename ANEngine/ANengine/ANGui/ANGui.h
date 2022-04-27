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
	bool CheckBox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar);
	bool SliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar);
	bool SliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar);
private:
	ANCore* m_pCore;
};

