/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file Lockable.h
	@brief The Lock<T> and Lockable<T> template classes. */

// Modified by Lasse Oorni for Urho3D

#ifdef KNET_USE_BOOST
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>
#elif defined(WIN32)
// Urho3D: windows.h in lowercase to fix MinGW cross-compiling on a case-sensitive system
#include <windows.h>
#else
#include <pthread.h>
#endif

#include <assert.h>
#include "PolledTimer.h"
#include "NetworkLogging.h"

namespace kNet
{

template<typename T>
class Lockable;

/// @internal Wraps mutex-lock acquisition and releasing into a RAII-style object that automatically releases the lock when the scope
/// is exited. Lock operates in an std::auto_ptr style in deciding which object has the ownership of the lock.
template<typename T>
class Lock
{
public:
	explicit Lock(Lockable<T> *lockedObject_)
	:lockedObject(lockedObject_), value(&lockedObject->LockGet())
	{
	}

	Lock(const Lock<T> &rhs)
	:lockedObject(rhs.lockedObject), value(rhs.value)
	{
		assert(this != &rhs);
		rhs.TearDown();
	}

	Lock<T> &operator=(const Lock<T> &rhs)
	{
		if (&rhs == this)
			return *this;

		lockedObject = rhs.lockedObject();
		value = rhs.value;

		rhs.TearDown();
	}

	~Lock()
	{
		Unlock();
	}

	void Unlock()
	{
		if (lockedObject)
		{
			lockedObject->Unlock();
			lockedObject = 0;
		}
	}

	T *operator ->() const { return value; }
	T &operator *() { return *value; }

private:
	mutable Lockable<T> *lockedObject;
	mutable T *value;

	/// Clears the pointer to the object this Lock points to. This function is const to allow std::auto_ptr -like
	/// lock ownership passing in copy-ctor.
	void TearDown() const { lockedObject = 0; value = 0; }
};

/// @internal Wraps mutex-lock acquisition and releasing to const data into a RAII-style object 
/// that automatically releases the lock when the scope is exited.
template<typename T>
class ConstLock
{
public:
	explicit ConstLock(const Lockable<T> *lockedObject_)
	:lockedObject(lockedObject_), value(&lockedObject->LockGet())
	{
	}

	ConstLock(const ConstLock<T> &rhs)
	:lockedObject(rhs.lockedObject), value(rhs.value)
	{
		assert(this != &rhs);
		rhs.TearDown();
	}

	ConstLock<T> &operator=(const ConstLock<T> &rhs)
	{
		if (&rhs == this)
			return *this;

		lockedObject = rhs.lockedObject();
		value = rhs.value;

		rhs.TearDown();
	}

	~ConstLock()
	{
		if (lockedObject)
			lockedObject->Unlock();
	}

	const T *operator ->() const { return value; }
	const T &operator *() const { return *value; }

private:
	mutable const Lockable<T> *lockedObject;
	mutable const T *value;

	/// Clears the pointer to the object this Lock points to. This function is const to allow std::auto_ptr -like
	/// lock ownership passing in copy-ctor.
	void TearDown() const { lockedObject = 0; value = 0; }
};

/// Stores an object of type T behind a mutex-locked shield. To access the object, one has to acquire a lock to it first, and remember
/// to free the lock when done. Use @see Lock and @see ConstLock to manage the locks in a RAII-style manner.
template<typename T>
class Lockable
{
public:
	typedef Lock<T> LockType;
	typedef ConstLock<T> ConstLockType;

	Lockable()
	{
#ifndef KNET_USE_BOOST
#ifdef WIN32
		InitializeCriticalSection(&lockObject);
#else
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex, &attr);
#endif
#endif
	}
/* Lockable objects are noncopyable. If thread-safe copying were to be supported, it should be implemented something like this:
	Lockable(const Lockable<T> &other)
	{		
		InitializeCriticalSection(&lockObject);
		value = other.Lock();
		other.Unlock();
	}
*/
	explicit Lockable(const T &value_)
	:value(value_)
	{
#ifndef KNET_USE_BOOST
#ifdef WIN32
		InitializeCriticalSection(&lockObject);
#else
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&mutex, &attr);
#endif
#endif
	}

	~Lockable()
	{
#ifndef KNET_USE_BOOST
#ifdef WIN32
		DeleteCriticalSection(&lockObject);
#else
		pthread_mutex_destroy(&mutex);
#endif
#endif
	}
/* Lockable objects are nonassignable. If thread-safe copying were to be supported, it should be implemented something like this:
	Lockable &operator=(const Lockable<T> &other)
	{
		if (this == &other)
			return *this;

		this->Lock();
		value = other.Lock();
		other.Unlock();
		this->Unlock();
	}
*/
	T &LockGet()
	{
#ifdef KNET_USE_BOOST
		boostMutex.lock();
#elif defined(WIN32)
		EnterCriticalSection(&lockObject);
#else
		pthread_mutex_lock(&mutex);
#endif
		return value;
	}

	const T &LockGet() const
	{
#ifdef KNET_USE_BOOST
		boostMutex.lock();
#elif defined(WIN32)
		EnterCriticalSection(&lockObject);
#else
		pthread_mutex_lock(&mutex);
#endif
		return value;
	}

	void Unlock() const
	{
#ifdef KNET_USE_BOOST
		boostMutex.unlock();
#elif defined(WIN32)
		LeaveCriticalSection(&lockObject);
#else
		pthread_mutex_unlock(&mutex);
#endif
	}

	LockType Acquire()
	{
		return LockType(this);
	}

	ConstLockType Acquire() const
	{
		return ConstLockType(this);
	}

	/// Ignores the mutex guard and directly returns a reference to the locked value.
	/// Warning: This is unsafe for threading. Call only when the other threads accessing
	/// the data have been finished, or if you can guarantee by other means that the data
	/// will not be accessed.
	T &UnsafeGetValue()
	{
		return value;
	}

	/// Ignores the mutex guard and directly returns a reference to the locked value.
	/// Warning: This is unsafe for threading. Call only when the other threads accessing
	/// the data have been finished, or if you can guarantee by other means that the data
	/// will not be accessed.
	const T &UnsafeGetValue() const
	{
		return value;
	}

#ifdef KNET_USE_BOOST
	mutable boost::recursive_mutex boostMutex;
#elif defined(WIN32)
	mutable CRITICAL_SECTION lockObject;
#else
	mutable pthread_mutex_t mutex;
#endif

private:
	T value;

	void operator=(const Lockable<T> &);
	Lockable(const Lockable<T> &);
};

} // ~kNet
