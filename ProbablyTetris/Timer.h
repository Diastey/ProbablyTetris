#pragma once

class Timer
{
	float m_targetTime;
	float m_currentTime;

public:
	Timer()
		:m_targetTime(0), m_currentTime(0)
	{
	}
	Timer(float targetTime)
		:m_targetTime(targetTime), m_currentTime(0)
	{
	}

	float GetTargetTime()
	{
		return m_targetTime;
	}
	float GetTime()
	{
		return m_currentTime;
	}
	void SetTargetTime(float targetTime)
	{
		m_targetTime = targetTime;
		m_currentTime = 0;
	}
	bool TimerCheck(float timePassed)
	{
		AddCurrentTime(timePassed);
		if (m_currentTime >= m_targetTime)
		{
			m_currentTime = 0;
			return true;
		}
		return false;
	}
	void AddCurrentTime(float timePassed)
	{
		m_currentTime += timePassed;
	}
	void DelayCurrentTimeByPercentage(float percentage)
	{
		if (m_currentTime >= (m_targetTime * percentage))
			m_currentTime -= (m_targetTime * percentage);
	}
	float TimerPercentage()
	{
		return m_currentTime / m_targetTime;
	}
	void ResetTimer()
	{
		m_currentTime = 0;
	}
};