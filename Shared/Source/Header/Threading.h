#ifndef THREADING_H
#define THREADING_H

#include <thread>
#include <atomic>

namespace AKCore
{
	class Runnable
	{
	public:
		virtual ~Runnable() {}
		virtual void run() = 0;

		void incReference() { ++m_refs; }
		void decReference()
		{
			if (!--m_refs)
				delete this;
		}
	private:
		std::atomic_long m_refs;
	};

	enum Priority
	{
		Priority_Idle,
		Priority_Lowest,
		Priority_Low,
		Priority_Normal,
		Priority_High,
		Priority_Highest,
		Priority_Realtime,
	};

	class Thread
	{
	public:
		Thread();
		explicit Thread(Runnable* instance);
		~Thread();

		bool wait();
		void destroy();

		void setPriority(Priority type);

		static void Sleep(unsigned long msecs);
		static std::thread::id currentId();

	private:
		Thread(const Thread&);
		Thread& operator=(const Thread&);

		static void ThreadTask(void* param);

		Runnable* const m_task;
		std::thread::id m_iThreadId;
		std::thread m_ThreadImp;
	};
}
#endif