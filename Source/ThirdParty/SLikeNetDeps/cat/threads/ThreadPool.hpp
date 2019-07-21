/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CAT_THREAD_POOL_HPP
#define CAT_THREAD_POOL_HPP

#include <cat/Singleton.hpp>
#include <cat/threads/Mutex.hpp>
#include <cat/crypt/tunnel/KeyAgreement.hpp>
#include <cat/threads/RegionAllocator.hpp>
#include <cat/io/AsyncBuffer.hpp>
#include <cat/threads/Thread.hpp>
#include <cat/threads/WaitableFlag.hpp>

#if defined(CAT_OS_WINDOWS)
# include <cat/port/WindowsInclude.hpp>
#endif

namespace cat {


// Reference Object priorities
enum RefObjectPriorities
{
	REFOBJ_PRIO_0,
	REFOBJ_PRIO_COUNT = 32,
};


/*
    class ThreadRefObject

    Base class for any thread-safe reference-counted thread pool object

	Designed this way so that all of these objects can be automatically deleted
*/
class ThreadRefObject
{
    friend class ThreadPool;
    ThreadRefObject *last, *next;

	int _priorityLevel;
    volatile u32 _refCount;

public:
    ThreadRefObject(int priorityLevel);
    CAT_INLINE virtual ~ThreadRefObject() {}

public:
    void AddRef();
    void ReleaseRef();

	// Safe release -- If not null, then releases and sets to null
	template<class T>
	static CAT_INLINE void SafeRelease(T * &object)
	{
		if (object)
		{
			object->ReleaseRef();
			object = 0;
		}
	}
};


// Auto release for ThreadRefObject references
template<class T>
class AutoRef
{
	T *_ref;

public:
	CAT_INLINE AutoRef(T *ref = 0) throw() { _ref = ref; }
	CAT_INLINE ~AutoRef() throw() { ThreadRefObject::SafeRelease(_ref); }
	CAT_INLINE AutoRef &operator=(T *ref) throw() { Reset(ref); return *this; }

	CAT_INLINE T *Get() throw() { return _ref; }
	CAT_INLINE T *operator->() throw() { return _ref; }
	CAT_INLINE T &operator*() throw() { return *_ref; }
	CAT_INLINE operator T*() { return _ref; }

	CAT_INLINE void Forget() throw() { _ref = 0; }
	CAT_INLINE void Reset(T *ref = 0) throw() { ThreadRefObject::SafeRelease(_ref); _ref = ref; }
};


//// TLS

class ThreadPoolLocalStorage
{
public:
	BigTwistedEdwards *math;
	FortunaOutput *csprng;

	ThreadPoolLocalStorage();
	~ThreadPoolLocalStorage();

	bool Valid();
};


//// Shutdown

class ShutdownWait;
class ShutdownObserver;

class ShutdownWait
{
	friend class ShutdownObserver;

	WaitableFlag _kill_flag;
	ShutdownObserver *_observer;

	void OnShutdownDone();

public:
	// Priority number must be higher than users'
	ShutdownWait(int priorityLevel);
	/*virtual*/ ~ShutdownWait();

	CAT_INLINE ShutdownObserver *GetObserver() { return _observer; }

	bool WaitForShutdown(u32 milliseconds);
};

class ShutdownObserver : public ThreadRefObject
{
	friend class ShutdownWait;

	ShutdownWait *_wait;

private:
	ShutdownObserver(int priorityLevel, ShutdownWait *wait);
	~ShutdownObserver();
};


//// ThreadPoolWorker

class ThreadPoolWorker : public Thread
{
public:
	virtual bool ThreadFunction(void *port);
};

#if defined(CAT_OS_WINDOWS)
	typedef HANDLE ThreadPoolHandle;
#else
	typedef int ThreadPoolHandle;
#endif

/*
    class ThreadPool

    Startup()  : Call to start up the thread pool
    Shutdown() : Call to destroy the thread pool and objects
*/
class ThreadPool : public Singleton<ThreadPool>
{
	friend class ThreadRefObject;

    CAT_SINGLETON(ThreadPool);

#if defined(CAT_OS_WINDOWS)
    HANDLE _port;
#endif

	int _processor_count, _active_thread_count;

	static const int MAX_THREADS = 256;
	ThreadPoolWorker _threads[MAX_THREADS];

	// Track sockets for graceful termination
    Mutex _objectRefLock[REFOBJ_PRIO_COUNT];
    ThreadRefObject *_objectRefHead[REFOBJ_PRIO_COUNT];

protected:
    void TrackObject(ThreadRefObject *object);
    void UntrackObject(ThreadRefObject *object);

    bool SpawnThread();
    bool SpawnThreads();

public:
    bool Startup();
    void Shutdown();
	bool Associate(ThreadPoolHandle h, ThreadRefObject *key);

	int GetProcessorCount() { return _processor_count; }
	int GetThreadCount() { return _active_thread_count; }
};


} // namespace cat

#endif // CAT_THREAD_POOL_HPP
