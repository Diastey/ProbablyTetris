#pragma once
#include <Windows.h>

class FrameTimer
{
	LARGE_INTEGER m_timerFreq;
	LARGE_INTEGER m_timeNow;
	LARGE_INTEGER m_timePrevious;

	int m_requestedFps;
	float m_intervalsPerFrame;
	float m_deltaTime;

public:
	void Init(int fps);
	int FramesToUpdate();
};