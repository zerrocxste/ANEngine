#include "../ANEngine.h"

ANPerfomance::ANPerfomance() :
	m_FpsSecondTimer(0),
	m_iCurrentFpsCounter(0),
	m_iFpsCounter(0),
	m_BeginFrameTick(0),
	m_EndFrameTick(0),
	m_MaxFpsFrameTime(0),
	m_bFrameTimeIsGrabbed(false),
	m_iCurrentSkippedFrame(0),
	m_iMaxFps(0)
{

}

ANPerfomance::~ANPerfomance()
{

}

ANPerfomanceTick ANPerfomance::GetTick()
{
	ANPerfomanceTick T = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&T);
	return T;
}

int ANPerfomance::GetFramePerSecond()
{
	return this->m_iFpsCounter;
}

double ANPerfomance::GetFrameTime()
{
	return this->m_MaxFpsFrameTime;
}

void ANPerfomance::SetMaxFps(int iMaxFps)
{
	this->m_iMaxFps = iMaxFps;
}

bool ANPerfomance::PrepareScene()
{
	if (this->m_iMaxFps > 0)
	{
		if (this->m_iCurrentSkippedFrame > 0)
		{
			if (!this->m_bFrameTimeIsGrabbed)
			{
				this->m_bFrameTimeIsGrabbed = true;
				this->m_BeginFrameTick = GetTick();
			}
			this->m_iCurrentSkippedFrame--;
			return false;
		}

		this->m_iCurrentSkippedFrame = ((1000000 * 2.5f) / this->m_iMaxFps) + ((this->m_EndFrameTick - this->m_BeginFrameTick) / 10);
		this->m_bFrameTimeIsGrabbed = false;
	}
	else
	{
		this->m_BeginFrameTick = GetTick();
	}

	if (!this->m_FpsSecondTimer)
		this->m_FpsSecondTimer = this->m_BeginFrameTick;

	return true;
}

void ANPerfomance::Update()
{
	this->m_iCurrentFpsCounter++;

	this->m_EndFrameTick = GetTick();

	if ((this->m_EndFrameTick - this->m_FpsSecondTimer) / 10000 >= 1000)
	{
		this->m_iFpsCounter = this->m_iCurrentFpsCounter;
		this->m_FpsSecondTimer = 0;
		this->m_iCurrentFpsCounter = 0;
	}

	this->m_MaxFpsFrameTime = (double)(this->m_EndFrameTick - this->m_BeginFrameTick) / 10000000;
}