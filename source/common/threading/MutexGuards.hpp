#pragma once

template<typename T>
class LockGuard
{
private:
	T& m_mutex;

private:
	// disable copy constructors
	LockGuard(const LockGuard&);
	LockGuard& operator=(const LockGuard&);

public:
	LockGuard(T& mutex)
		: m_mutex(mutex)
	{
		m_mutex.lock();
	}

	~LockGuard()
	{
		m_mutex.unlock();
	}
};
