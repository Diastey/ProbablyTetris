#pragma once

class Timer
{
	float m_targetTime;
	float m_currentTime;
	bool m_autoReset;

public:
	Timer()
		:m_targetTime(0), m_currentTime(0), m_autoReset(false)
	{
	}
	Timer(float targetTime, bool autoReset)
		:m_targetTime(targetTime), m_currentTime(0), m_autoReset(autoReset)
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
			if (m_autoReset)
			{
				m_currentTime = 0;
			}
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