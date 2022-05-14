#pragma once

class ANPerfomance
{
public:
	ANPerfomance();
	~ANPerfomance();

	ANPerfomanceTick GetTick();
	ANPerfomanceTick GetPrevFrameTick();

	int GetFramePerSecond();
	float GetFrameTime();
	void SetMaxFps(int iMaxFps);
	void Update();
private:
	ANPerfomanceTick m_FpsSecondTimer;
	int m_iCurrentFpsCounter;
	int m_iFpsCounter;
	ANPerfomanceTick m_BeginFrameTick;
	ANPerfomanceTick m_EndFrameTick;
	ANPerfomanceTick m_PrevFrameTick;
	float m_MaxFpsFrameTime;

	bool m_bFrameTimeIsGrabbed;
	int m_iCurrentSkippedFrame;

	int m_iMaxFps;
};

