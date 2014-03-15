//
// Copyright (c) 2008-2014 the Urho3D project.
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

#include "Object.h"

namespace Urho3D
{

class BorderImage;
class Engine;
class Font;
class LineEdit;
class Text;
class UIElement;
class XMLFile;

/// %Console window with log history and command line prompt.
class URHO3D_API Console : public Object
{
    OBJECT(Console);

public:
    /// Construct.
    Console(Context* context);
    /// Destruct.
    ~Console();

    /// Set UI elements' style from an XML file.
    void SetDefaultStyle(XMLFile* style);
    /// Show or hide. Showing automatically focuses the line edit.
    void SetVisible(bool enable);
    /// Toggle visibility.
    void Toggle();
    /// Automatically set console to visible when receiving an error log message.
    void SetAutoVisibleOnError(bool enable) { autoVisibleOnError_ = enable; }
    /// Set number of displayed rows.
    void SetNumRows(unsigned rows);
    /// Set command history maximum size, 0 disables history.
    void SetNumHistoryRows(unsigned rows);
    /// Update elements to layout properly. Call this after manually adjusting the sub-elements.
    void UpdateElements();

    /// Return the UI style file.
    XMLFile* GetDefaultStyle() const;
    /// Return the background element.
    BorderImage* GetBackground() const { return background_; }
    /// Return the line edit element.
    LineEdit* GetLineEdit() const { return lineEdit_; }
    /// Return whether is visible.
    bool IsVisible() const;
    /// Return true when console is set to automatically visible when receiving an error log message.
    bool IsAutoVisibleOnError() const { return autoVisibleOnError_; }
    /// Return number of displayed rows.
    unsigned GetNumRows() const;
    /// Return history maximum size.
    unsigned GetNumHistoryRows() const { return historyRows_; }
    /// Return current history position.
    unsigned GetHistoryPosition() const { return historyPosition_; }
    /// Return history row at index.
    const String& GetHistoryRow(unsigned index) const;

private:
    /// Handle enter pressed on the line edit.
    void HandleTextFinished(StringHash eventType, VariantMap& eventData);
    /// Handle unhandled key on the line edit for scrolling the history.
    void HandleLineEditKey(StringHash eventType, VariantMap& eventData);
    /// Handle rendering window resize.
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle a log message.
    void HandleLogMessage(StringHash eventType, VariantMap& eventData);
    /// Handle the application post-update.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Auto visible on error flag.
    bool autoVisibleOnError_;
    /// Background.
    SharedPtr<BorderImage> background_;
    /// Container for text rows.
    SharedPtr<UIElement> rowContainer_;
    /// Line edit.
    SharedPtr<LineEdit> lineEdit_;
    /// Command history.
    Vector<String> history_;
    /// Pending log message rows.
    Vector<Pair<int, String> > pendingRows_;
    /// Current row being edited.
    String currentRow_;
    /// Command history maximum rows.
    unsigned historyRows_;
    /// Command history current position.
    unsigned historyPosition_;
    /// Flag when printing messages to prevent endless loop.
    bool printing_;
};

}
