// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

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
