#pragma once

class ANGuiWindow
{
	friend ANGui;
	friend ANRenderer;
public:
	ANGuiWindow(anVec2 Size);
	~ANGuiWindow();

private:
	ANInternalGuiWindowID m_InternalGuiWindowID;
	anVec2 m_Pos;
	anVec2 m_Size;
};