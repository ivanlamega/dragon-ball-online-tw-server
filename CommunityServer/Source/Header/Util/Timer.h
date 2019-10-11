#ifndef AKCORE_TIMER_H
#define AKCORE_TIMER_H

#pragma once

#include <Define.h>

#include <algorithm>
#include <iostream>
#include <string>

class CommunityTimer
{
private:
	static uint32 m_iTime;
	static uint32 m_iPrevTime;
public:

	// get current server time
	static uint32 getMSTime();

	// get time difference between two timestamps
	static inline uint32 getMSTimeDiff(const uint32& oldMSTime, const uint32& newMSTime)
	{
		if (oldMSTime > newMSTime)
		{
			const uint32 diff_1 = (uint32(0xFFFFFFFF) - oldMSTime) + newMSTime;
			const uint32 diff_2 = oldMSTime - newMSTime;

			return (std::min)(diff_1, diff_2);
		}

		return newMSTime - oldMSTime;
	}

	// get last world tick time
	static uint32 tickTime();
	// get previous world tick time
	static uint32 tickPrevTime();
	// tick world timer
	static uint32 tick();
};

class IntervalTimer
{
public:
	IntervalTimer() : _interval(0), _current(0) {}

	void Update(time_t diff)
	{
		_current += diff;
		if (_current < 0)
			_current = 0;
	}
	bool Passed() const { return _current >= _interval; }
	void Reset()
	{
		if (_current >= _interval)
			_current -= _interval;
	}

	void SetCurrent(time_t current) { _current = current; }
	void SetInterval(time_t interval) { _interval = interval; }
	time_t GetInterval() const { return _interval; }
	time_t GetCurrent() const { return _current; }

private:
	time_t _interval;
	time_t _current;
};

class ShortIntervalTimer
{
public:
	ShortIntervalTimer() : _interval(0), _current(0) {}

	void Update(uint32 diff)
	{
		_current += diff;
	}

	bool Passed() const { return _current >= _interval; }
	void Reset()
	{
		if (_current >= _interval)
			_current -= _interval;
	}

	void SetCurrent(uint32 current) { _current = current; }
	void SetInterval(uint32 interval) { _interval = interval; }
	uint32 GetInterval() const { return _interval; }
	uint32 GetCurrent() const { return _current; }

private:
	uint32 _interval;
	uint32 _current;
};

struct TimeTracker
{
public:
	TimeTracker(time_t expiry) : i_expiryTime(expiry) {}
	void Update(time_t diff) { i_expiryTime -= diff; }
	bool Passed() const { return (i_expiryTime <= 0); }
	void Reset(time_t interval) { i_expiryTime = interval; }
	time_t GetExpiry() const { return i_expiryTime; }

private:
	time_t i_expiryTime;
};

struct ShortTimeTracker
{
public:
	ShortTimeTracker(int32 expiry = 0) : i_expiryTime(expiry) {}
	void Update(int32 diff) { i_expiryTime -= diff; }
	bool Passed() const { return (i_expiryTime <= 0); }
	void Reset(int32 interval) { i_expiryTime = interval; }
	int32 GetExpiry() const { return i_expiryTime; }

private:
	int32 i_expiryTime;
};

#endif
