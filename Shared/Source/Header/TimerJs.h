#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

template<typename A>
struct TimerArguments {
	TimerArguments(int id, A argument) : idTimer(id), Argument(argument)
	{

	}

	int idTimer;
	A	Argument;
};

class TimerJs {
private:
	bool clear = false;

	int lastTimerId = 0;

	typedef std::vector<int> TimersList;
	typedef TimersList::const_iterator TimersListIt;
	std::vector<int> timers;

	void AddTimer(int id);
	void DeleteTimer(int id);
	bool FindTimer(int id);

public:

	int	GetNewId();

	template<typename A>
	void setTimeout(A function, int delay);
	template<typename A>
	void setInterval(A function, int interval);

	template<typename A>
	void setTimeout(A function, int delay, int id);
	template<typename A>
	void setInterval(A function, int interval, int id);

	template<typename A, typename B>
	void setTimeout(A function, int delay, B argument);
	template<typename A, typename B>
	void setInterval(A function, int interval, B argument);

	template<typename A, typename B>
	void setTimeout(A function, int delay, B argument, int id);
	template<typename A, typename B>
	void setInterval(A function, int interval, B argument, int id);

	void stop();
	void stop(int id);

};

template<typename A>
void TimerJs::setTimeout(A function, int delay) {
	this->clear = false;
	std::thread t([=]() {
		if (this->clear) return;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (this->clear) return;
		function();
		});
	t.detach();
}

template<typename A>
void TimerJs::setInterval(A function, int interval) {
	this->clear = false;
	std::thread t([=]() {
		while (true) {
			if (this->clear) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (this->clear) return;
			function();
		}
		});
	t.detach();
}

template<typename A>
void TimerJs::setTimeout(A function, int delay, int id) {
	this->clear = false;
	AddTimer(id);
	std::thread t([=]() {
		if (!FindTimer(id)) return;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (!FindTimer(id)) return;
		function();
		DeleteTimer(id);
		});
	t.detach();
}

template<typename A>
void TimerJs::setInterval(A function, int interval, int id) {
	this->clear = false;
	AddTimer(id);
	std::thread t([=]() {
		while (true) {
			if (!FindTimer(id)) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (!FindTimer(id)) return;
			function();
		}
		});
	t.detach();
}

template<typename A, typename B>
void TimerJs::setTimeout(A function, int delay, B argument) {
	this->clear = false;
	std::thread t([=]() {
		if (this->clear) return;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (this->clear) return;
		function(argument);
		});
	t.detach();
}

template<typename A, typename B>
void TimerJs::setInterval(A function, int interval, B argument) {
	this->clear = false;
	std::thread t([=]() {
		while (true) {
			if (this->clear) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (this->clear) return;
			function(argument);
		}
		});
	t.detach();
}

template<typename A, typename B>
void TimerJs::setTimeout(A function, int delay, B argument, int id) {
	this->clear = false;
	AddTimer(id);
	std::thread t([=]() {
		if (!FindTimer(id)) return;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (!FindTimer(id)) return;
		function(argument);
		DeleteTimer(id);
		});
	t.detach();
}

template<typename A, typename B>
void TimerJs::setInterval(A function, int interval, B argument, int id) {
	this->clear = false;
	AddTimer(id);
	std::thread t([=]() {
		while (true) {
			if (!FindTimer(id)) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (!FindTimer(id)) return;
			function(argument);
		}
		});
	t.detach();
}

#define Timer AKCore::Singleton<TimerJs>::Instance()
