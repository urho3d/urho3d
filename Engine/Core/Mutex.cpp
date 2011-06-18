//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"
#include "Mutex.h"

#ifndef USE_SDL
#include <Windows.h>
#else
#include <SDL.h>
#endif

#include "DebugNew.h"

#ifndef USE_SDL
Mutex::Mutex() :
    criticalSection_(new CRITICAL_SECTION)
{
    InitializeCriticalSection((CRITICAL_SECTION*)criticalSection_);
}

Mutex::~Mutex()
{
    CRITICAL_SECTION* cs = (CRITICAL_SECTION*)criticalSection_;
    DeleteCriticalSection(cs);
    delete cs;
    criticalSection_ = 0;
}

void Mutex::Acquire()
{
    EnterCriticalSection((CRITICAL_SECTION*)criticalSection_);
}

void Mutex::Release()
{
    LeaveCriticalSection((CRITICAL_SECTION*)criticalSection_);
}
#else
Mutex::Mutex() :
    criticalSection_(SDL_CreateMutex())
{
}

Mutex::~Mutex()
{
    SDL_DestroyMutex((SDL_mutex*)criticalSection_);
    criticalSection_ = 0;
}

void Mutex::Acquire()
{
    SDL_mutexP((SDL_mutex*)criticalSection_);
}

void Mutex::Release()
{
    SDL_mutexV((SDL_mutex*)criticalSection_);
}
#endif

MutexLock::MutexLock(Mutex& mutex) :
    mutex_(mutex)
{
    mutex_.Acquire();
}

MutexLock::~MutexLock()
{
    mutex_.Release();
}
