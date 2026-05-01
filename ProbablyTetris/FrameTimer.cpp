#include "FrameTimer.h"
#include <profileapi.h>

FrameTimer::FrameTimer(int fps)
{
	Init(fps);
}

void FrameTimer::Init(int fps)
{
	QueryPerformanceFrequency(&m_timerFreq);
	QueryPerformanceCounter(&m_timeNow);
	QueryPerformanceCounter(&m_timePrevious);

	m_requestedFps = fps;

	m_intervalsPerFrame = (float)(m_timerFreq.QuadPart / m_requestedFps);
}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;

	QueryPerformanceCounter(&m_timeNow);

	m_deltaTime = m_timeNow.QuadPart - m_timePrevious.QuadPart;

	framesToUpdate = (int)(m_deltaTime / m_intervalsPerFrame);

	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&m_timePrevious);
	}

	return framesToUpdate;
}
