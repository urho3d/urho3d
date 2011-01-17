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

#ifndef UI_CHECKBOX_H
#define UI_CHECKBOX_H

#include "BorderImage.h"

class CheckBox : public BorderImage
{
    DEFINE_TYPE(CheckBox);
    
public:
    //! Construct with name
    CheckBox(const std::string& name = std::string());
    //! Destruct
    virtual ~CheckBox();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    //! React to mouse click
    virtual void onClick(const IntVector2& position, const IntVector2& screenPosition, unsigned buttons);
    
    //! Set checked state
    void setChecked(bool enable);
    //! Set unchecked image rectangle
    void setUncheckedRect(const IntRect& rect);
    //! Set unchecked image rectangle
    void setUncheckedRect(int left, int top, int right, int bottom);
    //! Set checked image rectangle
    void setCheckedRect(const IntRect& rect);
    //! Set checked image rectangle
    void setCheckedRect(int left, int top, int right, int bottom);
    
    //! Return whether is checked
    bool isChecked() const { return mChecked; }
    //! Return unchecked image rectangle
    const IntRect& getUncheckedRect() const { return mUncheckedRect; }
    //! Return checked image rectangle
    const IntRect& getCheckedRect() const { return mCheckedRect; }
    
protected:
    //! Unchecked image rectangle
    IntRect mUncheckedRect;
    //! Checked image rectangle
    IntRect mCheckedRect;
    //! Current checked state
    bool mChecked;
};

#endif // UI_CHECKBOX_H
