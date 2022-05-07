// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../Urho2D/StaticSprite2D.h"

namespace Urho3D
{
/// Stretchable sprite component.
class URHO3D_API StretchableSprite2D : public StaticSprite2D
{
    URHO3D_OBJECT(StretchableSprite2D, StaticSprite2D);

public:
    /// Construct.
    explicit StretchableSprite2D(Context* context);
    /// Register object factory. Drawable2D must be registered first.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Set border as number of pixels from each side.
    /// @property
    void SetBorder(const IntRect& border);
    /// Get border as number of pixels from each side.
    /// @property
    const IntRect& GetBorder() const { return border_; }

protected:
    /// Update source batches.
    void UpdateSourceBatches() override;

    /// The border, represented by the number of pixels from each side.
    IntRect border_; // absolute border in pixels
};

}
