#include "../ANEngine.h"

ANPerfomance::ANPerfomance() :
	m_FpsSecondTimer(0),
	m_iCurrentFpsCounter(0),
	m_iFpsCounter(0),
	m_BeginFrameTick(0),
	m_EndFrameTick(0),
	m_PrevFrameTick(0),
	m_MaxFpsFrameTime(0),
	m_bFrameTimeIsGrabbed(false),
	m_iCurrentSkippedFrame(0),
	m_iMaxFps(0),
	m_TotalRenderTime(0.)
{

}

ANPerfomance::~ANPerfomance()
{

}

ANPerfomanceTick ANPerfomance::GetTick()
{
	return this->m_BeginFrameTick;
}

ANPerfomanceTick ANPerfomance::GetPrevFrameTick()
{
	return this->m_PrevFrameTick;
}

int ANPerfomance::GetFramePerSecond()
{
	return this->m_iFpsCounter;
}

float ANPerfomance::GetFrameTime()
{
	return this->m_MaxFpsFrameTime;
}

double ANPerfomance::GetTotalRenderTime()
{
	return this->m_TotalRenderTime;
}

void ANPerfomance::SetMaxFps(int iMaxFps)
{
	this->m_iMaxFps = iMaxFps;
}

void ANPerfomance::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&this->m_BeginFrameTick);

	this->m_MaxFpsFrameTime = (float)(this->m_BeginFrameTick - this->m_EndFrameTick) / 10000000.f;

	if (this->m_EndFrameTick != 0)
		this->m_TotalRenderTime += this->m_MaxFpsFrameTime;

	this->m_PrevFrameTick = this->m_EndFrameTick;
	this->m_EndFrameTick = this->m_BeginFrameTick;

	this->m_iCurrentFpsCounter++;

	if ((this->m_EndFrameTick - this->m_FpsSecondTimer) / 10000 >= 1000)
	{
		this->m_iFpsCounter = this->m_iCurrentFpsCounter;
		this->m_FpsSecondTimer = 0;
		this->m_iCurrentFpsCounter = 0;
	}

	if (!this->m_FpsSecondTimer)
		this->m_FpsSecondTimer = this->m_BeginFrameTick;
}