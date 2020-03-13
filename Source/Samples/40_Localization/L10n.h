//
// Copyright (c) 2008-2020 the Urho3D project.
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

#include "Sample.h"

/// Localization example.
/// This sample demonstrates:
///     - Loading a collection of strings from JSON-files
///     - Creating text elements that automatically translates itself by changing the language
///     - The manually reaction to change language
class L10n : public Sample
{
    URHO3D_OBJECT(L10n, Sample);

public:
    /// Construct.
    explicit L10n(Context* context);

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

private:
    // Load strings from JSON files and subscribe to the change language event
    void InitLocalizationSystem();
    // Init the 3D space
    void CreateScene();
    // Init the user interface
    void CreateGUI();
    /// Handle the logic update event.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    // Handle the change language event.
    void HandleChangeLanguage(StringHash eventType, VariantMap& eventData);
    // Hook up to the buttons pressing
    void HandleChangeLangButtonPressed(StringHash eventType, VariantMap& eventData);
    void HandleQuitButtonPressed(StringHash eventType, VariantMap& eventData);
};


