#pragma once

class ANPerfomance
{
public:
	ANPerfomance();
	~ANPerfomance();

	int GetFramePerSecond();
	double GetFrameTime();
	void SetMaxFps(int iMaxFps);
	bool PrepareScene();
	void Update();
private:
	ANPerfomanceTick GetTick();

	ANPerfomanceTick m_FpsSecondTimer;
	int m_iCurrentFpsCounter;
	int m_iFpsCounter;
	ANPerfomanceTick m_BeginFrameTick;
	ANPerfomanceTick m_EndFrameTick;
	double m_MaxFpsFrameTime;

	bool m_bFrameTimeIsGrabbed;
	int m_iCurrentSkippedFrame;

	int m_iMaxFps;
};

