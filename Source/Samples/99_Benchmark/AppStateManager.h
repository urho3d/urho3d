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

#pragma once

#include "AppState_Base.h"

#include <Urho3D/Container/HashMap.h>

using AppStateId = unsigned;

inline constexpr AppStateId APPSTATEID_NULL = 0;
inline constexpr AppStateId APPSTATEID_MAINSCREEN = 1;
inline constexpr AppStateId APPSTATEID_RESULTSCREEN = 2;
inline constexpr AppStateId APPSTATEID_BENCHMARK01 = 3;
inline constexpr AppStateId APPSTATEID_BENCHMARK02 = 4;

class AppStateManager : public U3D::Object
{
    URHO3D_OBJECT(AppStateManager, Object);

private:
    U3D::HashMap<AppStateId, U3D::SharedPtr<AppState_Base>> appStates_;
    AppStateId currentAppStateId_ = APPSTATEID_NULL;
    AppStateId requiredAppStateId_ = APPSTATEID_NULL;

public:
    AppStateManager(U3D::Context* context);

    AppStateId GetCurrentAppStateId() const { return currentAppStateId_; }

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
