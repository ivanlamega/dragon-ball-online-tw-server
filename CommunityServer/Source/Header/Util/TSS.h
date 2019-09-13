#ifndef TSS_H
#define TSS_H

#include <boost/thread/tss.hpp>
#include <functional>

namespace AKCore
{
	template <typename T>
	class thread_local_ptr : public boost::thread_specific_ptr<T>
	{
	private:
		typedef std::function<T* ()> Generate;
		typedef std::function<void(T*)> Cleanup;

		Generate m_generator;

	public:
		thread_local_ptr() : m_generator([]() { return new T; }) {}
		thread_local_ptr(Generate generator) : m_generator(generator) {}
		thread_local_ptr(Generate generator, Cleanup cleanup) : m_generator(generator), boost::thread_specific_ptr<T>(cleanup) {}

		// this get allows for a nullptr return value
		T* get_value() { return boost::thread_specific_ptr<T>::get(); }

		T* get()
		{
			T* ret = get_value();
			if (!ret)
			{
				ret = m_generator();
				boost::thread_specific_ptr<T>::reset(ret);
			}
			return ret;
		}

		T* operator -> ()
		{
			return get();
		}

		typename boost::detail::sp_dereference< T >::type operator*() const
		{
			return *get();
		}
	};
}

#endif /*TSS_H*/