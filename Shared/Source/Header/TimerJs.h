#pragma once
#include <iostream>
#include <thread>
#include <chrono>

class TimerJs {
	bool clear = false;

public:
	template<typename A>
	void setTimeout(A function, int delay);
	template<typename A>
	void setInterval(A function, int interval);
	template<typename A, typename B>
	void setIntervalArg(A function, int interval, B argument);
;	void stop();

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

template<typename A, typename B>
void TimerJs::setIntervalArg(A function, int interval, B argument) {
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

#define Timer AKCore::Singleton<TimerJs>::Instance()
