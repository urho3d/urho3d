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

#include "BorderImage.h"
#include "../Math/Vector2.h"
#include "Text.h"

namespace Urho3D
{

/// %ProgressBar bar %UI element.
class URHO3D_API ProgressBar : public BorderImage
{
    URHO3D_OBJECT(ProgressBar, BorderImage);

public:
    /// Construct.
    explicit ProgressBar(Context *context);

    /// Destruct.
    ~ProgressBar() override;

    /// Register object factory.
    static void RegisterObject(Context *context);

    /// React to resize.
    void OnResize(const IntVector2& newSize, const IntVector2& delta) override;

    /// Set orientation type.
    void SetOrientation(Orientation orientation);

    /// Set ProgressBar range maximum value (minimum value is always 0).
    void SetRange(float range);

    /// Set ProgressBar current value.
    void SetValue(float value);

    /// Change value by a delta.
    void ChangeValue(float delta);

    /// Return orientation type.
    Orientation GetOrientation() const { return orientation_; }

    /// Return ProgressBar range.
    float GetRange() const { return range_; }

    /// Return ProgressBar current value.
    float GetValue() const { return value_; }

    /// Return knob element.
    BorderImage *GetKnob() const { return knob_; }

    /// Sets the loading percent style.
    void SetLoadingPercentStyle(const String &style) { loadingPercentStyle_ = style; }

    /// Returns the loading percent style.
    const String& GetLoadingPercentStyle() const { return loadingPercentStyle_; }

    /// Sets the flag to display the percent text.
    void SetShowPercentText(bool enable);

    /// Returns the flag to display the percent text.
    bool GetShowPercentText() const { return showPercentText_; }

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement &dest) const override;

    /// Update ProgressBar knob position & size.
    void UpdateProgressBar();

    /// ProgressBar knob.
    SharedPtr<BorderImage> knob_;
    /// ProgressBar text.
    SharedPtr<Text> loadingText_;
    /// Orientation.
    Orientation orientation_;
    /// ProgressBar text style.
    String loadingPercentStyle_;
    /// ProgressBar range.
    float range_;
    /// ProgressBar current value.
    float value_;
    /// Flag to show the percent text.
    bool showPercentText_;
};

}
