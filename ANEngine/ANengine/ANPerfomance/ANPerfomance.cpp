#include "../ANEngine.h"

ANPerfomance::ANPerfomance() :
	m_flFpsCounter(0),
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

float ANPerfomance::GetFramePerSecond()
{
	return this->m_flFpsCounter;
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
	ANPlatform::GetPerfomanceTick(this->m_BeginFrameTick);

	this->m_MaxFpsFrameTime = ((double)(this->m_BeginFrameTick - this->m_EndFrameTick) / 10000000.);

	if (this->m_EndFrameTick != 0)
	{
		this->m_TotalRenderTime += this->m_MaxFpsFrameTime;
		this->m_flFpsCounter = (float)((1.0 / this->m_MaxFpsFrameTime));
	}
	else 
	{
		this->m_flFpsCounter = FLT_MAX;
	}
		
	this->m_PrevFrameTick = this->m_EndFrameTick;
	this->m_EndFrameTick = this->m_BeginFrameTick;
}