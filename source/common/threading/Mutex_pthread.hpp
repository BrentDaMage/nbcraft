#pragma once
#include <pthread.h>
#include <cassert>
#include "compat/LegacyCPP.hpp"

class Mutex
{
private:
	pthread_mutex_t m_mutex;

private:
	// disable copy constructors
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);

public:
	Mutex()
	{
		int result = pthread_mutex_init(&m_mutex, nullptr);
		assert(result == 0);
	}

	~Mutex()
	{
		int result = pthread_mutex_destroy(&m_mutex);
		assert(result == 0);
	}

public:
	void lock()
	{
		int result = pthread_mutex_lock(&m_mutex);
		assert(result == 0);
	}

	void unlock()
	{
		int result = pthread_mutex_unlock(&m_mutex);
		assert(result == 0);
	}
};

class RecursiveMutex
{
private:
	pthread_mutex_t m_mutex;

private:
	// disable copy constructors
	RecursiveMutex(const RecursiveMutex&);
	RecursiveMutex& operator=(const RecursiveMutex&);

public:
	RecursiveMutex()
	{
		int result;
		pthread_mutexattr_t attr;

		result = pthread_mutexattr_init(&attr);
		assert(result == 0);
		result = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		assert(result == 0);

		result = pthread_mutex_init(&m_mutex, &attr);
		assert(result == 0);

		result = pthread_mutexattr_destroy(&attr);
		assert(result == 0);
	}

	~RecursiveMutex()
	{
		int result = pthread_mutex_destroy(&m_mutex);
		assert(result == 0);
	}

public:
	void lock()
	{
		int result = pthread_mutex_lock(&m_mutex);
		assert(result == 0);
	}

	void unlock()
	{
		int result = pthread_mutex_unlock(&m_mutex);
		assert(result == 0);
	}
};
