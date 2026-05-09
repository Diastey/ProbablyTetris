#include "FrameTimer.h"

void FrameTimer::Init(int fps)
{
	QueryPerformanceFrequency(&m_timerFreq);
	QueryPerformanceCounter(&m_timeNow);
	QueryPerformanceCounter(&m_frameTimePrevious);
	QueryPerformanceCounter(&m_realTimePrevious);

	m_requestedFps = fps;

	m_intervalsPerFrame = (float)(m_timerFreq.QuadPart / m_requestedFps);
}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;

	QueryPerformanceCounter(&m_timeNow);

	m_timePassed = (double)(m_timeNow.QuadPart - m_realTimePrevious.QuadPart) / (double)m_timerFreq.QuadPart;
	m_realTimePrevious = m_timeNow;

	m_deltaTime = m_timeNow.QuadPart - m_frameTimePrevious.QuadPart;
	framesToUpdate = (int)(m_deltaTime / m_intervalsPerFrame);
	if (framesToUpdate != 0) {
		QueryPerformanceCounter(&m_frameTimePrevious);
	}

	return framesToUpdate;
}

double FrameTimer::GetTimePassed()
{
	return m_timePassed;
}
