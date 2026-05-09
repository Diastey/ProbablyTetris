#pragma once
#include <Windows.h>

class FrameTimer
{
	LARGE_INTEGER m_timerFreq;
	LARGE_INTEGER m_timeNow;
	LARGE_INTEGER m_frameTimePrevious;
	LARGE_INTEGER m_realTimePrevious;

	int m_requestedFps;
	float m_intervalsPerFrame;
	float m_deltaTime;
	double m_timePassed;

public:
	FrameTimer(int fps)
	{
		Init(fps);
	}

	void Init(int fps);
	int FramesToUpdate();
	double GetTimePassed();
};