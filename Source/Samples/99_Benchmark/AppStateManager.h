// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "AppState_Base.h"

#include <Urho3D/Container/HashMap.h>

using AppStateId = unsigned;

inline constexpr AppStateId APPSTATEID_NULL = 0;
inline constexpr AppStateId APPSTATEID_MAINSCREEN = 1;
inline constexpr AppStateId APPSTATEID_RESULTSCREEN = 2;
inline constexpr AppStateId APPSTATEID_BENCHMARK01 = 3;
inline constexpr AppStateId APPSTATEID_BENCHMARK02 = 4;
inline constexpr AppStateId APPSTATEID_BENCHMARK03 = 5;

class AppStateManager : public U3D::Object
{
public:
    URHO3D_OBJECT(AppStateManager, Object);

private:
    U3D::HashMap<AppStateId, U3D::SharedPtr<AppState_Base>> appStates_;
    AppStateId currentAppStateId_ = APPSTATEID_NULL;
    AppStateId previousAppStateId_ = APPSTATEID_NULL;
    AppStateId requiredAppStateId_ = APPSTATEID_NULL;

public:
    AppStateManager(U3D::Context* context);

    AppStateId GetCurrentAppStateId() const { return currentAppStateId_; }
    AppStateId GetPreviousAppStateId() const { return previousAppStateId_; }

    AppStateId GetRequiredAppStateId() const { return requiredAppStateId_; }
    void SetRequiredAppStateId(AppStateId id) { requiredAppStateId_ = id; }

    // Change state if currentAppStateId_ != requiredAppStateId_
    void Apply();

    const U3D::String& GetName(AppStateId appStateId) const
    {
        auto it = appStates_.Find(appStateId);
        assert(it != appStates_.End());
        return it->second_->GetName();
    }

    const FpsCounter& GetResult(AppStateId appStateId) const
    {
        auto it = appStates_.Find(appStateId);
        assert(it != appStates_.End());
        return it->second_->GetResult();
    }

    void ClearAllResults()
    {
        for (auto& pair : appStates_)
            pair.second_->ClearResult();
    }
};
