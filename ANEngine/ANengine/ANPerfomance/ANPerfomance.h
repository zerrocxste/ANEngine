#pragma once

class ANPerfomance
{
public:
	ANPerfomance();
	~ANPerfomance();

	ANPerfomanceTick GetTick();
	ANPerfomanceTick GetPrevFrameTick();

	float GetFramePerSecond();
	float GetFrameTime();
	double GetTotalRenderTime();
	void SetMaxFps(int iMaxFps);
	void Update();
private:
	float m_flFpsCounter;
	ANPerfomanceTick m_BeginFrameTick;
	ANPerfomanceTick m_EndFrameTick;
	ANPerfomanceTick m_PrevFrameTick;
	double m_MaxFpsFrameTime;

	bool m_bFrameTimeIsGrabbed;
	int m_iCurrentSkippedFrame;

	int m_iMaxFps;

	double m_TotalRenderTime;
};

