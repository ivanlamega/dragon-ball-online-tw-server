#include "TimerJs.h"

void TimerJs::stop() 
{
	this->clear = true;
}

void TimerJs::stop(int id) 
{
	DeleteTimer(id);
}

void TimerJs::AddTimer(int id) 
{
	lastTimerId = id;
	timers.push_back(id);
};

int TimerJs::GetNewId()
{
	bool found = false;
	int newId = lastTimerId+1;
	while (!found)
	{
		if (!FindTimer(newId))
		{
			return newId;
		}
		else
		{
			newId++;
		}
	}
}

void TimerJs::DeleteTimer(int id) {
	int timer = -1;
	for (TimersListIt iter = timers.cbegin(); iter != timers.cend(); ++iter)
	{
		timer = (*iter);

		if (timer == -1)
		{
			continue;
		}

		if (timer == id)
		{
			timers.erase(iter);
			break;
		}
	}
};

bool TimerJs::FindTimer(int id)
{
	for (std::vector<int>::size_type i = 0; i != timers.size(); i++)
	{
		if (timers[i] == id)
		{
			return true;
		}
	}
	return false;
}