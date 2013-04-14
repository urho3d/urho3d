//
// Copyright (c) 2008-2013 the Urho3D project.
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

#include "Drawable.h"

namespace Urho3D
{

class Text;

/// 3D text component.
class Text3D : public Drawable
{
    OBJECT(Text3D);
    
public:
    /// Construct.
    Text3D(Context* context);
    /// Destruct.
    ~Text3D();
    /// Register object factory. Drawable must be registered first.
    static void RegisterObject(Context* context);
    
    /// Set font and font size.
    bool SetFont(const String& fontName, int size = DEFAULT_FONT_SIZE);
    /// Set font and font size.
    bool SetFont(Font* font, int size = DEFAULT_FONT_SIZE);
    /// Set text. Text is assumed to be either ASCII or UTF8-encoded.
    void SetText(const String& text);
    /// Set row alignment.
    void SetTextAlignment(HorizontalAlignment align);
    /// Set row spacing, 1.0 for original font spacing.
    void SetRowSpacing(float spacing);
    /// Set wordwrap. In wordwrap mode the text element will respect its current width. Otherwise it resizes itself freely.
    void SetWordwrap(bool enable);
    /// Set material. To render fonts correctly, the material's pixel shader needs to read diffuse texture alpha as opacity.
    void SetMaterial(Material* material);
    
    /// Return font.
    Font* GetFont() const;
    /// Return font size.
    int GetFontSize() const;
    /// Return text.
    const String& GetText() const;
    /// Return row alignment.
    HorizontalAlignment GetTextAlignment() const;
    /// Return row spacing.
    float GetRowSpacing() const;
    /// Return wordwrap mode.
    bool GetWordwrap() const;
    /// Return row height.
    int GetRowHeight() const;
    /// Return number of rows.
    unsigned GetNumRows() const;
    /// Return width of each row.
    const PODVector<int>& GetRowWidths() const;
    /// Return material.
    Material* GetMaterial() const;
    
    /// Set font attribute.
    void SetFontAttr(ResourceRef value);
    /// Return font attribute.
    ResourceRef GetFontAttr() const;
    
protected:
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    
private:
    /// Internally used text element.
    SharedPtr<Text> text_;
};

}

