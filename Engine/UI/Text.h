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

#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "UIElement.h"

static const int DEFAULT_FONT_SIZE = 12;

class Font;

//! An UI element that displays text
class Text : public UIElement
{
    DEFINE_TYPE(Text);
    
public:
    //! Construct with initial text and name
    Text(const std::string& text = std::string(), const std::string& name = std::string());
    //! Destruct
    virtual ~Text();
    
    //! Set UI element style from XML data
    virtual void setStyle(const XMLElement& element, ResourceCache* cache);
    //! Return UI rendering batches
    virtual void getBatches(std::vector<UIBatch>& batches, std::vector<UIQuad>& quads, const IntRect& currentScissor);
    
    //! Set font and font size
    bool setFont(Font* font, int size = DEFAULT_FONT_SIZE);
    //! Set maximum row width
    void setMaxWidth(int maxWidth);
    //! Set text
    void setText(const std::string& text);
    //! Set row alignment
    void setTextAlignment(HorizontalAlignment align);
    //! Set row spacing, 1.0 for original font spacing
    void setTextSpacing(float spacing);
    
    //! Return font
    Font* getFont() const { return mFont; }
    //! Return font size
    int getFontSize() const { return mFontSize; }
    //! Return maximum row width
    int getMaxWidth() const { return mMaxWidth; }
    //! Return text
    const std::string& getText() const { return mText; }
    //! Return row alignment
    HorizontalAlignment getTextAlignment() const { return mTextAlignment; }
    //! Return row spacing
    float getTextSpacing() const { return mTextSpacing; }
    //! Return number of rows
    unsigned getNumRows() const { return mRowWidths.size(); }
    //! Return width of each row
    const std::vector<int>& getRowWidths() const { return mRowWidths; }
    //! Return row height
    int getRowHeight() const;
    
protected:
    //! Calculate text size
    void calculateTextSize();
    //! Return row start X position
    int getRowStartPosition(unsigned rowIndex) const;
    
    //! Font
    SharedPtr<Font> mFont;
    //! Font size
    int mFontSize;
    //! Maximum row width
    int mMaxWidth;
    //! Text
    std::string mText;
    //! Text modified into printed form
    std::string mPrintText;
    //! Row alignment
    HorizontalAlignment mTextAlignment;
    //! Row spacing
    float mTextSpacing;
    //! Row widths
    std::vector<int> mRowWidths;
};

#endif // UI_STATICTEXT_H
