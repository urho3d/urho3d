//
// Copyright (c) 2008-2022 the Urho3D project.
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

#include "AppStateManager.h"

#include "AppState_Benchmark01.h"
#include "AppState_Benchmark02.h"
#include "AppState_Benchmark03.h"
#include "AppState_MainScreen.h"
#include "AppState_ResultScreen.h"

#include <Urho3D/DebugNew.h>

using namespace Urho3D;

AppStateManager::AppStateManager(Context* context)
    : Object(context)
{
    appStates_.Insert({APPSTATEID_MAINSCREEN, MakeShared<AppState_MainScreen>(context_)});
    appStates_.Insert({APPSTATEID_RESULTSCREEN, MakeShared<AppState_ResultScreen>(context_)});
    appStates_.Insert({APPSTATEID_BENCHMARK01, MakeShared<AppState_Benchmark01>(context_)});
    appStates_.Insert({APPSTATEID_BENCHMARK02, MakeShared<AppState_Benchmark02>(context_)});
    appStates_.Insert({APPSTATEID_BENCHMARK03, MakeShared<AppState_Benchmark03>(context_)});
}

void AppStateManager::Apply()
{
    if (requiredAppStateId_ == currentAppStateId_)
        return;

    assert(requiredAppStateId_ != APPSTATEID_NULL);

    if (currentAppStateId_ != APPSTATEID_NULL)
    {
        SharedPtr<AppState_Base> currentAppStatePtr = appStates_[currentAppStateId_];
        currentAppStatePtr->OnLeave();
    }

    previousAppStateId_ = currentAppStateId_;
    currentAppStateId_ = requiredAppStateId_;

    SharedPtr<AppState_Base> requiredAppStatePtr = appStates_[requiredAppStateId_];
    requiredAppStatePtr->OnEnter();
}
